#ifndef ARRAY_H
#define ARRAY_H

typedef struct Array {
    int* arr;
    int n;
} Array;

Array* make_array(int n);
void resize_array(Array* arr, int n );
void free_array(Array* arr);

void print_array(Array* arr);
void fill_array(Array* arr, int v);
void reverse_array(Array* arr);

#endif