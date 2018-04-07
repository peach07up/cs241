/**
 * Machine Problem 4
 * CS 241 - Spring 2016
 */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <assert.h>

//create link list to track memory been used, memory is a pool, but we cannot access it directly,  get it from the sbrk function
void * head = NULL;//make a linked list with the struct meta_data as data_type, we need a head
//last: the last of the linked list, made to keep track of all pointers created
struct meta_data{
    size_t size;
    struct meta_data * next;//corresponding size of the block to the corresponding pointer
    int is_free;//we have memory that have some block been allocate and some not, is_free will tell us if it is allocated or not
};//store or keep track of the pointers that malloc returns, basic structure to store the next pointer and the size of the block

//we use a pointer to a pointer, we are changing the address to which the pointer is pointing
struct meta_data *findFreeBlock(struct meta_data **last, size_t size) {//check if we already have a block that is free and has that size, we give this pointer to the new requiremnt
    struct meta_data *current = head;
    while (current && !(current->is_free && current->size >= size)) {//search in linked list for a pointer which is free and has size greater than or equal to the requirement and returns that pointer and check whether the pointer exists
        * last = current;//
        current = current->next;//traverse through the linked list
    }
    return current;
}// if this is not there then we will have to ask sbrk everytime and we will waste a lot of space


struct meta_data *requestNewSpace(struct meta_data * last, size_t size) {//if we dont find a reusabel space we just ask sbrk then
    struct meta_data *block;
    block = sbrk(0);
    void *request = sbrk(size + sizeof( struct meta_data));//sbrk to give us the size required plus some more space for the linked list block we are using to store the pointer and its size
    if (request == (void*) -1) {// If sbrk is unable to give us any pointer , we just return the null pointer
        return NULL;
    }
    assert((void *)block == request);
    if (last) last->next = block;//we are creating a new bolck, so we are supposed to add data about this new block to our linked list, we get it from there and we just modify its next to point it to our new block
    //When calling the request_space function passing the last block of linked list, now when we have a new block from sbrk , we have to add it to our linked list
    //the request_space function modifies the last because we added a new memory space to our accessible last
    block->size = size;
    block->next = NULL;
    block->is_free = 0;
    return block;
}
void * malloc(size_t size);
/**
 * Allocate space for array in memory
 *
 * Allocates a block of memory for an array of num elements, each of them size
 * bytes long, and initializes all its bits to zero. The effective result is
 * the allocation of an zero-initialized memory block of (num * size) bytes.
 *
 * @param num
 *    Number of elements to be allocated.
 * @param size
 *    Size of elements.
 *
 * @return
 *    A pointer to the memory block allocated by the function.
 *
 *    The type of this pointer is always void*, which can be cast to the
 *    desired type of data pointer in order to be dereferenceable.
 *
 *    If the function failed to allocate the requested block of memory, a
 *    NULL pointer is returned.
 *
 * @see http://www.cplusplus.com/reference/clibrary/cstdlib/calloc/
 */
void *calloc(size_t num, size_t size) {//calloc makes all data default value to 0, while malloc just gives the memory and doesn't care about any garbage values in the memory
    size_t final_size = num * size;
    void *ptr = malloc(final_size);
    memset(ptr, 0, size);
    return ptr;
}

/**
 * Allocate memory block
 *
 * Allocates a block of size bytes of memory, returning a pointer to the
 * beginning of the block.  The content of the newly allocated block of
 * memory is not initialized, remaining with indeterminate values.
 *
 * @param size
 *    Size of the memory block, in bytes.
 *
 * @return
 *    On success, a pointer to the memory block allocated by the function.
 *
 *    The type of this pointer is always void*, which can be cast to the
 *    desired type of data pointer in order to be dereferenceable.
 *
 *    If the function failed to allocate the requested block of memory,
 *    a null pointer is returned.
 *
 * @see http://www.cplusplus.com/reference/clibrary/cstdlib/malloc/
 */

void * malloc(size_t size) {
    struct meta_data *block;
    
    if (size <= 0) {//checks if the size required is a valid one
        return NULL;
    }
    
    if (!head) {//check if a linked list for pointers already exists or not, if the head is null we have no accessible memory
        block = requestNewSpace(NULL, size);//if head does not already exist we have to create it
        if (!block) {
            return NULL;
        }
        head = block;//when we get one pointer it means that the head needs to be re assigned so we put the head as the new pointer we created
    } else {// if head exists we use it
        struct meta_data *last = head;//creating the pointer last to use, we do not know the end of the linked list, so we assign the head to last,then keep on traversing till we actually find last
        block = findFreeBlock(&last, size);//if the head already exists, we have to first search if the existing memory has some free space
        if (!block) {
            block = requestNewSpace(last, size);//and if not then we have to request
            if (!block) {
                return NULL;
            }
        } else {
            block->is_free = 0;
        }
    }
    
    return (block+1);//return a pointer to the region after meta_data, +1 increments the address by one
}

/**
 * Deallocate space in memory
 *
 * A block of memory previously allocated using a call to malloc(),
 * calloc() or realloc() is deallocated, making it available again for
 * further allocations.
 *
 * Notice that this function leaves the value of ptr unchanged, hence
 * it still points to the same (now invalid) location, and not to the
 * null pointer.
 *
 * @param ptr
 *    Pointer to a memory block previously allocated with malloc(),
 *    calloc() or realloc() to be deallocated.  If a null pointer is
 *    passed as argument, no action occurs.
 */
//void free(void *ptr) {

// implement free!
//}
struct meta_data *get_block_ptr(void *ptr) {
    return (struct meta_data*)ptr - 1;//just like block+1
}

void free(void *ptr) {
    if (!ptr) {
        return;
    }
    struct meta_data* block_ptr = get_block_ptr(ptr);
    assert(block_ptr->is_free == 0);
    block_ptr->is_free = 1;
    //block_ptr->size = 0;
    //block_ptr->next = NULL;
}



/**
 * Reallocate memory block
 *
 * The size of the memory block pointed to by the ptr parameter is changed
 * to the size bytes, expanding or reducing the amount of memory available
 * in the block.
 *
 * The function may move the memory block to a new location, in which case
 * the new location is returned. The content of the memory block is preserved
 * up to the lesser of the new and old sizes, even if the block is moved. If
 * the new size is larger, the value of the newly allocated portion is
 * indeterminate.
 *
 * In case that ptr is NULL, the function behaves exactly as malloc, assigning
 * a new block of size bytes and returning a pointer to the beginning of it.
 *
 * In case that the size is 0, the memory previously allocated in ptr is
 * deallocated as if a call to free was made, and a NULL pointer is returned.
 *
 * @param ptr
 *    Pointer to a memory block previously allocated with malloc(), calloc()
 *    or realloc() to be reallocated.
 *
 *    If this is NULL, a new block is allocated and a pointer to it is
 *    returned by the function.
 *
 * @param size
 *    New size for the memory block, in bytes.
 *
 *    If it is 0 and ptr points to an existing block of memory, the memory
 *    block pointed by ptr is deallocated and a NULL pointer is returned.
 *
 * @return
 *    A pointer to the reallocated memory block, which may be either the
 *    same as the ptr argument or a new location.
 *
 *    The type of this pointer is void*, which can be cast to the desired
 *    type of data pointer in order to be dereferenceable.
 *
 *    If the function failed to allocate the requested block of memory,
 *    a NULL pointer is returned, and the memory block pointed to by
 *    argument ptr is left unchanged.
 *
 * @see http://www.cplusplus.com/reference/clibrary/cstdlib/realloc/
 */

void *realloc(void *ptr, size_t size) {
    if (!ptr) {//if NULL ptr realloc should act like malloc.
        return malloc(size);
    }
    
    struct meta_data* block_ptr = get_block_ptr(ptr);//getting the block pointer and then checking for the size
    if (block_ptr->size >= size) {
        return ptr;
    }
    
    void *new_ptr;
    new_ptr = malloc(size);
    if (!new_ptr) {
        return NULL;
    }
    memcpy(new_ptr, ptr, block_ptr->size);//takes the existing array and then creates a bigger one then copies
    free(ptr);
    return new_ptr;
}


