#include "hash_table.h"
#include <stdio.h>
#include <assert.h>
#include <string.h>


hashTable HashTableCreate(size_t capacity, types type, size_t (*HashFunction)(const void*, size_t)) {
    hashTable t = {0};
    if (capacity == 0) {
        capacity = 97;
    }
    t.data = malloc(sizeof(list) * capacity);
    if (t.data == NULL) {
        fprintf(stderr, "ERROR: could not allocate memory for hash table\n");
        exit(1);
    }
    for (size_t i = 0; i < capacity; ++i) {
        t.data[i] = ListCreate(type);
    }

    t.capacity = capacity;
    t.size = 0;
    t.type = type;
    t.HashFunction = HashFunction;

    return t;
}

size_t HashTableDefaultHash(const void* e, size_t size) {
    size_t hash = 5381;
    for (size_t i = 0; i < size; ++i) {
        hash = ((hash << 5) + hash) + ((char*)e)[i];
    }
    return hash;
}

size_t HashTableHash(const hashTable* t, const void* e) {
    if (t == NULL) {
        fprintf(stderr, "ERROR: could not calc hash (ivalid pointer to hash table)\n");
        exit(1);
    }

    size_t size;
    switch (t->type) {
        case String:
            size = strlen((char*) e);
            break;
        case Double:
            size = sizeof(double);
            break;
        case Int:
            size = sizeof(int);
            break;
        default:
            fprintf(stderr, "EROOR: could not hash not valid data type\n");
            exit(1);
    }

    return t->HashFunction(e, size); 
}

bool HashTableContains(const hashTable* t, const void* elem) {
    if (t == NULL) {
        fprintf(stderr, "ERROR: could not count element in NULL-table\n");
        exit(1);
    }
    size_t index = HashTableHash(t, elem) % t->capacity;
    return ListContains(&t->data[index], elem);

}

void HashTableRemove(hashTable* t, const void* elem) {
    if (t == NULL) {
        fprintf(stderr, "ERROR: could not remove element from NULL-table\n");
        exit(1);
    }
    size_t index = HashTableHash(t, elem) % t->capacity;
    ListErase(&t->data[index], elem);
    t->size--;
}

void HashTableInsert(hashTable* t, const void* elem) {
    if (t == NULL) {
        fprintf(stderr, "ERROR: could not insert element to NULL-table\n");
        exit(1);
    }

    if (HashTableContains(t, elem)) {
        /* dont insert one element twice */
        return;
    }

    size_t index = HashTableHash(t, elem) % t->capacity;
    ListPushBack(&t->data[index], elem);
    t->size++;
    // TODO calculate the average fill rate of a hash table to resize
}

void HashTablePrint(const hashTable* t) {
    for (size_t i = 0; i < t->capacity; ++i) {
        printf("%lu : ", i);
        if (t->data[i].head != NULL) {
            ListPrint(&t->data[i]);
        } else {
            printf("\n");
        }
    }
}

void HashTableDestroy(hashTable* t) {
    if (t == NULL) {
        fprintf(stderr, "ERROR: could not destroy NULL ptr\n");
        exit(1);
    }
    for (size_t i = 0; i < t->capacity; ++i) {
        ListDestroy(&t->data[i]);
    }
    free(t->data);
    t->capacity = 0;
    t->size = 0;
}

