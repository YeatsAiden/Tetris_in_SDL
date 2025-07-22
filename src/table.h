#ifndef HASH_TABLES_H
#define HASH_TABLES_H

typedef enum{
    SURFACE,
    TEXTURE,
    OTHER /* Literally any standard variable type that C has */
} Value_type;

typedef struct entry{
    char *key;
    void *value;

    struct entry *next;

    Value_type type;
} entry_t;

typedef struct hash_table{
    unsigned int count;
    unsigned int length;

    entry_t **entries;

    unsigned int (*hash_function)(char *key);
} hash_table_t;

unsigned int jenkins_one_at_a_time_hash(char *key);
hash_table_t *init_hashtable(unsigned int (*hash_function)(char *key), unsigned int length);
void hash_table_insert(hash_table_t *ht, char *key, void *value, Value_type type);
void *hash_table_get(hash_table_t *ht, char *key);
void hash_table_delete(hash_table_t *ht, char *key);

#endif
