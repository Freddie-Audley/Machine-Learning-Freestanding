#include "slib/definitions.h"

#define BLOCK_DATA_SIZE 20
#define align(x) ((((x - 1) >> 2) << 2) + 4)

void* head = NULL;

typedef struct {
    int free;
    size_t size;
    block* next;
    block* prev;
    void* ptr;
    char data[];
} block;


void find_block(size_t size) {
    block* current_block = head;
    while (current_block && !(current_block -> free && current_block -> size >= size)) {
        current_block = current_block -> next;
    }
}


void split_block(block* block_arg, size_t size) {
    block* new_block = (block*) (block_arg -> data + size);
    new_block -> free = 1;
    new_block -> size = block_arg -> size - size - BLOCK_DATA_SIZE;
    new_block -> next = block_arg -> next;
    new_block -> prev = block_arg;
    new_block -> ptr = block_arg -> data;

    block_arg -> next = new_block;
    block_arg -> size = size;

    if (new_block -> next) {
        new_block -> next -> prev = new_block;
    }
}
