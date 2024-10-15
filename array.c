#include "array.h"
#include <stdio.h>
#include <stdlib.h>

Array *make_array(int n) {
  Array *array = calloc(1, sizeof(Array));
  array->arr = calloc(n, sizeof(int));
  array->n = n;
  return array;
}

void resize_array(Array *array, int n) {
  array->arr = realloc(array->arr, sizeof(int) * n);
  array->n = n;
}

void free_array(Array *array) {
  free(array->arr);
  free(array);
}

// Print an array
void print_array(Array *arr) {
  for (int i = 0; i < arr->n; i++) {
    printf("%2d ", arr->arr[i]);
  }
  printf("\n");
}

// Helper function for initializing an array
void fill_array(Array *arr, int v) {
  for (int i = 0; i < arr->n; i++) {
    arr->arr[i] = v;
  }
}

void reverse_array(Array *arr) {
  int start = 0;
  int end = arr->n - 1;
  while (start < end) {
    int temp = arr->arr[start];
    arr->arr[start] = arr->arr[end];
    arr->arr[end] = temp;
    start++;
    end--;
  }
}
