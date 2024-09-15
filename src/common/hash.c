
/*
 *
 *  https://programming.guide/hash-tables-open-addressing.html
 *
 * The hash table uses linear probing where the probing distance is
 * hash & 0x0F. If the result is 0 then the distance is 1. When a hash
 * is deleted, the memory is freed and the tombstone flag is set. When
 * a hash is added, it can be added to a bucket which is a tombstone.
 *
 * The table is full when 3/4 of the buckets are in use. The table is
 * resized and all of the existing hashes are rehashed into the new table.
 *
 * The add function tracks the max number of hops that are needed to
 * insert a new hash. If the hops exceed a certain number, then the hash
 * table should be rehashed, but only if a certain number of adds have
 * taken place to avoid performance problems.
 *
 * Maybe tombstones should be counted instead of hops, but I do not
 * anticipate needing to delete a lot of entries. Rehashing deletes
 * tombstones.
 *
 * Test build string:
 * clang -Wall -Wextra -DTEST -g -o t hash_examp.c memory.c
 */

#include <assert.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hash.h"
#include "memory.h"
#include "myassert.h"

#define RESULT(v) do { \
        if(result != NULL) \
            *result = (v); \
    } while(0)
    
static uint32_t hash_func(const char* key) {

    uint32_t hash = 2166136261u;
    int slen = strlen(key);

    for(int i = 0; i < slen; i++) {
        hash ^= (uint8_t)key[i];
        hash *= 16777619;
    }

    return hash;
}

static int find_slot(HashTable* tab, const char* key) {

    uint32_t hash = hash_func(key) & (tab->cap - 1);
    int inc = hash & 0x0F;
    inc = (inc == 0) ? 1 : inc;

    if(tab->table[hash] == NULL) {
        tab->count++;
        return hash;
    }
    else {
        do {
            for(int i = 0; i < tab->cap; i++) {
                if(tab->table[hash] == NULL) {
                    tab->count++;
                    return hash;
                }
                else if(tab->table[hash]->key == NULL) {
                    tab->tombstones--;
                    tab->count++;
                    return hash;
                }
                else if(strcmp(tab->table[hash]->key, key) == 0) {
                    return hash; // duplicate key
                }
                else
                    hash = (hash + inc) & (tab->cap - 1);
            }
            inc = 1; // slot not found
        } while(true);
    }

    return -1; // keep the compiler happy
}

static void rehash_table(HashTable* tab) {

    if(tab->count * 1.75 > tab->cap) {
        int oldcap = tab->cap;
        _hash_node** oldtab = tab->table;
        tab->cap <<= 1; // double the capacity
        tab->tombstones = 0;
        tab->count = 0;
        tab->table = _ALLOC_DS_ARRAY(_hash_node*, tab->cap);
        for(int i = 0; i < tab->cap; i++)
            tab->table[i] = NULL;

        int slot;

        for(int i = 0; i < oldcap; i++) {
            if(oldtab[i] != NULL && oldtab[i]->key != NULL) {
                slot = find_slot(tab, oldtab[i]->key);
                tab->table[slot] = oldtab[i];
            }
        }
        _FREE(oldtab);
    }
}

/******************************************************************
 * Public Interface 
 * 
 */

/**
 * @brief Create a hashtable object
 * 
 * @return HashTable* 
 */
HashTable* create_hashtable(void) {

    HashTable* tab = _ALLOC_DS(HashTable);

    tab->count = 0;
    tab->cap = 0x01 << 3;

    tab->table = _ALLOC_DS_ARRAY(_hash_node*, tab->cap);
    for(int i = 0; i < tab->cap; i++)
        tab->table[i] = NULL;

    return tab;
}

/**
 * @brief Destroy hashtable object.
 * 
 * @param table 
 */
void destroy_hashtable(HashTable* table) {

    ASSERT(table != NULL);
    
    if(table != NULL) {
        for(int i = 0; i < table->cap; i++) {
            if(table->table[i] != NULL) {
                if(table->table[i]->key != NULL) {
                    _FREE(table->table[i]->key);
                    _FREE(table->table[i]->data);
                }
            }
            _FREE(table->table[i]);
        }

        _FREE(table->table);
        _FREE(table);
    }
}

/**
 * @brief Insert a value into the hash table. If the value is a duplicate, 
 * then set the result to be HASH_DUP to indicate an error. Otherwise, set the
 * result to HASH_OK. If the result pointer is NULL, then do not try to update 
 * it.
 * 
 * @param table 
 * @param str 
 * @param data 
 * @param result 
 */
void insert_hashtable(HashTable* table, String* str, void* data, int* result) {

    ASSERT(table != NULL);
    ASSERT(str != NULL);
    ASSERT(data != NULL);
    
    rehash_table(table);

    const char* key = raw_string(str);
    int slot = find_slot(table, key);
    if(slot < 0) {
        RESULT(HASH_ERR);
        return;
    }

    // help me, obi wan optimizer, you are my only hope
    if(table->table[slot] != NULL) {
        if(table->table[slot]->key != NULL) {
            RESULT(HASH_DUP);
            return;
        }
    }
    else
        table->table[slot] = _ALLOC_DS(_hash_node);

    table->table[slot]->key = _DUP_STR(key);
    table->table[slot]->data = data;

    RESULT(HASH_OK);
    return;
}

/**
 * @brief Find a value in the hash table.
 * 
 * @param tab 
 * @param str 
 * @param result 
 * @return void* 
 */
void* find_hashtable(HashTable* tab, String* str, int* result) {

    ASSERT(tab != NULL);
    ASSERT(str != NULL);

    const char* key = raw_string(str);
    int slot = find_slot(tab, key);

    if(tab->table[slot] != NULL && tab->table[slot]->key != NULL) {
        if(strcmp(tab->table[slot]->key, key) == 0) {
            RESULT(HASH_OK);
            return tab->table[slot]->data;
        }
    }

    RESULT(HASH_NF);
    return NULL;
}

/**
 * @brief Remove a value from the hash table.
 * 
 * @param tab 
 * @param str 
 */
void remove_hashtable(HashTable* tab, String* str, int* result) {

    ASSERT(tab != NULL);
    ASSERT(str != NULL);

    const char* key = raw_string(str);
    int slot = find_slot(tab, key);

    if((tab->table[slot] != NULL) && (tab->table[slot]->key != NULL)) {
        if(strcmp(tab->table[slot]->key, key) == 0) {
            _FREE(tab->table[slot]->data);
            _FREE(tab->table[slot]->key);
            tab->table[slot]->key = NULL;
            tab->table[slot]->data = NULL;
            tab->table[slot]->size = 0;
            tab->count--;
            tab->tombstones++;
            RESULT(HASH_OK);
        }
    }

    RESULT(HASH_NF);
}

/**
 * @brief Dump the hash table keys to the console.
 * 
 * @param tab 
 */
void dump_hashtable(HashTable* tab) {

    int count = 1;

    for(int i = 0; i < tab->cap; i++) {
        if(tab->table[i] != NULL) {
            if(tab->table[i]->key != NULL) {
                printf("%3d. %s\n", count, tab->table[i]->key);
                count++;
            }
        }
    }
}
