#include "vector.h"
#include <stdio.h>

void print_int(const void* elem) {
  printf("%d ", *(const int*)elem);
}

int compare_int(const void* a, const void* b) {
  int int_a = *(int*)a; 
  int int_b = *(int*)b;

  return int_a - int_b;
}

int main() {
  GenericVector* v = vec_create(sizeof(int), 4);

  int a = 2, b = 3, c = 1;
  vec_insert(v, 0, &b);
  vec_print(v, print_int);

  vec_push(v, &a);
  vec_print(v, print_int);

  vec_insert(v, 1, &c);
  vec_print(v, print_int);

  vec_prepend(v, &c);
  vec_print(v, print_int);

  int h;
  vec_pop(v,&h);
  printf("%d\n", h);
  vec_print(v, print_int);

  int index = vec_find(v, &b, compare_int);
  if (index >= 0) 
    printf("Element found at position: %d\n", index);
  else 
    printf("Element was not found\n");

  vec_remove(v, &a, compare_int);
  vec_print(v, print_int);

  printf("%p\n", v);
  vec_destroy(&v);
  printf("%p\n", v);

  return 1;
}
