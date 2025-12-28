#pragma once

#include "_typedefs.h"

#include "object/object.h"

/* Defines *******************************************************************/

/* Types *********************************************************************/

struct Application;
struct Function;

struct TryCatchFinally {
    struct Object obj;
    struct Object* tryExpr;
    struct Function* catchRules;
    struct Object* finallyExpr;
};

struct OutStream;
struct Vector;

/* Forward declarations ******************************************************/

/* Global variables **********************************************************/

/* Lifecycle functions *******************************************************/

struct TryCatchFinally* tryCatchFinally_new(struct Object* tryExpr, struct Function* catchRules, struct Object* finallyExpr);

/* Public functions **********************************************************/

/* Unique functions ******************/

/* Object functions ******************/

struct Object* tryCatchFinally_close_rec(struct TryCatchFinally* tcf, struct Etor_rec* etor);
bool_t tryCatchFinally_eval_rec(struct TryCatchFinally* tcf, struct Etor_rec* etor, struct Object** value);
void tryCatchFinally_freeVars(struct TryCatchFinally* tcf, struct Vector* freeVars);
void tryCatchFinally_show(struct TryCatchFinally* tcf, struct OutStream* outStream);
