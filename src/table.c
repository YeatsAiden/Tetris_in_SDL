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

size_t hash(hash_table_t *ht, char *key){
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

entry_t *free_entry(entry_t *entry){
    entry_t *next_entry = entry->next;

    free(entry->key);
    free_value(entry);
    free(entry);

    return next_entry;
}

void set_key(entry_t *entry, char *key){
    entry->key = malloc(strlen(key) + 1); /* +1 because of the null terminator */
    if (entry->key != NULL){
        strcpy(entry->key, key);
    }
}

entry_t *pair_value(char *key, void *value, Value_Type_t type){
    entry_t *entry = malloc(sizeof(entry_t));

    if (entry != NULL){
        set_key(entry, key);
        entry->value = value;
        entry->next = NULL;
        entry->type = type;
    }

    return entry;
}

void hash_table_insert(hash_table_t *ht, char *key, void *value, Value_Type_t type){

    if (ht->count / ht->length >= 0.7){
        /* I'll add resizing later. */
    }

    size_t index = hash(ht, key);

    entry_t *entry = ht->entries[index];

    if (entry == NULL){
        ht->entries[index] = pair_value(key, value, type);
        ht->count++;
        return;
    }

    entry_t *prev_entry;

    while (entry != NULL) {
        if (strcmp(key, entry->key) == 0){
            free_value(entry);
            entry->value = value;
            return;
        }

        prev_entry = entry;
        entry = entry->next;
    }

    prev_entry->next = pair_value(key, value, type);
    ht->count++;
}

void *hash_table_get(hash_table_t *ht, char *key){
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

void hash_table_delete(hash_table_t *ht, char *key){
    unsigned int index = hash(ht, key);

    entry_t *entry = ht->entries[index];

    if (entry == NULL){
        return;
    }

    if (strcmp(key, entry->key) == 0){
        ht->entries[index] = free_entry(entry);
        return;
    }

    entry_t *next_entry = entry->next;

    while (next_entry){
        if (strcmp(key, next_entry->key) == 0){
            entry->next = free_entry(next_entry);
            return;
        }

        entry = next_entry;
        next_entry = next_entry->next;
    }
}

hash_table_t *init_hashtable(unsigned int (*hash_function)(char *key), unsigned int length){
    hash_table_t *ht = malloc(sizeof(hash_table_t));

    if (ht != NULL){
        ht->entries = malloc(length * sizeof(entry_t*));
        for (int i=0;i<length;i++){
            ht->entries[i] = NULL;
        }
        ht->count = 0;
        ht->length = length;
        ht->hash_function = hash_function;
    }

    return ht;
}

void free_hash_table(hash_table_t *ht){
    /* Delete all entries */
    for (int i=0;i<ht->length;i++){
        while (ht->entries[i] != NULL){
            ht->entries[i] = free_entry(ht->entries[i]);
        }
    }

    free(ht);
}

