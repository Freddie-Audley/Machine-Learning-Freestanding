#include "slib/memory.h"
#include "malloc.c"


Block* merge_blocks(Block* block) {
    if (block -> next && block -> next -> free) {
        block -> size += BLOCK_HEADER_SIZE + block -> next -> size;
        block -> next = block -> next -> next;
    }

    if (block -> next) {
        block -> next -> prev = block;
    }

    return block;
}


void free(void* ptr) {
    if (!ptr) return;

    Block* block = (Block*) ((char *) ptr - BLOCK_HEADER_SIZE);
    block -> free = 1;

    if (block -> prev && block -> prev -> free) {
        block = merge_blocks(block -> prev);
    }

    if (block -> next && block -> next -> free) {
        block = merge_blocks(block);
    }

    if (!block -> next) {
        if (block -> prev) {
            block -> prev -> next = NULL;
        } else {
            head = NULL;
        }
        munmap(block, BLOCK_HEADER_SIZE + block -> size);
    }
}