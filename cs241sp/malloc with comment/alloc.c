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
    struct meta_data * next_free;//pointer to the next free block, if this is NULL then there is no next free block
};//store or keep track of the pointers that malloc returns, basic structure to store the next pointer and the size of the block

/*struct free_meta_data{
 struct meta_data * meta_data;
 struct free_mdata_data * next;
 };
 
 struct free_sizes{
 struct free_sizes * next;
 size_t size;
 struct free_meta_data * data;
 };*/

// We have both the normal linked list
// And a seperate linked list for tracking free memory
// Head_free is the head of the free memory linked list
struct meta_data * head_free = NULL;

// This is the last of the normal memory linked list, it's renamed to avoid naming
// conflicts
struct meta_data * tail = NULL;

// This is the last of the free memory linked list
struct meta_data * tail_free = NULL;

void * pbrk = NULL;

//we use a pointer to a pointer, we are changing the address to which the pointer is pointing
struct meta_data *findFreeBlock(size_t size) {//check if we already have a block that is free and has that size, we give this pointer to the new requiremnt
    // Here's what we want to do
    // 1. Go through free sizes to find something free that where free_sizes->size >= size
    // 2. If so, we go to that free_sizes->data and take the first one, and move the head of that
    // 3. If not, we'll return NULL and go for sbrk
    
    struct meta_data *current = head_free;
    struct meta_data *last = current;
    while(current && current->size < size)
    {
        // We want to check if the next block is free too, that is next_free != NULL
        // If it is, we'll see what we can merge
        
        size_t merged_size = current->size;
        struct meta_data *merge = current->next;
        
        // Merge is the next block thats right next to you
        // Keep finding blocks that is right next to you as long as they are known to be free
        // If we find enough blocks so that the total size is big enough we stop
        
        // The key thing is how we determine if a block is a free memory block
        // A block is a free memory block if its in the free memory block linked list
        // Its in the linked list if 1 of 2 conditions are met
        // 1. it's next_free value actually points to another free memory block, if its NULL it's probably not free
        // 2. The only exception to #1 is if the free memory block is the very last memory block, because as you know
        // The last item of a linked list points to NULL, so we also keep track of the last item
        // And if what we are checking is the list item, then it's obviously on the free memory block list
        while(merge != NULL && (merge->next_free != NULL || merge == tail_free) && merged_size < size)
        {
            merged_size += merge->size + sizeof(struct meta_data);
            merge = merge->next;
        }
        // If we've found enough blocks, because the blocks are right next to each other
        // We just change the size of the current block and set the next block to
        // the next block after the blocks we are merging
        // The meta_data structs in the merged blocks become part of the free space
        if(merged_size >= size)
        {
            current->size = merged_size;
            current->next = merge;
            break;
        }
        
        last = current;
        // Current is head_free so its a free memory block
        // next_free would be the next free memory block in the linked list
        // So we'll now check the next free memory block if its big enough in size
        current = current->next_free;
    }
    if(last != NULL && current != NULL)
    {
        last->next_free = current->next_free;
    }
    if(current == head_free && current != NULL)
    {
        head_free = head_free->next_free;
    }
    if(current == tail_free)
    {
        tail_free = NULL;
    }
    if(current != NULL)
    {
        current->next_free = NULL;
    }
    
    // We will dynamically decrease the size after we have our block, as
    // opposed to increasing the size, when we do that when looking for it
    // First we check if there's enough size to make it worth like
    // Then we'll create a new metadata structure there
    /*if(current != NULL && (size + sizeof(struct meta_data)) <= current->size * 2)
     {
     // New size is the size of the new block
     // Current Block Size - Requested Size + Size of a new Meta Data Struct
     size_t new_size = current->size - (size + sizeof(struct meta_data));
     current->size = size;
     // Block + 1
     // Current + 1 moves the pointer to the start of the free space, like malloc
     // Then we move the pointer the entire requested size so we are at the start
     // Of the space that is not needed in this block
     char * ptr = (char *)current;
     ptr = ptr + current->size + sizeof(struct meta_data);
     
     // We'll then create a new block and fill in all the values like
     // requestNewSpace
     struct meta_data * new_block = (struct meta_data *)ptr;
     new_block->size = new_size;
     new_block->next = current->next;
     // The only thing different is we'll add this to the free list as well
     if(head_free == NULL)
     {
     tail_free = new_block;
     new_block->next_free = NULL;
     }
     else
     {
     new_block->next_free = head_free->next_free;
     }
     head_free = new_block;
     // And if the current block is the last block, we'll update that value too
     // So the new block is now the last block
     if (current == tail) tail = new_block;
     current->next = new_block;
     }*/
    
    return current;
    
    /*struct meta_data *current = head;
     while (current && !(current->is_free && current->size >= size)) {//search in linked list for a pointer which is free and has size greater than or equal to the requirement and returns that pointer and check whether the pointer exists
     * last = current;//
     current = current->next;//traverse through the linked list
     }
     return current;*/
}// if this is not there then we will have to ask sbrk everytime and we will waste a lot of space


struct meta_data *requestNewSpace(size_t size) {//if we dont find a reusabel space we just ask sbrk then
    struct meta_data *block;
    block = sbrk(0);
    
    // No pbrk, work exactly as before
    if(pbrk == NULL)
    {
        void *request = sbrk(size + sizeof( struct meta_data));//sbrk to give us the size required plus some more space for the linked list block we are using to store the pointer and its size
        if (request == (void*) -1) {// If sbrk is unable to give us any pointer , we just return the null pointer
            return NULL;
        }
        assert((void *)block == request);
    }
    // We have some free space in pbrk, but its not enough
    else if(pbrk != NULL && (size_t)((char *)block - (char *)pbrk) < (size + sizeof(struct meta_data)))
    {
        // Calculate the amount of free space we have
        size_t reuse = (size_t)((char *)block - (char *)pbrk);
        // And subtract that from the free space we are requesting from sbrk
        void *request = sbrk(size + sizeof( struct meta_data) - reuse);//sbrk to give us the size required plus some more space for the linked list block we are using to store the pointer and its size
        if (request == (void*) -1) {// If sbrk is unable to give us any pointer , we just return the null pointer
            return NULL;
        }
        // Since we are starting in free space, we'll redefine block to point
        // to the start of our free space, rather than the start of the space
        // we got from sbrk
        block = (struct meta_data *)pbrk;
        pbrk = NULL;
    }
    // block - pbrk shows there is enough free space to not have to use sbrk
    else
    {
        // Instead of using sbrk, let's use existing blocks
        // Instead of block = sbrk(0), aka the start of the new memory
        // We'll use block = pbrk, the start of the existing memory that we have
        // marked as free
        block = (struct meta_data *)pbrk;
        // Then we increment pbrk forward, like how sbrk works
        pbrk = (void *)((char *)pbrk + size + sizeof(struct meta_data));
    }
    if (tail) tail->next = block;//we are creating a new bolck, so we are supposed to add data about this new block to our linked list, we get it from there and we just modify its next to point it to our new block
    //When calling the request_space function passing the last block of linked list, now when we have a new block from sbrk , we have to add it to our linked list
    //the request_space function modifies the last because we added a new memory space to our accessible last
    block->size = size;
    block->next = NULL;
    block->next_free = NULL;
    tail = block;
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
        block = requestNewSpace(size);//if head does not already exist we have to create it
        if (!block) {
            return NULL;
        }
        head = block;//when we get one pointer it means that the head needs to be re assigned so we put the head as the new pointer we created
    } else {// if head exists we use it
        block = findFreeBlock(size);//if the head already exists, we have to first search if the existing memory has some free space
        if (!block) {
            block = requestNewSpace(size);//and if not then we have to request
            if (!block) {
                return NULL;
            }
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
    
    // First let's get the size of block_ptr
    // Search through head_free until we get size >= block_ptr's size
    // Put block_ptr right before this block
    
    /*struct meta_data* current = head_free;
     struct meta_data* last = current;
     
     while(current && current->size < block_ptr->size)
     {
     last = current;
     current = current->next_free;
     }
     if(current == NULL)
     {
     head_free = block_ptr;
     }
     else
     {
     last->next_free = block_ptr;
     block_ptr->next_free = current;
     }*/
    block_ptr->next_free = head_free;
    if(head_free == NULL)
    {
        tail_free = block_ptr;
    }
    head_free = block_ptr;
    
    // Now when are we going to set pbrk and declare there is some free space
    // We'll do it when the entire list is empty
    // To do that, we'll first need to make sure what we just freed was the end
    // of the list
    if(tail == head_free && head != NULL)
    {
        struct meta_data *current = (struct meta_data*)head;
        // Next we're going to go from the very start and go right to the end
        // If we come across any blocks that are not free then we won't set pbrk
        while(current->next && (current->next->next_free != NULL || current->next == tail_free))
        {
            current = current->next;
        }
        // So if we got to the end properly, we'll set pbrk to the front of the list
        // We'll clear everything else out as well
        // We've now basically completely reset the memory list
        if(current == tail)
        {
            pbrk = head;
            head = NULL;
            head_free = NULL;
            tail_free = NULL;
            tail = NULL;
        }
    }
    
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



