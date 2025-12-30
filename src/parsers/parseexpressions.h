#pragma once

#include "_typedefs.h"

#include "parsers/parser.h"

/* Defines *******************************************************************/

/* Types *********************************************************************/

/* Forward declarations ******************************************************/

/* Global variables **********************************************************/

/* Lifecycle functions *******************************************************/

/* Public functions **********************************************************/

enum ParseStatus pApply(struct ParseState* parseState);
enum ParseStatus pAsync(struct ParseState* parseState);
enum ParseStatus pBinOp(struct ParseState* parseState);
enum ParseStatus pCobegin(struct ParseState* parseState);
enum ParseStatus pFunction(struct ParseState* parseState);
enum ParseStatus pIfThen(struct ParseState* parseState);
enum ParseStatus pLet(struct ParseState* parseState);
enum ParseStatus pMacro(struct ParseState* parseState);
enum ParseStatus pMatch(struct ParseState* parseState);
enum ParseStatus pNondet(struct ParseState* parseState);
enum ParseStatus pQuote(struct ParseState* parseState);
enum ParseStatus pSeq(struct ParseState* parseState);
enum ParseStatus pSubscript(struct ParseState* parseState);
enum ParseStatus pTryCatchFinally(struct ParseState* parseState);
enum ParseStatus pWhile(struct ParseState* parseState);
