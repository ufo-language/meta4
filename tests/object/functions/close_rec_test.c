#include "_test.h"
#include "_typedefs.h"

#include "object/evaluator/etor_rec.h"
#include "object/functions/close_rec.h"
#include "object/types/array.h"
#include "object/types/binding.h"
#include "object/types/binop.h"
#include "object/types/boolean.h"
#include "object/types/dec.h"
#include "object/types/function.h"
#include "object/types/identifier.h"
#include "object/types/ifthen.h"
#include "object/types/inc.h"
#include "object/types/integer.h"
#include "object/types/let.h"
#include "object/types/nil.h"
#include "object/types/pair.h"
#include "object/types/quote.h"
#include "object/types/sequence.h"
#include "object/types/string.h"
#include "object/types/subscript.h"
#include "object/types/symbol.h"
#include "object/types/term.h"
#include "object/types/trycatchfinally.h"
#include "object/types/while.h"

int main(int argc, char* argv[]) {
    BEGIN_TESTS

    struct Identifier* x = identifier_new("x");
    struct Identifier* y = identifier_new("y");
    struct Integer* i42 = integer_new(42);
    struct Integer* i100 = integer_new(100);
    struct Symbol* sym = symbol_new("test");

    TEST(close_constants)
        struct Etor_rec* etor = etor_rec_new();
        
        EXPECT_EQ(i42, close_rec(OBJ(i42), etor));
        EXPECT_EQ(g_nil, close_rec(OBJ(g_nil), etor));
        EXPECT_EQ(sym, close_rec(OBJ(sym), etor));
        
        struct Boolean* boolTrue = boolean_new(true);
        EXPECT_EQ(boolTrue, close_rec(OBJ(boolTrue), etor));
        
        struct String* str = string_new("hello");
        EXPECT_EQ(str, close_rec(OBJ(str), etor));
    END

    TEST(close_identifier_unbound)
        struct Etor_rec* etor = etor_rec_new();
        struct Object* result = close_rec(OBJ(x), etor);
        EXPECT_EQ(x, result);
    END

    TEST(close_identifier_bound)
        struct Etor_rec* etor = etor_rec_new();
        etor_rec_bind(etor, x, OBJ(i42));
        struct Object* result = close_rec(OBJ(x), etor);
        EXPECT_EQ(i42, result);
    END

    TEST(close_dec)
        struct Etor_rec* etor = etor_rec_new();
        etor_rec_bind(etor, x, OBJ(i42));
        struct Dec* dec = dec_new(OBJ(x));
        struct Object* result = close_rec(OBJ(dec), etor);
        EXPECT_ISA(OT_Dec, result);
        struct Dec* closedDec = (struct Dec*)result;
        EXPECT_EQ(i42, closedDec->expr);
    END

    TEST(close_inc)
        struct Etor_rec* etor = etor_rec_new();
        etor_rec_bind(etor, x, OBJ(i42));
        struct Inc* inc = inc_new(OBJ(x));
        struct Object* result = close_rec(OBJ(inc), etor);
        EXPECT_ISA(OT_Inc, result);
        struct Inc* closedInc = (struct Inc*)result;
        EXPECT_EQ(i42, closedInc->expr);
    END

    TEST(close_quote)
        struct Etor_rec* etor = etor_rec_new();
        etor_rec_bind(etor, x, OBJ(i42));
        struct Quote* quote = quote_new(OBJ(x));
        struct Object* result = close_rec(OBJ(quote), etor);
        EXPECT_EQ(quote, result);
    END

    TEST(close_pair)
        struct Etor_rec* etor = etor_rec_new();
        etor_rec_bind(etor, x, OBJ(i42));
        etor_rec_bind(etor, y, OBJ(i100));
        struct Pair* pair = pair_new(OBJ(x), OBJ(y));
        struct Object* result = close_rec(OBJ(pair), etor);
        EXPECT_ISA(OT_Pair, result);
        struct Pair* closedPair = (struct Pair*)result;
        EXPECT_EQ(i42, closedPair->first);
        EXPECT_EQ(i100, closedPair->rest);
    END

    TEST(close_array)
        struct Etor_rec* etor = etor_rec_new();
        etor_rec_bind(etor, x, OBJ(i42));
        etor_rec_bind(etor, y, OBJ(i100));
        count_t nElems = 2;
        struct Object* elems[] = {OBJ(x), OBJ(y)};
        struct Array* array = array_new_withElems(nElems, elems);
        struct Object* result = close_rec(OBJ(array), etor);
        EXPECT_ISA(OT_Array, result);
        struct Array* closedArray = (struct Array*)result;
        EXPECT_EQ(i42, closedArray->elems[0]);
        EXPECT_EQ(i100, closedArray->elems[1]);
    END

    TEST(close_sequence)
        struct Etor_rec* etor = etor_rec_new();
        struct Identifier* z = identifier_new("z");
        count_t nExprs = 2;
        struct Object* exprs[] = {OBJ(x), OBJ(z)};
        struct Sequence* seq = sequence_new(nExprs, exprs);
        struct Object* result = close_rec(OBJ(seq), etor);
        EXPECT_ISA(OT_Sequence, result);
    END

    TEST(close_binding)
        struct Etor_rec* etor = etor_rec_new();
        etor_rec_bind(etor, x, OBJ(i42));
        struct Binding* binding = binding_new(OBJ(sym), OBJ(x), g_emptyBinding);
        struct Object* result = close_rec(OBJ(binding), etor);
        EXPECT_ISA(OT_Binding, result);
        struct Binding* closedBinding = (struct Binding*)result;
        EXPECT_EQ(sym, closedBinding->key);
        EXPECT_EQ(i42, closedBinding->value);
    END

    TEST(close_binop)
        struct Etor_rec* etor = etor_rec_new();
        etor_rec_bind(etor, x, OBJ(i42));
        etor_rec_bind(etor, y, OBJ(i100));
        struct Identifier* plus = identifier_new("+");
        struct BinOp* binop = binOp_new(OBJ(x), OBJ(plus), OBJ(y));
        struct Object* result = close_rec(OBJ(binop), etor);
        EXPECT_ISA(OT_BinOp, result);
    END

    TEST(close_term)
        struct Etor_rec* etor = etor_rec_new();
        etor_rec_bind(etor, x, OBJ(i42));
        etor_rec_bind(etor, y, OBJ(i100));
        count_t nArgs = 2;
        struct Object* args[] = {OBJ(x), OBJ(y)};
        struct Term* term = term_new(sym, nArgs, args, OBJ(g_nil));
        struct Object* result = close_rec(OBJ(term), etor);
        EXPECT_ISA(OT_Term, result);
        struct Term* closedTerm = (struct Term*)result;
        EXPECT_EQ(sym, closedTerm->name);
        EXPECT_EQ(i42, closedTerm->args[0]);
        EXPECT_EQ(i100, closedTerm->args[1]);
    END

    TEST(close_function)
        struct Etor_rec* etor = etor_rec_new();
        etor_rec_bind(etor, y, OBJ(i100));
        struct Identifier* f = identifier_new("f");
        struct Function* function = function_new(f);
        count_t nParams = 1;
        struct Object* params[] = {OBJ(x)};
        struct Object* body = OBJ(y);
        function_addlRule(function, nParams, params, body);
        struct Object* result = close_rec(OBJ(function), etor);
        EXPECT_ISA(OT_Function, result);
        struct Function* closedFunc = (struct Function*)result;
        EXPECT_EQ(i100, closedFunc->rules->closedBody);
    END

    TEST(close_let)
        struct Etor_rec* etor = etor_rec_new();
        etor_rec_bind(etor, y, OBJ(i100));
        struct Binding* binding = binding_new(OBJ(sym), OBJ(y), g_emptyBinding);
        struct Let* let = let_new(OBJ(binding), OBJ(x));
        struct Object* result = close_rec(OBJ(let), etor);
        EXPECT_ISA(OT_Let, result);
    END

    TEST(close_ifthen)
        struct Etor_rec* etor = etor_rec_new();
        etor_rec_bind(etor, x, OBJ(i42));
        struct Boolean* condition = boolean_new(true);
        struct IfThen* ifthen = ifThen_new(OBJ(condition), OBJ(x), OBJ(g_nil));
        struct Object* result = close_rec(OBJ(ifthen), etor);
        EXPECT_ISA(OT_IfThen, result);
    END

    TEST(close_while)
        struct Etor_rec* etor = etor_rec_new();
        etor_rec_bind(etor, x, OBJ(i42));
        struct Boolean* condition = boolean_new(true);
        struct While* whileLoop = while_new(OBJ(condition), OBJ(x));
        struct Object* result = close_rec(OBJ(whileLoop), etor);
        EXPECT_ISA(OT_While, result);
    END

    TEST(close_subscript)
        struct Etor_rec* etor = etor_rec_new();
        etor_rec_bind(etor, x, OBJ(i42));
        etor_rec_bind(etor, y, OBJ(i100));
        struct Subscript* subscript = subscript_new(OBJ(x), OBJ(y));
        struct Object* result = close_rec(OBJ(subscript), etor);
        EXPECT_ISA(OT_Subscript, result);
    END

    TEST(close_trycatchfinally)
        MESSAGE("Skipping TryCatchFinally test - close_rec not yet implemented for this type");
    END

    END_TESTS
}
