#pragma once

#include "_typedefs.h"

#include "parsers/parsestate.h"

/* Defines *******************************************************************/

/* Types *********************************************************************/

struct Object;
struct Symbol;
struct Vector;

enum ParseStatus {
    PS_Success,
    PS_Fail,
    PS_Error
};

typedef enum ParseStatus (*ParserFunction)(struct ParseState* parseState);

/* Forward declarations ******************************************************/

/* Global variables **********************************************************/

/* Lifecycle functions *******************************************************/

/* Public functions **********************************************************/

enum ParseStatus pError(const string_t message, struct ParseState* parseState);
enum ParseStatus pIgnore(ParserFunction parser, struct ParseState* parseState);
enum ParseStatus pListOf(ParserFunction open, ParserFunction elem, ParserFunction sep, ParserFunction close, struct ParseState* parseState);
enum ParseStatus pOneOf(count_t nParsers, ParserFunction parsers[], struct ParseState* parseState);
enum ParseStatus pSepBy(ParserFunction elem, ParserFunction separator, count_t minElems, struct ParseState* parseState);
enum ParseStatus pSequence(count_t nParsers, ParserFunction parsers[], struct ParseState* parseState);
enum ParseStatus pSpot(struct Symbol* tokenType, struct ParseState* parseState);
#if 0
enum ParseStatus pSpotSpecific(struct Symbol* tokenType, const string_t tokenString, struct ParseState* parseState);
#endif

/* Composable parsers */

enum ParseStatus pStrip(struct ParseState* parseState);

/* Private functions *********************************************************/
