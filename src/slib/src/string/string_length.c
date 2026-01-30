#include "slib/string.h"

long string_length(const char* str)
{
    int i = 0;
    while (str[i]) i++;     // Increment i until a null character is reached
    return i;
}
