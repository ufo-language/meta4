#pragma once

#include "_typedefs.h"

/* Defines *******************************************************************/

/* Types *********************************************************************/

enum TypeId {
    OT_Null,  /* Should never be used */
    OT_Boolean,
    OT_InStream,
    OT_Integer,
    OT_Nil,
    OT_OutStream,
    OT_Primitive,
    OT_Real,
    OT_String,
    OT_Symbol,
    OT_ConstantLimit,  /* Constant typeIds are less than this value */
    /* Containers */
    OT_Array,
    OT_Binding,
    OT_ByteBuffer,
    OT_HashTable,
    OT_IntArray,
    OT_IntVector,
    OT_IntVar,
    OT_Pair,
    OT_Queue,
    OT_Set,
    OT_Term,
    OT_Vector,
    OT_Var,
    /* Expressions */
    OT_Application,
    OT_BinOp,
    OT_Dec,
    OT_Function,
    OT_Identifier,
    OT_IfThen,
    OT_Inc,
    OT_Let,
    OT_Quote,
    OT_Sequence,
    OT_Subscript,
    OT_TryCatchFinally,
    OT_While,
    /* Other */
    OT_Etor_Rec,
    OT_Etor_CPS,
    OT_Continuation,
    OT_User,
    OT_Test,
    OT_Any,
    OT_Max
};

/* Forward declarations ******************************************************/

/* Global variables **********************************************************/

/* Lifecycle functions *******************************************************/

/* Public functions **********************************************************/

string_t typeName(enum TypeId typeId);
