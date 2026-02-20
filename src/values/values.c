#include "values.h"
#include <stdlib.h>

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

hdb_value_t *value_create_array(size_t initial_capacity) {
    if (initial_capacity == 0) {
        initial_capacity = 4;
    }
    hdb_value_t *value = malloc(sizeof(hdb_value_t));
    if (!value) return NULL;


    value->type = ARRAY;
    value->data.array.size = 0;
    value->data.array.capacity = initial_capacity;

    hdb_value_t **items = malloc(initial_capacity * sizeof(hdb_value_t *));
    if (!items) {
        free(value);
        return NULL;
    }

    value->data.array.items = items;

    return value;
}

void value_free(hdb_value_t *value) {
    if (!value) return;

    switch(value->type) {
        case STRING: {
            free(value->data.string.buffer);
            break;
        }
        case ARRAY: {
            for (size_t i = 0; i < value->data.array.size; i++) {
                value_free(value->data.array.items[i]);
            }
            free(value->data.array.items);
            value->data.array.items = NULL;
            break;
        }
        case INTEGER:
        case FLOAT:
            break;
    }

    free(value);
};

hdb_value_t *array_push(hdb_value_t *array_value, hdb_value_t *item) {
    if (!array_value || array_value->type != ARRAY) return NULL;

    if (array_value->data.array.size == array_value->data.array.capacity) {
        size_t new_capacity = array_value->data.array.capacity == 0 ? 4 : array_value->data.array.capacity * 2;
        
        hdb_value_t **new_items = realloc(array_value->data.array.items, new_capacity * sizeof(hdb_value_t*));
        if(!new_items) return NULL;

        array_value->data.array.items = new_items;
        array_value->data.array.capacity = new_capacity;
    }
    array_value->data.array.items[array_value->data.array.size] = item;
    array_value->data.array.size++;

    return array_value;
}


hdb_value_t *array_set(hdb_value_t *array_value, int index, hdb_value_t *item) {
    if (!array_value || array_value->type != ARRAY) return NULL;
    if ((size_t)abs(index) > array_value->data.array.size - 1) return NULL;

    int comp_index = index < 0 ? array_value->data.array.size + index : index;

    hdb_value_t *old_value = array_value->data.array.items[comp_index];
    value_free(old_value);
    array_value->data.array.items[comp_index] = item;

    return array_value;
}

hdb_value_t *array_get(hdb_value_t *array_value, int index) {
    if (!array_value || array_value->type != ARRAY) return NULL;

    int comp_index = index < 0 ? array_value->data.array.size + index : index;
    if (comp_index >= 0 && (size_t)comp_index < array_value->data.array.size) {
        return array_value->data.array.items[comp_index];
    }
    return NULL;
}
