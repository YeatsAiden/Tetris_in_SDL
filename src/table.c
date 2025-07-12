#include <stdlib.h>
#include <string.h>
#include "table.h"

typedef struct entry{
    char *key;
    void *value;
    struct entry *next;
} entry_t;

typedef struct {
    entry_t **entries;
    unsigned int count;
    unsigned int length;
    unsigned int (*hash_function)(char *key);
} hash_table_t;

unsigned int jenkins_one_at_a_time_hash(char *key){
    unsigned int hash = 0;
    for (int i=0;i<strlen(key);i++){
        hash += key[i];
        hash += hash << 10;
        hash ^= hash >> 6;
    }
    hash += hash << 3;
    hash ^= hash >> 11;
    hash += hash << 15;
    return hash;
}

hash_table_t *init_hashtable(unsigned int (*hash_function)(char *key), unsigned int length){
    hash_table_t *ht = malloc(sizeof(hash_table_t));

    ht->entries = calloc(length, sizeof(entry_t*));
    ht->count = 0;
    ht->length = length;
    ht->hash_function = hash_function;

    return ht;
}

unsigned int hash(hash_table_t *ht, char *key){
    return ht->hash_function(key) % ht->length;
}

entry_t *pair_value(char *key, void *value, unsigned int value_size){
    entry_t *entry = malloc(sizeof(entry_t));

    entry->key = malloc(strlen(key) + 1); /* +1 because of the null terminator */
    entry->value = malloc(value_size);

    strcpy(entry->key, key);
    memcpy(entry->value, value, value_size);

    entry->next = NULL;

    return entry;
}

void set_value(hash_table_t *ht, char *key, void *value, unsigned int value_size){
    unsigned int index = hash(ht, key);

    entry_t *entry = ht->entries[index];

    if (entry == NULL){
        ht->entries[index] = pair_value(key, value, value_size);
        return;
    }

    if (strcmp(key, entry->key) == 0){
        free(entry->value);
        entry->value = malloc(value_size);
        memcpy(entry->value, value, value_size);
        return;
    }

    entry_t *prev_entry;

    while (entry != NULL) {
        prev_entry = entry;
        entry = entry->next;
    }

    prev_entry->next = pair_value(key, value, value_size);
}

void *get_value(hash_table_t *ht, char *key){
    unsigned int index = hash(ht, key);

    entry_t *entry = ht->entries[index];

    if (entry != NULL ){
        return NULL;
    }

    entry_t *prev_entry;

    while (entry){
        if (strcmp(key, entry->key) == 0){
            return entry->value;
        }

        prev_entry = entry;
        entry = entry->next;
    }

    return NULL;
}
