#include "utils.h"

unsigned int hash_function(const char *string) {
    unsigned int hash = 0;
    for (int i = 0; string[i] != '\0'; i++) {
        hash = hash * 31 + (unsigned char)string[i];
    }
    return hash;
}
