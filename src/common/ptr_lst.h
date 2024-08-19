/*
 * Public interface for dynamic pointer lists.
 */
#ifndef _PTR_LST_H_
#define _PTR_LST_H_

#include <stdlib.h>

typedef struct {
    void** list;
    size_t cap;
    size_t len;
} PtrLst;

PtrLst* create_ptr_lst(void);
void destroy_ptr_lst(PtrLst* lst);
void append_ptr_lst(PtrLst* lst, void* data);
void prepend_ptr_lst(PtrLst* lst, void* data);
void* get_ptr_lst(PtrLst* lst, int idx);
void del_ptr_lst(PtrLst* lst, int idx);
void insert_ptr_lst(PtrLst* lst, void* data, int idx);
void push_ptr_lst(PtrLst* lst, void* data);
void* pop_ptr_lst(PtrLst* lst);
void* peek_ptr_lst(PtrLst* lst);
void clear_ptr_list(PtrLst* lst);
void* iterate_ptr_lst(PtrLst* lst, int* post);

#endif /* _PTR_LST_H_ */
