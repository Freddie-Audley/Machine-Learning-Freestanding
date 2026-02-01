#pragma once

#include "slib/definitions.h"

extern void* mmap(void* address, size_t length, int prot, int flags, int fd, off_t offset);
extern void munmap(void* address, size_t length);

void* malloc(size_t size);
void free(void* address);
