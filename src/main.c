#include <stdio.h>

#include "kv.h" 

int main(){

    kv_t *db = kv_init(16);

    printf("%p\n", db);
    printf("%ld\n", db->capacity);

    return 0;
}