//
// Created by hlawr_000 on 3/24/2016.
//

#ifndef DATASTRUCTURES_DYNAMICLIST_H
#define DATASTRUCTURES_DYNAMICLIST_H

#include <stdbool.h>

typedef struct {
    int size;
    void *inner;
} DynamicList;

DynamicList *new_dynamic_list(int initialSize);

void destroy_dynamic_list(DynamicList * list, bool cascade);

void dynamic_list_add(DynamicList * list, void * value);

void dynamic_list_add_to_index(DynamicList * list, void * value, int index);

void * dynamic_list_get(DynamicList * list, int index);

void dynamic_list_remove(DynamicList * list, void * value);

void dynamic_list_remove_index(DynamicList * list, int index);

int dynamic_list_index_of(DynamicList * list, void * value);

char * dynamic_list_to_string(DynamicList * list);

#endif //DATASTRUCTURES_DYNAMICLIST_H
