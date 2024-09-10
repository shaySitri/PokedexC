#ifndef LINKEDLIST_H_
#define LINKEDLIST_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Defs.h"

/**
 * Header File of LinkedList (ADT)
 */

typedef struct LinkedList_t* LinkedList;

/*
 * Functions needed to use this LINKED LIST:
 * 1. copyFunction - function returned copy of element/
 * 2. freeFuction - function free element.
 * 3. printFunction - print element
 * 4. equalFunction - function check if element is equal to specific attribute.
 * 5. comapreFunction - function compare between 2 elemnts.
 */

/* createLinkedList
 * get - element necessary functions
 * return - pointer to new empty linkedlist created.
 */
LinkedList createLinkedList(copyFunction, freeFunction, printFunction,
		equalFunction, compareFunction);

/* destroyList - destroy linkedlist, clear memory.
 * get - pointer to linked list
 * return - None
 */
status destroyList(LinkedList list);

/* appendNode -
 * get - pointer to linkedlist, element ITSELF to add linked list.
 * return - status: Failure - NULL element, Memofail - cannot allocate heap memory for node,
 * Success - otherwise.
 */
status appendNode(LinkedList list, Element element);

/* deleteNode - search element in LinkedList using compare function
 * (compare between element in node in linked list between element user want to delete if exist in list)
 * get - pointer to linkedlist, element ITSELF to delete from linked list.
 * return - status: Success if delete succeeded, Failure if element not exist in list.
 */
status deleteNode(LinkedList list, Element elem);

/* displayList - print all nodes in list.
 * get - pointer to linkedlist
 * return - status. failure if element or list is NULL;
 */
status displayList(LinkedList list);

/* searchByKeyInList - search specific elemnt with key as needed using equal function use sent.
 * get - pointer to -key-(!!) of element stored in linkedlist.
 * return -COPY of Elemnt if exist, NULL if not.
 */
Element searchByKeyInList(LinkedList list, Element element);


/* getNode - return specific node in specific index.
 * get - LINKEDLIST to get node from, index.
 * return - the i'th NODE if index exist.
 */
Element getNode(LinkedList, int);

/* getElemNum - return number of elements in linked list.
 *  get - linked list
 *  return - int, num of elements in linkedlist.
 */
int getElemNum(LinkedList);

#endif /* LINKEDLIST_H_ */
