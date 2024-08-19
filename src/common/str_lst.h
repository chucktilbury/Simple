/*
 * Public interface to the string list.
 */
#ifndef _STR_LST_H_
#define _STR_LST_H_

#include "ptr_lst.h"
#include "str.h"

typedef PtrLst StrLst;

StrLst* create_str_lst(void);
void destroy_str_lst(StrLst* lst);
void append_str_lst(StrLst* lst, String* data);
void prepend_str_lst(StrLst* lst, String* data);
String* get_str_lst(StrLst* lst, int idx);
void insert_str_lst(StrLst* lst, String* data, int idx);
void push_str_lst(StrLst* lst, String* data);
String* pop_str_lst(StrLst* lst);
String* peek_str_lst(StrLst* lst);
void clear_str_lst(StrLst* lst);
String* iterate_str_lst(StrLst* lst, int* post);
int search_str_lst(StrLst* lst, const char* str);
void sort_str_lst(StrLst* lst);

StrLst* split_string(String* str, const char* mark);
String* join_string(StrLst* lst, const char* str);

#endif /* _STR_LST_H_ */
