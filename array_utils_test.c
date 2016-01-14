#include <stdio.h>
#include <assert.h>
#include "array_utils.h"

void test_for_create() {
    Array_util array_1 = create(sizeof(char), 4);

    assert(array_1.type_size == 1);
    assert(array_1.length == 4);

    Array_util array_2 = create(sizeof(int), 5);

    assert(array_2.type_size == 4);
    assert(array_2.length == 5);

    Array_util array_3 = create(sizeof(float), 6);

    assert(array_3.type_size == 4);
    assert(array_3.length == 6);

    Array_util array_4 = create(sizeof(double), 7);

    assert(array_4.type_size == 8);
    assert(array_4.length == 7);
};

void test_for_are_equal() {
    Array_util first_array, second_array, third_array;
    first_array = create(4, 3);
    second_array = create(4, 3);
    third_array = create(4, 4);

    assert(are_equal(first_array, second_array) == 1);
    assert(are_equal(second_array,first_array) == 1);
    assert(are_equal(first_array, third_array) == 0);
    assert(are_equal(second_array, third_array) == 0);
    assert(are_equal(second_array, second_array) == 1);
    assert(are_equal(first_array, first_array) == 1);
    assert(are_equal(third_array, third_array) == 1);
};

void test_for_resize() {
    Array_util array;
    array = create(sizeof(char), 4);

    assert(array.length == 4);

    array = resize(array,5);

    assert(array.length == 5);

    array = resize(array,2);

    assert(array.length == 2);
};

void test_for_find_index() {
    Array_util array_1;
    array_1 = create(sizeof(int), 4);

    int * array = (int *)array_1.base;
    array[0] = 1;
    array[1] = 2;
    array[2] = 3;
    array[3] = 4;

    int element_1 = 2;
    int element_2 = 6;
    assert(find_index(array_1, &element_1) == 1);
    assert(find_index(array_1, &element_2) == -1);
};

void test_for_dispose() {
    Array_util array_1;
    array_1 = create(sizeof(char), 3);
    char * array = (char *)array_1.base;
    array[0] = 'A';
    array[1] = 'B';
    array[2] = 'C';
    array[3] = 'D';

    char element = 'C';
    assert(find_index(array_1, &element) == 2);

    dispose(array_1);
};

int is_even(void * hint, void * item) {
    int * number = (int *)item;
    if ( * number % 2 == 0)
        return * number;
    return 0;
};

int is_divisible(void * hint, void * item) {
    int * dividend = (int *)item;
    int * divisor = (int *)hint;
    if (* dividend % * divisor == 0)
       return * dividend;
    return 0;
};

void test_for_find_first() {
    Array_util array_1;
    array_1 = create(sizeof(int), 4);
    int * array = (int *)array_1.base;
    array[0] = 1;
    array[1] = 2;
    array[2] = 3;
    array[3] = 4;

    void * hint_1 = NULL;
    void * hint_2 = (void *)&array[1];
    int * result_1 = find_first(array_1, &is_even, hint_1);
    int * result_2 = find_first(array_1, &is_divisible, hint_2);

    assert(* result_1 == 2);
    assert(* result_2 == 2);
};

void test_for_find_last() {
    Array_util array_2;
    array_2 = create(sizeof(int), 4);
    int * array = (int *)array_2.base;
    array[0] = 1;
    array[1] = 2;
    array[2] = 3;
    array[3] = 4;

    int hint_1 = NULL;
    int hint_2 = 4;
    int * result_1 = find_last(array_2, &is_even, &hint_1);
    int * result_2 = find_last(array_2, &is_divisible, &hint_2);

    assert(* result_1 == 4);
    assert(* result_2 == 4);
};

void test_for_count() {
    Array_util array_2;
    array_2 = create(sizeof(int), 6);
    int * array = (int *)array_2.base;
    array[0] = 1;
    array[1] = 2;
    array[2] = 3;
    array[3] = 4;
    array[4] = 5;
    array[5] = 6;

    int hint_1 = NULL;
    int hint_2 = 2;
    int hint_3 = 5;
    int result_1 = count(array_2, &is_even, &hint_1);
    int result_2 = count(array_2, &is_divisible, &hint_2);
    int result_3 = count(array_2, &is_divisible, &hint_3);

    assert(result_1 == 3);
    assert(result_2 == 3);
    assert(result_3 == 1);
};

void test_for_filter() {
    Array_util source, destination;
    source = create(sizeof(int), 6);
    destination = create(sizeof(int), 3);
    int * array = (int *)source.base;
    array[0] = 1;
    array[1] = 2;
    array[2] = 3;
    array[3] = 4;
    array[4] = 5;
    array[5] = 6;

    int hint = 2;
    void ** end = (void **)destination.base;
    int result_1 = filter(source, &is_divisible, &hint, end, 3);
    int ** result_2 = (int **)end;

    assert(result_1 == 3);
    assert(*result_2[0] == 2);
    assert(*result_2[1] == 4);
    assert(*result_2[2] == 6);
    assert(destination.length == 3);
};

void add_hint(void * hint, void * source_item, void * destination_item) {
    int * source_element = (int *)source_item;
    int * destination_element = (int *)destination_item;
    int * adder = (int *)hint;
    * destination_element = * source_element + * adder;
};

void test_for_map() {
    Array_util source, destination;
    source = create(sizeof(int), 6);
    destination = create(sizeof(int), 6);
    int * array_1 = (int *)source.base;
    int * array_2 = (int *)destination.base;
    array_1[0] = 1;
    array_1[1] = 2;
    array_1[2] = 3;
    array_1[3] = 4;
    array_1[4] = 5;
    array_1[5] = 6;
    int hint = 2;

    map(source, destination, &add_hint, &hint);

    assert(array_2[0] == 3);
    assert(array_2[1] == 4);
    assert(array_2[2] == 5);
    assert(destination.length == 6);
};

void mutiply_value(void * hint, void * item) {
    int * multiplier = (int *)hint;
    *(int *)item = *(int *)item * (* multiplier);   
};

void test_for_for_each() {
    Array_util source;
    source = create(sizeof(int), 6);
    int * array_1 = (int *)source.base;
    array_1[0] = 1;
    array_1[1] = 2;
    array_1[2] = 3;
    array_1[3] = 4;
    array_1[4] = 5;
    array_1[5] = 6;
    int hint = 2;

    for_each(source, &mutiply_value, &hint);

    assert(array_1[0] == 2);
    assert(array_1[1] == 4);
    assert(array_1[2] == 6);
    assert(source.length == 6);
};

void * add_all(void * hint, void * previous_item, void * item) {
    *(int *)previous_item += *(int *)item;
    return  previous_item;
};

void test_for_reduce() {
    Array_util source;
    source = create(sizeof(int), 6);
    int * array = (int *)source.base;
    array[0] = 1;
    array[1] = 2;
    array[2] = 3;
    array[3] = 4;
    array[4] = 5;
    array[5] = 6;
    int hint = NULL;
    int initial_value = 2;

    int * result = (int *)reduce(source, &add_all, &hint, &initial_value);

    assert(* result == 23);
};