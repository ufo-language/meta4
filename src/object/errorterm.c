#include <stdarg.h>

#include "_typedefs.h"

#include "object/errorterm.h"
#include "object/globals.h"
#include "object/types/binding.h"
#include "object/types/string.h"
#include "object/types/symbol.h"
#include "object/types/term.h"
#include "object/types/vector.h"

/* Defines *******************************************************************/

/* Types *********************************************************************/

/* Forward declarations ******************************************************/

/* Global variables **********************************************************/

/* Lifecycle functions *******************************************************/

/* Public functions **********************************************************/

/* Unique functions ******************/

struct Term* errorTerm(const string_t name, const string_t message, count_t nArgs, ...) {
    count_t nTermArgs = nArgs + 1;
    struct Term* et = term_new_nArgs(symbol_new(name), nTermArgs, (struct Object*)g_nil);
    struct Object** termArgs = et->args;
    index_t termArgIndex = 0;
    termArgs[termArgIndex++] = (struct Object*)string_new(message);
    va_list args;
    va_start(args, nArgs);
    for (count_t n=0; n<nArgs; n++) {
        string_t bindingName = va_arg(args, string_t);
        struct Object* bindingValue = va_arg(args, struct Object*);
        struct Binding* binding = binding_new((struct Object*)symbol_new(bindingName), bindingValue, g_emptyBinding);
        termArgs[termArgIndex++] = (struct Object*)binding;
    }
    va_end(args);
    return et;
}

struct Term* errorTerm0(const string_t name, const string_t message) {
    count_t nArgs = 1;
    struct Object* args[] = {(struct Object*)string_new(message)};
    return term_new(symbol_new(name), nArgs, args, (struct Object*)g_nil);
}

struct Term* errorTerm1(const string_t name, const string_t message, struct Object* arg) {
    count_t nArgs = 2;
    struct Object* args[] = {(struct Object*)string_new(message), arg};
    return term_new(symbol_new(name), nArgs, args, (struct Object*)g_nil);
}

struct Term* errorTerm_objAndType(const string_t name, const string_t message, struct Object* arg) {
    return errorTerm(name, message, 2,
        "Object", arg,
        "Type", typeSymbol(arg->typeId)
    );
}

/* Object functions ******************/

/* Private functions *********************************************************/
