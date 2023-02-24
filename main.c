#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "./linked_list/list.h"
#include "hash_table.h"

void exit_with_message(const char* msg, int status) {
    fprintf(stderr, "%s\n", msg);
    exit(status);
}

void usage() {
    printf("1) insert \t 2) remove\t 3) consist\t 0) exit\n");
}

size_t BadHashFunc(const void* e, size_t n) {
    return 1;
}

#define INTEGER 1
#define DOUBLE  2
#define STRING  3

/* define type of data in Hash Table*/
#ifndef TYPEOFHASHTABLE
 #define TYPEOFHASHTABLE  (STRING)
#endif

#if TYPEOFHASHTABLE == INTEGER

void loop() {
    printf("Type: integer\n");
    hashTable t = HashTableCreate(13, Int, DEFAULTHASHFUNC);
    int q;
    int x;
    usage();
    while (1) {
        printf("enter query number: ");
        scanf("%d", &q);
        if (q == 0) {
            break;
        }
        if (q == 1) {
            printf("enter value: ");
            scanf("%d", &x);
            HashTableInsert(&t, &x);
        } else if (q == 2) {
            printf("enter value: ");
            scanf("%d", &x);
            HashTableRemove(&t, &x);
        } else if (q == 3) {
            printf("enter value: ");
            scanf("%d", &x);
            if (HashTableContains(&t, &x)) {
                printf("%d present in the table\n", x);
            } else {
                printf("%d not in the table\n", x);
            }
        } else {
            printf("bad query numder\n");
            usage();
            continue;
        }
        HashTablePrint(&t);
    }

    HashTableDestroy(&t);
}

#elif TYPEOFHASHTABLE == DOUBLE


void loop() {
    printf("Type: double\n");
    /* set custom Hash function*/
    hashTable t = HashTableCreate(3, Double, BadHashFunc);
    int q;
    double x;
    usage();
    while (1) {
        printf("enter query number: ");
        scanf("%d", &q);
        if (q == 0) {
            break;
        }
        if (q == 1) {
            printf("enter value: ");
            scanf("%lf", &x);
            HashTableInsert(&t, &x);
        } else if (q == 2) {
            printf("enter value: ");
            scanf("%lf", &x);
            HashTableRemove(&t, &x);
        } else if (q == 3) {
            printf("enter value: ");
            scanf("%lf", &x);
            if (HashTableContains(&t, &x)) {
                printf("%lf present in the table\n", x);
            } else {
                printf("%lf not in the table\n", x);
            }
        } else {
            printf("bad query numder\n");
            usage();
            continue;
        }
        HashTablePrint(&t);
    }

    HashTableDestroy(&t);
}

#elif TYPEOFHASHTABLE == STRING

char* readString(FILE* fp){
    char* str;
    int ch;
    size_t len = 0;
    size_t size = 10; //size is start size
    str = malloc(sizeof(char)*size);
    if (str == NULL) return NULL;

    while ((ch = fgetc(fp)) != EOF && ch != '\n') {
        str[len++] = ch;
        if (len + 1 == size - 1) {
            size *= 2;
            char* tmp = realloc(str, sizeof(char)*size);
            if (tmp == NULL) {
                free(str);
                exit_with_message("ERROR: could not allocate memory for input string", 1);
            }
            str = tmp;
        }
    }
    str[len++]='\0';

    return str;
}

void loop() {
    printf("Type: string\n");
    hashTable t = HashTableCreate(3, String, DEFAULTHASHFUNC);
    int q;
    char* x;
    usage();
    while (1) {
        printf("enter query number: ");
        scanf("%d", &q);
        // remove \n from stdin after scanf
        fgetc(stdin);

        if (q == 0) {
            break;
        }
        if (q == 1) {
            printf("enter value: ");
            x = readString(stdin);
            HashTableInsert(&t, x);
            free(x);
            x = NULL;
        } else if (q == 2) {
            printf("enter value: ");
            x = readString(stdin);
            HashTableRemove(&t, x);
            free(x);
            x = NULL;
        } else if (q == 3) {
            printf("enter value: ");
            x = readString(stdin);
            if (HashTableContains(&t, x)) {
                printf("`%s` present in the table\n", x);
            } else {
                printf("`%s` not in the table\n", x);
            }
            free(x);
            x = NULL;
        } else {
            printf("bad query numder\n");
            usage();
            continue;
        }
        HashTablePrint(&t);
    }

    HashTableDestroy(&t);
}

#else
 #error "Unexpected value of TYPEOFHASHTABLE."
#endif

int main() {
    loop();
    return 0;
}

