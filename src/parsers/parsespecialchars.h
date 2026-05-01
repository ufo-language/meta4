#pragma once

#include "_typedefs.h"

#include "parsers/parserprims.h"

/* Defines *******************************************************************/

/* Types *********************************************************************/

struct ParseState;

/* Forward declarations ******************************************************/

/* Global variables **********************************************************/

/* Lifecycle functions *******************************************************/

/* Public functions **********************************************************/

enum ParseResultStatus pSpecialOpenBrace(struct ParseState* parseState);
enum ParseResultStatus pSpecialCloseBrace(struct ParseState* parseState);
enum ParseResultStatus pSpecialOpenBracket(struct ParseState* parseState);
enum ParseResultStatus pSpecialCloseBracket(struct ParseState* parseState);
enum ParseResultStatus pSpecialOpenParen(struct ParseState* parseState);
enum ParseResultStatus pSpecialCloseParen(struct ParseState* parseState);
enum ParseResultStatus pSpecialComma(struct ParseState* parseState);
enum ParseResultStatus pSpecialSemicolon(struct ParseState* parseState);
enum ParseResultStatus pSpecialEqual(struct ParseState* parseState);
enum ParseResultStatus pSpecialPipe(struct ParseState* parseState);

/* Private functions *********************************************************/
