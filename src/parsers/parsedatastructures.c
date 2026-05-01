#include "_typedefs.h"

#include "object/globals.h"
#include "object/types/array.h"
#include "object/types/binding.h"
#include "object/types/identifier.h"
#include "object/types/pair.h"
#include "object/types/symbol.h"
#include "object/types/term.h"
#include "object/types/vector.h"
#include "parsers/parser.h"
#include "parsers/parseany.h"
#include "parsers/parsedatastructures.h"
#include "parsers/parserprims.h"
#include "parsers/parsespecialchars.h"
#include "parsers/parseoperators.h"
#include "parsers/parsememotable.h"

/* Defines *******************************************************************/

/* Types *********************************************************************/

/* Forward declarations ******************************************************/

/* Global variables **********************************************************/

/* Lifecycle functions *******************************************************/

/* Public functions **********************************************************/

enum ParseResultStatus pArray(struct ParseState* parseState) {
    enum ParseResultStatus parseResult = pListOf(pSpecialOpenBrace, pAny, pSpecialComma, pSpecialCloseBrace, parseState);
    if (parseResult == PRS_Pass) {
        struct Vector* elems = (struct Vector*)parseState->result;
        struct Array* array = array_fromVector(elems);
        parseState->result = (struct Object*)array;
    }
    return parseResult;
}

enum ParseResultStatus pBinding(struct ParseState* parseState) {
    ParserFunction parsers[] = {pAny, pSpecialEqual, pAny};
    parser_addRecursionBarrier(pBinding, parseState);
    enum ParseResultStatus status = pSequence(3, parsers, parseState);
    
    if (status == PRS_Pass) {
        struct Vector* results = (struct Vector*)parseState->result;
        struct Object* key = results->elems->elems[0];
        struct Object* value = results->elems->elems[2];
        struct Binding* binding = binding_new(key, value, g_emptyBinding);
        parseState->result = (struct Object*)binding;
    }
    
    return status;
}

enum ParseResultStatus pHashTable(struct ParseState* parseState) {
    (void)parseState;
    return PRS_Fail;
}

enum ParseResultStatus pPair(struct ParseState* parseState) {
    index_t savedIndex = parseState->index;
    
    if (pSpecialOpenBracket(parseState) != PRS_Pass) {
        parseState->index = savedIndex;
        return PRS_Fail;
    }
    
    struct Vector* elems = vector_new();
    struct Object* tail = (struct Object*)g_emptyPair;
    
    while (true) {
        if (pSpecialCloseBracket(parseState) == PRS_Pass) {
            break;
        }
        
        if (pSpecialPipe(parseState) == PRS_Pass) {
            if (pAny(parseState) != PRS_Pass) {
                parseState->index = savedIndex;
                return PRS_Error;
            }
            tail = parseState->result;
            
            if (pSpecialCloseBracket(parseState) != PRS_Pass) {
                parseState->index = savedIndex;
                return PRS_Error;
            }
            break;
        }
        
        if (pAny(parseState) != PRS_Pass) {
            if (elems->nElems == 0) {
                parseState->index = savedIndex;
                return PRS_Fail;
            } else {
                parseState->index = savedIndex;
                return PRS_Error;
            }
        }
        
        vector_push(elems, parseState->result);
        
        if (pSpecialComma(parseState) != PRS_Pass) {
            continue;
        }
    }
    
    struct Pair* result = (struct Pair*)tail;
    for (index_t i = elems->nElems; i > 0; --i) {
        result = pair_new(elems->elems->elems[i-1], (struct Object*)result);
    }
    
    parseState->result = (struct Object*)result;
    return PRS_Pass;
}

enum ParseResultStatus pQueue(struct ParseState* parseState) {
    (void)parseState;
    return PRS_Fail;
}

enum ParseResultStatus pSet(struct ParseState* parseState) {
    (void)parseState;
    return PRS_Fail;
}

enum ParseResultStatus pTerm(struct ParseState* parseState) {
    index_t savedIndex = parseState->index;
    
    if (pSpot(g_symSymbol, parseState) != PRS_Pass) {
        parseState->index = savedIndex;
        return PRS_Fail;
    }
    
    struct Object* tokenObj = parseState->result;
    if (tokenObj->typeId != OT_Term) {
        parseState->index = savedIndex;
        return PRS_Fail;
    }
    struct Term* token = (struct Term*)tokenObj;
    if (token->nArgs != 1 || token->args[0]->typeId != OT_Symbol) {
        parseState->index = savedIndex;
        return PRS_Fail;
    }
    struct Symbol* name = (struct Symbol*)token->args[0];
    
    enum ParseResultStatus parseResult = pListOf(pSpecialOpenBrace, pAny, pSpecialComma, pSpecialCloseBrace, parseState);
    if (parseResult != PRS_Pass) {
        parseState->index = savedIndex;
        return PRS_Fail;
    }
    
    struct Vector* args = (struct Vector*)parseState->result;
    count_t nArgs = args->nElems;
    struct Object** argElems = args->elems->elems;
    
    struct Term* term = term_new(name, nArgs, argElems, (struct Object*)g_nil);
    parseState->result = (struct Object*)term;
    return PRS_Pass;
}

enum ParseResultStatus pVector(struct ParseState* parseState) {
    (void)parseState;
    return PRS_Fail;
}

/* Private functions *********************************************************/
