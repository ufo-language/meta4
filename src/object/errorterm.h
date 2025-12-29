#pragma once

#include "_typedefs.h"

/* Defines *******************************************************************/

/* Types *********************************************************************/

struct Object;

/* Forward declarations ******************************************************/

/* Global variables **********************************************************/

/* Lifecycle functions *******************************************************/

/* Public functions **********************************************************/

/* Unique functions ******************/

struct Term* errorTerm(const string_t name, const string_t message, count_t nArgs, ...);
struct Term* errorTerm0(const string_t name, const string_t message);
struct Term* errorTerm1(const string_t name, const string_t message, struct Object* arg);
struct Term* errorTerm_objAndType(const string_t name, const string_t message, struct Object* arg);

/* Object functions ******************/
