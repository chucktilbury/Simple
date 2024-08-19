/*
 * Public interface for hash tables.
 */
#ifndef _HASH_H_
#define _HASH_H_

#include <stdlib.h> // size_t

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
} HashResult;

// TODO: use the list functions for the table. That means that the list needs to
// be able to handle NULL pointers.
HashTable* create_hashtable(void);
void destroy_hashtable(HashTable* table);
HashResult insert_hashtable(HashTable* table, const char* key, void* data, size_t size);
HashResult find_hashtable(HashTable* tab, const char* key, void* data, size_t size);
HashResult remove_hashtable(HashTable* tab, const char* key);

void dump_hashtable(HashTable* tab);

#endif
