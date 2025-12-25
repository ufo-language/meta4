#pragma once

#include "_typedefs.h"

#include "object/object.h"

/* Defines *******************************************************************/

/* Types *********************************************************************/

struct Application;

struct BinOp {
    struct Object obj;
    struct Object* lhs;
    struct Object* oper;
    struct Object* rhs;
    struct Application* application;
};

struct Etor_rec;
struct OutStream;

/* Forward declarations ******************************************************/

/* Global variables **********************************************************/

/* Lifecycle functions *******************************************************/

struct BinOp* binOp_new(struct Object* lhs, struct Object* oper, struct Object* rhs);

/* Public functions **********************************************************/

/* Unique functions ******************/

/* Object functions ******************/

struct Object* binOp_close_rec(struct BinOp* binOp, struct Etor_rec* etor);
bool_t binOp_eval_rec(struct BinOp* binOp, struct Etor_rec* etor, struct Object** value);
void binOp_show(struct BinOp* binOp, struct OutStream* outStream);
