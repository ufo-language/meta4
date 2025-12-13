#pragma once

/* Defines *******************************************************************/

/* Types *********************************************************************/

enum {
    C_OTHER = 0,
    C_ALPHA,
    C_DIGIT,
    C_WS,
    C_OPER
};

/* Forward declarations ******************************************************/

/* Global variables **********************************************************/

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Winitializer-overrides"
#pragma clang diagnostic ignored "-Wgnu-designator"
/* This warning is disabled because the charClassTable defines values twice:
   Once with the '[0 ... 255] = C_OTHER' clause, and then below that it
   re-defines specific values.
*/

int charType[256] = {
    [0 ... 255] = C_OTHER,

    /* whitespace */
    [' ']  = C_WS,
    ['\t'] = C_WS,
    ['\n'] = C_WS,
    ['\r'] = C_WS,
    ['\f'] = C_WS,
    ['\v'] = C_WS,

    /* digits */
    ['0'] = C_DIGIT, ['1'] = C_DIGIT, ['2'] = C_DIGIT, ['3'] = C_DIGIT,
    ['4'] = C_DIGIT, ['5'] = C_DIGIT, ['6'] = C_DIGIT, ['7'] = C_DIGIT,
    ['8'] = C_DIGIT, ['9'] = C_DIGIT,

    /* uppercase alpha */
    ['A'] = C_ALPHA, ['B'] = C_ALPHA, ['C'] = C_ALPHA, ['D'] = C_ALPHA,
    ['E'] = C_ALPHA, ['F'] = C_ALPHA, ['G'] = C_ALPHA, ['H'] = C_ALPHA,
    ['I'] = C_ALPHA, ['J'] = C_ALPHA, ['K'] = C_ALPHA, ['L'] = C_ALPHA,
    ['M'] = C_ALPHA, ['N'] = C_ALPHA, ['O'] = C_ALPHA, ['P'] = C_ALPHA,
    ['Q'] = C_ALPHA, ['R'] = C_ALPHA, ['S'] = C_ALPHA, ['T'] = C_ALPHA,
    ['U'] = C_ALPHA, ['V'] = C_ALPHA, ['W'] = C_ALPHA, ['X'] = C_ALPHA,
    ['Y'] = C_ALPHA, ['Z'] = C_ALPHA,

    /* lowercase alpha */
    ['a'] = C_ALPHA, ['b'] = C_ALPHA, ['c'] = C_ALPHA, ['d'] = C_ALPHA,
    ['e'] = C_ALPHA, ['f'] = C_ALPHA, ['g'] = C_ALPHA, ['h'] = C_ALPHA,
    ['i'] = C_ALPHA, ['j'] = C_ALPHA, ['k'] = C_ALPHA, ['l'] = C_ALPHA,
    ['m'] = C_ALPHA, ['n'] = C_ALPHA, ['o'] = C_ALPHA, ['p'] = C_ALPHA,
    ['q'] = C_ALPHA, ['r'] = C_ALPHA, ['s'] = C_ALPHA, ['t'] = C_ALPHA,
    ['u'] = C_ALPHA, ['v'] = C_ALPHA, ['w'] = C_ALPHA, ['x'] = C_ALPHA,
    ['y'] = C_ALPHA, ['z'] = C_ALPHA,

    /* operators */
    ['!'] = C_OPER, ['#'] = C_OPER, ['$'] = C_OPER,
    ['%'] = C_OPER, ['&'] = C_OPER,
    ['*'] = C_OPER, ['+'] = C_OPER, [','] = C_OPER,
    ['-'] = C_OPER, ['.'] = C_OPER, ['/'] = C_OPER, [':'] = C_OPER,
    ['<'] = C_OPER, ['='] = C_OPER, ['>'] = C_OPER,
    ['?'] = C_OPER, ['@'] = C_OPER,
    ['^'] = C_OPER, ['_'] = C_OPER,
    ['|'] = C_OPER, ['~'] = C_OPER,
};
#pragma clang diagnostic pop

/* Lifecycle functions *******************************************************/

/* Public functions **********************************************************/

/* Unique functions ******************/

/* Object functions ******************/

/* Private functions *********************************************************/
