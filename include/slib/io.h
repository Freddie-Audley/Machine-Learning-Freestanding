#pragma once
#include "definitions.h"

extern ssize_t write(int fileDescriptor, const char* buffer, long count);
void print(const char* output);
