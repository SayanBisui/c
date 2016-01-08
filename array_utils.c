#include <stdio.h>
#include "array_utils.h"
#include <stdlib.h>
#include <string.h>

int are_equal(Array_util first_array, Array_util second_array) {
    int length =  first_array.length > second_array.length ? first_array.length : second_array.length;
    int mem_cmp = memcmp(first_array.base, second_array.base, length);

    if (first_array.type_size == second_array.type_size && first_array.length == second_array.length && mem_cmp == 0) {
        return 1;
    }
    return 0;
};

Array_util create(int type_size, int length) {
    Array_util array;
    array.base = calloc(length, type_size);
    array.type_size = type_size;
    array.length = length;
    return array;
};

Array_util resize(Array_util array, int length) {
    array.base = realloc(array.base, array.type_size * length);
    array.length = length;
    return array;
};

int find_index(Array_util array, void * element) {
    void * array_base = array.base;
    for (int i = 0; i < array.length; i++) {
        if (memcmp(array_base, element, array.type_size) == 0)
            return i;
          array_base += array.type_size;
    }
    return -1;
};