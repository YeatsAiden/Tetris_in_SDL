#include <SDL2/SDL.h>
#include "table.h"

size_t jenkins_one_at_a_time_hash(char *key){
    size_t hash = 0;
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

size_t hash(HashTable *ht, char *key){
    return ht->hash_function(key) % ht->length;
}

void free_value(Entry *entry){
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

Entry *free_entry(Entry *entry){
    Entry *next_entry = entry->next;

    free(entry->key);
    free_value(entry);
    free(entry);

    return next_entry;
}

void set_key(Entry *entry, char *key){
    entry->key = malloc(strlen(key) + 1); /* +1 because of the null terminator */
    if (entry->key != NULL){
        strcpy(entry->key, key);
    }
}

Entry *pair_value(char *key, void *value, ValueType type){
    Entry *entry = malloc(sizeof(Entry));

    if (entry != NULL){
        set_key(entry, key);
        entry->value = value;
        entry->next = NULL;
        entry->type = type;
    }

    return entry;
}

void hash_table_insert(HashTable *ht, char *key, void *value, ValueType type){

    if (ht->count / ht->length >= 0.7){
        /* I'll add resizing later. */
    }

    size_t index = hash(ht, key);

    Entry *entry = ht->entries[index];

    if (entry == NULL){
        ht->entries[index] = pair_value(key, value, type);
        ht->count++;
        return;
    }

    Entry *prev_entry;

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

void *hash_table_get(HashTable *ht, char *key){
    unsigned int index = hash(ht, key);

    Entry *entry = ht->entries[index];

    if (entry == NULL){
        return NULL;
    }

    Entry *prev_entry;

    while (entry != NULL){
        if (strcmp(key, entry->key) == 0){
            return entry->value;
        }

        prev_entry = entry;
        entry = entry->next;
    }

    return NULL;
}

void hash_table_delete(HashTable *ht, char *key){
    unsigned int index = hash(ht, key);

    Entry *entry = ht->entries[index];

    if (entry == NULL){
        return;
    }

    if (strcmp(key, entry->key) == 0){
        ht->entries[index] = free_entry(entry);
        return;
    }

    Entry *next_entry = entry->next;

    while (next_entry){
        if (strcmp(key, next_entry->key) == 0){
            entry->next = free_entry(next_entry);
            return;
        }

        entry = next_entry;
        next_entry = next_entry->next;
    }
}

HashTable *init_hashtable(size_t (*hash_function)(char *key), size_t length){
    HashTable *ht = malloc(sizeof(HashTable));

    if (ht != NULL){
        ht->entries = malloc(length * sizeof(Entry*));
        for (int i=0;i<length;i++){
            ht->entries[i] = NULL;
        }
        ht->count = 0;
        ht->length = length;
        ht->hash_function = hash_function;
    }

    return ht;
}

void free_hash_table(HashTable *ht){
    /* Delete all entries */
    for (int i=0;i<ht->length;i++){
        while (ht->entries[i] != NULL){
            ht->entries[i] = free_entry(ht->entries[i]);
        }
    }

    free(ht);
}

