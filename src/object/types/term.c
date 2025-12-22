#include <stdio.h>
#include <string.h>

#include "_typedefs.h"

#include "memory/memory.h"
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

/* Types *********************************************************************/

/* for reference
struct Term {
    struct Object obj;
    struct Symbol* name;
    struct Object* attrib;
    count_t nArgs;
    struct Object* args[];
};
*/

/* Forward declarations ******************************************************/

/* Global variables **********************************************************/

/* Lifecycle functions *******************************************************/

/* Public functions **********************************************************/

// struct Term* term_new(struct Symbol* name, struct Object* attrib, count_t nArgs, struct Object* args[]) {
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

/* Unique functions ******************/

/* Object functions ******************/

bool_t term_close(struct Term* term, struct Etor_rec* etor, struct Object** value) {
    /* TODO Change the array_close function. Add array_closeElems, and then call that
       function from this one.
    */
    (void)term;
    (void)etor;
    (void)value;
    return false;
}

bool_t term_equal(struct Term* term, struct Term* other);

bool_t term_eval_rec(struct Term* term, struct Etor_rec* etor, struct Object** value) {
    count_t nArgs = term->nArgs;
    struct Term* newTerm = (struct Term*)object_new(OT_Term, NWORDS(*term) + nArgs);
    newTerm->nArgs = nArgs;
    struct Object* newName;
    if (!eval_rec((struct Object*)term->name, etor, &newName)) {
        return false;
    }
    if (newName->typeId != OT_Symbol) {
        outStream_fwriteLn(g_stderr,
            'S', "ERROR: Term name must be a symbol: ",
            'O', newName,
            'S', " :: ",
            'S', typeName(newName->typeId),
            0);
        return false;
    }
    newTerm->name = (struct Symbol*)newName;
    if (!eval_rec((struct Object*)term->attrib, etor, &term->attrib)) {
        return false;
    }
    if (!array_evalElems_rec(nArgs, term->args, newTerm->args, etor, value)) {
        return false;
    }
    *value = (struct Object*)newTerm;
    return true;
}

void term_freeVars(struct Object* obj, struct Vector* freeVars);
bool_t term_match(struct Object* obj, struct Object* other, struct Vector* bindings);

void term_show(struct Term* term, struct OutStream* outStream) {
    show((struct Object*)term->name, outStream);
    array_showElems(term->nArgs, term->args, "{", ", ", "}", outStream);
    outStream_writeChar(outStream, '%');
    show(term->attrib, outStream);
}

/* Private functions *********************************************************/
