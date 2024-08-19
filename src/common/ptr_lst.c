/**
 * @file ptr_lst.c
 *
 * @brief This implements a dynamic list functionality for arbitrary
 * pointers. It also includes the logic required for a stack or a queue
 * of pointers.
 *
 * @author Chuck Tilbury (chucktilbury@gmail.com)
 * @version 0.0
 * @date 2024-06-10
 * @copyright Copyright (c) 2024
 *
 */
#include <assert.h>
#include <string.h>

#include "memory.h"
#include "myassert.h"
#include "ptr_lst.h"

/**
 * @brief This returns a positive integer that represents the actual index
 * into the list. If a negative value is returned, then the index lays outside
 * of the list.
 *
 * @param lst
 * @param idx
 * @return int
 */
static inline int normalize_index(PtrLst* lst, int idx) {

    if(idx >= 0 && idx < (int)lst->len)
        return idx;
    else if(idx < 0)
        return normalize_index(lst, lst->len + idx);
    else
        return -1;
}

/**
 * @brief Grow the list if needed, else do nothing.
 *
 * @param lst
 */
static inline void grow_list(PtrLst* lst) {

    if(lst->len + 1 >= lst->cap) {
        lst->cap <<= 1;
        lst->list = _REALLOC_DS_ARRAY(lst->list, void*, lst->cap);
    }
}

/******************************************************************************
 *
 * Public Interface
 *
 */

/**
 * @brief Create a ptr lst object. Allocate the memory for a pointer list and
 * get it ready to accept content.
 *
 * @return PtrLst*
 */
PtrLst* create_ptr_lst(void) {

    PtrLst* ptr = _ALLOC_DS(PtrLst);
    ptr->len    = 0;
    ptr->cap    = 0x01 << 3;
    ptr->list   = _ALLOC_DS_ARRAY(void*, ptr->cap);

    return ptr;
}

/**
 * @brief Free the memory associated with a pointer list. Note that the caller
 * is requred to free the actual content.
 *
 * @param lst
 */
void destroy_ptr_lst(PtrLst* lst) {

    if(lst != NULL) {
        if(lst->list != NULL)
            _FREE(lst->list);
        _FREE(lst);
    }
}

/**
 * @brief Append a pointer to the pointer list and grow the list if needed.
 * NULL pointers cannot be stored in the list.
 *
 * @param lst
 * @param data
 */
void append_ptr_lst(PtrLst* lst, void* data) {

    ASSERT(lst != NULL);
    ASSERT(data != NULL);

    grow_list(lst);

    lst->list[lst->len] = data;
    lst->len++;
}

/**
 * @brief Prepend a pointer to the pointer list and grow the list if needed.
 * NULL pointers cannot be stored in the list.
 *
 * @param lst
 * @param data
 */
void prepend_ptr_lst(PtrLst* lst, void* data) {

    insert_ptr_lst(lst, data, 0);
}

/**
 * @brief Get the ptr lst object at the given index. This also accepts negative
 * numbers such that it references the end of the list. For example, the number
 * -1 references the list item in the list. If the index falls outside of the
 * list them NULL is returned.
 *
 * @param lst
 * @param idx
 * @return void*
 */
void* get_ptr_lst(PtrLst* lst, int idx) {

    ASSERT(lst != NULL);

    void* ptr = NULL;
    int i     = normalize_index(lst, idx);

    if(i >= 0)
        ptr = lst->list[i];

    return ptr;
}

/**
 * @brief Insert the pointer into the list at the index given. If the index is
 * negative then it references the end of the list. If the index is outside of
 * the list then this simply appeands the pointer to the end of the list. Grow
 * the list if needed.
 *
 * @param lst
 * @param data
 * @param idx
 */
void insert_ptr_lst(PtrLst* lst, void* data, int idx) {

    ASSERT(lst != NULL);
    ASSERT(data != NULL);

    grow_list(lst);
    int i = normalize_index(lst, idx);

    if(i >= 0) {
        memmove(&lst->list[i + 1], &lst->list[i], (lst->len - i) * sizeof(void*));
        lst->list[i] = data;
        lst->len++;
    }
    else
        append_ptr_lst(lst, data);
}

/**
 * @brief Append the pointer to the end of the list. Grow the list if required.
 *
 * @param lst
 * @param data
 */
void push_ptr_lst(PtrLst* lst, void* data) {

    ASSERT(lst != NULL);
    ASSERT(data != NULL);

    append_ptr_lst(lst, data);
}

/**
 * @brief Remove the pointer at the end of the list and return a pointer to
 * it. If the list is empty, then return NULL.
 *
 * @param lst
 * @return void*
 */
void* pop_ptr_lst(PtrLst* lst) {

    ASSERT(lst != NULL);

    void* ptr = NULL;

    if(lst->len > 0) {
        ptr = lst->list[lst->len];
        lst->len--;
    }

    return ptr;
}

/**
 * @brief Return the pointer on the top of the list. If the list is empty
 * then return NULL. Does to have any effect on the content of the list.
 *
 * @param lst
 * @return void*
 */
void* peek_ptr_lst(PtrLst* lst) {

    ASSERT(lst != NULL);

    void* ptr = NULL;

    if(lst->len > 0)
        ptr = lst->list[lst->len];

    return ptr;
}

/**
 * @brief Reentrantly iterate the list. The post parameter must point to an
 * integer and it must be initialized to zero before the first call to iterate.
 * The post must not be changed while iterating the list. Also, the list must
 * not be altered while iterating it. There is no specific checking done, but
 * the results could be undefined.
 *
 * @param lst
 * @param post
 * @return void*
 */
void* iterate_ptr_lst(PtrLst* lst, int* post) {

    ASSERT(lst != NULL);
    ASSERT(post != NULL);

    void* ptr = get_ptr_lst(lst, *post);
    *post     = *post + 1;

    return ptr;
}

/*
 * Remove all of the pointers in the list but don't change the actual length.
 */
void clear_ptr_list(PtrLst* lst) {

    lst->len = 0; // just line that....
}

/*
 * Remove a single pointer from the list. If the index lies outside of the list
 * the silently fail.
 */
void del_ptr_lst(PtrLst* lst, int idx) {

    int i = normalize_index(lst, idx);
    if(i >= 0) {
        memmove(&lst->list[i], &lst->list[i + 1], ((lst->len - i) + 1) * sizeof(void*));
        lst->len--;
    }
}

/******************************************************************************
 *
 * Test Code
 *
 */
#ifdef TEST_PTR_LST

#include <stdarg.h>
void dump_ptr_lst(PtrLst* lst, const char* fmt, ...) {

    va_list args;

    fputc('\n', stdout);
    va_start(args, fmt);
    vprintf(fmt, args);
    va_end(args);
    fputc('\n', stdout);

    printf("capacity: %lu\n", lst->cap);
    printf("length: %lu\n", lst->len);
    int post = 0;
    char* str;
    while(NULL != (str = iterate_ptr_lst(lst, &post)))
        printf("   %d. %s\n", post, str);
}

int main(void) {

    char* const strs[] = { "test string 0",
                           "test string 1",
                           "test string 2",
                           "test string 3",
                           "test string 4",
                           "test string 5",
                           "test string 6",
                           "test string 7",
                           "test string 8",
                           "test string 9",
                           NULL };

    PtrLst* lst = create_ptr_lst();
    dump_ptr_lst(lst, "new list");

    for(int i = 0; i < 3; i++)
        append_ptr_lst(lst, strs[i]);
    dump_ptr_lst(lst, "3 items");

    prepend_ptr_lst(lst, strs[4]);
    dump_ptr_lst(lst, "insert the beginning. 4 items");

    insert_ptr_lst(lst, strs[3], 2);
    dump_ptr_lst(lst, "insert 3 at 3. 5 items");

    insert_ptr_lst(lst, strs[7], -1);
    dump_ptr_lst(lst, "insert 7 at -1. 6 items");

    destroy_ptr_lst(lst);
    lst = create_ptr_lst();
    dump_ptr_lst(lst, "re-create the list");

    for(int i = 0; i < 7; i++)
        append_ptr_lst(lst, strs[i]);
    dump_ptr_lst(lst, "new list. 7 items");

    for(int i = 7; i < 9; i++)
        append_ptr_lst(lst, strs[i]);
    dump_ptr_lst(lst, "resize list. 9 items");

    printf("\ndelete first, last and a middle item\n");
    del_ptr_lst(lst, 0);
    // dump_ptr_lst(lst, "after delete item 0. 6 items");
    del_ptr_lst(lst, 5);
    // dump_ptr_lst(lst, "after delete item 5. 6 items");
    del_ptr_lst(lst, -1);
    dump_ptr_lst(lst, "after delete item -1. 6 items");

    printf("\nfinished\n");
    return 0;
}

#endif
