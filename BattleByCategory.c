#include "BattleByCategory.h"
#include "LinkedList.h"
#include "MaxHeap.h"

struct battle_s
{
	copyFunction copyFunc;
	freeFunction freeFunc;
	printFunction printFunc;
	getCategoryFunction getCategory;
	getAttackFunction getAttack;
	int capacity;
	int numberOfCategories;
	LinkedList bList;

};


/*
 * This function get pointer to heap, and creates shallow copy.
 * get - Heap
 * return new pointer to same heap
 */
MaxHeap CopyHeap(MaxHeap heap)
{
	if (heap == NULL)
		return NULL;
	return heap;
}

int comapreHeap(MaxHeap heap, char* ID)
{
	if ((heap == NULL) || (ID == NULL)) return -1;
	char* heapName = getHeapId(heap);
	if (strcmp(heapName,ID) == 0)
		{
			free(heapName);
			return 0;
		}
	else
	{
		free(heapName);
		return 1;
	}
}
int heapEqual(MaxHeap heap1, MaxHeap heap2)
{
	if ((heap1 == NULL) || (heap1 == NULL)) return -1;
	char* h1ID = getHeapId(heap1);
	if (h1ID == NULL)
		return -1;

	char* h2ID = getHeapId(heap2);

	if (h2ID == NULL)
	{
		free(h1ID);
		return -1;
	}

	int res = strcmp(h1ID,h2ID);
	free(h1ID);
	free(h2ID);

	return res;

}

Battle createBattleByCategory(int capacity,int numberOfCategories,char* categories,equalFunction equalElement,copyFunction copyElement,freeFunction freeElement,getCategoryFunction getCategory,getAttackFunction getAttack,printFunction printElement)
{

	if ((capacity < 0) || (numberOfCategories < 0) ||(categories == NULL) || (copyElement == NULL) || (freeElement == NULL) ||
				(printElement == NULL) || (equalElement == NULL) || (getAttack == NULL) || (getCategory == NULL))
		return NULL;
	Battle battle = (Battle) malloc (sizeof(struct battle_s));
	if (battle == NULL)
		return NULL;

	battle->bList = createLinkedList((copyFunction)CopyHeap, (freeFunction)destroyHeap,
			(printFunction)printHeap, (equalFunction)heapEqual, (compareFunction)comapreHeap);
	if (battle->bList == NULL)
	{
		free(battle);
		battle = NULL;
		return NULL;
	}
	battle->printFunc = printElement;
	battle->copyFunc = copyElement;
	battle->freeFunc = freeElement;
	battle->getCategory = getCategory;
	battle->getAttack = getAttack;
	int i;
	status appednS;
	char* heapID = NULL;
	heapID = strtok(categories, ",");
	for (i=0; i<numberOfCategories; i++)
	{
		 // know its legal input
		MaxHeap heap;
		// heap gets element attribute
		heap = CreateHeap(capacity, heapID, copyElement, freeElement, printElement, equalElement);
		if (heap == NULL)
		{
			destroyList(battle->bList);
			battle->bList = NULL;
			free(battle);
			battle = NULL;
			destroyBattleByCategory(battle);
			battle = NULL;
			return NULL;
		}
		appednS = appendNode(battle->bList, heap);
		if (appednS == memofail)
		{
			// this node coudlnt be created
			// 1. delte linked list -> in linked list, free function is heap free function
			destroyHeap(heap);
			heap = NULL;
			destroyList(battle->bList);
			battle->bList = NULL;
			destroyBattleByCategory(battle);
			battle = NULL;
			return NULL;
		}
		heapID = strtok(NULL, ",");
	}
	return battle;
}


void displayObjectsByCategories(Battle b)
{
	if (b != NULL)
	{
		displayList(b->bList);
	}
}

status destroyBattleByCategory(Battle b)
{
	status s;
	if (b == NULL)
		return failure;
	// nothing to destroy
	if (b->bList != NULL)
		s = destroyList(b->bList);
	b->bList = NULL;
	free(b);
	b = NULL;
	return s;
}

status insertObject(Battle b, element elem)
{
	if ((b == NULL) || (elem == NULL))
		return failure;
	char* cat = b->getCategory(elem);
	MaxHeap insertTo = searchByKeyInList(b->bList, cat);
	if (insertTo == NULL)
		// category doesn't exist, or MEMOFAIL
		return failure;

	else
		return insertToHeap(insertTo, elem);
}

element removeMaxByCategory(Battle b,char* category)
{
	if ((b == NULL) || (category == NULL)) return NULL;
	MaxHeap removeFrom = searchByKeyInList(b->bList, category);
	if (removeFrom == NULL) return NULL;
	return PopMaxHeap(removeFrom);
}

int getNumberOfObjectsInCategory(Battle b,char* category)
{
	if ((b == NULL) || (category == NULL)) return -1;
	MaxHeap objNumIn = searchByKeyInList(b->bList, category);
	return getHeapCurrentSize(objNumIn);
}

element fight(Battle b,element elem)
{

	if ((b == NULL) || (elem == NULL)) return NULL;
	if (getElemNum(b->bList) == 0) return NULL; // no elements to fight with
	// the first element in each heap is the strongest.
	int i = 0;
	//MaxHeap maxHeap = NULL;
	MaxHeap curHeap = NULL;
	element maxElem = NULL;
	element curElem = NULL;
	int MaxAttack1 = 0;
	int MaxAttack2 = 0;
	int attack1 = 0;
	int attack2 = 0;
	int difAttacks = 0;
	int winner = 0;
	for (i = 0; i < getElemNum(b->bList); i++)
	{
		curHeap = getNode(b->bList, i);
		if (maxElem == NULL)
		{
			if (getHeapCurrentSize(curHeap) == 0) continue;
			else
			{
				maxElem = TopMaxHeap(curHeap);
				if (maxElem == NULL) return NULL;
				winner = b->getAttack(maxElem, elem, &MaxAttack1, &MaxAttack2);
			}
		}
		else
		{
			if (getHeapCurrentSize(curHeap) == 0) continue;
			curElem = TopMaxHeap(curHeap);
			if (curElem == NULL) return NULL;
			difAttacks = b->getAttack(curElem, elem, &attack1, &attack2);
			if (difAttacks > winner)
			{
				b->freeFunc(maxElem);
				maxElem = curElem;
				MaxAttack1 = attack1;
				MaxAttack2 = attack2;
				winner = difAttacks;
			}
			else
				b->freeFunc(curElem);

		}
	}
	if (maxElem == NULL)
		return NULL;


	printf("The final battle between:\n");
	b->printFunc(elem);
	printf("In this battle his attack is :%d\n\n", MaxAttack2);
	printf("against ");
	b->printFunc(maxElem);
	printf("In this battle his attack is :%d\n\n", MaxAttack1);
	if (winner == 0)
	{
		printf("IT IS A DRAW.\n");
		return maxElem;
	}
	else
	{
		printf("THE WINNER IS:\n");
		if (winner > 0)
		{
			b->printFunc(maxElem);
			return maxElem;
		}
		else
		{
			b->printFunc(elem);
			b->freeFunc(maxElem);
			maxElem = NULL;
			return elem;
		}
	}
}


