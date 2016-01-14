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

void dispose(Array_util array) {
    free(array.base);
};

void * find_first(Array_util array,Match_function * match, void * hint) {
   int * elements = array.base;
   for (int i = 0; i < array.length; i++) {
       if (match(hint, &elements[i]))
           return &elements[i];
   }
   return NULL;
};

void * find_last(Array_util array, Match_function * match, void * hint) {
   int * elements = array.base;
   for (int i = array.length; i > 0; i--) {
       if (match(hint, &elements[i]))
           return &elements[i];
   }
   return NULL;
};

int count(Array_util array, Match_function * match, void * hint) {
    int * elements = array.base;
    int count = 0;
    for (int i = array.length; i > 0; i--) {
        if (match(hint,&elements[i]))
           count++;
    }
    return count;
};

int filter(Array_util array, Match_function * match, void * hint, void ** destination, int max_items) {
    int * elements = array.base;
    int count = 0;
    for (int i = 0; i < array.length; i++) {
        if (match(hint, &elements[i]) && count < max_items) {
            destination[count] = &elements[i];
            count++;
        }
    }
    return count;
};

void map(Array_util source, Array_util destination, Convert_function * convert, void * hint) {
    int * elements = source.base;
    int * array = destination.base;
    for (int i = 0; i < source.length; i++) {
        convert(hint, &elements[i], &array[i]);
    }
};

void for_each(Array_util source, Operation_function * operation, void * hint) {
    void * elements = source.base;
    for (int i = 0; i < source.length; i++) {
        operation(hint, elements);
        elements += source.type_size;
    }
};

void * reduce(Array_util array, Reducer_function * reducer, void * hint, void * intial_value) {
    void * elements = array.base;
    for (int i = 0; i < array.length; i++) {
        intial_value = reducer(hint, intial_value, elements);
        elements += array.type_size;
    }
    return intial_value;
};
