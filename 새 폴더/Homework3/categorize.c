#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include "QUEUEADT.h"

void fillQueues(QUEUE*, QUEUE*, QUEUE*, QUEUE*);
void printOneQueue(QUEUE* queue);
void printQueues(QUEUE*, QUEUE*, QUEUE*, QUEUE*);

int main(void)
{
	QUEUE* q0to9;
	QUEUE* q10to19;
	QUEUE* q20to29;
	QUEUE* qover29;

	q0to9 = createQueue();
	q10to19 = createQueue();
	q20to29 = createQueue();
	qover29 = createQueue();

	fillQueues(q0to9, q10to19, q20to29, qover29);
	printQueues(q0to9, q10to19, q20to29, qover29);
	return 0;
}

void fillQueues(QUEUE* q0to9, QUEUE* q10to19, QUEUE* q20to29, QUEUE* qover29)
{
	int category;
	int item;
	int* dataPtr;
	int number;
	printf("Input the number of data to be categorized: ");
	scanf("%d", &number);
	srand(time(NULL));
	for (int i = 1; i <= number; i++)
	{
		if (!(dataPtr = (int*)malloc(sizeof(int))))
			printf("Overflow in fillQueues\n"),
			exit(100);
		*dataPtr = rand() % 50 + 1;
		item = *dataPtr;
		category = item / 10;
		printf("%3d", item);
		switch (category)
		{
			case 0: enqueue(q0to9, dataPtr); break;
			case 1: enqueue(q10to19, dataPtr); break;
			case 2: enqueue(q20to29, dataPtr); break;
			default: enqueue(qover29, dataPtr); break;
		}
	}
	printf("\nEnd of data categorization\n\n");
}

void printQueues(QUEUE* q0to9, QUEUE* q10to19, QUEUE* q20to29, QUEUE* qover29)
{
	printf("Data 0~9: ");
	printOneQueue(q0to9);

	printf("Data 10~19: ");
	printOneQueue(q10to19);

	printf("Data 20~29: ");
	printOneQueue(q20to29);

	printf("Data over 29: ");
	printOneQueue(qover29);
}

void printOneQueue(QUEUE* queue)
{
	int lineCount;
	int* dataPtr;
	lineCount = 0;
	while (!emptyQueue(queue))
	{
		dequeue(queue, (void*) &dataPtr);
		if (lineCount++ > 10)
		{
			lineCount = 1;
			printf("\n");
		}
		printf("%3d", *dataPtr);
	}
	printf("\n");
}