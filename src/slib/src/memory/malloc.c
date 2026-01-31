#include "slib/definitions.h"

#define BLOCK_DATA_SIZE 20
#define align(x) ((((x - 1) >> 2) << 2) + 4)

void* head = NULL;

struct block {
    int free;
    size_t size;
    struct block* next;
    struct block* prev;
    void* ptr;
    char data[];
};


void find_block(size_t size) {
    struct block* current_block = head;
    while (current_block && !(current_block -> free && current_block -> size >= size)) {
        current_block = current_block -> next;
    }
}


void split_block(struct block* block, size_t size) {
    struct block* new_block = (struct block*) (block -> data + size);
    new_block -> free = 1;
    new_block -> size = block -> size - size - BLOCK_DATA_SIZE;
    new_block -> next = block -> next;
    new_block -> prev = block;
    new_block -> ptr = new_block -> data;

    block -> next = new_block;
    block -> size = size;

    if (new_block -> next) {
        new_block -> next -> prev = new_block;
    }
}
