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

    hdb_destroy_hashtable(hashtable);

    hdb_hashtable_t *new_hashtable = hdb_create_hashtable(0);

    assert(hashtable != NULL);
    assert(hashtable->capacity == 8);
    assert(hashtable->size == 0);

    hdb_destroy_hashtable(new_hashtable);
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

    hdb_destroy_hashtable(hashtable);
}

void test_hdb_insert_auto_resize(void) {
    hdb_hashtable_t *hashtable = hdb_create_hashtable(4);

    assert(hashtable != NULL);
    assert(hashtable->capacity == 4);

    hdb_value_t *valueone = value_create_string("one");
    hdb_value_t *valuetwo = value_create_string("two");
    hdb_value_t *valuethree = value_create_string("three");
    const char *keyone = "one";
    const char *keytwo = "two";
    const char *keythree = "three";
    hdb_insert(hashtable, keyone, valueone);
    hdb_insert(hashtable, keytwo, valuetwo);
    hdb_insert(hashtable, keythree, valuethree);

    assert(hashtable->capacity == 8);
    assert(hashtable->size == 3);

    assert(hdb_get(hashtable, "one") != NULL);
    assert(hdb_get(hashtable, "two") != NULL);
    assert(hdb_get(hashtable, "three") != NULL);


    hdb_destroy_hashtable(hashtable);
}


void test_hdb_destroy_hashtable(void) {
    hdb_hashtable_t *hashtable = hdb_create_hashtable(8);

    assert(hashtable != NULL);
    assert(hashtable->capacity == 8);

    hdb_destroy_hashtable(hashtable);
}

void test_hdb_resize_hashtable(void) {
    hdb_hashtable_t *hashtable = hdb_create_hashtable(4);
    assert(hashtable->capacity == 4);
    hdb_resize_hashtable(hashtable, 10);

    assert(hashtable->capacity == 10);

    hdb_destroy_hashtable(hashtable);
}
