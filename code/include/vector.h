#ifndef VECTOR_H
#define VECTOR_H

#include <stddef.h>
#include <stdbool.h>

typedef struct {
  void* data;
  size_t element_size;
  int size;
  int capacity;
} GenericVector;

GenericVector* vec_create(size_t element_size, int capacity);

int vec_destroy(GenericVector** v);

int vec_size(GenericVector* v);

int vec_capacity(GenericVector* v);

bool vec_is_empty(GenericVector* v);

void* vec_at(GenericVector* v, const int index);

int vec_push(GenericVector* v, const void* elem);

int vec_insert(GenericVector* v, const int index, const void* elem);

int vec_prepend(GenericVector* v, const void* elem);

int vec_pop(GenericVector* v, void* out_elem);

int vec_delete(GenericVector* v, const int index);

typedef int (*ComparisonFunc)(const void*, const void*);

int vec_remove(GenericVector* v, const void* elem, ComparisonFunc);

int vec_find(GenericVector* v, const void* elem, ComparisonFunc);

int vec_resize(GenericVector* v, const int capacity);

typedef void (*PrintFunc)(const void*);

void vec_print(GenericVector* v, PrintFunc);

#endif // VECTOR_H
