#include <string.h>
#include "hashtable.h"
#include "../utils/utils.h"

hdb_hashtable_t *hdb_create_hashtable(size_t initial_capacity) {
    if (initial_capacity == 0) {
        initial_capacity = 8;
    }

    hdb_hashtable_t *hashtable = malloc(sizeof(hdb_hashtable_t));
    if (!hashtable) return NULL;


    hdb_entry_t **buckets = malloc(initial_capacity * sizeof(hdb_entry_t*));
    if (!buckets) {
        free(hashtable);
        return NULL;
    }
    hashtable->capacity = initial_capacity;
    hashtable->size = 0;
    hashtable->buckets = buckets;

    for (size_t i = 0; i < hashtable->capacity; i++) {
        hashtable->buckets[i] = NULL;
    }
    
    return hashtable;
}

hdb_entry_t *hdb_create_entry(const char *key, hdb_value_t *value) {
    hdb_entry_t *entry = malloc(sizeof(hdb_entry_t));
    if (!entry) return NULL;

    entry->key = malloc(strlen(key) + 1);
    if (!entry->key) {
        free(entry);
        return NULL;
    }

    strcpy(entry->key, key);
    entry->value = value;
    entry->next = NULL;

    return entry;
}

void hdb_insert(hdb_hashtable_t *table, const char *key, hdb_value_t *value) {
    int index = hash_function(key) % table->capacity;
    hdb_entry_t *curr = table->buckets[index];

    while(curr) {
        if (strcmp(curr->key, key) == 0) {
            curr->value = value;
            return;
        } 
        curr = curr->next;
    }

    hdb_entry_t *entry = hdb_create_entry(key, value);
    entry->next = table->buckets[index];
    table->buckets[index] = entry;
    table->size++;
}
