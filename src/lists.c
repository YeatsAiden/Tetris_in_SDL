#include <stdlib.h>
#include <string.h>
#include "lists.h"
#include "utils.h"

void *init_array(void *self, size_t element_size, size_t element_alignment, size_t length, size_t count){
    // We add element_alignment for some extra space when calculating the next aligned pointer for the array
    array_header_t *header = malloc(sizeof(array_header_t) + length * element_size + element_alignment);

    if (header == NULL) return NULL;

    header->count = count;
    header->length = length;
    header->element_size = element_size;
    header->element_alignment = element_alignment;
    header->self = self;

    return header;
}

void append(array_header_t *header, void *element){
    size_t count = header->count;
    size_t length = header->length;
    size_t element_size = header->element_size;
    void *arr_ptr = array_pointer(header);

    if (count == length){
        array_header_t *new_header = init_array(header->self, element_size, header->element_alignment, length * 2, count);

        memcpy(array_pointer(new_header), arr_ptr, length * element_size);

        *header->self = new_header;
        free(header);
        header = new_header;
    }

    arr_ptr = array_pointer(header);

    memcpy((char *)arr_ptr + (count * element_size), element, element_size);
}

void pop(array_header_t *header, size_t index){
    size_t count = header->count;
    size_t length = header->length;
    size_t element_size = header->element_size;
    void *arr_ptr = array_pointer(header);

    if (index > count || index < -count){
        fprintf(stderr, "Index out of range: %ld\n", index);
        return;
    }

    if (index < 0) index = count + index;

    if (index == count - 1){
        char *element_to_delete = (char *)arr_ptr + (index * element_size);
        memcpy(element_to_delete, element_to_delete + 1, (count - index + 1) * element_size);
    }

    header->count--;
}
