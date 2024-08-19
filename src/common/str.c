/**
 * @file str.c
 *
 * @brief Simple strings implementation. Same general idea as Python. This is
 * based upon the Buffers data structure.
 *
 * @author Chuck Tilbury (chucktilbury@gmail.com)
 * @version 0.0
 * @date 2024-06-10
 * @copyright Copyright (c) 2024
 *
 */
#include <ctype.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>

#include "buffer.h"
#include "memory.h"
#include "str.h"

/**
 * @brief Create a string object. Allocate memory for a dynamic string.
 *
 * @param str
 * @return String*
 */
String* create_string(const char* str) {

    if(str != NULL)
        return create_buffer((unsigned char*)str, strlen(str));
    else
        return create_buffer(NULL, 0);
}

/**
 * @brief Free all of the memory for a dynamic string.
 *
 * @param str
 */
void destroy_string(String* str) {

    destroy_buffer(str);
}

/**
 * @brief Append the const char* string to the buffer.
 *
 * @param ptr
 * @param str
 */
void append_string_str(String* ptr, const char* str) {

    append_buffer(ptr, (unsigned char*)str, strlen(str));
}

/**
 * @brief Append another String data structure to the existing one. Do not
 * modify the source string.
 *
 * @param ptr
 * @param str
 */
void append_string_string(String* ptr, String* str) {

    append_buffer(ptr, str->buffer, str->length);
}

/**
 * @brief Append a character to the string.
 *
 * @param ptr
 * @param ch
 */
void append_string_char(String* ptr, int ch) {

    append_buffer(ptr, (void*)&ch, 1);
}

/**
 * @brief Append a const char* to the string after formatting.
 *
 * @param ptr
 * @param fmt
 * @param ...
 */
void append_string_fmt(String* ptr, const char* fmt, ...) {

    va_list args;

    va_start(args, fmt);
    size_t len = vsnprintf(NULL, 0, fmt, args);
    va_end(args);

    char* b = _ALLOC(len + 1);
    va_start(args, fmt);
    vsprintf(b, fmt, args);
    va_end(args);

    append_buffer(ptr, (unsigned char*)b, len);
    _FREE(b);
}

/**
 * @brief Insert a string into another at the given index. If the index is
 * outside the existing string, then simple append it.
 *
 * @param ptr
 * @param idx
 * @param str
 */
void insert_string_str(String* ptr, int idx, const char* str) {

    insert_buffer(ptr, (unsigned char*)str, strlen(str), idx);
}

/**
 * @brief Insert a String into the existing string at the given index.
 *
 * @param ptr
 * @param idx
 * @param str
 */
void insert_string_string(String* ptr, int idx, String* str) {

    insert_buffer(ptr, str->buffer, str->length, idx);
}

/**
 * @brief Insert a character into the existing string at the given index.
 *
 * @param ptr
 * @param idx
 * @param ch
 */
void insert_string_char(String* ptr, int idx, int ch) {

    insert_buffer(ptr, (void*)&ch, 1, idx);
}

/**
 * @brief Insert a string into the string after formatting.
 *
 * @param ptr
 * @param idx
 * @param fmt
 * @param ...
 */
void insert_string_fmt(String* ptr, int idx, const char* fmt, ...) {

    va_list args;

    va_start(args, fmt);
    size_t len = vsnprintf(NULL, 0, fmt, args);
    va_end(args);

    char* b = _ALLOC(len + 1);
    va_start(args, fmt);
    vsprintf(b, fmt, args);
    va_end(args);

    insert_buffer(ptr, (unsigned char*)b, len, idx);
    _FREE(b);
}

/**
 * @brief Find the string in the ptr and replace it with the replacement
 * string.
 *
 * @param ptr
 * @param find
 * @param repl
 */
void replace_string_str(String* ptr, const char* find, const char* repl) {

    int fnd_idx = search_string(ptr, find);
    if(fnd_idx >= 0) {
        clip_string(ptr, fnd_idx, fnd_idx + strlen(find));
        insert_string_str(ptr, fnd_idx, repl);
    }
}

/**
 * @brief Find the string and replace it with the String.
 *
 * @param ptr
 * @param find
 * @param repl
 */
void replace_string_string(String* ptr, const char* find, String* repl) {

    replace_string_str(ptr, find, raw_string(repl));
}

/**
 * @brief Find the string and replace it with the formatted string.
 *
 * @param ptr
 * @param find
 * @param fmt
 * @param ...
 */
void replace_string_fmt(String* ptr, const char* find, const char* fmt, ...) {

    va_list args;

    va_start(args, fmt);
    size_t len = vsnprintf(NULL, 0, fmt, args);
    va_end(args);

    char* b = _ALLOC(len + 1);
    va_start(args, fmt);
    vsprintf(b, fmt, args);
    va_end(args);

    replace_string_str(ptr, find, b);
    _FREE(b);
}

/**
 * @brief Clear the string, but do not reset the capacity.
 *
 * @param str
 */
void clear_string(String* str) {

    str->length    = 0;
    str->buffer[0] = '\0';
}

/**
 * @brief Make a copy of the string and return the copy. Does not change the
 * existing string.
 *
 * @param str
 * @return String*
 */
String* copy_string(String* str) {

    return create_string(raw_string(str));
}

/**
 * @brief Convert the string to lower case.
 *
 * @param str
 */
void lower_string(String* str) {

    for(size_t i = 0; i < str->length; i++)
        str->buffer[i] = tolower(str->buffer[i]);
}

/**
 * @brief Convert the string to upper case.
 *
 * @param str
 */
void upper_string(String* str) {

    for(size_t i = 0; i < str->length; i++)
        str->buffer[i] = toupper(str->buffer[i]);
}

/**
 * @brief Return a pointer to the string that is usable by system calls such
 * as printf().
 *
 * @param str
 * @return const char*
 */
const char* raw_string(String* str) {

    if(str != NULL) {
        str->buffer[str->length] = '\0';
        return (const char*)str->buffer;
    }
    else
        return NULL;
}

/**
 * @brief Delete the part of the string that is between the start and the end
 * indexes.
 *
 * @param str
 * @param start
 * @param end
 * @return const char*
 */
const char* clip_string(String* str, int start, int end) {

    return (const char*)clip_buffer(str, start, end);
}

/**
 * @brief Return the string one character at a time and 0 when the end of the
 * buffer is reached.
 *
 * @param str
 * @param post
 * @return int
 */
int iterate_string(String* str, int* post) {

    int ch = iterate_buffer(str, post);
    if(*post == -1)
        return 0;
    else
        return ch;
}

/**
 * @brief Return successive tokens from the string, similar to strtok(). On
 * the first call, post must point to 0. That resets strtok so that it begins
 * in the string. This function allocates a buffer to operate on so that the
 * original string does not need to be writable. Uses strtok() to tokenize
 * the string.
 *
 * @param str
 * @param post
 * @param mark
 * @return const char*
 */
const char* tokenize_string(String* str, int* post, const char* mark) {

    static const char* ptr = NULL;
    const char* retv;

    if(*post == 0) {
        if(ptr != NULL)
            _FREE(ptr);
        ptr   = _DUP_STR((const char*)str->buffer);
        *post = 1;
        retv  = strtok((char*)ptr, mark);
    }
    else
        retv = strtok(NULL, mark);

    return retv;
}

/**
 * @brief Return the index of the first character in the str, of the srch
 * string.
 *
 * @param str
 * @param srch
 * @return int
 */
int search_string(String* str, const char* srch) {

    return search_buffer(str, (void*)srch, strlen(srch));
}

/**
 * @brief Compare the String to the const char* str and return what strcmp()
 * would find.
 *
 * @param ptr
 * @param str
 * @return int
 */
int comp_string_str(String* ptr, const char* str) {

    return strcmp(raw_string(ptr), str);
}

/**
 * @brief Compare the String to the String and return what strcmp() would
 * find.
 *
 * @param ptr
 * @param str
 * @return int
 */
int comp_string_string(String* ptr, String* str) {

    return strcmp(raw_string(ptr), raw_string(str));
}

/**
 * @brief Compare the String to the formatted string return what strcmp()
 * would find.
 *
 * @param ptr
 * @param fmt
 * @param ...
 * @return int
 */
int comp_string_fmt(String* ptr, const char* fmt, ...) {

    va_list args;

    va_start(args, fmt);
    size_t len = vsnprintf(NULL, 0, fmt, args);
    va_end(args);

    char* b = _ALLOC(len + 1);
    va_start(args, fmt);
    vsprintf(b, fmt, args);
    va_end(args);

    int retv = strcmp(raw_string(ptr), b);
    _FREE(b);

    return retv;
}
