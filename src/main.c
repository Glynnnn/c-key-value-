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
    if (kv_put(db, "Mum", "Mother") == -1){
        printf("Error\n");
    }
    if (kv_put(db, "Keanu", "Awesomw") == -1){
        printf("Error\n");
    }

    // printf("Value: %s\n", kv_get(db, "Keanu"));
    // printf("Value: %s\n", kv_get(db, "Gizmo"));
    // printf("Value: %s\n", kv_get(db, "Mum"));

    kv_delete(db, "Keanu");
    kv_delete(db, "Mum");
    kv_delete(db, "Gizmo");


    for (int i = 0; i < db->capacity; i++){
        if (db->entries[i].key && db->entries[i].key != TOMBSTONE){
            printf("[%d] %s : %s\n", i, db->entries[i].key, db->entries[i].value);
        }
    }

    return 0;
}