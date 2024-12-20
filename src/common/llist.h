/**
 * @file linked_list.h
 *
 * @brief Low level routines for manipulating a list of pointers.
 *
 * @author Charles Tilbury (chucktilbury@gmail.com)
 * @version 0.0
 * @date 03-28-2024
 * @copyright Copyright (c) 2024
 */
#ifndef _LLIST_H_
#define _LLIST_H_

#include <stdbool.h>

typedef struct _link_list_elem_ {
    void* data;
    struct _link_list_elem_* next;
} LinkListElem;

typedef struct {
    LinkListElem* first;
    LinkListElem* crnt;
    LinkListElem* last;
    bool is_changed;
    int length;
} LinkList;

LinkList* create_link_list(void);
void destroy_link_list(LinkList* lst);
void append_link_list(LinkList* ll, void* data);
void prepend_link_list(LinkList* ll, void* data);
void push_link_list(LinkList* ll, void* data);
void* pop_link_list(LinkList* ll);
void* peek_link_list(LinkList* ll);
void* last_link_list(LinkList* lst);
void* iter_link_list(LinkList* ll, void** post);
int len_link_list(LinkList* ll);

#endif /* _LLIST_H_ */
