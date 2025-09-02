#include <stdlib.h>
#include <string.h>
#include "list.h"

void *init_array(void *self, int element_size, int element_alignment, int length, int count){
    // We add element_alignment for some extra space when calculating the next aligned pointer for the array
    ArrayHeader *header = malloc(sizeof(ArrayHeader) + length * element_size + element_alignment);

    if (header == NULL) return NULL;

    header->count = count;
    header->length = length;
    header->element_size = element_size;
    header->element_alignment = element_alignment;
    header->self = self;

    return header;
}

void append(ArrayHeader *header, void *element){
    int count = header->count;
    int length = header->length;
    int element_size = header->element_size;
    void *arr_ptr = Array_Pointer(header);

    if (count == length){
        ArrayHeader *new_header = init_array(header->self, element_size, header->element_alignment, length * 2, count);

        memcpy(Array_Pointer(new_header), arr_ptr, length * element_size);

        *header->self = new_header;
        free(header);
        header = new_header;
    }

    arr_ptr = Array_Pointer(header);

    memcpy((char *)arr_ptr + (count * element_size), element, element_size);
    header->count++;
}

void pop(ArrayHeader *header, int index){
    int count = header->count;
    int element_size = header->element_size;
    void *arr_ptr = Array_Pointer(header);

    if (index >= count || -index >= count){
        fprintf(stderr, "Index out of range: %d, and count: %d\n", index, count);
        return;
    }

    if (index < 0) index = count + index;

    if (index == count - 1){
        char *element_to_delete = (char *)arr_ptr + (index * element_size);
        memcpy(element_to_delete, element_to_delete + 1, (count - index + 1) * element_size);
    }

    header->count--;
}

int compare

int includes(ArrayHeader *header, void *element){
    int count = header->count;
    int element_size = header->element_size;
    void *arr_ptr = Array_Pointer(header);
    
    for (int i=0;i<count;i++){
        if ( memcmp(((char *)arr_ptr) + (i * element_size), element, element_size) == 0) return 1;
    }

    return 0;
}

int find_first(ArrayHeader *header, void *element){
    int count = header->count;
    int element_size = header->element_size;
    void *arr_ptr = Array_Pointer(header);
    
    for (int i=0;i<count;i++){
        if ( memcmp(((char *)arr_ptr) + (i * element_size), element, element_size) == 0) return i;
    }

    return 0;
}

void reset_array(ArrayHeader *header){
    header->count = 0;
}
