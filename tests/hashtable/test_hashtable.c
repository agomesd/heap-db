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

void test_hdb_crud(void) {
    const char *key = "test";
    hdb_hashtable_t *hashtable = hdb_create_hashtable(8);
    hdb_value_t *value = value_create_string("moose");
    hdb_insert(hashtable, key, value);

    assert(hashtable->size == 1);

    hdb_value_t *get_value = hdb_get(hashtable, key);

    assert(get_value->type == STRING);
    assert(strcmp(get_value->data.string.buffer, value->data.string.buffer) == 0);

    const char *key_int = "test_int";
    hdb_value_t *value_int = value_create_int(69);
    hdb_insert(hashtable, key_int, value_int);

    assert(hashtable->size == 2);
    
    hdb_value_t *get_value_int = hdb_get(hashtable, key_int);
    assert(get_value_int->type == INTEGER);
    assert(get_value_int->data.integer == 69);

    hdb_value_t *new_int_value = value_create_int(5);

    hdb_insert(hashtable, key_int, new_int_value);
    assert(hashtable->size = 2);
    get_value_int = hdb_get(hashtable, key_int);
    
    assert(get_value_int->data.integer == 5);

    int remove_success = hdb_remove(hashtable, key_int);
    assert(hashtable->size = 1);
    assert(remove_success == 1);

    int remove_failed = hdb_remove(hashtable, "no_key");
    assert(remove_failed == 0);

    free(hashtable);
    free(value);
}
