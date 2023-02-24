#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <stdlib.h>
#include "./linked_list/list.h"

#define DEFAULTHASHFUNC HashTableDefaultHash

typedef struct hashTable {
   list*   data;
   size_t  size;
   size_t  capacity;
   types   type;
   size_t  (*HashFunction)(const void*, size_t);
} hashTable;

hashTable  HashTableCreate   (size_t capacity, types type, size_t (*HashFunction)(const void*, size_t));
void       HashTableInsert      (hashTable* t, const void* elem);
void       HashTableRemove      (hashTable* t, const void* elem);
bool       HashTableContains    (const hashTable* t, const void* elem);
size_t     HashTableDefaultHash (const void* e, size_t size);
void       HashTablePrint       (const hashTable* t);
void       HashTableDestroy     (hashTable* t);

#endif /* ifndef HASH_TABLE_H */

