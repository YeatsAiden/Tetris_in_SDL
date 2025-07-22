#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>

/* Checks how many times a string can be found within another string */
size_t times_found(char *string, char *query){
    size_t count = 0;

    char *temp = string;

    while((temp = strstr(temp, query)) != NULL){
        count++;
        temp += strlen(query);
    }

    return count;
}
