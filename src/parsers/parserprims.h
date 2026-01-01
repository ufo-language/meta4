#pragma once

#include "_typedefs.h"

#include "parsers/parser.h"

/* Defines *******************************************************************/

/* Types *********************************************************************/

struct Object;
struct Symbol;
struct Vector;

/* Forward declarations ******************************************************/

/* Global variables **********************************************************/

/* Lifecycle functions *******************************************************/

/* Public functions **********************************************************/

enum ParseResultStatus pDebug(ParserFunction parser, const string_t message, struct ParseState* parseState);
enum ParseResultStatus pEnsure(ParserFunction parser, const string_t message, struct ParseState* parseState);
enum ParseResultStatus pError(const string_t message, struct ParseState* parseState);
enum ParseResultStatus pIgnore(ParserFunction parser, struct ParseState* parseState);
enum ParseResultStatus pListOf(ParserFunction open, ParserFunction elem, ParserFunction sep, ParserFunction close, struct ParseState* parseState);
enum ParseResultStatus pOneOf(count_t nParsers, ParserFunction parsers[], struct ParseState* parseState);
enum ParseResultStatus pSepBy(ParserFunction elem, ParserFunction separator, count_t minElems, struct ParseState* parseState);
enum ParseResultStatus pSequence(count_t nParsers, ParserFunction parsers[], struct ParseState* parseState);
enum ParseResultStatus pSpot(struct Symbol* tokenType, struct ParseState* parseState);

/* Composable parsers */

enum ParseResultStatus pStrip(struct ParseState* parseState);

/* Private functions *********************************************************/
