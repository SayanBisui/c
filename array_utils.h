#include <stdio.h>

typedef struct {
  void * base;
  int type_size;
  int length;
} Array_util;
typedef int Match_function(void *, void *);
typedef void Convert_function(void *, void *, void *);

Array_util create (int, int);
int are_equal  (Array_util, Array_util);
Array_util resize(Array_util, int);
int find_index(Array_util array, void * element);
void dispose(Array_util);
void * find_first(Array_util, Match_function *, void *);
void * find_last(Array_util, Match_function *, void *);
int count(Array_util, Match_function *, void *);
int filter(Array_util, Match_function *, void *, void **, int);
void map(Array_util, Array_util, Convert_function *, void *);