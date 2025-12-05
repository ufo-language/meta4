#include <stdio.h>

enum ObjectType {
    OT_Null,  /* Should never be used */
    OT_Boolean,
    OT_Device,
    OT_Integer,
    OT_Nil,
    OT_Primitive,
    OT_Real,
    OT_String,
    OT_Symbol,
    OT_Constant_section,  /* Constant typeIds are less than this value */
    /* Containers */
    OT_Array,
    OT_ByteBuffer,
    OT_HashTable,
    OT_IVar,
    OT_List,
    OT_Var,
    /* Expressions */
    OT_Apply,
    OT_BinOp,
    OT_Dec,
    OT_Function,
    OT_Identifier,
    OT_IfThen,
    OT_Inc,
    OT_Let,
    OT_Quote,
    OT_Sequence,
    OT_While,
    /* Other */
    OT_Test,
    OT_Max
};

struct Evaluator {
};

struct Object {
    enum ObjectType typeId;
};

typedef void (*EvalFunction)(struct Object* obj, struct Evaluator* etor);

struct EvalFunction_handler {
    enum ObjectType typeId;
    EvalFunction function;
};

typedef void (*ShowFunction)(struct Object* obj, FILE* stream);
struct ShowFunction_handler {
    enum ObjectType typeId;
    ShowFunction function;
};

/* Foo section */
/* functions */
void foo_eval(struct Object* fooObj, struct Evaluator* etor) { fputs("foo_eval\n", stderr); }
void foo_show(struct Object* fooObj, FILE* stream) { fputs("foo_show\n", stream); }
/* handler structs */
__attribute__((used, section("eval_function")))
static const struct EvalFunction_handler h_foo_eval = {OT_Boolean, foo_eval};
__attribute__((used, section("show_function")))
static const struct ShowFunction_handler h_foo_show = {OT_Boolean, foo_show};

/* Bar section */
/* functions */
void bar_eval(struct Object* fooObj, struct Evaluator* etor) { fputs("bar_eval\n", stderr); }
void bar_show(struct Object* fooObj, FILE* stream) { fputs("bar_show\n", stream); }
/* handler structs */
__attribute__((used, section("eval_function")))
static const struct EvalFunction_handler h_bar_eval = {OT_Nil, bar_eval};
__attribute__((used, section("show_function")))
static const struct ShowFunction_handler h_bar_show = {OT_Nil, bar_show};


extern const struct ShowFunction_handler __start_show_function;
extern const struct ShowFunction_handler __stop_show_function;

extern const struct EvalFunction_handler __start_eval_function;
extern const struct EvalFunction_handler __stop_eval_function;

int main() {
    for (const struct ShowFunction_handler *h = &__start_show_function; h < &__stop_show_function; h++) {
        fprintf(stderr, "calling show function '%u'\n", h->typeId);
        h->function(NULL, stderr);
    }

    for (const struct EvalFunction_handler *h = &__start_eval_function; h < &__stop_eval_function; h++) {
        fprintf(stderr, "calling eval function '%u'\n", h->typeId);
        h->function(NULL, NULL);
    }

}
