#include "slib/definitions.h"
#include "slib/memory.h"

#define PROT_READ 0x1
#define PROT_WRITE 0x2
#define MAP_PRIVATE 0x2
#define MAP_ANONYMOUS 0x20
#define MAP_FAILED ((void*)-1)

#define BLOCK_DATA_SIZE 20
#define align(x) ((((x - 1) >> 2) << 2) + 4)

void* head = NULL;

typedef struct block_struct {
    int free;
    size_t size;
    struct block_struct* next;
    struct block_struct* prev;
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


block* extend_heap(block* end, size_t size) {
    block* new_block = mmap(NULL, BLOCK_DATA_SIZE + size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    if (new_block == MAP_FAILED) {
        return NULL;
    }

    new_block -> size = size;
    new_block -> free = 0;
    new_block -> next = NULL;
    new_block -> prev = end;

    if (end) {
        end -> next = new_block;
    }

    return new_block;
}
