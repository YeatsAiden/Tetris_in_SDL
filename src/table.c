#include <stdlib.h>
#include <string.h>
#include <SDL2/SDL.h>
#include "table.h"

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

unsigned int hash(hash_table_t *ht, char *key){
    return ht->hash_function(key) % ht->length;
}

void free_value(entry_t *entry){
    switch (entry->type) { 
        case SURFACE:
            SDL_FreeSurface(entry->value);
        break;
        case TEXTURE:
            SDL_DestroyTexture(entry->value);
        break;
        case OTHER:
            free(entry->value);
        break;
    }
}

void free_entry(entry_t *entry){
    free(entry->key);
    free_value(entry);
    
    while (entry)
}

void set_value(entry_t *entry, void *value, unsigned int value_size){
    entry->value = malloc(value_size);
    memcpy(entry->value, value, value_size);
}

void set_key(entry_t *entry, char *key){
    entry->key = malloc(strlen(key) + 1); /* +1 because of the null terminator */
    strcpy(entry->key, key);
}

entry_t *pair_value(char *key, void *value, unsigned int value_size, Value_type type){
    entry_t *entry = malloc(sizeof(entry_t));

    set_key(entry, key);
    set_value(entry, value, value_size);
    entry->next = NULL;
    entry->type = type;

    return entry;
}

void insert(hash_table_t *ht, char *key, void *value, unsigned int value_size, Value_type type){
    unsigned int index = hash(ht, key);

    entry_t *entry = ht->entries[index];

    if (entry == NULL){
        ht->entries[index] = pair_value(key, value, value_size, type);
        return;
    }

    entry_t *prev_entry;

    while (entry != NULL) {
        if (strcmp(key, entry->key) == 0){
            free_value(entry);
            set_value(entry, value, value_size);
            return;
        }
        prev_entry = entry;
        entry = entry->next;
    }

    prev_entry->next = pair_value(key, value, value_size, type);
}

void *get(hash_table_t *ht, char *key){
    unsigned int index = hash(ht, key);

    entry_t *entry = ht->entries[index];

    if (entry == NULL){
        return NULL;
    }

    entry_t *prev_entry;

    while (entry != NULL){
        if (strcmp(key, entry->key) == 0){
            return entry->value;
        }

        prev_entry = entry;
        entry = entry->next;
    }

    return NULL;
}

void *delete(hash_table_t *ht, char *key){
    unsigned int index = hash(ht, key);

    entry_t *entry = ht->entries[index];

    if (entry == NULL){
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

void resize(hash_table_t ht, unsigned int length){

}

hash_table_t *init_hashtable(unsigned int (*hash_function)(char *key), unsigned int length){
    hash_table_t *ht = malloc(sizeof(hash_table_t));

    ht->entries = malloc(length * sizeof(entry_t*));
    for (int i=0;i<length * sizeof(entry_t*);i+=sizeof(entry_t*)){
        ht->entries[i] = NULL;
    }
    ht->count = 0;
    ht->length = length;
    ht->hash_function = hash_function;
    ht->insert = insert;
    ht->get = get;

    return ht;
}
