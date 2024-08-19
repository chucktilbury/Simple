/*
 * Implementation of string list.
 *
 * Simple wrappers for the ptr_lst functions so that types are cast in a
 * sensible way.
 */
#include "str_lst.h"

/**
 * @brief Create a str lst object
 *
 * @return StrLst*
 */
StrLst* create_str_lst(void) {

    return create_ptr_lst();
}

/**
 * @brief Destroy a string list.
 *
 * @param lst
 */
void destroy_str_lst(StrLst* lst) {

    if(lst != NULL) {
        int post = 0;
        String* str;
        while(NULL != (str = iterate_ptr_lst(lst, &post)))
            destroy_string(str);
        destroy_ptr_lst(lst);
    }
}

/**
 * @brief Add a string to the end of the list.
 *
 * @param lst
 * @param data
 */
void append_str_lst(StrLst* lst, String* data) {

    append_ptr_lst(lst, (void*)data);
}

/**
 * @brief Add a string to the end of the list.
 *
 * @param lst
 * @param data
 */
void prepend_str_lst(StrLst* lst, String* data) {

    insert_ptr_lst(lst, (void*)data, 0);
}

/**
 * @brief Get the str lst object at the index given.
 *
 * @param lst
 * @param idx
 * @return String*
 */
String* get_str_lst(StrLst* lst, int idx) {

    return (String*)get_ptr_lst(lst, idx);
}

/**
 * @brief Insert a string into the list at the index given.
 *
 * @param lst
 * @param data
 * @param idx
 */
void insert_str_lst(StrLst* lst, String* data, int idx) {

    insert_ptr_lst(lst, (void*)data, idx);
}

/**
 * @brief Push the string on the list as if the list was a FIFO.
 *
 * @param lst
 * @param data
 */
void push_str_lst(StrLst* lst, String* data) {

    push_ptr_lst(lst, (void*)data);
}

/**
 * @brief Pop the string from the FIFO.
 *
 * @param lst
 * @return String*
 */
String* pop_str_lst(StrLst* lst) {

    return (String*)pop_ptr_lst(lst);
}

/**
 * @brief Peek at the end of the list and return the pointer. Does not modify
 * the list in any way.
 *
 * @param lst
 * @return String*
 */
String* peek_str_lst(StrLst* lst) {

    return (String*)peek_ptr_lst(lst);
}

/**
 * @brief Iterate the string list.
 *
 * @param lst
 * @param post
 * @return String*
 */
String* iterate_str_lst(StrLst* lst, int* post) {

    return (String*)iterate_ptr_lst(lst, post);
}

/**
 * @brief Clear the list and free all entries, but do not destroy the list.
 *
 * @param lst
 */
void clear_str_lst(StrLst* lst) {

    int post = 0;
    String* str;

    while(NULL != (str = iterate_str_lst(lst, &post)))
        destroy_string(str);

    lst->len = 0;
}

int search_str_lst(StrLst* lst, const char* str) {

    String* ptr;
    int post = 0;

    while(NULL != (ptr = iterate_str_lst(lst, &post))) {
        if(!comp_string_str(ptr, str))
            return post;
    }

    return -1;
}

/**
 * @brief Do a bubble sort on a list of strings.
 *
 * @param lst
 */
void sort_str_lst(StrLst* lst) {

    int flag = 1;

    while(flag > 0) {
        flag = 0;
        for(size_t i = 0; i < lst->len - 1; i++) {
            if(comp_string_string(lst->list[i], lst->list[i + 1]) > 0) {
                String* tmp      = lst->list[i];
                lst->list[i]     = lst->list[i + 1];
                lst->list[i + 1] = tmp;
                flag++;
            }
        }
    }
}

/**
 * @brief Split the string into an array of char* where the character is
 * locatied.
 *
 * @param str
 * @param mark
 * @return StrLst*
 */
StrLst* split_string(String* str, const char* mark) {

    int post    = 0;
    StrLst* lst = create_str_lst();
    const char* tmp;

    while(NULL != (tmp = tokenize_string(str, &post, mark))) {
        append_str_lst(lst, create_string(tmp));
    }

    return lst;
}

/**
 * @brief Join an array of strings where the given str is between them.
 *
 * @param lst
 * @param str
 * @return String*
 */
String* join_string(StrLst* lst, const char* str) {

    int post  = 0;
    String* s = create_string(NULL);
    String* tmp;

    tmp = iterate_str_lst(lst, &post);
    while(tmp != NULL) {
        append_string_string(s, tmp);
        tmp = iterate_str_lst(lst, &post);
        if(tmp != NULL)
            append_string_str(s, str);
    }

    return s;
}
