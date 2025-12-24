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

struct Term* errorTerm0(const string_t name, const string_t message);
struct Term* errorTerm1(const string_t name, const string_t message, struct Object* arg);

/* Object functions ******************/
