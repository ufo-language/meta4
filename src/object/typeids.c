#include <stdio.h>

#include "_typedefs.h"

#include "object/typeids.h"

/* Defines *******************************************************************/

/* Types *********************************************************************/

/* Forward declarations ******************************************************/

/* Global variables **********************************************************/

/* Lifecycle functions *******************************************************/

/* Public functions **********************************************************/

string_t typeName(enum TypeId typeId) {
    switch (typeId) {
        case OT_Any:             return "Any";
        case OT_Application:     return "Application";
        case OT_Array:           return "Array";
        case OT_Binding:         return "Binding";
        case OT_BinOp:           return "BinOp";
        case OT_Boolean:         return "Boolean";
        case OT_ByteBuffer:      return "ByteBuffer";
        case OT_ConstantLimit:   return "ConstantLimit";
        case OT_Continuation:    return "Continuation";
        case OT_Dec:             return "Dec";
        case OT_Etor_CPS:        return "EvaluatorCPS";
        case OT_Etor_Rec:        return "EvaluatorRec";
        case OT_Function:        return "Function";
        case OT_HashTable:       return "HashTable";
        case OT_Identifier:      return "Identifier";
        case OT_IfThen:          return "IfThen";
        case OT_Inc:             return "Inc";
        case OT_InStream:        return "InStream";
        case OT_IntArray:        return "IntArray";
        case OT_Integer:         return "Integer";
        case OT_IntVar:          return "IntVar";
        case OT_IntVector:       return "IntVector";
        case OT_Let:             return "Let";
        case OT_Nil:             return "Nil";
        case OT_Null:            return "Null";
        case OT_OutStream:       return "OutStream";
        case OT_Pair:            return "Pair";
        case OT_Primitive:       return "Primitive";
        case OT_Queue:           return "Queue";
        case OT_Quote:           return "Quote";
        case OT_Real:            return "Real";
        case OT_Sequence:        return "Sequence";
        case OT_Set:             return "Set";
        case OT_String:          return "String";
        case OT_Subscript:       return "Subscript";
        case OT_Symbol:          return "Symbol";
        case OT_Term:            return "Term";
        case OT_Test:            return "Test";
        case OT_TryCatchFinally: return "TryCatchFinally";
        case OT_User:            return "User";
        case OT_Var:             return "Var";
        case OT_Vector:          return "Vector";
        case OT_While:           return "While";
        default:
            fprintf(stderr, "Unknown type ID %u\n", typeId);
            return "UNKNOWN";
    }
}
