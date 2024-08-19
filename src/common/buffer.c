/**
 * @file buffer.c
 *
 * @brief Implementation for dynamic buffers. This is intended to hold
 * strings, but can hold an object of any size, as long as all entries
 * are the same size.
 *
 * @author Chuck Tilbury (chucktilbury@gmail.com)
 * @version 0.0
 * @date 2024-06-10
 * @copyright Copyright (c) 2024
 *
 */
#include <assert.h>
#include <string.h>

#include "buffer.h"
#include "memory.h"
#include "myassert.h"

#define MIN(l, r) (((l) < (r)) ? (l) : (r))

/**
 * @brief This returns a positive integer that represents the actual index
 * into the list. If a negative value is returned, then the index lays outside
 * of the list.
 *
 * @param buf
 * @param idx
 * @return int
 */
static inline int normalize_index(Buffer* buf, int idx) {

    if(idx >= 0 && idx <= (int)buf->length)
        return idx;
    else if(idx < 0)
        return normalize_index(buf, (buf->length + 1) + idx);
    else
        return -1;
}

/**
 * @brief Resize the buffer if it's too small to handle the additional length.
 * Otherwise do nothing.
 *
 * @param buf
 * @param len
 */
static inline void resize_buffer(Buffer* buf, size_t len) {

    if((buf->length + len) >= buf->capacity) {
        while((buf->length + len) >= buf->capacity)
            buf->capacity <<= 1;
        buf->buffer = _REALLOC_DS_ARRAY(buf->buffer, unsigned char, buf->capacity);
    }
}

/*******************************************************************************
 * Public Interface
 */

/**
 * @brief Create a buffer object. Allocate the memory for a memory buffer and
 * initialize the data structure.
 *
 * @param bytes
 * @param length
 * @return Buffer*
 */
Buffer* create_buffer(void* bytes, size_t length) {

    Buffer* ptr   = _ALLOC_DS(Buffer);
    ptr->length   = 0;
    ptr->capacity = 0x01 << 3;
    ptr->buffer   = _ALLOC_DS_ARRAY(unsigned char, ptr->capacity);

    if(bytes != NULL)
        append_buffer(ptr, bytes, length);

    return ptr;
}

/**
 * @brief Free memory that is associated with the buffer and that is managed
 * by the routines in this module.
 *
 * @param buf
 */
void destroy_buffer(Buffer* buf) {

    if(buf != NULL) {
        if(buf->buffer != NULL)
            _FREE(buf->buffer);
        _FREE(buf);
    }
}

/**
 * @brief Add the bytes to the end of the buffer. Resize the buffer as needed.
 *
 * @param buf
 * @param bytes
 * @param length
 */
void append_buffer(Buffer* buf, void* bytes, size_t length) {

    ASSERT(buf != NULL);

    resize_buffer(buf, length);
    memcpy(&buf->buffer[buf->length], bytes, length);
    buf->length += length;
    buf->buffer[buf->length] = '\0';
}

/**
 * @brief Insert the bytes at the beginning of the buffer.
 *
 * @param buf
 * @param bytes
 * @param length
 */
void prepend_buffer(Buffer* buf, void* bytes, size_t length) {

    ASSERT(buf != NULL);

    insert_buffer(buf, bytes, length, 0);
}

/**
 * @brief Reset the data in the buffer but do not resize it.
 *
 * @param buf
 */
void clear_buffer(Buffer* buf) {

    ASSERT(buf != NULL);
    buf->length = 0;
    memset(buf->buffer, 0, buf->capacity);
}

/**
 * @brief Return a copy of the data that is currently in the buffer. The
 * pointer returned should be free()d when it is no longer in use.
 *
 * @param buf
 * @return void*
 */
void* raw_buffer(Buffer* buf) {

    ASSERT(buf != NULL);
    return (void*)_DUP_MEM(buf->buffer, buf->length);
}

/**
 * @brief Return the number of bytes in the buffer.
 *
 * @param buf
 * @return size_t
 */
size_t len_buffer(Buffer* buf) {

    ASSERT(buf != NULL);
    return buf->length;
}

/**
 * @brief Return bytes of the buffer. When (*post == -1) then the end of the
 * buffer has been reached.
 *
 * @param buf
 * @param post
 * @return int
 */
int iterate_buffer(Buffer* buf, int* post) {

    ASSERT(buf != NULL);
    int retv = 0;

    if(*post >= 0 && *post < (int)buf->length) {
        retv  = buf->buffer[*post];
        *post = *post + 1;
    }
    else
        *post = -1;

    return retv;
}

/**
 * @brief Insert the bytes into the buffer at the given index. If the index is
 * outside the bounds of the existing buffer then the bites are appended
 * instead of inserted. If the index is (<0) then it refers to the end of the
 * buffer.
 *
 * @param buf
 * @param bytes
 * @param len
 * @param index
 */
void insert_buffer(Buffer* buf, void* bytes, size_t len, int index) {

    ASSERT(buf != NULL);
    ASSERT(bytes != NULL);

    int idx = normalize_index(buf, index);
    if(idx >= 0) {
        resize_buffer(buf, len);
        memmove(&buf->buffer[idx + len], &buf->buffer[idx], buf->length - idx);
        memcpy(&buf->buffer[idx], bytes, len);
        buf->length += len;
    }
    else
        append_buffer(buf, bytes, len);
}

/**
 * @brief Replacing the bytes in the buffer with the new bytes. If the new bytes
 * make the buffer longer, then adjust the size of the buffer.
 *
 * @param buf
 * @param bytes
 * @param len
 * @param index
 */
void replace_buffer(Buffer* buf, void* bytes, size_t len, int index) {

    ASSERT(buf != NULL);
    ASSERT(bytes != NULL);

    int idx = normalize_index(buf, index);
    if(idx >= 0) {
        resize_buffer(buf, (idx + len) - buf->length);
        memcpy(&buf->buffer[idx], bytes, len);
        if((idx + len) > buf->length)
            buf->length += (idx + len) - buf->length;
    }
    else
        append_buffer(buf, bytes, len);
}

/**
 * @brief Remove the bytes from the buffer between the start index and the end
 * index and return them as a allocated raw buffer. The bytes are removed from
 * the buffer but the buffer is not resized.
 *
 * @param buf
 * @param start
 * @param end
 * @return void*
 */
void* clip_buffer(Buffer* buf, int start, int end) {

    ASSERT(buf != NULL);
    int si = normalize_index(buf, start);
    int ei = normalize_index(buf, end);

    if(si >= ei)
        return NULL;

    int len   = ei - si;
    char* tmp = _ALLOC(len + 1);
    memcpy(tmp, &buf->buffer[si], len);
    tmp[len] = '\0';
    memmove(&buf->buffer[si], &buf->buffer[ei], buf->length - len);
    buf->length -= len;
    buf->buffer[buf->length] = '\0';

    return (void*)tmp;
}

/**
 * @brief Return the index of the first byte that matches the sequence given.
 * If there is no match then return (<0).
 *
 * @param buf
 * @param bytes
 * @param len
 * @return int
 */
int search_buffer(Buffer* buf, void* bytes, size_t len) {

    int retv = -1;

    if(buf->length >= len) {
        int run = buf->length - len;
        for(int i = 0; i <= run; i++) {
            if(!memcmp(&buf->buffer[i], bytes, len)) {
                retv = i;
                break;
            }
        }
    }

    return retv;
}

/**
 * @brief Return the result of memcmp() as a raw byte compare on the two
 * buffers. If the buffers are not the same size then not a match.
 *
 * @param left
 * @param right
 * @return int
 */
int comp_buffer(Buffer* left, Buffer* right) {

    if(left->length != right->length)
        return left->length - right->length; // no zero, no match
    else
        return memcmp(left->buffer, right->buffer, MIN(left->length, right->length));
}

/******************************************************************************
 * Test code.
 *
 */
#ifdef TEST_BUFFER

#include <stdarg.h>
static void dump_buffer(Buffer* buf, const char* msg, ...) {

    va_list args;

    fputc('\n', stdout);
    va_start(args, msg);
    vprintf(msg, args);
    va_end(args);
    fputc('\n', stdout);

    printf("buffer: '%s'\n", buf->buffer);
    printf("length: %lu (%lu)\n", buf->length, strlen((const char*)buf->buffer));
    printf("capacity: %lu\n", buf->capacity);
}

/*
 * Test the buffer as if it was a string because that is the easiest way to
 * create bytes for the buffer.
 */
int main(void) {

    char* str   = "this is the test string";
    Buffer* buf = create_buffer((void*)str, strlen(str));
    dump_buffer(buf, "after create");

    append_buffer(buf, (void*)str, strlen(str));
    dump_buffer(buf, "appended raw string");

    clear_buffer(buf);
    dump_buffer(buf, "buffer cleared");

    prepend_buffer(buf, (void*)str, strlen(str));
    dump_buffer(buf, "prepend test");

    char* str1 = "try ";
    prepend_buffer(buf, (void*)str1, strlen(str1));
    dump_buffer(buf, "prepend '%s'", str1);

    str1 = "blartel ";
    insert_buffer(buf, (void*)str1, strlen(str1), 16);
    dump_buffer(buf, "insert '%s' at %d", str1, 16);

    printf("\ndestroy and recreate with a NULL initialzer\n");
    destroy_buffer(buf);
    buf = create_buffer(NULL, 0);
    dump_buffer(buf, "after create");

    str = "this is another test string";
    insert_buffer(buf, (void*)str, strlen(str), 10);
    dump_buffer(buf, "after insert at nonsense location of 10");

    str = " for fun";
    insert_buffer(buf, (void*)str, strlen(str), -1);
    dump_buffer(buf, "insert '%s' at -1", str);

    str = " plastic";
    insert_buffer(buf, (void*)str, strlen(str), -21);
    dump_buffer(buf, "insert '%s' at -21", str);

    str = " green";
    insert_buffer(buf, (void*)str, strlen(str), 15);
    dump_buffer(buf, "insert '%s' at 15", str);

    str = "green";
    printf("\nsearch for '%s' returned %d\nshould be 16\n", str,
           search_buffer(buf, (void*)str, strlen(str)));

    str = "this";
    printf("\nsearch for '%s' returned %d\nshould be 0\n", str,
           search_buffer(buf, (void*)str, strlen(str)));

    str = "fun";
    printf("\nsearch for '%s' returned %d\nshould be 46\n", str,
           search_buffer(buf, (void*)str, strlen(str)));

    str = "1234";
    printf("\nsearch for '%s' returned %d\nshould be -1\n", str,
           search_buffer(buf, (void*)str, strlen(str)));

    dump_buffer(buf, "dump buffer");

    str = "brown";
    replace_buffer(buf, (void*)str, strlen(str), 16);
    dump_buffer(buf, "replace '%s' at 16", str);

    str = "funny stories";
    replace_buffer(buf, (void*)str, strlen(str), 46);
    dump_buffer(buf, "replace '%s' at 46", str);

    str1 = (char*)clip_buffer(buf, 16, 21);
    dump_buffer(buf, "clipped '%s' from 16 to 21", str1);

    str1 = (char*)clip_buffer(buf, 0, 5);
    dump_buffer(buf, "clipped '%s' from 0 to 5", str1);

    str1 = (char*)clip_buffer(buf, 16, 21);
    dump_buffer(buf, "clipped '%s' from 16 to 21", str1);

    str1 = (char*)clip_buffer(buf, 0, -1);
    dump_buffer(buf, "clipped '%s' from 0 to -1", str1);

    printf("\ndestroy buffer\n");
    printf("finished\n");
    return 0;
}

#endif
