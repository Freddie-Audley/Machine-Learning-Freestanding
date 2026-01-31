#ifndef MEMORY_H
#define MEMORY_H

#include "slib/definitions.h"

extern void* mmap(void* address, size_t length, int prot, int flags, int fd, off_t offset);
void* malloc(size_t size);

#endif
