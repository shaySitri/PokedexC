#include "LinkedList.h"

struct LinkedList_t
{
	copyFunction copyFunc;
	freeFunction freeFunc;
	printFunction printFunc;
	equalFunction equalFunc;
	compareFunction cmpFunc;
	struct Node_t* head;
	struct Node_t* end;
	int numElem;
};

//, getCategoryFunction catFunc ||(catFunc == NULL)
typedef struct Node_t
{
	element elem; // element = void* -> so element is already pointer to sturct.
	struct Node_t *next;
}Node;

LinkedList createLinkedList(copyFunction copyFunc, freeFunction freeFunc, printFunction printFunc,
		equalFunction equalFunc, compareFunction cmpFunc)
{
	if ((copyFunc == NULL) || (freeFunc == NULL) ||
			(printFunc == NULL) || (equalFunc == NULL) )
		return NULL;
	// How to handle memory problem its a decision of user.
	LinkedList list = (LinkedList) malloc(sizeof(struct LinkedList_t));
	if (list == NULL) // malloc failed
		return NULL;
	else
	{
		list->copyFunc = copyFunc;
		list->equalFunc = equalFunc;
		list->freeFunc = freeFunc;
		list->printFunc = printFunc;
		list->cmpFunc = cmpFunc;
		list->numElem = 0;
		list->head = NULL;
		list->end = NULL;
	}
	return list;
}


status appendNode(LinkedList list, element element)
{
	if ((element == NULL) || (list == NULL))
	{
		return failure;
	}

	else
	{
		Node* insert_node = (Node*) malloc(sizeof(Node)); // allocate memory for
		if (insert_node == NULL) // allocation failed!
			return memofail; // after memory fail allocated place for another node-> it doiesnt destroy all list itself
								// destroy list or not?

		insert_node->elem = list->copyFunc(element);
		if (insert_node->elem == NULL)
			return memofail; // failed to allocate element.

		if (list->numElem == 0) // empty list
		{
			list->head = insert_node;
			list->end = insert_node;
		}
		else
		{
			list->end->next = insert_node;
			list->end = list->end->next;
		}
		list->numElem++;
	}
	return success;
}

status deleteNode(LinkedList list, element elem)
{
	// elem - is elemnet we want do delete.
	// equal func will check if 2 elements are equal.

	if ((list == NULL) || (elem == NULL)) return failure;
	else
	{
		Node* curNode = NULL;
		Node* prevNode = NULL;
		curNode = list->head;
		prevNode = NULL;

		bool exist;
		exist = false;

		int i = 0 ;
		//while(curNode != NULL) // check if element to delete exist in list
		// line 96 uninitialized value
		for (i=0; i<list->numElem; i++)
		{
			if (curNode != NULL){
			if (curNode->elem != NULL)
			{
				if (list->equalFunc(elem, curNode->elem) == 0)
				{
					exist = true;
					break;
				}

				prevNode = curNode;
				curNode = curNode->next;
			}
			}

		}

		if (exist == false) return failure; // element doesnt exist!


		if (curNode == list->head)
		{
			// if the element is the head of the linked list-
			// the head needed to be the previous head next
			// if the linked list has only 1 element, both head and end are null.
			list->head = curNode->next;
			if (curNode == list->end)
				list->end = curNode->next;
			//curNode->next = NULL;
			list->freeFunc(curNode->elem);
			curNode->elem = NULL;
			free(curNode);
			curNode = NULL;
		}
		else
		{
			// if element is the end of the list,
			// the new end of the list will be the previous to current Node.
			if (curNode == list->end)
				list->end = prevNode;
			prevNode->next = curNode->next;
			//curNode->next = NULL;
			list->freeFunc(curNode->elem);
			curNode->elem = NULL;
			free(curNode);
			curNode = NULL;

		}
		list->numElem--;
	}
	return success;

}


status destroyList(LinkedList list)
{
	// for destroy list - we will run all over list nodes, and delete them.
	// at the end - free list itself.
	status s = failure;
	if (list != NULL)
	{

		Node *curNode, *nextNode;
		curNode = list->head;
		nextNode = NULL;
		int i, prevENum;
		i = 0;
		prevENum = list->numElem;
		while(i < prevENum)
		{
			nextNode = curNode->next;
			s = deleteNode(list, curNode->elem);
			if (s == failure) return s; // if free faild, stop
			curNode = nextNode;
			i++;
		}

		free(list);
		list = NULL;
	}
	return s;
}

status displayList(LinkedList list)
{
	if (list == NULL) return failure;
	status s = failure;
	Node* curNode = NULL;
	curNode = list->head;
	int i;
	i= 0;
	while (i < list->numElem)
	{
		s = list->printFunc(curNode->elem);
		curNode = curNode->next;
		i++;
	}
	return s;
}

Element searchByKeyInList(LinkedList list, Element elem)
{
	// element - type of category we search by
	if ((list == NULL) || (elem == NULL))
		return NULL;
	else
	{
		Node* curNode;
		curNode = list->head;
		int i;
		i = 0;
		while(i < list->numElem)
		{
			if (list->cmpFunc(curNode->elem, elem) == 0)
				return list->copyFunc(curNode->elem);
			i++;
			curNode = curNode->next;
		}
	}
	return NULL;
}

Element getNode(LinkedList list, int i)
{
	if (list == NULL) return NULL;
	if (i >= list->numElem) return NULL;
	else
	{
		int x = 0;
		Node* curNode = list->head;
		while (x < list->numElem)
		{
			if (x == i)
				break;
			curNode = curNode->next;
			x++;
		}
		return list->copyFunc(curNode->elem);
	}
}

int getElemNum(LinkedList list)
{
	if (list == NULL) return -1;
	return list->numElem;
}

