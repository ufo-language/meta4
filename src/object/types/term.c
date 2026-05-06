#include <stdio.h>
#include <string.h>

#include "_typedefs.h"

#include "memory/memory.h"
#include "object/errorterm.h"
#include "object/evaluator/etor_rec.h"
#include "object/functions/close_rec.h"
#include "object/functions/eval_rec.h"
#include "object/functions/show.h"
#include "object/globals.h"
#include "object/object.h"
#include "object/types/array.h"
#include "object/types/outstream.h"
#include "object/types/symbol.h"
#include "object/types/term.h"
#include "object/types/vector.h"

/* Defines *******************************************************************/

#define SHOW_ATTRIB false

/* Types *********************************************************************/

/* Forward declarations ******************************************************/

/* Global variables **********************************************************/

/* Lifecycle functions *******************************************************/

/* Public functions **********************************************************/

struct Term* term_new(struct Symbol* name, count_t nArgs, struct Object* args[], struct Object* attrib) {
    struct Term* term = (struct Term*)object_new(OT_Term, NWORDS(*term) + nArgs);
    term->name = name;
    term->nArgs = nArgs;
    memcpy(term->args, args, sizeof(struct Object*) * nArgs);
    term->attrib = attrib;
    return term;
}

struct Term* term_new_1arg(struct Symbol* name, struct Object* arg, struct Object* attrib) {
    struct Object* args[] = {arg};
    return term_new(name, 1, args, attrib);
}

struct Term* term_new_nArgs(struct Symbol* name, count_t nArgs, struct Object* attrib) {
    struct Term* term = (struct Term*)object_new(OT_Term, NWORDS(*term) + nArgs);
    term->name = name;
    term->nArgs = nArgs;
    term->attrib = attrib;
    for (index_t n=0; n<nArgs; n++) {
        term->args[n] = (struct Object*)g_nil;
    }
    return term;
}

/* Unique functions ******************/

/* Object functions ******************/

struct Object* term_close_rec(struct Term* term, struct Etor_rec* etor) {
    count_t nArgs = term->nArgs;
    struct Term* newTerm = (struct Term*)object_new(OT_Term, NWORDS(*term) + nArgs);
    newTerm->name = term->name;
    newTerm->nArgs = nArgs;
    newTerm->attrib = close_rec(term->attrib, etor);
    array_close_rec_usingElems(nArgs, term->args, newTerm->args, etor);
    return (struct Object*)newTerm;
}

bool_t term_equal(struct Term* term, struct Term* other) {
    (void)term;
    (void)other;
    fputs("term_equal is incomplete\n", stderr);
    return false;
}

bool_t term_eval_rec(struct Term* term, struct Etor_rec* etor, struct Object** value) {
    count_t nArgs = term->nArgs;
    struct Term* newTerm = (struct Term*)object_new(OT_Term, NWORDS(*term) + nArgs);
    newTerm->nArgs = nArgs;
    if (!eval_rec((struct Object*)term->name, etor, value)) {
        return false;
    }
    struct Object* newName = *value;
    if (newName->typeId != OT_Symbol) {
        *value = (struct Object*)errorTerm_objAndType("TermError", "Term name must be a symbol", newName);
        return false;
    }
    newTerm->name = (struct Symbol*)newName;
    if (!eval_rec((struct Object*)term->attrib, etor, &term->attrib)) {
        return false;
    }
    term->attrib = *value;
    if (!array_eval_rec_usingElems(nArgs, term->args, newTerm->args, etor, value)) {
        return false;
    }
    *value = (struct Object*)newTerm;
    return true;
}

// void term_freeVars(struct Object* obj, struct Vector* freeVars);
// bool_t term_match(struct Object* obj, struct Object* other, struct Vector* bindings);

void term_show(struct Term* term, struct OutStream* outStream) {
    show((struct Object*)term->name, outStream);
    array_show_usingElems(term->nArgs, term->args, "{", ", ", "}", outStream);
#if SHOW_ATTRIB
    outStream_writeChar(outStream, '%');
    show(term->attrib, outStream);
#endif
}

/* Private functions *********************************************************/
