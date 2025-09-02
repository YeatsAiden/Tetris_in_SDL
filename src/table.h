#ifndef HASH_TABLES_H
#define HASH_TABLES_H

typedef enum ValueType{
    SURFACE,
    TEXTURE,
    OTHER /* Literally any standard variable type that C provides */
} ValueType;

typedef struct Entry{
    char *key;
    void *value;

    struct Entry *next;

    ValueType type;
} Entry;

typedef struct HashTable{
    size_t count;
    size_t length;

    Entry **entries;

    size_t (*hash_function)(char *key);
} HashTable;

size_t jenkins_one_at_a_time_hash(char *key);
HashTable *init_hashtable(size_t (*hash_function)(char *key), size_t length);
void hash_table_insert(HashTable *ht, char *key, void *value, ValueType type);
void *hash_table_get(HashTable *ht, char *key);
void hash_table_delete(HashTable *ht, char *key);
void free_hash_table(HashTable *ht);

#endif
