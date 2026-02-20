#include <string.h>
#include "hashtable.h"
#include "../values/values.h"
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
    unsigned int index = hash_function(key) % table->capacity;
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
    if ((float)table->size / (float)table->capacity >= 0.75) {
        hdb_resize_hashtable(table, table->capacity * 2);
    }
}

hdb_value_t *hdb_get(hdb_hashtable_t *table, const char *key) {
    unsigned int index =  hash_function(key) % table->capacity;
    hdb_entry_t *curr = table->buckets[index];

    while (curr) {
        if (strcmp(curr->key, key) == 0) {
            return curr->value;
        }
        curr = curr->next;
    }

    return NULL;
}

int hdb_remove(hdb_hashtable_t *table, const char *key) {
    size_t index = hash_function(key) % table->capacity;
    hdb_entry_t *curr = table->buckets[index];
    hdb_entry_t *prev = NULL;

    while (curr) {
        if (strcmp(curr->key, key) == 0) {
            value_free(curr->value);
            if (!prev) {
                table->buckets[index] = curr->next;
            } else {
                prev->next = curr->next;
            }
            free(curr);
            table->size--;
            return 1;
        }

        prev = curr;
        curr = curr->next;
    }
    return 0;
}


void hdb_destroy_hashtable(hdb_hashtable_t *table) {
    for (size_t i = 0; i < table->capacity; i++) {
        hdb_entry_t *curr = table->buckets[i];
        while (curr) {
            hdb_entry_t *next = curr->next;
            value_free(curr->value);
            free(curr);
            curr = next;
        }
    }
    free(table->buckets);
    free(table);
}

void hdb_resize_hashtable(hdb_hashtable_t *table, size_t new_capacity) {
    hdb_entry_t **new_buckets = malloc(new_capacity * sizeof(hdb_entry_t *));
    if (!new_buckets) return;
    for (size_t i = 0; i < new_capacity; i++) {
        new_buckets[i] = NULL;
    }
    
    for (size_t i = 0; i < table->capacity; i++) {
        hdb_entry_t *curr = table->buckets[i];
        while (curr) {
            hdb_entry_t *next = curr->next;

            unsigned int index = hash_function(curr->key) % new_capacity;
            curr->next = new_buckets[index];
            new_buckets[index] = curr;
            
            curr = next;
        }
    }

    free(table->buckets);
    table->buckets = new_buckets;
    table->capacity = new_capacity;
}
