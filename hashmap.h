#ifndef HASHMAP_H
#define HASHMAP_H


typedef struct {
    int size;
    void *privateInner;
} HashMap;


void *hash_map_get(HashMap *map, void *key);

void hash_map_put(HashMap *map, void *key, void *value);

void hash_map_remove(HashMap *map, void *key);

HashMap *new_hash_map(int (*compare)(void *key1, void *key2), int inititialCapacity, float loadFactor);

void destroy_hash_map(HashMap *toDestroy, bool cascade);

char *hash_map_to_string(HashMap *map);


#endif /* HASHMAP_H*/