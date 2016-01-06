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
};

void test_for_resize() {
  Array_util array;
  array = create(1, 4);

  assert(array.length == 4);

  array = resize(array,5);

  assert(array.length == 5);

  array = resize(array,2);

  assert(array.length == 2);
};

int main(void) {
  test_for_create();
  test_for_are_equal();
  test_for_resize();
};