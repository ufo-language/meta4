#include <stdio.h>

#include "_typedefs.h"

#include "object/functions/show.h"
#include "object/object.h"
#include "object/typeids.h"
#include "object/types/application.h"
#include "object/types/array.h"
#include "object/types/boolean.h"
#include "object/types/bytebuffer.h"
#include "object/types/continuation.h"
#include "object/types/dec.h"
#include "object/types/function.h"
#include "object/types/hashtable.h"
#include "object/types/ifthen.h"
#include "object/types/inc.h"
#include "object/types/instream.h"
#include "object/types/intarray.h"
#include "object/types/integer.h"
#include "object/types/intvar.h"
#include "object/types/intvector.h"
#include "object/types/let.h"
#include "object/types/outstream.h"
#include "object/types/pair.h"
#include "object/types/primitive.h"
#include "object/types/quote.h"
#include "object/types/nil.h"
#include "object/types/real.h"
#include "object/types/sequence.h"
#include "object/types/string.h"
#include "object/types/symbolic.h"
#include "object/types/term.h"
#include "object/types/binding.h"
#include "object/types/vector.h"
#include "object/types/while.h"

/* Defines *******************************************************************/

/* Types *********************************************************************/

/* Forward declarations ******************************************************/

/* Global variables **********************************************************/

/* Lifecycle functions *******************************************************/

/* Public functions **********************************************************/

void show(struct Object* obj, struct OutStream* outStream) {
    switch(obj->typeId) {
        case OT_Application:   application_show((struct Application*)obj, outStream); return;
        case OT_Array:         array_show((struct Array*)obj, outStream); return;
        case OT_Binding:       binding_show((struct Binding*)obj, outStream); return;
        case OT_BinOp:         break;
        case OT_Boolean:       boolean_show((struct Boolean*)obj, outStream); return;
        case OT_ByteBuffer:    byteBuffer_show((struct ByteBuffer*)obj, outStream); return;
        case OT_ConstantLimit: break;
        case OT_Continuation:  break;
        case OT_Dec:           dec_show((struct Dec*)obj, outStream); return;
        case OT_Etor_CPS:      break;
        case OT_Etor_Rec:      break;
        case OT_Function:      function_show((struct Function*)obj, outStream); return;
        case OT_HashTable:     hashTable_show((struct HashTable*)obj, outStream); return;
        case OT_Identifier:    symbolic_show((struct Symbolic*)obj, outStream); return;
        case OT_IfThen:        ifThen_show((struct IfThen*)obj, outStream); return;
        case OT_Inc:           inc_show((struct Inc*)obj, outStream); return;
        case OT_InStream:      inStream_show((struct InStream*)obj, outStream); return;
        case OT_IntArray:      intArray_show((struct IntArray*)obj, outStream); return;
        case OT_Integer:       integer_show((struct Integer*)obj, outStream); return;
        case OT_IntVector:     intVector_show((struct IntVector*)obj, outStream); return;
        case OT_IntVar:        intVar_show((struct IntVar*)obj, outStream); return;
        case OT_Let:           let_show((struct Let*)obj, outStream); return;
        case OT_Pair:          pair_show((struct Pair*)obj, outStream); return;
        case OT_Nil:           nil_show((struct Nil*)obj, outStream); return;
        case OT_Null:          outStream_writeString(outStream, "Null/Unique"); return;
        case OT_OutStream:     outStream_show((struct OutStream*)obj, outStream); return;
        case OT_Primitive:     prim_show((struct Primitive*)obj, outStream); return;
        case OT_Quote:         quote_show((struct Quote*)obj, outStream); return;
        case OT_Real:          real_show((struct Real*)obj, outStream); return;
        case OT_Sequence:      sequence_show((struct Sequence*)obj, outStream); return;
        case OT_String:        string_show((struct String*)obj, outStream); return;
        case OT_Symbol:        symbolic_show((struct Symbolic*)obj, outStream); return;
        case OT_Term:          term_show((struct Term*)obj, outStream); return;
        case OT_Test:          break;
        case OT_User:          break;
        case OT_Var:           break;
        case OT_Vector:        vector_show((struct Vector*)obj, outStream); return;
        case OT_While:         while_show((struct While*)obj, outStream); return;
        default:
            break;
    }
    fprintf(stderr, "show: Unknown type ID %u (%s)\n", obj->typeId, typeName(obj->typeId));
    outStream_writeString(outStream, "UNKNOWN");
}

/* Private functions *********************************************************/
