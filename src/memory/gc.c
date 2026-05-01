#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "_typedefs.h"

#include "memory/bumpallocator.h"
#include "memory/bumpallocator_struct.h"
#include "memory/gc.h"
#include "memory/memory.h"
#include "object/object.h"
#include "object/typeids.h"
#include "object/types/application.h"
#include "object/types/array.h"
#include "object/types/binding.h"
#include "object/types/binop.h"
#include "object/types/dec.h"
#include "object/types/function.h"
#include "object/types/hashtable.h"
#include "object/types/ifthen.h"
#include "object/types/inc.h"
#include "object/types/let.h"
#include "object/types/pair.h"
#include "object/types/queue.h"
#include "object/types/quote.h"
#include "object/types/sequence.h"
#include "object/types/subscript.h"
#include "object/types/symbol.h"
#include "object/types/term.h"
#include "object/types/trycatchfinally.h"
#include "object/types/vector.h"
#include "object/types/while.h"

/* Defines *******************************************************************/

/* Types *********************************************************************/

/* Forward declarations ******************************************************/

static struct Object* gc_copy(struct GC* gc, struct Object* obj);
static void gc_scanObject(struct GC* gc, struct Object* obj);

/* Global variables **********************************************************/

/* Lifecycle functions *******************************************************/

struct GC* gc_new(void) {
    struct GC* gc = (struct GC*)malloc(sizeof(*gc));
    gc->fromSpace = g_bumpAllocator;
    gc->toSpace = NULL;
    gc->rootStack = (struct Object**)malloc(DEFAULT_ROOT_STACK_CAPACITY * sizeof(struct Object*));
    gc->rootStackSize = 0;
    gc->rootStackCapacity = DEFAULT_ROOT_STACK_CAPACITY;
    gc->permanentRoots = (struct Object***)malloc(DEFAULT_ROOT_STACK_CAPACITY * sizeof(struct Object**));
    gc->nPermanentRoots = 0;
    gc->permanentRootsCapacity = DEFAULT_ROOT_STACK_CAPACITY;
    gc->gcThreshold = DEFAULT_GC_THRESHOLD;
    gc->allocatedSinceGC = 0;
    return gc;
}

void gc_free(struct GC* gc) {
    free(gc->rootStack);
    free(gc->permanentRoots);
    if (gc->toSpace != NULL) {
        bumpAllocator_free(gc->toSpace);
    }
    free(gc);
}

/* Public functions **********************************************************/

void gc_pushRoot(struct GC* gc, struct Object* obj) {
    if (gc->rootStackSize >= gc->rootStackCapacity) {
        gc->rootStackCapacity *= 2;
        gc->rootStack = (struct Object**)realloc(gc->rootStack, 
            gc->rootStackCapacity * sizeof(struct Object*));
    }
    gc->rootStack[gc->rootStackSize++] = obj;
}

void gc_popRoot(struct GC* gc) {
    if (gc->rootStackSize > 0) {
        gc->rootStackSize--;
    }
}

void gc_popRoots(struct GC* gc, count_t nRoots) {
    if (gc->rootStackSize >= nRoots) {
        gc->rootStackSize -= nRoots;
    }
    else {
        gc->rootStackSize = 0;
    }
}

void gc_setThreshold(struct GC* gc, count_t threshold) {
    gc->gcThreshold = threshold;
}

void gc_recordAllocation(struct GC* gc, count_t nWords) {
    gc->allocatedSinceGC += nWords;
}

void gc_registerPermanentRoot(struct GC* gc, struct Object** rootPtr) {
    if (gc->nPermanentRoots >= gc->permanentRootsCapacity) {
        gc->permanentRootsCapacity *= 2;
        gc->permanentRoots = (struct Object***)realloc(gc->permanentRoots,
            gc->permanentRootsCapacity * sizeof(struct Object**));
    }
    gc->permanentRoots[gc->nPermanentRoots++] = rootPtr;
}

bool_t gc_doGC(struct GC* gc) {
    if (gc->toSpace == NULL) {
        gc->toSpace = bumpAllocator_new(gc->fromSpace->nWordsCapacity);
    }
    else {
        bumpAllocator_init(gc->toSpace, gc->toSpace->nWordsCapacity);
    }
    
    index_t scan = 0;
    
    for (count_t i = 0; i < gc->rootStackSize; i++) {
        if (gc->rootStack[i] != NULL) {
            gc->rootStack[i] = gc_copy(gc, gc->rootStack[i]);
        }
    }
    
    for (count_t i = 0; i < gc->nPermanentRoots; i++) {
        if (gc->permanentRoots[i] != NULL && *gc->permanentRoots[i] != NULL) {
            *gc->permanentRoots[i] = gc_copy(gc, *gc->permanentRoots[i]);
        }
    }
    
    while (scan < gc->toSpace->nextFree) {
        word_t* scanPtr = &gc->toSpace->arena[scan];
        struct Object* obj = (struct Object*)scanPtr;
        gc_scanObject(gc, obj);
        scan += obj->nWords;
    }
    
    struct BumpAllocator* temp = gc->fromSpace;
    gc->fromSpace = gc->toSpace;
    gc->toSpace = temp;
    g_bumpAllocator = gc->fromSpace;
    
    gc->allocatedSinceGC = 0;
    
    count_t liveWords = gc->fromSpace->nextFree;
    count_t capacityWords = gc->fromSpace->nWordsCapacity;
    
    if (liveWords >= capacityWords) {
        return false;
    }
    
    return true;
}

/* Private functions *********************************************************/

static struct Object* gc_copy(struct GC* gc, struct Object* obj) {
    if (obj == NULL) {
        return NULL;
    }
    
    word_t* objWords = (word_t*)obj;
    struct BumpAllocator* from = gc->fromSpace;
    word_t* fromBase = from->arena;
    word_t* fromEnd = fromBase + from->nextFree;
    
    if (objWords < fromBase || objWords >= fromEnd) {
        return obj;
    }
    
    if (obj->typeId == OT_User) {
        address_t newAddr = (address_t)((word_t*)obj + 1);
        return *(struct Object**)newAddr;
    }
    
    address_t newAddr = bumpAllocator_allocate(gc->toSpace, obj->nWords);
    struct Object* newObj = (struct Object*)newAddr;
    memcpy(newObj, obj, obj->nWords * sizeof(word_t));
    
    obj->typeId = OT_User;
    address_t forwardPtr = (address_t)((word_t*)obj + 1);
    *(struct Object**)forwardPtr = newObj;
    
    return newObj;
}

static void gc_scanObject(struct GC* gc, struct Object* obj) {
    if (obj == NULL) {
        return;
    }
    
    switch (obj->typeId) {
        case OT_Application: {
            struct Application* app = (struct Application*)obj;
            app->abstraction = gc_copy(gc, app->abstraction);
            for (count_t i = 0; i < app->nArgs; i++) {
                app->args[i] = gc_copy(gc, app->args[i]);
            }
            break;
        }
        case OT_Array: {
            struct Array* array = (struct Array*)obj;
            for (count_t i = 0; i < array->nElems; i++) {
                array->elems[i] = gc_copy(gc, array->elems[i]);
            }
            break;
        }
        case OT_BinOp: {
            struct BinOp* binOp = (struct BinOp*)obj;
            binOp->lhs = gc_copy(gc, binOp->lhs);
            binOp->oper = gc_copy(gc, binOp->oper);
            binOp->rhs = gc_copy(gc, binOp->rhs);
            binOp->application = (struct Application*)gc_copy(gc, (struct Object*)binOp->application);
            break;
        }
        case OT_Binding: {
            struct Binding* binding = (struct Binding*)obj;
            binding->key = gc_copy(gc, binding->key);
            binding->value = gc_copy(gc, binding->value);
            binding->next = (struct Binding*)gc_copy(gc, (struct Object*)binding->next);
            break;
        }
        case OT_Dec: {
            struct Dec* dec = (struct Dec*)obj;
            dec->expr = gc_copy(gc, dec->expr);
            break;
        }
        case OT_Function: {
            struct Function* func = (struct Function*)obj;
            func->name = (struct Identifier*)gc_copy(gc, (struct Object*)func->name);
            struct FunctionRule* rule = func->rules;
            struct FunctionRule* prevRule = NULL;
            while (rule != NULL) {
                struct FunctionRule* newRule = (struct FunctionRule*)gc_copy(gc, (struct Object*)rule);
                if (prevRule == NULL) {
                    func->rules = newRule;
                }
                else {
                    prevRule->nextRule = newRule;
                }
                newRule->body = gc_copy(gc, newRule->body);
                newRule->closedBody = gc_copy(gc, newRule->closedBody);
                for (count_t i = 0; i < newRule->nParams; i++) {
                    newRule->params[i] = gc_copy(gc, newRule->params[i]);
                }
                prevRule = newRule;
                rule = newRule->nextRule;
            }
            break;
        }
        case OT_HashTable:
        case OT_Set: {
            struct HashTable* ht = (struct HashTable*)obj;
            for (count_t i = 0; i < ht->nBuckets; i++) {
                ht->buckets[i] = (struct Binding*)gc_copy(gc, (struct Object*)ht->buckets[i]);
            }
            break;
        }
        case OT_IfThen: {
            struct IfThen* ifThen = (struct IfThen*)obj;
            ifThen->cond = gc_copy(gc, ifThen->cond);
            ifThen->conseq = gc_copy(gc, ifThen->conseq);
            ifThen->alt = gc_copy(gc, ifThen->alt);
            break;
        }
        case OT_Inc: {
            struct Inc* inc = (struct Inc*)obj;
            inc->expr = gc_copy(gc, inc->expr);
            break;
        }
        case OT_Let: {
            struct Let* let = (struct Let*)obj;
            let->lhs = gc_copy(gc, let->lhs);
            let->rhs = gc_copy(gc, let->rhs);
            break;
        }
        case OT_Pair: {
            struct Pair* pair = (struct Pair*)obj;
            pair->first = gc_copy(gc, pair->first);
            pair->rest = gc_copy(gc, pair->rest);
            break;
        }
        case OT_Queue: {
            struct Queue* queue = (struct Queue*)obj;
            queue->first = (struct Pair*)gc_copy(gc, (struct Object*)queue->first);
            queue->last = (struct Pair*)gc_copy(gc, (struct Object*)queue->last);
            break;
        }
        case OT_Quote: {
            struct Quote* quote = (struct Quote*)obj;
            quote->expr = gc_copy(gc, quote->expr);
            break;
        }
        case OT_Sequence: {
            struct Sequence* seq = (struct Sequence*)obj;
            for (count_t i = 0; i < seq->nExprs; i++) {
                seq->exprs[i] = gc_copy(gc, seq->exprs[i]);
            }
            break;
        }
        case OT_Subscript: {
            struct Subscript* subscript = (struct Subscript*)obj;
            subscript->base = gc_copy(gc, subscript->base);
            subscript->index = gc_copy(gc, subscript->index);
            break;
        }
        case OT_Term: {
            struct Term* term = (struct Term*)obj;
            term->name = (struct Symbol*)gc_copy(gc, (struct Object*)term->name);
            term->attrib = gc_copy(gc, term->attrib);
            for (count_t i = 0; i < term->nArgs; i++) {
                term->args[i] = gc_copy(gc, term->args[i]);
            }
            break;
        }
        case OT_TryCatchFinally: {
            struct TryCatchFinally* tcf = (struct TryCatchFinally*)obj;
            tcf->tryExpr = gc_copy(gc, tcf->tryExpr);
            tcf->catchRules = (struct Function*)gc_copy(gc, (struct Object*)tcf->catchRules);
            tcf->finallyExpr = gc_copy(gc, tcf->finallyExpr);
            break;
        }
        case OT_Vector: {
            struct Vector* vector = (struct Vector*)obj;
            vector->elems = (struct Array*)gc_copy(gc, (struct Object*)vector->elems);
            break;
        }
        case OT_While: {
            struct While* while_ = (struct While*)obj;
            while_->cond = gc_copy(gc, while_->cond);
            while_->body = gc_copy(gc, while_->body);
            break;
        }
        default:
            break;
    }
}
