#include <stdio.h>
#include <stdlib.h>

#include "_typedefs.h"

#include "lexer/lexer.h"
#include "lexer/syntax.h"
#include "memory/memory.h"
#include "object/evaluator/etor_rec.h"
#include "object/functions/show.h"
#include "object/globals.h"
#include "object/primitives/defineprims.h"
#include "object/typeids.h"
#include "object/types/outstream.h"
#include "parsers/parseany.h"
#include "parsers/parser.h"
#include "meta4.h"


/* Defines ------------------------------------------------------------------*/

/* Types --------------------------------------------------------------------*/

enum {
    N_10   =         10,
    N_100K =     100000,
    N_1M   =    1000000,
    N_10M  =   10000000,
    N_100M =  100000000,
    N_1B   = 1000000000,
    N      = N_100M
};

/* Forward declarations -----------------------------------------------------*/

void _program1(void);
void _repl(void);

/* Global variables ---------------------------------------------------------*/

/* Lifecycle functions ------------------------------------------------------*/

void meta4_startup(void) {
    memory_init(DEFAULT_HEAP_SIZE);
    globals_init();
    definePrims_init(g_globalEnv);
}

void meta4_shutdown(void) {
    globals_free();
    memory_free();
}

/* Public functions ---------------------------------------------------------*/

int meta4_main(void) {
    meta4_startup();
    _repl();
    meta4_shutdown();
    return 0;
}

/* Private functions --------------------------------------------------------*/

#include "object/types/dec.h"
#include "object/types/intvar.h"
#include "object/types/while.h"

void _program1(void) {
    struct IntVar* intVar = intVar_new(N);
    struct Dec* dec = dec_new((struct Object*)intVar);
    struct While* while_ = while_new((struct Object*)intVar, (struct Object*)dec);
    struct Etor_rec* etor = etor_rec_new();
    struct Object* value = (struct Object*)g_nil;
    if (!etor_rec_run(etor, (struct Object*)while_, &value)) {
        outStream_fwriteLn(g_stderr,
            'S', "main _program1 error ",
            'O', value,
            0);
    }
    else {
        outStream_fwriteLn(g_stderr,
            'S', "main _program1 final value = ",
            'O', value,
            0);
    }
}

void _repl(void) {
    char line[1024];
    struct Etor_rec* etor = etor_rec_new();
    struct Vector* tokens = NULL;
    struct ParseState parseState;
    
    while (1) {
        printf("Meta4> ");
        fflush(stdout);
        
        if (fgets(line, sizeof(line), stdin) == NULL) {
            printf("\n");
            break;
        }
        
        tokens = lexer_lexAll(syntax, line);
        
        parseState_init(&parseState, tokens);
        enum ParseResultStatus parseResult = parse(pAnyOrBinding, &parseState);
        
        if (parseResult == PRS_Pass) {
            struct Object* value = (struct Object*)g_nil;
            bool_t evalSuccess = etor_rec_run(etor, parseState.result, &value);
            
            if (evalSuccess) {
                if (value != (struct Object*)g_nil) {
                    show(value, g_stdout);
                    printf(" :: %s\n", typeName(value->typeId));
                }
            } else {
                if (value != NULL && value != (struct Object*)g_nil) {
                    show(value, g_stderr);
                    outStream_nl(g_stderr);
                } else {
                    fprintf(stderr, "Evaluation error\n");
                }
            }
        } else if (parseResult == PRS_Error) {
            if (parseState.result != NULL && parseState.result != g_uniqueObject) {
                show(parseState.result, g_stderr);
                outStream_nl(g_stderr);
            }
        }
    }
}
