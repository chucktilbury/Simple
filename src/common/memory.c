/*
 * Implementation for memory interface. All memory allocation errors are fatal
 * error that abort the program.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "memory.h"

#ifdef USE_GARBAGE_COLLECTION
#include "gc.h"
#define LOC_MALLOC  GC_malloc
#define LOC_REALLOC GC_realloc
#define LOC_FREE    GC_free
#else /* USE_GARBAGE_COLLECTION */
#define LOC_MALLOC  malloc
#define LOC_REALLOC realloc
#define LOC_FREE    free
#endif /* USE_GARBAGE_COLLECTION */

void* mem_alloc(size_t size) {

    void* ptr = LOC_MALLOC(size);
    if(ptr == NULL) {
        fprintf(stderr, "Fatal: cannot allocate %lu bytes of memory\n", size);
        abort();
    }

    memset(ptr, 0, size);
    return ptr;
}

void* mem_realloc(void* ptr, size_t size) {

    void* nptr = LOC_REALLOC(ptr, size);
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
        LOC_FREE(ptr);
}
