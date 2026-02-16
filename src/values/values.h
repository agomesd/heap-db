#ifndef VALUES_H
#define VALUES_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stddef.h>

typedef struct Entry hdb_entry_t;

enum ValueType {
    STRING,
    INTEGER,
    FLOAT,
};

typedef struct StringValue {
    size_t length;
    char *buffer;
} hdb_string_value_t;


typedef struct Value {
    enum ValueType type;
    union {
        hdb_string_value_t string;
        int integer;
        float floating;
    } data;
} hdb_value_t;


hdb_value_t *value_create_string(char *string);
hdb_value_t *value_create_int(int value);
hdb_value_t *value_create_float(float value);

#endif
