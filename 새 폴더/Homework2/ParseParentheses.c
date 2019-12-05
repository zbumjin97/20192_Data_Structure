#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "stacksADT.h"

const char closMiss[] = "Close paren missing at line";
const char openMiss[] = "Open paren missing at line";

int main(void)
{
	STACK* stack;
	char token;
	char* dataPtr;
	char fileID[25];
	FILE* fpIn;
	int lineCount = 1;

	stack = createStack();
	printf("Enter file ID for file to be parsed: ");
	scanf("%s", &fileID);
	fpIn = fopen(fileID, "r");
	if (!fpIn)
		printf("Error opening %s\n", fileID), exit(100);
	while ((token = fgetc(fpIn)) != EOF)
	{
		if (token == '\n')
			lineCount++;
		if (token == '(')
		{
			dataPtr = (char*)malloc(sizeof(char));
			pushStack(stack, dataPtr);
		}
		else
		{
			if (token == ')')
			{
				if (emptyStack(stack))
				{
					printf("%s %d\n", openMiss, lineCount);
					return 1;
				}
				else
					popStack(stack);
			}
		}
	}
	if (!emptyStack(stack))
	{
		printf("%s %d\n", closMiss, lineCount);
		return 1;
	}
	destroyStack(stack);
	printf("Parsing is OK: %d Lines parsed.\n", lineCount);
	return 0;
}