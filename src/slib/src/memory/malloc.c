#include "slib/definitions.h"
#include "slib/memory.h"

#define PROT_READ 0x1
#define PROT_WRITE 0x2
#define MAP_PRIVATE 0x2
#define MAP_ANONYMOUS 0x20
#define MAP_FAILED ((void*)-1)

#define BLOCK_HEADER_SIZE sizeof(Block)
#define ALIGNMENT 8
#define align(x) (((x) + (ALIGNMENT - 1)) & ~(ALIGNMENT - 1))

typedef struct Block {
    int free;
    size_t size;
    struct Block* next;
    struct Block* prev;
    void* ptr;
    char data[];
} Block;

static Block* head = NULL;


Block* find_block(Block** tail, size_t size) {
    Block* current_block = head;
    *tail = NULL;

    while (current_block && !(current_block -> free && current_block -> size >= size)) {
        *tail = current_block;
        current_block = current_block -> next;
    }

    return current_block;
}


void split_block(Block* block, size_t size) {
    Block* new_block = (Block*) (block -> data + size);
    new_block -> free = 1;
    new_block -> size = block -> size - size - BLOCK_HEADER_SIZE;
    new_block -> next = block -> next;
    new_block -> prev = block;
    new_block -> ptr = new_block -> data;

    block -> next = new_block;
    block -> size = size;

    if (new_block -> next) {
        new_block -> next -> prev = new_block;
    }
}


Block* extend_heap(Block* tail, size_t size) {
    Block* new_block = mmap(NULL, BLOCK_HEADER_SIZE + size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    if (new_block == MAP_FAILED) {
        return NULL;
    }

    new_block -> size = size;
    new_block -> free = 0;
    new_block -> next = NULL;
    new_block -> prev = tail;
    new_block -> ptr = new_block -> data;

    if (tail) {
        tail -> next = new_block;
    }

    return new_block;
}


void* malloc(size_t size) {
    if (size == 0) return NULL;

    Block* new_block;
    size_t const aligned_size = align(size);

    if (head) {
        Block* tail = head;
        new_block = find_block(&tail, aligned_size);

        if (new_block) {
            if (new_block -> size - aligned_size >= BLOCK_HEADER_SIZE + ALIGNMENT) {
                split_block(new_block, aligned_size);
            }
            new_block -> free = 0;

        } else {
            new_block = extend_heap(tail, aligned_size);
            if (!new_block) {
                return NULL;
            }
        }

    } else {
        new_block = extend_heap(NULL, aligned_size);
        if (!new_block) {
            return NULL;
        }
        head = new_block;
    }

    return new_block -> data;
}
