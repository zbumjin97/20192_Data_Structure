#include <stdio.h>
#include <stdlib.h>
#include "stacksADT.h"
#include <stdbool.h>

typedef struct
{
	int row;
	int col;
} POSITION;

int getSize(void);
void fillBoard(STACK* stack, int boardSize);
void printBoard(STACK* stack, int boardSize);
bool guarded(int board[][9], int row, int col, int boardSize);

int main(void)
{
	STACK* stack;
	stack = createStack();
	int boardSize = getSize();
	fillBoard(stack, boardSize);
	printBoard(stack, boardSize);
	destroyStack(stack);
	return 0;
}

int getSize(void)
{
	int boardSize;
	printf("8 Queens: board size from 4x4 to 8x8.\n");
	printf("Please enter the board size: ");
	scanf_s("%d", &boardSize);
	while (boardSize < 4 || boardSize>8)
	{
		printf("Please re-enter the board size: ");
		scanf_s("%d", &boardSize);
	}
	return boardSize;
}

void fillBoard(STACK* stack, int boardSize)
{
	int row = 1, col = 0;
	int board[9][9] = { 0 };
	POSITION* pPos;
	while (row <= boardSize)
	{
		while (col <= boardSize && row <= boardSize)
		{
			col++;
			if (!guarded(board, row, col, boardSize))
			{
				board[row][col] = 1;
				pPos = (POSITION*)malloc(sizeof(POSITION));
				pPos->row = row;
				pPos->col = col;
				pushStack(stack, pPos);
				row++;
				col = 0;
			}
			while (col >= boardSize)
			{
				pPos = (POSITION*)popStack(stack);
				row = pPos->row;
				col = pPos->col;
				board[row][col] = 0;
				free(pPos);
			}
		}
	}
	return;
}

bool guarded(int board[][9], int chkRow, int chkCol, int boardSize)
{
	int row;
	int col;
	col = chkCol;
	for (row = 1; row <= chkRow; row++)
		if (board[row][col] == 1)
			return true;
	for (row = chkRow - 1, col = chkCol + 1;
		row > 0 && col <= boardSize;
		row--, col++)
		if (board[row][col] == 1)
			return true;
	for (row = chkRow - 1, col = chkCol - 1;
		row > 0 && col > 0;
		row--, col--)
		if (board[row][col] == 1)
			return true;
	return false;
}

void printBoard(STACK* stack, int boardSize)
{
	int col;
	POSITION *pPos;
	STACK* pOutStack;
	if (emptyStack(stack))
	{
		printf("No positions on this board.\n");
		return;
	}
	printf("\nSolution of placing queens:\n");
	pOutStack = createStack();
	while (!emptyStack(stack))
	{
		pPos = (POSITION*)popStack(stack);
		pushStack(pOutStack, pPos);
	}
	while (!emptyStack(pOutStack))
	{
		pPos = (POSITION*)popStack(pOutStack);
		printf("(%d, %d)\t",
			pPos->row, pPos->col);
		for (col = 1; col <= boardSize; col++)
		{
			if (pPos->col == col)
				printf("1 ");
			else
				printf("0 ");
		}
		printf("\n");
	}
	printf("\n");
	destroyStack(pOutStack);
	return;
}