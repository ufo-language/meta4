#pragma once

#include "_typedefs.h"

#include "parsers/parser.h"

/* Defines *******************************************************************/

/* Types *********************************************************************/

/* Forward declarations ******************************************************/

/* Global variables **********************************************************/

/* Lifecycle functions *******************************************************/

/* Public functions **********************************************************/

enum ParseResultStatus pApply(struct ParseState* parseState);
enum ParseResultStatus pAsync(struct ParseState* parseState);
enum ParseResultStatus pBinOp(struct ParseState* parseState);
enum ParseResultStatus pCobegin(struct ParseState* parseState);
enum ParseResultStatus pFunction(struct ParseState* parseState);
enum ParseResultStatus pIfThen(struct ParseState* parseState);
enum ParseResultStatus pLet(struct ParseState* parseState);
enum ParseResultStatus pMacro(struct ParseState* parseState);
enum ParseResultStatus pMatch(struct ParseState* parseState);
enum ParseResultStatus pNondet(struct ParseState* parseState);
enum ParseResultStatus pQuote(struct ParseState* parseState);
enum ParseResultStatus pSeq(struct ParseState* parseState);
enum ParseResultStatus pSubscript(struct ParseState* parseState);
enum ParseResultStatus pTryCatchFinally(struct ParseState* parseState);
enum ParseResultStatus pWhile(struct ParseState* parseState);
