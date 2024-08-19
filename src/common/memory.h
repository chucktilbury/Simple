/*
 * Public interface for memory operations.
 */
#ifndef _MEMORY_H_
#define _MEMORY_H_

#include <stddef.h> // size_t
#include <string.h> // strlen

#define _ALLOC(s) mem_alloc(s)
#define _ALLOC_DS(t) (t*)mem_alloc(sizeof(t))
#define _ALLOC_DS_ARRAY(t, s) (t*)mem_alloc(sizeof(t) * (s))
#define _REALLOC(p, s) mem_realloc((void*)(p), (s))
#define _REALLOC_DS_ARRAY(p, t, s) (t*)mem_realloc((void*)(p), sizeof(t) * (s))
#define _DUP_MEM(p, s) mem_dup((void*)(p), (s))
#define _DUP_DS(p, t) (t*)mem_dup(sizeof(t))
#define _DUP_STR(s)                                                    \
    (((s) != NULL) ? (const char*)mem_dup((void*)(s), strlen(s) + 1) : \
                     (const char*)mem_alloc(1))
#define _FREE(p) mem_free((void*)(p))

void* mem_alloc(size_t size);
void* mem_realloc(void* ptr, size_t size);
void* mem_dup(void* ptr, size_t size);
void mem_free(void* ptr);

#endif /* _MEMORY_H_ */
