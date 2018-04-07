/**
 * Machine Problem 1
 * CS 241 - Spring 2016
 */

#include "vector.h"
#include "stdio.h"

// Test your vector here
int main()
{
    printf("Vector Create\n");
    
    Vector *vector = Vector_create();
    
    printf("Vector Size %zu = 0\n", Vector_size(vector));
    
    Vector_append(vector, "ABC");
    
    Vector_append(vector, "123");
    
    printf("Vector Appended 0 %s = ABC 1 %s = 123 Size %zu = 2\n", Vector_get(vector, 0), Vector_get(vector, 1), Vector_size(vector));
    
    Vector_insert(vector, 3, "456");
    
    printf("Vector Inserted 2 %s =  3 %s = 456 Size %zu = 4\n", Vector_get(vector, 2), Vector_get(vector, 3), Vector_size(vector));
    
    Vector_set(vector, 2, "DEF");
    
    printf("Vector Set 2 %s = DEF 3 %s = 456 Size %zu = 4\n", Vector_get(vector, 2), Vector_get(vector, 3), Vector_size(vector));
    
    Vector_delete(vector, 1);
    
    printf("Vector Deleted 1 %s = DEF 2 %s = 456 Size %zu = 3\n", Vector_get(vector, 1), Vector_get(vector, 2), Vector_size(vector));
    
    Vector_insert(vector, 1, "a");
    
    printf("Vector Inserted 1 %s = a 2 %s = DEF Size %zu = 4\n", Vector_get(vector, 1), Vector_get(vector, 2), Vector_size(vector));
    
    Vector_insert(vector, 21, "a");
    
    printf("Vector Inserted 21 %s = a Size %zu = 22\n", Vector_get(vector, 21), Vector_size(vector));
    
    Vector_insert(vector, 31, "b");
    
    printf("Vector Inserted 31 %s = b Size %zu = 44\n", Vector_get(vector, 31), Vector_size(vector));
    
    Vector_destroy(vector);
    
    printf("Vector Destroyed");
    
}

