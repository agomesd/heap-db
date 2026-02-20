#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "../../src/values/values.h"

#define EPSILON 0.00001

void test_value_create_string(void) {
    char *string = "hello world";
    hdb_value_t *val = value_create_string(string);

    assert(val != NULL);
    assert(val->type == STRING);
    assert(val->data.string.length == strlen(string));
    assert(strcmp(val->data.string.buffer, string) == 0);

    value_free(val);
}

void test_value_create_int(void) {
    int integer = 69;
    hdb_value_t *val = value_create_int(integer);

    assert(val != NULL);
    assert(val->type == INTEGER);
    assert(val->data.integer == integer);

    value_free(val);
}

void test_value_create_float(void) {
    float floating = 3.14f;
    hdb_value_t *val = value_create_float(floating);

    assert(val != NULL);
    assert(val->type == FLOAT);
    assert(fabs(val->data.floating - floating) < EPSILON);

    value_free(val);
}

void test_value_create_array(void) {
    hdb_value_t *array = value_create_array(8);

    assert(array->type == ARRAY);
    assert(array->data.array.size == 0);
    assert(array->data.array.capacity == 8);
    assert(array->data.array.items != NULL);

    value_free(array);
}

void test_array_push(void) {
    hdb_value_t *array_value = value_create_array(4);
    assert(array_value->data.array.size == 0);

    char *item_one_str = "item_one";
    hdb_value_t *item_one = value_create_string(item_one_str);
    array_push(array_value, item_one);
    assert(array_value->data.array.size == 1);

    char *item_two_str = "item_two";
    hdb_value_t *item_two = value_create_string(item_two_str);
    array_push(array_value, item_two);
    assert(array_value->data.array.size == 2);

    char *item_three_str = "item_three";
    hdb_value_t *item_three = value_create_string(item_three_str);
    array_push(array_value, item_three);
    assert(array_value->data.array.size == 3);

    char *item_four_str = "item_four";
    hdb_value_t *item_four = value_create_string(item_four_str);
    array_push(array_value, item_four);
    assert(array_value->data.array.size == 4);

    char *item_five_str = "item_five";
    hdb_value_t *item_five = value_create_string(item_five_str);
    array_push(array_value, item_five);
    assert(array_value->data.array.size == 5);

    assert(array_value->data.array.capacity == 8);
    value_free(array_value);
}

void test_array_set_get(void) {
    hdb_value_t *item_one = value_create_string("item_one");
    hdb_value_t *item_two = value_create_string("item_two");
    hdb_value_t *item_three = value_create_string("item_three");
    hdb_value_t *array = value_create_array(4);

    array_push(array, item_one);
    array_push(array, item_two);
    array_push(array, item_three);

    hdb_value_t *get_item_two = array_get(array, 1);
    assert(get_item_two != NULL);
    assert(strcmp(get_item_two->data.string.buffer, item_two->data.string.buffer) == 0);

    hdb_value_t *test_value = value_create_string("test_value");
    array_set(array, 1, test_value);
    hdb_value_t *get_test_value = array_get(array, 1);
     assert(strcmp(get_test_value->data.string.buffer, test_value->data.string.buffer) == 0);

    value_free(array);
}

