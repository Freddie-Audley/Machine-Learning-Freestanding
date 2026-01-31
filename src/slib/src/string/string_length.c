#include "slib/string.h"

long string_length(const char* str) {
    int i = 0;
    while (str[i]) i++;
    return i;
}
