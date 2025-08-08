#include <stdlib.h>
#include "lists.h"

void *init_array(void *self, size_t element_size, size_t length, size_t count){
    array_header_t *header = malloc(sizeof(array_header_t) + length * element_size);

    if (header == NULL) return NULL;

    header->count = count;
    header->length = length;
    header->self = self;

    return next_aligned_pointer((void *)(header + 1), element_size);
}

void append(void *array, void *value){
    // aaaggghh pointer arithmetic :sob:
    array_header_t *array_header = array_header(array);
    size_t count = array_header->count;
    size_t length = array_header->length;

    if (count == length){
        void *new_array = init_array(length * 2, count);

        memcpy(new_array, array, length * sizeof(array[0]));

        array->self = new_array;
        free(array_header);
    }

    array[count] = value;
    array_header(array)->count++;
}

void pop(void *array, size_t index){
    array_header_t *array_header = ((array_header_t *) array - 1);
    size_t count = array_header->count;
    size_t length = array_header->length;

    if (index > count || index < -count){
        fprintf(stderr, "Index out of range: %ld\n", index);
        return;
    }

    if (index < 0) index = count + index;

    memcpy(void *restrict dest, const void *restrict src, size_t n)

    array_header->count--;
}

int array = Array(&array, int, 10);


for (int i=0;i<20;i++){
    append(array, i);
}
