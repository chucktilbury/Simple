/**
 * @file buffer.h
 *
 * @brief Public interface to buffers.
 *
 * @author Chuck Tilbury (chucktilbury@gmail.com)
 * @version 0.0
 * @date 2024-06-10
 * @copyright Copyright (c) 2024
 *
 */
#ifndef _BUFFER_H_
#define _BUFFER_H_

#include <stdlib.h>

typedef struct {
    unsigned char* buffer; // raw array of bytes.
    size_t capacity;       // number of bytes the buffer can hold
    size_t length;         // number of bytes currently in the buffer
} Buffer;

Buffer* create_buffer(void* bytes, size_t length);
void destroy_buffer(Buffer* buf);
void append_buffer(Buffer* buf, void* bytes, size_t length);
void prepend_buffer(Buffer* buf, void* bytes, size_t length);
void insert_buffer(Buffer* buf, void* bytes, size_t len, int index);
void replace_buffer(Buffer* buf, void* bytes, size_t len, int index);
void* clip_buffer(Buffer* buf, int start, int end);
int search_buffer(Buffer* buf, void* bytes, size_t len);
int comp_buffer(Buffer* left, Buffer* right);
int iterate_buffer(Buffer* buf, int* post);
void clear_buffer(Buffer* buf);
void* raw_buffer(Buffer* buf);
size_t len_buffer(Buffer* buf);

#endif /* _BUFFER_H_ */
