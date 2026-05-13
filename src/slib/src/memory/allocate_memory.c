#include "slib/definitions.h"
#include "slib/memory.h"

#define PROT_READ 0x1
#define PROT_WRITE 0x2
#define MAP_PRIVATE 0x2
#define MAP_ANONYMOUS 0x20
#define MAP_FAILED ((void*) - 1)

#define ALIGNMENT 8
#define align(x) (((x) + (ALIGNMENT - 1)) & ~(ALIGNMENT - 1))

#define PAGE_SIZE 4096
#define BLOCK_HEADER_SIZE align(sizeof(Block))
#define ARENA_HEADER_SIZE align(sizeof(Arena))
#define MIN_BLOCK_SIZE 16


typedef struct Block {
    int free;
    size_t size;
    struct Block* next;
    struct Block* prev;
    struct Block* next_free;
    struct Block* prev_free;
    struct Arena* arena;
    char data[];
} Block;


typedef struct Arena {
    size_t size;
    struct Arena* next;
    Block* first;
} Arena;


static Arena* arena_head = NULL;
static Block* free_list = NULL;


static void free_list_insert(Block* block) {
    block -> next_free = free_list;
    block -> prev_free = NULL;

    if (free_list) {
        free_list -> prev_free = block;
    }

    free_list = block;
}


static void free_list_remove(Block* block) {
    if (block -> prev_free) {
        block -> prev_free -> next_free = block -> next_free;
    } else {
        free_list = block -> next_free;
    }

    if (block -> next_free) {
        block -> next_free -> prev_free = block -> prev_free;
    }
}


static Arena* new_arena(size_t min_size) {
    size_t total_size = ARENA_HEADER_SIZE + BLOCK_HEADER_SIZE + min_size;
    size_t arena_size = PAGE_SIZE;

    while (arena_size < total_size) {
        arena_size += PAGE_SIZE;
    }

    Arena* arena = mmap(NULL, arena_size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    if (arena == MAP_FAILED) {
        return NULL;
    }

    arena -> size = arena_size;
    arena -> next = arena_head;
    arena_head = arena;

    Block* block = (Block*) ((char*) arena + ARENA_HEADER_SIZE);
    block -> size = arena_size - ARENA_HEADER_SIZE - BLOCK_HEADER_SIZE;
    block -> free = 1;
    block -> next = NULL;
    block -> prev = NULL;
    block -> next_free = NULL;
    block -> prev_free = NULL;
    block -> arena = arena;

    arena -> first = block;

    free_list_insert(block);

    return arena;
}


static Block* find_block(size_t size) {
    Block* block = free_list;

    while (block) {
        if (block -> size >= size) return block;
        block = block -> next;
    }

    return NULL;
}


static void split_block(Block* block, size_t size) {
    if (block -> size < size + BLOCK_HEADER_SIZE + MIN_BLOCK_SIZE) return;

    Block* new_block = (Block*) (block -> data + size);
    new_block -> free = 1;
    new_block -> size = block -> size - size - BLOCK_HEADER_SIZE;
    new_block -> next = block -> next;
    new_block -> prev = block;
    new_block -> next_free = NULL;
    new_block -> prev_free = NULL;
    new_block -> arena = block -> arena;

    if (new_block -> next) {
        new_block -> next -> prev = new_block;
    }

    block -> size = size;
    block -> next = new_block;
    free_list_insert(new_block);
}


static Block* merge_with_next(Block* block) {
    Block* next = block -> next;

    if (!next || !next -> free) {
        return block;
    }

    free_list_remove(next);

    block -> size += BLOCK_HEADER_SIZE + next -> size;
    block -> next = next -> next;

    if (block -> next) {
        block -> next -> prev = block;
    }

    return block;
}


void* allocate_memory(size_t size) {
    if (size == 0) return NULL;

    size = align(size);

    Block* block = find_block(size);
    if (!block) {
        Arena* arena = new_arena(size);
        if (!arena) return NULL;
        block = arena -> first;
    }

    free_list_remove(block);
    split_block(block, size);
    block -> free = 0;

    return block -> data;
}


void free(void* ptr) {
    if (!ptr) return;

    Block* block = (Block*) ((char *) ptr - BLOCK_HEADER_SIZE);
    block -> free = 1;

    if (block -> prev && block -> prev -> free) {
        block = merge_with_next(block -> prev);
    }

    if (block -> next && block -> next -> free) {
        block = merge_with_next(block);
    }

    Arena* arena = block -> arena;
    if (!block -> prev && !block -> next) {
        Arena** head_ptr_ptr = &arena_head;

        while (*head_ptr_ptr && *head_ptr_ptr != arena) {
            head_ptr_ptr = &(*head_ptr_ptr) -> next;
        }

        if (*head_ptr_ptr == arena) {
            *head_ptr_ptr = arena -> next;
        }

        munmap(arena, arena -> size);
        return;
    }

    free_list_insert(block);
}
