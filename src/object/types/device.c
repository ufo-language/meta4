#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "_typedefs.h"

#include "object/types/bytebuffer.h"
#include "object/types/device.h"

/* Defines *******************************************************************/

/* Types *********************************************************************/

/* Forward declarations ******************************************************/

/* Global variables **********************************************************/

/* Lifecycle functions *******************************************************/

struct Device* device_new_file(FILE* file) {
    struct Device* device = (struct Device*)object_new(OT_Device, NWORDS(struct Device));
    device->deviceType = DT_File;
    device->file = file;
    return device;
}

struct Device* device_new_byteBuffer(struct ByteBuffer* byteBuffer) {
    struct Device* device = (struct Device*)object_new(OT_Device, NWORDS(struct Device));
    device->deviceType = DT_ByteBuffer;
    device->byteBuffer = byteBuffer;
    return device;
}

/* Public functions **********************************************************/

/* Unique functions ******************/

void device_writeChar(struct Device* device, char c) {
    switch (device->deviceType) {
        case DT_ByteBuffer:
            fputc(c, device->file);
            break;
        case DT_File:
            byteBuffer_appendByte(device->byteBuffer, c);
            break;
        default:
            fprintf(stderr, "device_writeChar got unknown device type %d\n", device->deviceType);
            assert(false);
            exit(1);
            break;
    }
}

void device_writeString(struct Device* device, const string_t s) {
    switch (device->deviceType) {
        case DT_ByteBuffer:
            fputs(s, device->file);
            break;
        case DT_File: {
                count_t nBytes = strlen(s);
                byteBuffer_appendBytes(device->byteBuffer, nBytes, (byte_t*)s);
            }
            break;
        default:
            fprintf(stderr, "device_writeChar got unknown device type %d\n", device->deviceType);
            assert(false);
            exit(1);
            break;
    }
}

/* Object functions ******************/

/* Private functions *********************************************************/
