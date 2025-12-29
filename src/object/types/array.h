#pragma once

#include "_typedefs.h"

#include "object/functions/compare.h"
#include "object/object.h"
#include "object/types/subscript.h"

/* Defines *******************************************************************/

/* Types *********************************************************************/

struct Array {
    struct Object obj;
    count_t nElems;
    struct Object* elems[];
};

struct Etor_rec;
struct OutStream;
struct Vector;

/* Forward declarations ******************************************************/

/* Global variables **********************************************************/

/* Lifecycle functions *******************************************************/

struct Array* array_new_withElem(count_t nElems, struct Object* elem);
struct Array* array_new_withElems(count_t nElems, struct Object* elems[]);
struct Array* array_new_noFill(count_t nElems);
void array_init(struct Array* array, count_t nElems, struct Object* elems[]);

/* Public functions **********************************************************/

/* Unique functions ******************/

enum SubscriptResult array_get(struct Array* array, struct Object* indexObj, struct Object** value);
enum SubscriptResult array_get_index_t(struct Array* array, index_t index, struct Object** value);
enum SubscriptResult array_set(struct Array* array, struct Object* indexObj, struct Object* value);
enum SubscriptResult array_set_index_t(struct Array* array, index_t index, struct Object* value);

/* Element/array-wise operations; also used by other types */
void array_close_rec_usingElems(count_t nElems, struct Object* elems[], struct Object* newElems[], struct Etor_rec* etor);
bool_t array_eval_rec_usingElems(count_t nElems, struct Object* elems[], struct Object* newElems[], struct Etor_rec* etor, struct Object** error);
bool_t array_locate_usingElems(count_t nElems, struct Object* elems[], struct Object* key, int_t* index);
bool_t array_lookup_usingElems(count_t nElems, struct Object* elems[], struct Object* key, struct Object** value);
bool_t array_match_usingElems(count_t nElems, struct Object* elems[], struct Object* otherElems[], struct Vector* bindings);
void array_show_usingElems(count_t nElems, struct Object* elems[], const string_t open, const string_t sep, const string_t close, struct OutStream* outStream);
void array_showBindings(count_t nElems, struct Object* elems[], const string_t open, const string_t sep, const string_t close, struct OutStream* outStream);

/* Object functions ******************/

struct Object* array_close_rec(struct Array* array, struct Etor_rec* etor);
enum CompareResult array_compare(struct Array* array, struct Array* otherArray);
bool_t array_eval_rec(struct Array* array, struct Etor_rec* etor, struct Object** value);
bool_t array_match(struct Array* array, struct Array* other, struct Vector* bindings);
void array_show(struct Array* array, struct OutStream* outStream);
