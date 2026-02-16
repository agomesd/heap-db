#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "test_hashtable.h"
#include "../../src/hashtable/hashtable.h"
#include "../../src/values/values.h"

void test_hdb_create_table(void) {
    hdb_hashtable_t *hashtable = hdb_create_hashtable(5);

    assert(hashtable != NULL);
    assert(hashtable->capacity == 5);
    assert(hashtable->size == 0);

    for (size_t i = 0; i < hashtable->capacity; i++) {
        assert(hashtable->buckets[i] == NULL);
    }

    free(hashtable);

    hdb_hashtable_t *new_hashtable = hdb_create_hashtable(0);

    assert(hashtable != NULL);
    assert(hashtable->capacity == 8);
    assert(hashtable->size == 0);

    free(new_hashtable);
}

void test_hdb_create_entry(void) {
    const char *key = "test";
    hdb_value_t *value = value_create_string("moose");
    hdb_entry_t *entry = hdb_create_entry(key, value);

    assert(entry != NULL);
    assert(strcmp(entry->key, key) == 0);
    assert(entry->value->type == value->type);
    assert(entry->value->data.string.buffer == value->data.string.buffer);
    assert(entry->next == NULL);

    free(value);
    free(entry);
}

void test_hdb_insert(void) {
    hdb_hashtable_t *hashtable = hdb_create_hashtable(8);
    hdb_value_t *value= value_create_string("moose");
    hdb_insert(hashtable, "test", value);
}
