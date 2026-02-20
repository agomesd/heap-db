#ifndef VALUES_H
#define VALUES_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stddef.h>

typedef struct Entry hdb_entry_t;
typedef struct Value hdb_value_t;

enum ValueType {
    STRING,
    INTEGER,
    FLOAT,
    ARRAY
};

typedef struct StringValue {
    size_t length;
    char *buffer;
} hdb_string_value_t;


typedef struct Array {
    size_t size;
    size_t capacity;
    hdb_value_t **items;
} hdb_array_t;

typedef struct Value {
    enum ValueType type;
    union {
        hdb_string_value_t string;
        int integer;
        float floating;
        hdb_array_t array;
    } data;
} hdb_value_t;



hdb_value_t *value_create_string(char *string);
hdb_value_t *value_create_int(int value);
hdb_value_t *value_create_float(float value);
hdb_value_t *value_create_array(size_t initial_capacity);
hdb_value_t *array_push(hdb_value_t *array_value, hdb_value_t *item);
hdb_value_t *array_set(hdb_value_t *array_value, int index, hdb_value_t *item);
hdb_value_t *array_get(hdb_value_t *array_value, int index);
void value_free(hdb_value_t *value);

#endif
