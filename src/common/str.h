/**
 * @file str.h
 *
 * @brief Public interface for string manipulation routines.
 *
 * @author Chuck Tilbury (chucktilbury@gmail.com)
 * @version 0.0
 * @date 2024-06-10
 * @copyright Copyright (c) 2024
 *
 */
#ifndef _STR_H_
#define _STR_H_

#include "buffer.h"

typedef Buffer String;

String* create_string(const char* str);
void destroy_string(String* str);
void append_string_str(String* ptr, const char* str);
void append_string_string(String* ptr, String* str);
void append_string_char(String* ptr, int ch);
void append_string_fmt(String* ptr, const char* fmt, ...);

void insert_string_str(String* ptr, int idx, const char* str);
void insert_string_string(String* ptr, int idx, String* str);
void insert_string_char(String* ptr, int idx, int ch);
void insert_string_fmt(String* ptr, int idx, const char* fmt, ...);

void replace_string_str(String* ptr, const char* find, const char* repl);
void replace_string_fmt(String* ptr, const char* find, const char* fmt, ...);

void clear_string(String* str);
void lower_string(String* str);
void upper_string(String* str);
String* copy_string(String* str);

const char* raw_string(String* str);
const char* clip_string(String* str, int start, int end);
int iterate_string(String* str, int* post);
const char* tokenize_string(String* str, int* post, const char* mark);

int search_string(String* str, const char* srch);
int comp_string_str(String* ptr, const char* str);
int comp_string_string(String* ptr, String* str);
int comp_string_fmt(String* ptr, const char* fmt, ...);

#endif /* _STR_H_ */
