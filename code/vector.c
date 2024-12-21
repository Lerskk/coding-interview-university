#include <stdio.h>
#include <stdlib.h>

typedef struct {
  int* data;
  size_t size;
  size_t capacity;
} Vector;

Vector* create_vector() {
  Vector* vector = (Vector*)malloc(sizeof(Vector));
  vector->data = NULL;
  vector->size = 0;
  vector->capacity = 0;
  return vector;
}

void push(Vector* vector, int element) {
  if (vector->data == NULL) {
    vector->data = (int*)malloc(sizeof(int));
    vector->capacity = 1;
  } 
  else if (vector->capacity <= vector->size) {
    vector->capacity *= 2;
    vector->data = (int*)realloc(vector->data, sizeof(int) * vector->capacity);
  }

  *(vector->data + vector->size) = element;
  vector->size++;
}

size_t size(Vector* vector) {
  return vector->size;
}

int is_empty(Vector* vector) {
  return vector->size == 0;
}

void delete_vector(Vector* vector) {
  free(vector->data);
  free(vector);
}

int at(Vector* vector, int index) {
  if (index < 0 || vector->size - 1 < index) return -1;
  return *(vector->data + index);
}

void print_vector(Vector* vector) {
  printf("%s", "Vector: ");
  for (int i = 0; i < vector->size; i++) {
    printf("%d ", *(vector->data + i));
  }
  printf("%c", '\n');
}

int shift(Vector* vector, int index, int shiftRight) {
  if (vector->size <= index ) {
    printf("Index out of bounds\n");
    return -1;
  }

  if (shiftRight && vector->capacity <= vector->size) {
    vector->capacity *= 2;
    vector->data = (int*)realloc(vector->data, sizeof(int) * vector->capacity);
  }

  if (shiftRight) {
    for (int i = vector->size; index < i; i--) {
      *(vector->data + i) = *(vector->data + i - 1); 
    }
    return 0;
  }

  if (vector->capacity <= 1 / 3 * vector->size) {
    vector->capacity /= 2;
    vector->data = (int*)realloc(vector->data, sizeof(int) * vector->capacity);
  }

  for (int i = index; i < vector->size; i++) {
    *(vector->data + i) = *(vector->data + i + 1); 
  }
  return 0;
}

int find_element(Vector* vector, int find) {
  for (int i = 0; i < vector->size; i++) {
    if (*(vector->data + i) == find) {
      return i;
    }
  }
  return -1;
}

void delete(Vector* vector, int index) {
  int failed = shift(vector, index, 0);

  if (!failed)
    vector->size--;
}

void remove_element(Vector* vector, int find) {
  int index = find_element(vector, find);
  while(index != -1) {
    delete(vector, index);
    vector->size--;
    index = find_element(vector, find);
  }
}

void insert(Vector* vector, int index, int element) {

  int failed = shift(vector, index, 1);

  if (!failed) {
    *(vector->data + index) = element;
    vector->size++;
  }
}

void prepend(Vector* vector, int element) {
  insert(vector, 0, element);
}

int pop(Vector* vector) {
  if (vector->size == 0) {
    printf("No elements to pop D:\n");
    fprintf(stderr, "Poping empty vector. Exiting...\n"); 
    exit(EXIT_FAILURE);
  }
  vector->size--;
  return *(vector->data + vector->size);
}

int main() {
  Vector* vec = create_vector();

  push(vec, 1);
  push(vec, 2);
  push(vec, 3);

  insert(vec, 2, 4);
  print_vector(vec);
  push(vec, 2);
  print_vector(vec);
  remove_element(vec, 2);
  print_vector(vec);
  remove_element(vec, 3);
  printf("%d %d\n", find_element(vec, 2), find_element(vec, 1));
  printf("%zu %zu", vec->size, vec->capacity);

  delete_vector(vec);
}
