#include "slib/io.h"
#include "slib/string.h"


typedef long ssize_t;

extern ssize_t write(int fileDescriptor, const char* buffer, long count);

void print(const char* output)
{
    write(1, output, string_length(output));
}
