/*
 * MaxHeap.h
 *
 *  Created on: Dec 12, 2021
 *      Author: ise
 */

#ifndef MAXHEAP_H_
#define MAXHEAP_H_


#include "Defs.h"

/*
 * Header file of MaxHeap
 */

typedef struct MaxHeap_t* MaxHeap;


/*
 * Functions needed to use this LINKED LIST:
 * 1. copyFunction - function returned copy of element.
 * 2. freeFuction - function free element.
 * 3. printFunction - print element
 * 4. equalFunction - function compare between 2 elements.
 */


/* CreateHeap
 * get - element necessary functions, heap name and capcity of heap
 * return - pointer to new empty maxyheap created.
 */
MaxHeap CreateHeap(int, char*, copyFunction, freeFunction, printFunction, equalFunction);

/* destroyHeap - clean the memory
 * get - pointer to maxheap
 * return none
 */
status destroyHeap(MaxHeap);

/* insertToHeap
 * get - pointer to specific heap, elemnt
 * return - status if insertion succeed. Insertion failed when - heap in full capcity, memofail??
 */
status insertToHeap(MaxHeap, element);

/* printHeap
 * get - pointer to MaxHeap
 * return - status if print succeed. print fail when pointer is unavailable.
 */
status printHeap(MaxHeap);

/* PopMaxHeap - delete and return max elemnt from heap
 *  get pointer to maxheap
 *  return element with max val in maxheap
 */
element PopMaxHeap(MaxHeap);

/* PopMaxHeap - return max elemnt from heap
 *  get  pinter to maxheap
 *  return COPY max element with max val in maxheap
 */
element TopMaxHeap(MaxHeap);


/* getHeapId
 * get - pointer to MaxHeap
 * return - COPY name of max heap
 */
char* getHeapId(MaxHeap);

/* getHeapCurrentSize
 * get - pointer to MaxHeap
 * return - current elemnts in heap, return -1 if heap doesnt exist\NULL
 */
int getHeapCurrentSize(MaxHeap);




#endif /* MAXHEAP_H_ */
