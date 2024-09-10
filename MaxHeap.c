#include "MaxHeap.h"

struct MaxHeap_t
{
	copyFunction copyFunc;
	freeFunction freeFunc;
	printFunction printFunc;
	equalFunction equalFunc;
	int capcity;
	int curNumElem;
	char* heapID;
	element* arrHeap;
};

/* maxHeapify - helper function. Necessary for maintains of heap.
 * get: heap, array of elements (actual heap), number of elements.
 * return - status if maxHeapify succeed to maintain heap.
 * return failure if heap is NULL or array of elements is NULL.
 */
status maxHeapify(MaxHeap heap,element* elemArr, int i, int elemNum)
{
	if ((heap == NULL) || (elemArr == NULL)) return failure;
	int left = 2*i+1;
	int right = 2*i+2;
	int maxIdx = i;
	element tmp = NULL;
	if ((left < elemNum) && (heap->equalFunc(elemArr[left],elemArr[maxIdx]) == 1))
		maxIdx = left;
	else
		maxIdx = i;
	if ((right < elemNum) && (heap->equalFunc(elemArr[right],elemArr[maxIdx]) == 1))
		maxIdx = right;
	if (maxIdx != i)
	{
		tmp = elemArr[i];
		elemArr[i] = elemArr[maxIdx];
		elemArr[maxIdx] = tmp;
		maxHeapify(heap, elemArr, maxIdx, elemNum);
	}
	return success;
}

/* printHelper - print elements in list from bigger to smaller.
 * get - heap
 *  return status. print failes when heap is NULL somehow.
 */
status printHelper(MaxHeap heap) // heap sort and then print
{
	status s = failure;
	if (heap == NULL) return s;
	element sortedHeap[heap->curNumElem];
	element temp = NULL;
	int i;
	for (i = 0; i<heap->curNumElem; i++) // copy heap to temporally heap (not dynamic)
		sortedHeap[i] = heap->arrHeap[i];
	int elemNum = heap->curNumElem;
	for (i = heap->curNumElem-1; i>=0; i--)
	{
		temp = sortedHeap[0];
		sortedHeap[0] = sortedHeap[elemNum-1];
		sortedHeap[elemNum-1] = temp;
		elemNum--;
		s = maxHeapify(heap, sortedHeap, 0, i);
		if (s == failure)
			return s;
	}

	int indexprint = 1;
	for (i = heap->curNumElem-1; i>=0; i--)
	{
		printf("%d. ",indexprint);
		s = heap->printFunc(sortedHeap[i]);
		indexprint++;
		if (s == failure)
			return s;
	}
	return s;

}

/* HeapIncreaseKey - helper function for adding new element to heap.
 * get - heap, i - number of elements, copy of elements to add.
 * return status.
 */
status HeapIncreaseKey(MaxHeap heap, int i, element elem)
{
	if ((heap == NULL) || (elem == NULL)) return failure;
	heap->arrHeap[i-1] = elem;
	// 0 = equal, 1-new element > parent, -1- new element<parent
	while ((i > 1) && (heap->equalFunc(elem, heap->arrHeap[(i/2)-1]) == 1))
	{
		heap->arrHeap[i - 1] = heap->arrHeap[(i/2)-1];
		heap->arrHeap[(i/2) - 1] = elem;
		i = i/2;
	}
	return success;
}



MaxHeap CreateHeap(int capacity, char* name, copyFunction copyFunc, freeFunction freeFunc,
		printFunction printFunc, equalFunction equalFunc)
{
	if ((capacity < 0) || (name == NULL) || (copyFunc == NULL) || (freeFunc == NULL) ||
			(printFunc == NULL) || (equalFunc == NULL))
		return NULL;
	MaxHeap heap = (MaxHeap) malloc(sizeof(struct MaxHeap_t));
	if (heap == NULL)
		return NULL;
	else
	{
		heap->heapID = (char*) calloc((strlen(name))+1, (sizeof(char)));
		if (heap->heapID == NULL)
			return NULL;

		else
		{
			strcpy(heap->heapID, name);
			heap->capcity = capacity;
			heap->curNumElem = 0;
			heap->copyFunc = copyFunc;
			heap->freeFunc = freeFunc;
			heap->printFunc = printFunc;
			heap-> equalFunc = equalFunc;
			// dynamic array, at first there are no elements.
			heap->arrHeap = (element*) calloc(0,sizeof(element));
		}
	}
	return heap;
}

status destroyHeap(MaxHeap heap)
{
	status stat = success;
	if (heap == NULL)
	{
		if (heap->curNumElem != 0)
			return failure;

	}
	int i;
	if (heap->curNumElem != 0)
	{
		for(i = 0; i<heap->curNumElem; i++)
		{
			if (heap->arrHeap[i] != NULL)
				heap->freeFunc(heap->arrHeap[i]);
			else
				stat = failure;
		}
	}

	free(heap->arrHeap);
	heap->arrHeap = NULL;
	free(heap->heapID);
	heap->heapID = NULL;
	free(heap);
	heap = NULL;
	return stat;

}

int getHeapCurrentSize(MaxHeap heap)
{
	if (heap == NULL)
		return -1;
	return heap->curNumElem;
}

status printHeap(MaxHeap heap)
{
	// in this function we print ONLY heap names, and check if there are element inside.
	status s = failure;
	if (heap == NULL)
		return failure;
	if (heap->curNumElem == 0)
	{
		printf("%s:\n",heap->heapID);
		printf("No elements.\n\n");
		s = success;
	}
	else
	{
		printf("%s:\n",heap->heapID);
		s = printHelper(heap);
		if (s == failure)
			return s;
		s = success;
	}
	return s;
}


status insertToHeap(MaxHeap heap, element elem)
{
	if ((heap == NULL)||(elem == NULL))
		return failure;
	if (heap->capcity == heap->curNumElem)
		return failure; // no place

	heap->curNumElem++;

	element insertElem = heap->copyFunc(elem);
	if (insertElem == NULL) return memofail;
	heap->arrHeap = (element*) realloc(heap->arrHeap, sizeof(element)*heap->curNumElem);
	if (heap->arrHeap == NULL)
		return memofail;
	if (heap->curNumElem == 1)
		heap->arrHeap[0] = insertElem;

	else
	{
		int i;
		heap->arrHeap[heap->curNumElem-1] = insertElem;
		for (i = (heap->curNumElem/2)-1; i>=0; i--)
				maxHeapify(heap, heap->arrHeap, i, heap->curNumElem);
	}
		//s = HeapIncreaseKey(heap, heap->curNumElem, insertElem);
	return success;

}

element PopMaxHeap(MaxHeap heap)
{
	if (heap == NULL) return NULL;
	if (heap->curNumElem == 0) return NULL;
	Element popElem = heap->arrHeap[0];
	heap->arrHeap[0] = heap->arrHeap[heap->curNumElem-1];
	heap->curNumElem--;
	int i;
	for (i = (heap->curNumElem/2)-1; i>=0; i--)
		maxHeapify(heap, heap->arrHeap, i, heap->curNumElem);
	return popElem;
}

element TopMaxHeap(MaxHeap heap)
{
	if (heap == NULL) return NULL;
	if (heap->curNumElem == 0) return NULL;
	element TopElem = heap->copyFunc(heap->arrHeap[0]);
	return TopElem;
}

char* getHeapId(MaxHeap heap)
{
	if (heap == NULL)
		return NULL;
	char* copyHeapID = (char*) malloc(sizeof(char)*(strlen(heap->heapID) + 1));
	strcpy(copyHeapID, heap->heapID);
	if (copyHeapID == NULL) return NULL;
	return copyHeapID;
}


