#include "values.h"

hdb_value_t *value_create_string(char *input_string) {
    size_t len = strlen(input_string);
    hdb_value_t *value = malloc(sizeof(hdb_value_t));
    if(!value) return NULL;

    char *buffer = malloc(len + 1);
    if(!buffer) {
        free(value);
        return NULL;
    }

    strcpy(buffer, input_string);

    value->data.string.buffer = buffer;
    value->data.string.length = len;
    value->type = STRING;
    return value;
}

hdb_value_t *value_create_int(int input_int) {
    hdb_value_t *value = malloc(sizeof(hdb_value_t));
    if (!value) return NULL;

    value->type = INTEGER;
    value->data.integer = input_int;

    return value;
}

hdb_value_t *value_create_float(float input_float) {
    hdb_value_t *value = malloc(sizeof(hdb_value_t));
    if (!value) return NULL;

    value->type = FLOAT;
    value->data.floating = input_float;

    return value;
}
