#ifndef LISTS_H
#define LISTS_H

#include "utils.h"

#define array_header(array) \
    size_t element_size = array[0];\
    (array_header_t *)( ((char *) array) - (element_size > sizeof(size_t) ? element_size - sizeof(size_t) : 0)) - 1

#define Array(self, T, length) (T*)init_array(self, sizeof(T), length, 0)

typedef struct array_header{
    size_t length;
    size_t count;
    void *self; //for referecing itself on the stack
} array_header_t;

void *init_array(void *self, size_t element_size, size_t length, size_t count);
void append(void *array, void *value);
void pop(void *array, size_t index);

#endif
