#include "slib/io.h"
#include "slib/string.h"


void print(const char* output) {
    write(1, output, string_length(output));
}
