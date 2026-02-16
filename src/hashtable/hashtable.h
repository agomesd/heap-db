#ifndef HASHTABLE_H
#define HASHTABLE_H

#include "../values/values.h"

typedef struct HashTable {
    size_t capacity;
    size_t size;
    hdb_entry_t **buckets;
} hdb_hashtable_t;

typedef struct Entry {
    char *key;
    hdb_value_t *value;
    hdb_entry_t *next;
} hdb_entry_t;

void hdb_insert(hdb_hashtable_t *table, const char *key, hdb_value_t *value);
hdb_value_t *hdb_get(hdb_hashtable_t *table, const char *key);

hdb_entry_t *hdb_create_entry(const char *key, hdb_value_t *value);
hdb_hashtable_t *hdb_create_hashtable(size_t initial_capacity);

#endif
