#include <stdio.h>

typedef struct {
  void * base;
  int type_size;
  int length;
} Array_util;

Array_util create (int, int);
int are_equal  (Array_util, Array_util);
Array_util resize(Array_util, int);
int find_index(Array_util array, void * element);
void dispose(Array_util);
