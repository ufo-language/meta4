#include <stdio.h>

#include "_typedefs.h"

#include "object/object.h"

/* Defines *******************************************************************/

/* Types *********************************************************************/

enum DeviceType {
    DT_File, DT_ByteBuffer
};

struct ByteBuffer;

struct Device {
    struct Object obj;
    enum DeviceType deviceType;
    union {
        FILE* file;
        struct ByteBuffer* byteBuffer;
    };
};

/* Forward declarations ******************************************************/

/* Global variables **********************************************************/

/* Lifecycle functions *******************************************************/

struct Device* device_new_file(FILE* file);
struct Device* device_new_byteBuffer(struct ByteBuffer* byteBuffer);

/* Public functions **********************************************************/

/* Unique functions ******************/

void device_writeChar(struct Device* device, char c);
void device_writeString(struct Device* device, const string_t s);

/* Object functions ******************/
