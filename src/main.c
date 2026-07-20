#include <stdio.h>

#include "kv.h" 

int main(){

    kv_t *db = kv_init(128);

    if (kv_put(db, "Keanu", "Boss") == -1){
        printf("Error\n");
    }
    if (kv_put(db, "Gizmo", "Dog") == -1){
        printf("Error\n");
    }
    if (kv_put(db, "Mum", "Boss") == -1){
        printf("Error\n");
    }
    if (kv_put(db, "Keanu", "Awesomw") == -1){
        printf("Error\n");
    }

    for (int i = 0; i < db->capacity; i++){
        if (db->entries[i].key){
            printf("[%d] %s : %s\n", i, db->entries[i].key, db->entries[i].value);
        }
    }

    return 0;
}