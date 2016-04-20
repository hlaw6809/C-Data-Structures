#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "hashmap.h"


/*
 *
 * Private Structures
 *
 */

typedef struct {
    void *key;
    void *value;
    bool occupied;
} Bucket;

typedef struct {
    Bucket *buckets;
    float loadFactor;
    int arraySize;
    int keySize;
    int valueSize;
    int (*compare)(void *key1, void *key2);
} PrivateHashMap;


/*
 *
 * Private Functions
 *
 */


int key_hash(void *key, int keySize) {
    int i, hash = 0;
    for (i = 0; i < keySize; i++) {
        char byte = ((char *) key)[i];
        hash += ((byte + 7) * (byte * 9));
    }
    return hash;
}


void _resize_hash_map(HashMap *map) {
    PrivateHashMap *inner = (PrivateHashMap*) map->privateInner;

    //New & Old Array Sizes
    int oldSize = inner->arraySize;
    int newSize = inner->arraySize * 2;

    //New & Old Bucket Arrays
    Bucket *oldBuckets = inner->buckets;
    Bucket *newBuckets = calloc(newSize, sizeof(Bucket));

    //Set New Values
    inner->buckets = newBuckets;
    inner->arraySize = newSize;

    //Populate New Bucket Array With Old Key/Value Pairs
    int i;
    for (i = 0; i < oldSize; i++) {
        Bucket oldBucket = oldBuckets[i];
        if (oldBucket.occupied) {
            hash_map_put(map, oldBucket.key, oldBucket.value);
        }
    }

    free(oldBuckets);
}


/*
 *
 * Public Functions
 *
 */


void *hash_map_get(HashMap *map, void *key) {
    PrivateHashMap *inner = (PrivateHashMap*) map->privateInner;
    Bucket *buckets = inner->buckets;
    int hash = key_hash(key, inner->keySize);
    int location = hash % inner->arraySize;
    while (buckets[location].occupied == true) {
        if (inner->compare(buckets[location].key, key)) {
            return buckets[location].value;
        } else {
            location++;
            location %= inner->arraySize;
        }
    }
    return NULL;
}


void hash_map_put(HashMap *map, void *key, void *value) {
    PrivateHashMap *inner = (PrivateHashMap*) map->privateInner;
    Bucket *buckets = inner->buckets;
    int hash = key_hash(key, inner->keySize);
    int location = hash % inner->arraySize;
    while (buckets[location].occupied == true) {
        location++;
        location %= inner->arraySize;
    }

    buckets[location].key = key;
    buckets[location].value = value;
    buckets[location].occupied = true;
    map->size++;
    float load = map->size / inner->arraySize;
    if (load >= inner->loadFactor) {
        _resize_hash_map(map);
    }
}


void hash_map_remove(HashMap *map, void *key) {
    PrivateHashMap *inner = (PrivateHashMap*) map->privateInner;
    Bucket *buckets = inner->buckets;
    int hash = key_hash(key, inner->keySize);
    int location = hash % inner->arraySize;
    while (buckets[location].occupied == true) {
        if (inner->compare(buckets[location].key, key)) {
            buckets[location].occupied = false;
        } else {
            location++;
            location %= inner->arraySize;
        }
    }
    map->size--;
}


HashMap *new_hash_map(int (*compare)(void *, void *), int initialCapacity, float loadFactor) {
    HashMap *newMap = malloc(sizeof(HashMap));
    newMap->size = 0;

    PrivateHashMap *inner = malloc(sizeof(PrivateHashMap));
    inner->buckets = calloc(initialCapacity, sizeof(Bucket));
    inner->loadFactor = loadFactor;
    inner->arraySize = initialCapacity;
    inner->compare = compare;
    newMap->privateInner = inner;

    return newMap;
}


void destroy_hash_map(HashMap *toDestroy, bool cascade) {
    PrivateHashMap *inner = (PrivateHashMap*) toDestroy->privateInner;

    if (cascade) {
        Bucket *buckets = inner->buckets;
        int i;
        for (i = 0; i < inner->arraySize; i++) {
            if (buckets[i].occupied) {
                free(buckets[i].key);
                free(buckets[i].value);
            }
        }
    }

    free(inner->buckets);
    free(inner);
    free(toDestroy);
}

char *hash_map_to_string(HashMap *map) {
    PrivateHashMap *inner = map->privateInner;
    char *buffer = calloc(1500, 1);
    char *bucketBuffer = malloc(1500);
    sprintf(buffer, "Hashmap, # of pairs: %d, # of buckets: %d, load factor: %f\n", map->size, inner->arraySize, inner->loadFactor);

    int i;
    for (i = 0; i < inner->arraySize; i++) {
        if (inner->buckets[i].occupied) {
            sprintf(bucketBuffer, "Key: %p, Value: %p\n", inner->buckets[i].key, inner->buckets[i].value);
            if (strlen(buffer) + strlen(bucketBuffer) < 1500) {
                strcat(buffer, bucketBuffer);
            }
        }
    }
    return buffer;
}