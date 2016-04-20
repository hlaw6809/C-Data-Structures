//
// Created by hlawr_000 on 3/24/2016.
//
#include <stdlib.h>
#include "dynamiclist.h"

typedef struct {
    int arraySize;
    int nextFreeIndex;
    void ** array;
} DynamicListInner;

DynamicList *new_dynamic_list(int initialSize) {
    DynamicListInner * inner = calloc(1, sizeof(DynamicListInner));
    DynamicList * list = calloc(1, sizeof(DynamicList));
    list->inner = inner;
    inner->arraySize = initialSize;
    inner->nextFreeIndex = 0;
    inner->array = calloc(initialSize, sizeof(void *));
    return list;
}

void destroy_dynamic_list(DynamicList * list, bool cascade) {
    DynamicListInner * inner = list->inner;
    if (cascade == true) {
        int i;
        for (i = 0; i < inner->arraySize; i++) {
            free(inner->array[i]);
        };
    }
    free(inner->array);
    free(inner);
    free(list);
}

void dynamic_list_double(DynamicList * list) {
    DynamicListInner * inner = list->inner;
    int newSize = 2 * inner->arraySize;
    void * newArray[newSize];
    int i;
    for (i = 0; i < inner->arraySize; i++) {
        newArray[i] = inner->array[i];
    }
    free(inner->array);
    inner->array = newArray;
    inner->arraySize = newSize;
}

void dynamic_list_add(DynamicList * list, void * value) {
    DynamicListInner * inner = list->inner;
    if (inner->arraySize == list->size) {
        dynamic_list_double(list);
    }
    inner->array[inner->nextFreeIndex] = value;
    inner->nextFreeIndex++;
    while (inner->nextFreeIndex != 0) {
        inner->nextFreeIndex++;
    }
    list->size++;
}

void dynamic_list_add_to_index(DynamicList * list, void * value, int index) {
    DynamicListInner * inner = list->inner;
    while (index >= inner->arraySize) {
        dynamic_list_double(list);
    }
    inner->array[index] = value;
    list->size++;
}

void * dynamic_list_get(DynamicList * list, int index) {
    DynamicListInner * inner = list->inner;
    return inner->array[index];
}

void dynamic_list_remove(DynamicList * list, void * value) {
    
}

void dynamic_list_remove_index(DynamicList * list, int index);

int dynamic_list_index_of(DynamicList * list, void * value);

char * dynamic_list_to_string(DynamicList * list);
