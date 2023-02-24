# hash_table
C Hash table for int, double, string 


# Hash table
A hash table uses a hash function to compute an index, also called a hash code, into an array of buckets or slots, from which the desired value can be found.\
Read more here: [Wikipedia](https://en.wikipedia.org/wiki/Hash_table)

# Collision resolution
Separate chaining — the process involves building a linked list with elements for each search array index. The collided items are chained together through a single linked list, which can be traversed to access the item. Collision resolution through chaining with linked list is a common method of implementation of hash tables.\
Implementation of a [linked list](https://github.com/Tnirpps/linked_list)

# Functions
| function     | description |
| ------------ | ------------|
| create*      | create an empty hash table |
| insert       | insert an element into the hash table |
| remove       | remove given element from the hash table |
| contains     | check if the hash table contains a certain element|
| print        | displays the contents of the hash table|
| destroy      | destroy the hash table and free allocated memory|
| default hash | returns hash of the element according to its size in bytes |

*create accepts three argument:
- type of elemenst (t can be `Int`, `Double` or `String`)
- capacity of table
- hash function (`DEFAULTHASHFUNC` or your own function name)

# Quick Start

Change this define in *main.c* to test different types of hash table values.
```C
#define TYPEOFHASHTABLE  (STRING)
```

```console
$ make
$ ./a.out
```

# Usage
