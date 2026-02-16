#include <stdio.h>
#include <assert.h>
#include "../../src/utils/utils.h"

void test_hash_function(void) {
    char *key = "moose";
    unsigned int val = hash_function(key);

    assert(val == 104080927);

}
