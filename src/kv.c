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

unsigned short get_index(char *key, size_t capacity){
    unsigned short hash = 5381;

    int c;

    while ((c = *key++)){
        hash = hash * 33 + c;
    }
    return hash % capacity;
}

int allocate_k_v(char **p_key, char **p_value, char *key, char *value){
    
    char *p_new_key = malloc(sizeof(char) * (strlen(key) + 1));
    char *p_new_value = malloc(sizeof(char) * (strlen(value) + 1));

    if (p_new_value == NULL || p_new_key == NULL) return -1;

    *p_key = p_new_key;
    *p_value = p_new_value;

    return 0;
}

void assign_new_kv(kv_t *table, int index, char *p_new_key, char *p_new_value){
        table->entries[index].key = p_new_key;
        table->entries[index].value = p_new_value;
        table->count++;
}

int kv_put(kv_t *table, char *key, char *value){

    if(key == NULL || value == NULL) return -1;


    unsigned short index = get_index(key, table->capacity);

    // printf("INDEX: %d\n", index);

    // init tombstone to an index greater than the table capacity so we can check if it has been set
    int index_tombstone = table->capacity + 1;

    for (int i = 0; i + index < table->capacity; i++){
        
        char *extracted_key = table->entries[index + i].key;


        if (extracted_key == NULL){
            char *p_new_key;
            char *p_new_value;

            if (allocate_k_v(&p_new_key, &p_new_value, key, value) == -1) return -1;

            strcpy(p_new_key, key);
            strcpy(p_new_value, value);

            assign_new_kv(table, index + i, p_new_key, p_new_value);

        //     printf("Key: %s\n", table->entries[index + i].key);
        //     printf("Value: %s\n", table->entries[index + i].value);
        // printf("Added at: %d\n", index + i);

            return index + i;
        }
        else if (!strcmp(extracted_key, key))
        {

            char *p_new_value = malloc(sizeof(char) * (strlen(value) + 1));

            if (p_new_value == NULL) return -1;

            free(table->entries[index + i].value);
            strcpy(p_new_value, value);
            table->entries[index + i].value = p_new_value;

            // printf("Key: %s\n", table->entries[index + i].key);
            // printf("Value: %s\n", table->entries[index + i].value);

            return index + i;

        }
        else if (extracted_key == TOMBSTONE)
        {


            // only keep track of the first tombstone occurence
            if (index_tombstone > table->capacity){
                index_tombstone = index + i;
            }
        }
    
    }
    // if tombstone has been set
    if (index_tombstone < table->capacity){
        char *p_new_key;
        char *p_new_value;

        if (allocate_k_v(&p_new_key, &p_new_value, key, value) == -1) return -1;

        free(table->entries[index_tombstone].key);

        strcpy(p_new_key, key);
            strcpy(p_new_value, value);

        assign_new_kv(table, index_tombstone, p_new_key, p_new_value);

        // printf("Key: %s\n", table->entries[index_tombstone].key);
        // printf("Value: %s\n", table->entries[index_tombstone].value);

        return index_tombstone;
    }

    if (table->count >= table->capacity) return -1;

    return -1;

}


