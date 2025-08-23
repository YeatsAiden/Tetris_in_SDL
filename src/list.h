#ifndef LISTS_H
#define LISTS_H

#include "utils.h"

#define Init_Array_Header(self, T, length) init_array(self, sizeof(T), alignof(T), length, 0)

#define Array_Pointer(header) next_aligned_pointer(header + 1, header->element_alignment)

#define Array(header, T) ((T *)next_aligned_pointer(header + 1, header->element_alignment))

typedef struct array_header{
    int length;
    int count;
    int element_size;
    int element_alignment; // for finding the array
    struct array_header **self; // for referecing itself on the stack
} array_header_t;

void *init_array(void *self, int element_size, int element_alignment, int length, int count);
void append(array_header_t *header, void *element);
void pop(array_header_t *array, int index);
int includes(array_header_t *header, void *element);
void reset_array(array_header_t *header);

#endif
