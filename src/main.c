#include <stdio.h>

#include "kv.h" 

int main(){

    kv_t *db = kv_init(3);

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

    return 0;
}