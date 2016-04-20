#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "hashmap.h"

int keyCompare(void *key1, void *key2) {
    if (strcmp((char *) key1, (char *) key2) == 0) {
        return 1;
    } else {
        return 0;
    }
}


void test_hash_map() {
    printf("Starting Hash Map Test...\n\n");

    printf("Constructing Hash Map...\n");
    HashMap *map = new_hash_map(&keyCompare, 256, .75);
    printf("Hash Map Constructed...\n\n");

    printf("Putting to Hash Map...\n");
    hash_map_put(map, "Test Key", "Test Value");
    hash_map_put(map, "John", "Doe");
    hash_map_put(map, "Anon", "ymous");
    printf("Resulting Hash Map...\n");
    printf("%s", hash_map_to_string(map));
    printf("Hash Map put to...\n\n");

    printf("Getting from Hash Map...\n");
    printf("Expecting: \"Test Value\". Actual result: \"%s\"\n", (char *) hash_map_get(map, "Test Key"));
    printf("Hash Map retrieved from... \n\n");

    printf("Removing from Hash Map...\n");
    printf("Removing Pair with key \"Test Value\"\n");
    hash_map_remove(map, "Test Key");
    printf("Removed Pair with key \"Test Value\"\n");
    printf("Get expecting: (null). Actual result: \"%s\"\n", (char *) hash_map_get(map, "Test Key"));
    printf("Resulting Hash Map...\n");
    printf("%s", hash_map_to_string(map));
    printf("Hash Map removed from... \n\n");

    printf("Deconstructing Map Test...\n");
    destroy_hash_map(map, true);
    printf("Hash Map Deconstructed...\n\n");

    printf("Hash Map Test Finished!\n\n");
}





int main(int argc, char *argv) {
    test_hash_map();
    return 1;
}
