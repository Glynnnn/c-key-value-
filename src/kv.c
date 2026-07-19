#include <stdlib.h>
#include "kv.h"


kv_t* kv_init(int capacity){

    if (capacity <= 0) return NULL;

    kv_t *kv_table = malloc(sizeof(kv_t));

    if (kv_table == NULL) return NULL;

    kv_table->capacity=capacity;
    kv_table->size=0;

    kv_table->entries = calloc(kv_table->capacity, sizeof(kv_entry_t));

    if (kv_table->entries == NULL){
        free(kv_table);
        kv_table = NULL;
        return NULL;
    }

    return kv_table;

}


