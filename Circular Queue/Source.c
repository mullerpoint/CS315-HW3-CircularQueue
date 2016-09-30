//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Gary Muller
// Fall 2016
// CS 315 Assignment 3
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// A program that creates and utilizes a uni-directional cirular linked list to form a queue, 
// it will utilize a struct type def, and includes an add and remove functionality
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////


//Header files standard libraries and classes
#include <stdio.h> //standard io functions for C
#include <stdlib.h> //used for better malloc() function
#include <ctype.h> //used for tolower() function
#include <stdbool.h> //used for bool types


//Gloabal Variables and Defines
//Structure Type Definition for a linked list structure
typedef struct Queue
{
	//"payload"
	int itemData;
	//pointer to next item
	struct Queue *nextItem;
}QUEUE_ITEM;


//Function Prototypes
int addItem(QUEUE_ITEM**, char);
QUEUE_ITEM* removeItem(QUEUE_ITEM**);
int printQueue(QUEUE_ITEM**); //TEMP FUNCTION FOR TESTING PURPOSES 
//


main()
{
	//Variable Declarations
	char activity = ' ';
	char tempItemData = ' ';

	//Queue Declaration

	QUEUE_ITEM *ptrToQueueA = NULL;

	//loop for program body
	while (activity != 'q')
	{
		//query user for input on next action and normalize input
		printf(" Enter \"i\" to insert a new element, \"r\" to remove an element,  \"q\" to quit:");
		scanf(" %c", &activity);
		activity = tolower(activity); //make all inputs lowercase

		//use input as a case in switch

		switch (activity)
		{
		case 'i':
			//insert case
			//query user for number to add
			printf("Enter character to be enqueued (inserted): ");
			scanf(" %c", &tempItemData);

			//add number to queue
			addItem(&(ptrToQueueA), tempItemData);

			//print new queue for user
			//queue header
			//printf("\nThe queue is currently:\n");
			//printQueue(&(ptrToQueueA));

			break;

		case 'r':
			//remove case
			//only bother asking for a removal input if there is anything that could be removed
			if (ptrToQueueA != NULL)
			{
				//return variable
				QUEUE_ITEM *returnedItem;

				//remove next item from the queue
				returnedItem = removeItem(&(ptrToQueueA));

				//print new queue
				//queue header
				//printf("\nThe queue is currently:\n");
				//printQueue(&(ptrToQueueA));
				printf("The character removed was an \"%c\"\n\n", (returnedItem->itemData));
			}

			//the queue is already empty
			else
			{
				//inform the user they are a fool
				printf("The queue is currently empty\n\n");
			}

			break;

		case 'q':
			//quit case
			//print the final queue
			//printf("Your final queue was: ");
			//printQueue(&(ptrToQueueA));

			//quit gracefully
			printf("\n\nBye\n");

			break;

		default:
			printf("Please only use the specified inputs: i for insert, r for remove, or q to quit\n\n");
			break;
		}//switch

	}//while

}//main


//function that adds an item to the queue
int addItem(QUEUE_ITEM **queuePtr, char newItemData)
{
	//get memory for new insert
	QUEUE_ITEM *newQueueItemPtr = NULL;
	newQueueItemPtr = malloc(sizeof(QUEUE_ITEM));
	
	//build the queue item
	//set the items data to the data to what the user input
	newQueueItemPtr->itemData = newItemData;
	//set the next item to itself
	newQueueItemPtr->nextItem = newQueueItemPtr;
	
	//insert to empty queue
	if (*queuePtr == NULL)
	{
		//set the queue pointer to the new rear of the queue
		*queuePtr = newQueueItemPtr;

		//return success
		return 1;
	}
	//generall insert case
	else
	{
		//set newitem to point at what the rear points at points at
		newQueueItemPtr->nextItem = (*queuePtr)->nextItem;

		//set former rear to point at new rear
		(*queuePtr)->nextItem = newQueueItemPtr;

		//update the rear of the list
		*queuePtr = newQueueItemPtr;

		//return success
		return 1;
	}

	//return failure
	return 0;
}//addItem()


//function that removes a specific item from the specified queue
QUEUE_ITEM* removeItem(QUEUE_ITEM **queuePtr)
{

	//no items in queue
	if (*queuePtr == NULL)
	{
		//there is nothing to do
		printf("The queue is currently empty\n\n");

		//return success
		return NULL;
	}
	//only one item in queue
	else if ((*queuePtr)->nextItem == (*queuePtr))
	{
		//get the item to be removed
		QUEUE_ITEM *removalPtr = (*queuePtr);
		
		//becuase this is the only item in the queue set the queue to empty/NULL
		(*queuePtr) = NULL;
		
		//return success
		return removalPtr;
	}
	//normal removal
	else
	{
		//get the item to be removed
		QUEUE_ITEM *removalPtr = (*queuePtr)->nextItem;

		//set the rear to point at the new front
		(*queuePtr)->nextItem = removalPtr->nextItem;

		//return success
		return removalPtr;
	}




	return NULL;
}//removeItem()


//function that traverses the specified queu and prints out every item
int printQueue(QUEUE_ITEM **queuePtr)
{
	//check if the queue is empty
	if ((*queuePtr) == NULL)
	{
		printf("\n");
		//return success
		return 1;
	}

	else //the queue does not start with NULL ie: its not empty
	{
		//queue traversal pointer
		QUEUE_ITEM *queueTraversalPtr = (*queuePtr)->nextItem;

		//side decalration
		printf(" front -> ");

		//loop to print all the items in the queue stop when you get back to the start
		do
		{
			//print the item data
			printf("%c", queueTraversalPtr->itemData);

			//if its not the last item print an arrow
			if (queueTraversalPtr->nextItem != NULL)
			{
				printf(" -> ");
			}

			//traverse to the next item in the queue
			queueTraversalPtr = queueTraversalPtr->nextItem;

		} while (queueTraversalPtr != (*queuePtr)->nextItem);

		//side decaration
		printf("rear");

		//print newlines after the queue to indicate completion 
		printf("\n\n");

		//return success
		return 1;

	}//else

	//return failure
	return 0;
}//printQueue
