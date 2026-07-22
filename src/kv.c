#include <stdlib.h>
#include <string.h>

#include "kv.h"

#define TOMBSTONE ((char *)0x1)

kv_t* kv_init(size_t capacity){

    if (capacity <= 0) return NULL;

    kv_t *kv_table = malloc(sizeof(kv_t));

    if (kv_table == NULL) return NULL;

    kv_table->capacity=capacity;
    kv_table->count=0;

    kv_table->entries = calloc(kv_table->capacity, sizeof(kv_entry_t));

    if (kv_table->entries == NULL){
        free(kv_table);
        kv_table = NULL;
        return NULL;
    }

    return kv_table;
}

size_t get_index(char *key, size_t capacity){
    size_t hash = 5381;

    int c;

    while ((c = *key++)){
        hash = hash * 33 + c;
    }
    return hash % capacity;
}


int kv_put(kv_t *table, char *key, char *value){

    if(!table || !key || !value) return -1;

    unsigned short index = get_index(key, table->capacity);

    int index_tombstone = table->capacity + 1;

    for (int i = 0; i < table->capacity; i++){
        
        size_t real_index = (index + i) % table->capacity;
        kv_entry_t *entry = &table->entries[real_index];

        if (entry->key == NULL){
            // strdup allocates heap mem for a char* and returns it
            char *p_new_key = strdup(key);
            char *p_new_value = strdup(value);

            if (!p_new_key || !p_new_value ){

                free(p_new_key);
                free(p_new_value);
                return -1;
            } 

            entry->key = p_new_key;
            entry->value = p_new_value;
            table->count++;

            return 0;
        }
        else if (entry->key && entry->key != TOMBSTONE && !strcmp(entry->key, key))
        {

            char *p_new_value = strdup(value);

            if (p_new_value == NULL) return -1;

            free(table->entries[real_index].value);
            table->entries[real_index].value = p_new_value;

            return 0;

        }
        else if (entry->key == TOMBSTONE)
        {
            // only keep track of the first tombstone occurence
            if (index_tombstone > table->capacity){
                index_tombstone = real_index;
            }
        }
    
    }
    // if tombstone has been set
    if (index_tombstone < table->capacity){
        char *p_new_key = strdup(key);
        char *p_new_value = strdup(value);

        if (!p_new_key || !p_new_value ){

            free(p_new_key);
            free(p_new_value);
            return -1;
        } 

        table->entries[index_tombstone].key = p_new_key;
        table->entries[index_tombstone].value = p_new_value;
        table->count++;

        return 0;
    }

    // table is full
    return -1;

}

char *kv_get(kv_t *table, char *key){

    if (!key || !table) return NULL;

    // hash the key to get the index
    // loop through entire list until key is found or null is found
    // return valur or null

    int index = get_index(key, table->capacity);

    for (int i = 0; i < table->capacity; i++){

        int normalised_index = (index + i) % table->capacity;
        kv_entry_t *entry = &table->entries[normalised_index];

        if (entry->key && entry->key != TOMBSTONE && !strcmp(entry->key, key)){
            return entry->value;
        }
        else if (entry->key == NULL)
        {
            return NULL;
        }
    }
    return NULL;

}


