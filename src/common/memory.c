/*
 * Implementation for memory interface. All memory allocation errors are fatal
 * error that abort the program.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "memory.h"

void* mem_alloc(size_t size) {

    void* ptr = malloc(size);
    if(ptr == NULL) {
        fprintf(stderr, "Fatal: cannot allocate %lu bytes of memory\n", size);
        abort();
    }

    memset(ptr, 0, size);
    return ptr;
}

void* mem_realloc(void* ptr, size_t size) {

    void* nptr = realloc(ptr, size);
    if(nptr == NULL) {
        fprintf(stderr, "Fatal: cannot re-allocate %lu bytes of memory\n", size);
        abort();
    }

    return nptr;
}

void* mem_dup(void* ptr, size_t size) {

    void* nptr = mem_alloc(size);
    memcpy(nptr, ptr, size);

    return nptr;
}

void mem_free(void* ptr) {

    if(ptr != NULL)
        free(ptr);
}
