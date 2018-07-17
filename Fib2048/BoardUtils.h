#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
typedef struct Board Board;

//Board Struct which holds all the data of the Puzzle
struct Board {
	//Stores the Actual table of all values ,which are being displayed
	int **table;

	//No of rows of Table
	int rows;

};

Board * createBoard(int rows){
	if (rows <= 0)
	{
		return NULL;
	}

	Board *board = (Board*)malloc(sizeof(Board));
	int **firstIndexArray = (int **)malloc(sizeof(int*)*rows);
	for (int i = 0; i < rows; i++)
	{
		*(firstIndexArray + i) = (int *)malloc(sizeof(int)*rows);
	}
	board->table = firstIndexArray;
	board->rows = rows;
	return board;
}

void initializeBoard(Board * source, int rows){
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < rows; j++)
		{
			source->table[i][j] = 0;
		}
	}
	int count = 2;
	while (count != 0)
	{
		int x1, y1;
		x1 = rand() % rows;
		y1 = rand() % rows;
		if (source->table[x1][y1] == 0)
		{
			source->table[x1][y1] = 1;
			count--;
		}
	}
}

int adj_Fib(int x, int y, int *Fib,int rows)
{
	for (int i = 0; i <(2*rows*rows); i++)
	{
		if ((Fib[i] == x&&Fib[i+1] == y) || (Fib[i] == y&&Fib[i+1] == x))//If Adjacent Fibs then return's 1;
		{
			return 1;
		}
	}
	return 0;
}

int FourCorners(Board *board, int i, int j,int *Fib)
{
	int a = 0, b = 0, c = 0, d = 0;
	if (i - 1 >= 0 && i-1 < board->rows)
	{
		if (adj_Fib(board->table[i][j], board->table[i - 1][j],Fib,board->rows) == 1)
		{
			a = 1;
		}
	}
	if (i + 1 >= 0 && i+1 < board->rows)
	{
		if (adj_Fib(board->table[i][j], board->table[i + 1][j], Fib, board->rows) == 1)
		{
			b = 1;
		}
	}
	if (j-1>= 0 && j-1< board->rows)
	{
		if (adj_Fib(board->table[i][j], board->table[i][j-1], Fib, board->rows) == 1)
		{
			c = 1;
		}
	}
	if (j+1 >= 0 && j+1 < board->rows)
	{
		if (adj_Fib(board->table[i][j], board->table[i][j+1], Fib, board->rows) == 1)
		{
			d = 1;
		}
	}
	if (a + b + c + d != 0)
		return 1;
	return 0;
}

bool isEmpty_Tile1(Board *board)
{
	for (int i = 0; i < board->rows; i++)
	{
		for (int j = 0; j < board->rows; j++)
		{
			if (board->table[i][j] == 0)
				return true;
		}
	}
	return false;
}
/*
Check Win/Lose:
Winning condition is when any Tile reaches (2*(n*n))th Fibo number. Ie for 2x2 , game ends when any tile reaches 8th fibo number (2x2x2) . First fibo number is 0, 2nd is 1, 3rd is 1. 4 -> 2, 5-> 3, 6 -> 5 , 7 ->8, 8->13. So for a 2x2 board game ends when any tile reaches 13. For 3x3 board game ends when any tile reaches 18th fibo ie 1597.
-> Loosing condition is when no further moves can be made, ie the following board.

*/
int checkBoard(Board * board,int *Fib){
	if (isEmpty_Tile1(board) == true)
		return 0;
	for (int i = 0; i < board->rows; i++)
	{
		for (int j = 0; j < board->rows; j++)
		{
			if (FourCorners(board, i, j,Fib) == 1)
			{
				return 0;
			}
		}
	}
	return 1;
}


void drawBoardOnScreen(Board *board){

	for (int i = 0; i <board->rows; i++)
	{
		printf("\t\t\t\t");
		for (int j = 0; j < board->rows; j++)
		{
			if (*(*(board->table + i) + j) != 0)
			{
				printf("%d\t", *(*(board->table + i) + j));
			}
			else
			{
				printf(".\t");
			}
		}
		printf("\n\n");
	}
	printf("----------[W] UP --- [S] Down --- [A] LEFT --- [D] Right--------------\n\n");

}


//Clear The Screen , So that we can redraw the Board (which has modified values )

void clearScreen(){
	system("cls");
}


//Clear the Screen and ReDraw the Board ,Call above two functions

void clearAndRedrawScreen(Board * board){
	clearScreen();
	drawBoardOnScreen(board);
}

//Reloading the paused Game
void Reload_Game(Board *board, char **field, int len)
{
	int rows = board->rows;
	int k = 1;
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < rows; j++)
		{
			if (field[k][0] != '.')
				board->table[i][j] = atoi(field[k]);
			else
				board->table[i][j] = '.';
			k++;
		}
	}
}