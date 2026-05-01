#include "_typedefs.h"

#include "parsers/parseexpressions.h"
#include "parsers/parseany.h"
#include "parsers/parseliterals.h"
#include "parsers/parsespecialchars.h"
#include "parsers/parserprims.h"
#include "parsers/parsememotable.h"
#include "parsers/parsereservedwords.h"
#include "object/types/application.h"
#include "object/types/function.h"
#include "object/types/identifier.h"
#include "object/types/vector.h"
#include "object/globals.h"

/* Defines *******************************************************************/

/* Types *********************************************************************/

/* Forward declarations ******************************************************/

/* Global variables **********************************************************/

/* Lifecycle functions *******************************************************/

/* Public functions **********************************************************/

enum ParseResultStatus pApply(struct ParseState* parseState) {
    parser_addRecursionBarrier(pApply, parseState);
    index_t savedIndex = parseState->index;
    
    struct Object* abstraction = NULL;
    
    if (pSpecialOpenParen(parseState) == PRS_Pass) {
        if (pAny(parseState) != PRS_Pass) {
            parseState->index = savedIndex;
            return PRS_Fail;
        }
        abstraction = parseState->result;
        
        if (pSpecialCloseParen(parseState) != PRS_Pass) {
            parseState->index = savedIndex;
            return PRS_Fail;
        }
    }
    else if (pIdentifier(parseState) == PRS_Pass) {
        pStrip(parseState);
        abstraction = parseState->result;
    }
    else {
        parseState->index = savedIndex;
        return PRS_Fail;
    }
    
    enum ParseResultStatus parseResult = pListOf(pSpecialOpenParen, pAny, pSpecialComma, pSpecialCloseParen, parseState);
    if (parseResult != PRS_Pass) {
        parseState->index = savedIndex;
        return PRS_Fail;
    }
    
    struct Vector* argsVector = (struct Vector*)parseState->result;
    struct Application* app = application_new(abstraction, argsVector->nElems, argsVector->elems->elems);
    parseState->result = (struct Object*)app;
    return PRS_Pass;
}

enum ParseResultStatus pAsync(struct ParseState* parseState) {
    (void)parseState;
    return PRS_Fail;
}

enum ParseResultStatus pBinOp(struct ParseState* parseState) {
    (void)parseState;
    return PRS_Fail;
}

enum ParseResultStatus pCobegin(struct ParseState* parseState) {
    (void)parseState;
    return PRS_Fail;
}

enum ParseResultStatus pFunction(struct ParseState* parseState) {
    index_t savedIndex = parseState->index;
    
    if (pSpotReserved("fun", parseState) != PRS_Pass) {
        parseState->index = savedIndex;
        return PRS_Fail;
    }
    
    pStrip(parseState);
    
    struct Identifier* name = g_idNil;
    if (pIdentifier(parseState) == PRS_Pass) {
        pStrip(parseState);
        name = (struct Identifier*)parseState->result;
    }
    
    struct Function* function = function_new(name);
    
    while (true) {
        if (pSpecialOpenParen(parseState) != PRS_Pass) {
            parseState->index = savedIndex;
            return PRS_Fail;
        }
        
        struct Vector* params = vector_new();
        if (pSpecialCloseParen(parseState) != PRS_Pass) {
            while (true) {
                if (pAny(parseState) != PRS_Pass) {
                    parseState->index = savedIndex;
                    return PRS_Fail;
                }
                vector_push(params, parseState->result);
                
                if (pSpecialComma(parseState) != PRS_Pass) {
                    break;
                }
            }
            
            if (pSpecialCloseParen(parseState) != PRS_Pass) {
                parseState->index = savedIndex;
                return PRS_Fail;
            }
        }
        
        pStrip(parseState);
        
        if (pSpecialEqual(parseState) != PRS_Pass) {
            parseState->index = savedIndex;
            return PRS_Fail;
        }
        
        pStrip(parseState);
        
        if (pAny(parseState) != PRS_Pass) {
            parseState->index = savedIndex;
            return PRS_Fail;
        }
        
        struct Object* body = parseState->result;
        
        function_addlRule(function, params->nElems, params->elems->elems, body);
        
        pStrip(parseState);
        
        if (pSpecialPipe(parseState) != PRS_Pass) {
            break;
        }
        
        pStrip(parseState);
    }
    
    parseState->result = (struct Object*)function;
    return PRS_Pass;
}

enum ParseResultStatus pIfThen(struct ParseState* parseState) {
    (void)parseState;
    return PRS_Fail;
}

enum ParseResultStatus pLet(struct ParseState* parseState) {
    (void)parseState;
    return PRS_Fail;
}

enum ParseResultStatus pMacro(struct ParseState* parseState) {
    (void)parseState;
    return PRS_Fail;
}

enum ParseResultStatus pMatch(struct ParseState* parseState) {
    (void)parseState;
    return PRS_Fail;
}

enum ParseResultStatus pNondet(struct ParseState* parseState) {
    (void)parseState;
    return PRS_Fail;
}

enum ParseResultStatus pQuote(struct ParseState* parseState) {
    (void)parseState;
    return PRS_Fail;
}

enum ParseResultStatus pSeq(struct ParseState* parseState) {
    (void)parseState;
    return PRS_Fail;
}

enum ParseResultStatus pSubscript(struct ParseState* parseState) {
    (void)parseState;
    return PRS_Fail;
}

enum ParseResultStatus pTryCatchFinally(struct ParseState* parseState) {
    (void)parseState;
    return PRS_Fail;
}

enum ParseResultStatus pWhile(struct ParseState* parseState) {
    (void)parseState;
    return PRS_Fail;
}


/* Private functions *********************************************************/
