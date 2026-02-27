#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sea-float/test-suite.h>
#include "../../src/values/values.h"

#define EPSILON 0.00001
int test_value_create_string(void);
int test_value_create_int(void);
int test_value_create_float(void);
int test_value_create_array(void);
int test_array_push(void);
int test_array_get_basic(void);
int test_array_get_negative(void);
int test_array_get_oob(void);
int test_array_set_basic(void);
int test_array_set_negative(void);
int test_array_set_oob(void);
int test_array_remove_basic(void);
int test_array_remove_negative(void);


void test_values(void) {
    test_suite_t values_suite;
    test_suite_init(&values_suite, "Values");
    register_test(&values_suite, test_value_create_string, "value_create_string");
    register_test(&values_suite, test_value_create_int, "value_create_int");
    register_test(&values_suite, test_value_create_float, "value_create_float");
    register_test(&values_suite, test_value_create_array, "value_create_array");
    register_test(&values_suite, test_array_push, "array_push");
    register_test(&values_suite, test_array_get_basic, "array_get basic");
    register_test(&values_suite, test_array_get_negative, "array_get negative index");
    register_test(&values_suite, test_array_get_oob, "array_get out of bounds");
    register_test(&values_suite, test_array_set_basic, "array_set basic");
    register_test(&values_suite, test_array_set_negative, "array_set negative index");
    register_test(&values_suite, test_array_set_oob, "array_set out of bounds");
    register_test(&values_suite, test_array_remove_basic, "array_remove basic");
    register_test(&values_suite, test_array_remove_negative, "array_remove negative index");

    run_all_tests(&values_suite);
    test_suite_destroy(&values_suite);
}

int test_value_create_string(void) {
    char *string = "hello world";
    hdb_value_t *val = value_create_string(string);

    if (!val) {
        fprintf(stderr, "Value should not be NULL.\n");
        return 1;
    }
    if (val->type != STRING) {
        fprintf(stderr, "Value type: %s should be STRING.\n", value_type_to_string(val->type));
        return 1;
    }
    if (val->data.string.length != strlen(string)) {
        fprintf(stderr, "String length: %zu should be %lu.\n", val->data.string.length, strlen(string));
        return 1;
    }
    if (strcmp(val->data.string.buffer, string) != 0) {
        fprintf(stderr, "String: '%s' should be equal to '%s'\n", val->data.string.buffer, string);
        return 1;
    }
    
    value_free(&val);
    return 0;
}

int test_value_create_int(void) {
    int integer = 69;
    hdb_value_t *val = value_create_int(integer);

    if (val == NULL) {
        fprintf(stderr, "Value should not be NULL.\n");
        return 1;
    }
    if (val->type != INTEGER) {
        fprintf(stderr, "Value type: %s should be INTEGER.\n", value_type_to_string(val->type));
        return 1;
    }
    if (val->data.integer != integer) {
        fprintf(stderr, "Value %d should be %d.\n", val->data.integer, integer);
        return 1;
    }

    value_free(&val);
    return 0;
}

int test_value_create_float(void) {
    float floating = 3.14f;
    hdb_value_t *val = value_create_float(floating);

    if (val == NULL) {
        fprintf(stderr, "Value should not be NULL.\n");
        return 1;
    }
    if (val->type != FLOAT) {
        fprintf(stderr, "Value type: %s should be FLOAT.\n", value_type_to_string(val->type));
        return 1;
    }
    if (fabs(val->data.floating - floating) >= EPSILON) {
        fprintf(stderr, "Value %f should be %f.\n", val->data.floating, floating);
        return 1;
    }

    value_free(&val);
    return 0;
}

int test_value_create_array(void) {
    size_t initial_capacity = 4;
    hdb_value_t *array = value_create_array(initial_capacity);

    if (array == NULL) {
        fprintf(stderr, "Array value should not be NULL.\n");
        return 1;
    }
    if (array->type != ARRAY) {
        fprintf(stderr, "Value type: %s should be ARRAY.\n", value_type_to_string(array->type));
        return 1;
    }
    if (array->data.array.size != 0) {
        fprintf(stderr, "Array size should be initalised to 0. Actual: %zu.\n", array->data.array.size);
        return 1;
    }
    if (array->data.array.capacity != 4) {
        fprintf(stderr, "Array capacity should be %zu. Actual: %zu.\n", initial_capacity, array->data.array.capacity);
        return 1;
    }
    if (array->data.array.items == NULL) {
        fprintf(stderr, "Array items should be initalised to a pointer. Actual: %p.\n", array->data.array.items);
        return 1;
    }

    array = value_create_array(0);

    if (array->data.array.capacity != 4) {
        fprintf(stderr, "Array initialised with 0 should default to capacity of 4. Actual capacity: %zu.\n", array->data.array.capacity);
        return 1;
    }

    value_free(&array);
    return 0;
}

int test_array_push(void) {
    size_t initial_capacity = 4;
    hdb_value_t *array = value_create_array(initial_capacity);

    hdb_value_t *item_one = value_create_string("item_one");
    array_push(array, item_one);
    if (array->data.array.size != 1) {
        fprintf(stderr, "Array size should be 1. Actual: %zu.\n", array->data.array.size);
        return 1;
    }
    
    hdb_value_t *item_two = value_create_string("item_two");
    array_push(array, item_two);
    if (array->data.array.size != 2) {
        fprintf(stderr, "Array size should be 2. Actual: %zu.\n", array->data.array.size);
        return 1;
    }
    
    hdb_value_t *item_three = value_create_string("item_three");
    array_push(array, item_three);
    if (array->data.array.size != 3) {
        fprintf(stderr, "Array size should be 3. Actual: %zu.\n", array->data.array.size);
        return 1;
    }
    
    hdb_value_t *item_four = value_create_string("item_four");
    array_push(array, item_four);
    if (array->data.array.size != 4) {
        fprintf(stderr, "Array size should be 4. Actual: %zu.\n", array->data.array.size);
        return 1;
    }
    
    hdb_value_t *item_five = value_create_string("item_five");
    array_push(array, item_five);
    if (array->data.array.size != 5) {
        fprintf(stderr, "Array size should be 5. Actual: %zu.\n", array->data.array.size);
        return 1;
    }

    if (array->data.array.capacity != initial_capacity * 2) {
        fprintf(stderr, "Array capacity reached it's limit after last insert, it should have doubled. Initial: %zu, Actual: %zu.\n, ", initial_capacity, array->data.array.capacity);
        return 1;
    }

    value_free(&array);
    return 0;
}

int test_array_get_basic(void) {
    hdb_value_t *array = value_create_array(4);

    array_push(array, value_create_int(0));
    array_push(array, value_create_int(1));
    array_push(array, value_create_int(2));

    hdb_value_t *value = array_get(array, 1);

    if (value == NULL) {
        fprintf(stderr, "Value should not be NULL.\n");
        return 1;
    }

    if (value->data.integer != 1) {
        fprintf(stderr, "Value should be 1. Actual: %d.\n", value->data.integer);
        return 1;
    }

    value_free(&array);
    return 0;
}


int test_array_get_negative(void) {
    hdb_value_t *array = value_create_array(4);

    array_push(array, value_create_int(0));
    array_push(array, value_create_int(1));
    array_push(array, value_create_int(2));

    hdb_value_t *value = array_get(array, -1);

    if (value == NULL) {
        fprintf(stderr, "Value should not be NULL.\n");
        return 1;
    }

    if (value->data.integer != 2) {
        fprintf(stderr, "Value should be 2. Actual: %d.\n", value->data.integer);
        return 1;
    }

    value_free(&array);
    return 0;
}

int test_array_get_oob(void) {
    hdb_value_t *array = value_create_array(4);

    array_push(array, value_create_int(0));
    array_push(array, value_create_int(1));
    array_push(array, value_create_int(2));

    hdb_value_t *value = array_get(array, 4);
    hdb_value_t *negative_value = array_get(array, -4);

    if (value != NULL) {
        fprintf(stderr, "Out of bound get value should be NULL.\n");
        return 1;
    }

    if (negative_value != NULL) {
        fprintf(stderr, "Out of bound negative get value should be NULL.\n");
        return 1;
    }

    value_free(&array);
    return 0;
}


int test_array_set_basic(void) {
    hdb_value_t *array = value_create_array(4);

    array_push(array, value_create_int(0));
    array_push(array, value_create_int(1));
    array_push(array, value_create_int(2));

    array_set(array, 2, value_create_int(3));

    hdb_value_t *value = array_get(array, 2);

    if (value == NULL) {
        fprintf(stderr, "Value should not be NULL.\n");
        return 1;
    }

    if (value->data.integer != 3) {
        fprintf(stderr, "Value should be 3. Actual: %d.\n", value->data.integer);
        return 1;
    }

    value_free(&array);
    return 0;
}

int test_array_set_negative(void) {
    hdb_value_t *array = value_create_array(4);

    array_push(array, value_create_int(0));
    array_push(array, value_create_int(1));
    array_push(array, value_create_int(2));

    array_set(array, -1, value_create_int(3));

    hdb_value_t *value = array_get(array, 2);

    if (value == NULL) {
        fprintf(stderr, "Value should not be NULL.\n");
        return 1;
    }

    if (value->data.integer != 3) {
        fprintf(stderr, "Value should be 3. Actual: %d.\n", value->data.integer);
        return 1;
    }

    value_free(&array);
    return 0;
}


int test_array_set_oob(void) {
    hdb_value_t *array = value_create_array(4);

    array_push(array, value_create_int(0));
    array_push(array, value_create_int(1));
    array_push(array, value_create_int(2));

    hdb_value_t *value = array_set(array, 4, value_create_int(3));

    if (value != NULL) {
        fprintf(stderr, "Out of bound set value should be NULL.\n");
        return 1;
    }

    value_free(&array);
    value_free(&value);
    return 0;
}

int test_array_remove_basic(void) {
    hdb_value_t *array = value_create_array(4);

    array_push(array, value_create_int(0));
    array_push(array, value_create_int(1));
    array_push(array, value_create_int(2));
    array_push(array, value_create_int(3));


    hdb_value_t *invalid_array = value_create_int(5);

    hdb_value_t *invalid_value = array_remove(invalid_array, 1);

    if (invalid_value != NULL) {
        fprintf(stderr, "array_remove on non-array value. Should return NULL.\n");
        return 1;
    }

    array = array_remove(array, 1);
    if (array->data.array.size != 3) {
        fprintf(stderr, "Array size should have decreased to 3 after remove. Actual size: %zu\n", array->data.array.size);
        return 1;
    }

    hdb_value_t *oob_value = array_get(array, 3);

    if (oob_value != NULL) {
        fprintf(stderr, "Out of bound value after array remove should be NULL.\n");
        return 1;
    }
    array = array_remove(array, 1);
    array = array_remove(array, 1);

    if (array->data.array.capacity != 2) {
        fprintf(stderr, "Array capacity should have decreased to 2 after removig. Actual: %zu\n", array->data.array.capacity);
        return 1;
    }


    value_free(&array);
    return 0;
}

int test_array_remove_negative(void) {
    return 0;
}
