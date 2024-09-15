/*
 * Public interface for hash tables.
 */
#ifndef _HASH_H_
#define _HASH_H_

#include <stdlib.h> // size_t
#include "str.h"

typedef struct {
    const char* key;
    void* data;
    size_t size;
} _hash_node;

/*
 * If a node's key is NULL, but the bucket pointer in the table
 * is not NULL, then the bucket is a tombstone.
 */
typedef struct {
    _hash_node** table;
    int cap;
    int count;
    int tombstones;
} HashTable;

typedef enum {
    HASH_OK,
    HASH_DUP,
    HASH_NF,
    HASH_ERR,
} HashResult;

HashTable* create_hashtable(void);
void destroy_hashtable(HashTable* table);
void insert_hashtable(HashTable* table, String* key, void* data, int* result);
void* find_hashtable(HashTable* tab, String* key, int* result);
void remove_hashtable(HashTable* tab, String* key, int* result);

void dump_hashtable(HashTable* tab);

#endif /* _HASH_H_ */
