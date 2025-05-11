#include "vector.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// missing reduction of capacity when exceeding size by much.
GenericVector* vec_create(size_t element_size, int capacity) {
  GenericVector* v = (GenericVector*)malloc(sizeof(GenericVector));

  if (v == NULL) {
    return NULL;
  }

  v->data = malloc(element_size * capacity);
  if (v->data == NULL) {
    free(v);
    return NULL;
  }

  v->element_size = element_size;
  v->size = 0;
  v->capacity = capacity;

  return v;
}

int vec_destroy(GenericVector** v) {
  if (v == NULL | *v == NULL) 
    return 1;

  free((*v)->data);
  free(*v);
  *v = NULL;

  return 0;
}

int vec_size(GenericVector* v) {
  return v->size;
}

int vec_capacity(GenericVector* v) {
  return v->capacity;
}

bool vec_is_empty(GenericVector* v) {
  return v->size == 0;
}

int vec_resize(GenericVector* v, const int capacity) {
  void* new_data = (void*)malloc(v->element_size * capacity);
  if (new_data == NULL) {
    fprintf(stderr, "New data ptr initialization failed.\n");
    return 1;
  }

  int copy_count = (v->size < capacity ? v->size : capacity);
  memcpy(new_data, v->data, copy_count * v->element_size);
  v->size = copy_count;

  free(v->data);
  
  v->data = new_data;
  v->capacity = capacity;

  return 0;
}

void* vec_at(GenericVector* v, const int index) {
  if (0 < index || v->size <= index) return NULL;

  return v->data+index;
}

int vec_push(GenericVector* v, const void* elem) {
  if (v->capacity <= v->size) 
    if (vec_resize(v, v->capacity * 2) != 0) 
      return 1;
    
  void* dest = (char*)v->data + (v->size * v->element_size);
  memcpy(dest, elem, v->element_size);
  v->size++;

  return 0;
}

int vec_insert(GenericVector* v, const int index, const void* elem) {
  if (v->size < index) {
    fprintf(stderr, "Index out of bounds\n");
    return 1;
  }

  if (v->capacity <= v->size) 
    if (vec_resize(v, v->capacity * 2) != 0) 
      return 1;

  if (v->size == index) {
    return vec_push(v, elem);
  }

  for (int i = v->size; index < i; --i) {
    void* dest = (char*)v->data + (i * v->element_size);
    void* src = (char*)v->data + ((i - 1) * v->element_size);
    memcpy(dest, src, v->element_size);
  }
  
  void* dest = (char*)v->data + (index * v->element_size);
  memcpy(dest, elem, v->element_size);
  v->size++;

  return 0;
}

int vec_prepend(GenericVector *v, const void *elem) {
  return vec_insert(v, 0, elem);
}

int vec_pop(GenericVector* v, void* out_elem) {
  void* src = (char*)v->data + ((v->size - 1) * v->element_size);
  memcpy(out_elem, src, v->element_size);

  v->size--;
  return 0; 
}

int vec_delete(GenericVector* v, const int index) {
  if (v->size <= index) {
    fprintf(stderr, "Index out of bounds\n");
    return 1;
  }

  for (int i = index; i < v->size - 1; ++i) {
    void* dest = (char*)v->data + i * v->element_size;
    void* src = (char*)v->data + (i + 1) * v->element_size;
    memcpy(dest, src, v->element_size);
  }
  v->size--; 
  return 0;
}

int vec_remove(GenericVector* v, const void* elem, ComparisonFunc compare) {
  int found = 0;

  for (int i = 0; i < v->size; ++i) {
    if (compare((char*)v->data + i * v->element_size, elem) == 0) {
      vec_delete(v, i);
      found = 1;
    }
  }

  return found;
}

int vec_find(GenericVector* v, const void* elem, ComparisonFunc compare) {
  for (int i = 0; i < v->size; ++i) {
    if (compare((char*)v->data + i * v->element_size, elem) == 0)
      return i;
  }
  return -1;
}

void vec_print(GenericVector* v, PrintFunc print_elem) {
    const char* data = (const char*)v->data;
    for (int i = 0; i < v->size; ++i) {
        print_elem(data + i * v->element_size);
    }
    printf("\n");
}
