#include "slib/memory.h"
#include "malloc.c"


block* merge_blocks(block* block_arg) {
    if (block_arg -> next && block_arg -> next -> free) {
        block_arg -> size += BLOCK_HEADER_SIZE + block_arg -> next -> size;
        block_arg -> next = block_arg -> next -> next;
    }

    if (block_arg -> next) {
        block_arg -> next -> prev = block_arg;
    }

    return block_arg;
}


void free(void* ptr) {
    if (!ptr) return;

    block* block_to_free = (block*) ((char *) ptr - BLOCK_HEADER_SIZE);
    block_to_free -> free = 1;

    if (block_to_free -> prev && block_to_free -> prev -> free) {
        block_to_free = merge_blocks(block_to_free -> prev);
    }

    if (block_to_free -> next && block_to_free -> next -> free) {
        block_to_free = merge_blocks(block_to_free);
    }

    if (!block_to_free -> next) {
        if (block_to_free -> prev) {
            block_to_free -> prev -> next = NULL;
        } else {
            head = NULL;
        }
        munmap(block_to_free, BLOCK_HEADER_SIZE + block_to_free -> size);
    }
}