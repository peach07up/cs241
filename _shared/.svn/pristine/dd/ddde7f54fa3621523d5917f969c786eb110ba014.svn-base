/**
 * Ideal Indirection Lab
 * CS 241 - Spring 2016
 */
#ifndef __PageTable_H__
#define __PageTable_H__

#include <stdlib.h>
#define PAGETABLE_SIZE 4096
typedef struct {
  // These pages could point to a frame in physcial memory
  // or it could point to another page table.
  // Who knows?
  void *pages[PAGETABLE_SIZE];
  // 4096 = 2^12
} PageTable;

/**
  Allocate and return a new Page Table.
*/
PageTable *PageTable_create();

/**
  Gets the 'index'th page from 'pt'.

  Note: You must use this method for getting pages from a page table and under
  no circumstances are you to break the page table abstraction.
  A NULL pointer means that the 'index'-th page in 'pt' has not been assigned
  yet to somewhere in physical memory.
*/
void *PageTable_get_entry(PageTable *pt, size_t index);

void PageTable_set_entry(PageTable *pt, size_t index, void *entry);

void Pagetable_delete_tree(PageTable *base);

#endif /* __PageTable_H__ */
