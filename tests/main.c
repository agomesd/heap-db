#include <stdio.h>
#include "utils/test_utils.h"
#include "values/test_values.h"
#include "hashtable/test_hashtable.h"

int main() {
    test_value_create_string();
    test_value_create_int();
    test_value_create_float();
    test_hash_function();
    test_hdb_create_entry();
    test_hdb_create_table();
    test_hdb_crud();
    printf("All tests passed!\n");
    return 0;
}
