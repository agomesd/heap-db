#include <assert.h>
#include <stdio.h>
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

    free(val->data.string.buffer);
    free(val);
}

void test_value_create_int(void) {
    int integer = 69;
    hdb_value_t *val = value_create_int(integer);

    assert(val != NULL);
    assert(val->type == INTEGER);
    assert(val->data.integer == integer);

    free(val);
}

void test_value_create_float(void) {
    float floating = 3.14f;
    hdb_value_t *val = value_create_float(floating);

    assert(val != NULL);
    assert(val->type == FLOAT);
    assert(fabs(val->data.floating - floating) < EPSILON);

    free(val);
}

