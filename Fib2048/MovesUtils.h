
#include<stdio.h>
#include"BoardUtils.h"
#include"UserUtils.h"
int goLeft(Board *board);
int goUp(Board *board);
int goDown(Board *board);
int goRight(Board *board);
void swap(Board *board, int x1, int y1, int x2, int y2);
int isValidInput(char letter);
int check(Board *board, int x, int y, int *FibArray);
void playMove(Board *board, User *user, char choice);
void Random_Tile(Board *board);
void Win_Condition(Board *board, int x, int y, User *user);
void ShiftRight_all_Zeros(Board *board);
void ShiftLeft_all_Zeros(Board *board);
void ShiftUp_all_Zeros(Board *board);
void ShiftDown_all_Zeros(Board *board);
bool isEmpty_Tile(Board *board,bool possible);

/*
Take Only Valid Input W,A,S,D,w,a,s,d . If Invalid input is entered ,Take input again . Keep Taking input until its valid
Hint : Use While Loop and isValidInput function
*/

char takeInput()
{
	char c;
	while (1)
	{
		scanf("%c", &c);
		if (isValidInput(c) == 1)
		{
			return c;
		}
		else
		{
			fflush(stdin);
		}
	}
}
/*
Return 1 for Valid Input ie if w,a,s,d,W,A,S,D are entered .
Return 0 for all other inputs
*/
int isValidInput(char letter){

	if (letter == 'W' || letter == 'A' || letter == 'S' || letter == 'D' || letter == 'w' || letter == 'a' || letter == 's' || letter == 'd' || letter == 'Z' || letter == 'z'||letter=='P'||letter=='p')
	{
		return 1;
	}
	return 0;
}

void Random_Tile(Board *board)
{
	while (1)
	{
		int x1, y1;
		x1 = rand() % board->rows;
		y1 = rand() % board->rows;
		if (board->table[x1][y1] == 0)
		{
			board->table[x1][y1] = 1;
			break;
		}
	}
}

bool isEmpty_Tile(Board *board)
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

int final_check(Board *board,bool possible)
{
	possible = isEmpty_Tile(board);									//Generate Random Empty Tile With 1
	if (possible == true)
	{
		Random_Tile(board);
		return 1;
	}
	else
		return 0;
}

int goLeft(Board *board, int *Fib, User *user)
{
	bool possible = false;
	for (int i = 0; i <board->rows&&user->flag == 0; i++)					//Move to Each Row
	{
		int j = 0, k = 1;
		while (user->flag == 0&&j < (board->rows) - 1 && k<board->rows)
		{
			if (board->table[i][j] == 0)					//Check For First non Empty Tile
			{
				j++;
				k++;
			}
			else if (board->table[i][k] == 0)			    //Check For Second Non Empty Tile
			{
				k++;
			}
			else if (check(board, board->table[i][j], board->table[i][k], Fib) == 1)	     	//Check Adjacent Numbers or Not
			{
				possible = true;
				board->table[i][j] = board->table[i][j] + board->table[i][k];
				board->table[i][k] = 0;
				Win_Condition(board, i, j, user);
				j = k + 1;
				k = j + 1;
			}
			else
			{
				j = k;
				k = j + 1;
			}
		}
		ShiftRight_all_Zeros(board);
	}
	if (user->flag == 0)
		return final_check(board, possible);
	else
		return 0;
}

int goRight(Board *board, int *Fib, User *user)
{
	bool possible = false;
	for (int i = 0; i <board->rows&&user->flag == 0; i++)					//Move to Each Row
	{
		int j = (board->rows) - 1, k = j - 1;
		while (j >0 && k >= 0 && user->flag == 0)
		{
			if (board->table[i][j] == 0)					//Check For First non Empty Tile
			{
				j--;
				k--;
			}
			else if (board->table[i][k] == 0)			    //Check For Second Non Empty Tile
			{
				k--;
			}
			else if (check(board, board->table[i][j], board->table[i][k], Fib) == 1)		    //Check Adjacent Numbers or Not
			{
				possible = true;
				board->table[i][j] = board->table[i][j] + board->table[i][k];
				board->table[i][k] = 0;
				Win_Condition(board, i, j, user);
				j = k - 1;
				k = j - 1;
			}
			else
			{
				j = k;
				k = j - 1;
			}
		}
		ShiftLeft_all_Zeros(board);						    //ShiftLeft_allZeros
	}
	if (user->flag == 0)
		return final_check(board, possible);
	else
		return 0;
}

int goUp(Board *board, int *Fib, User *user)
{
	bool possible = false;
	for (int i = 0; i<board->rows&&user->flag == 0; i++)				   		//Move to Each Column
	{
		int j = 0, k = 1;
		while (user->flag == 0&&k < board->rows&&j<(board->rows) - 1)
		{
			if (board->table[j][i] == 0)					//Check For First non Empty Tile
			{
				j++;
				k++;
			}
			else if (board->table[k][i] == 0)	     		//Check For Second Non Empty Tile
			{
				k++;
			}
			else if (check(board, board->table[j][i], board->table[k][i], Fib) == 1)	    	//Check Adjacent Numbers or Not
			{
				possible = true;
				board->table[j][i] = board->table[j][i] + board->table[k][i];
				board->table[k][i] = 0;
				Win_Condition(board, j, i, user);
				j = k + 1;
				k = j + 1;
			}
			else
			{
				j = k;
				k = j + 1;
			}
		}
		ShiftDown_all_Zeros(board);
	}
	if (user->flag == 0)
		return final_check(board, possible);
	else
		return 0;
}


int goDown(Board *board, int *Fib, User *user)
{
	bool possible = false;
	for (int i = 0; i<board->rows&&user->flag==0; i++)					//Move to Each Column
	{
		int j = (board->rows) - 1, k = j - 1;
		while (j >0 && k >= 0 && user->flag == 0)
		{
			if (board->table[j][i] == 0)					//Check For First non Empty Tile
			{
				j--;
				k--;
			}
			else if (board->table[k][i] == 0)			//Check For Second Non Empty Tile
			{
				k--;
			}
			else if (check(board, board->table[j][i], board->table[k][i], Fib) == 1)		//Check Adjacent Numbers or Not
			{
				possible = true;
				board->table[j][i] = board->table[j][i] + board->table[k][i];
				board->table[k][i] = 0;
				Win_Condition(board, j, i, user);
				j= k - 1;
				k = j- 1;
			}
			else
			{
				j = k;
				k = j - 1;
			}
		}
		ShiftUp_all_Zeros(board);
	}
	if (user->flag == 0)
		return final_check(board, possible);
	else
		return 0;
}

int processInput(Board *board, char inputChar, int *Fib, User *user)
{
	if (inputChar == 'W' || inputChar == 'w')
	{
		return goUp(board, Fib, user);
	}
	if (inputChar == 'A' || inputChar == 'a')
	{
		return goLeft(board, Fib, user);
	}
	if (inputChar == 'S' || inputChar == 's')
	{
		return goDown(board, Fib, user);
	}
	if (inputChar == 'D' || inputChar == 'd')
	{
		return goRight(board, Fib, user);
	}
	if (inputChar == 'Z' || inputChar == 'z')
	{
		//Save Present State and Stop Game
		FILE *fp;
		fp = fopen("SavedGameData.txt", "w");
		for (int i = 0; i < board->rows; i++)
		{
			for (int j = 0; j < board->rows; j++)
			{
				fprintf(fp, "%d ", board->table[i][j]);
			}
		}
		fclose(fp);
		user->flag = 2;
		return -1;
	}
	return 0;
}


void playMove(Board* board, User * user, char choice, int *Fib)
{
	while (1)
	{
		int res = processInput(board, choice, Fib, user);
		if (res == 1&&user->flag==0)
		{
			modifyMoveCountBasedOnProccessInput(user, 1);
				break;
		}
		else if (user->flag == 0)
		{
			choice = takeInput();
		}
		else if (res==-1)
			break;
		clearAndRedrawScreen(board);
		printf("You Have Done %d moves\n", user->movesCount);
	}
	clearAndRedrawScreen(board);
	printf("You Have Done %d moves\n", user->movesCount);
}



int check(Board *board, int x, int y, int *FibArray)
{
	for (int i = 0; i < ((2 *board->rows*board->rows)-1); i++)
	{
		if ((FibArray[i] == x && FibArray[i + 1] == y) || (FibArray[i + 1] == x && FibArray[i] == y))
		{
			return 1;
		}
	}
	return 0;
}

void Win_Condition(Board *board, int x, int y, User *user)
{
	if ((board->table[x][y] == 1346269 && board->rows == 4) || (board->table[x][y] == 13 && board->rows == 2))
	{
		user->flag = 1;
		modifyMoveCountBasedOnProccessInput(user,1);
		clearAndRedrawScreen(board);
		printUser(user);
	}
}

void ShiftRight_all_Zeros(Board *board)
{
	for (int i = 0; i < board->rows; i++)
	{
		int j = 0;
		while (j<board->rows)
		{
			if (board->table[i][j] == 0)
			{
				int m = j + 1;
				while (m < board->rows)
				{
					if (board->table[i][m] != 0)
					{
						board->table[i][j] = board->table[i][m];
						board->table[i][m] = 0;
						break;
					}
					m++;
				}
			}
			j++;
		}
	}
}


void ShiftLeft_all_Zeros(Board *board)
{
	for (int i = 0; i < board->rows; i++)
	{
		int j = (board->rows) - 1;
		while (j >= 0)
		{
			if (board->table[i][j] == 0)
			{
				int m = j - 1;
				while (m >= 0)
				{
					if (board->table[i][m] != 0)
					{
						board->table[i][j] = board->table[i][m];
						board->table[i][m] = 0;
						break;
					}
					m--;
				}
			}
			j--;
		}
	}
}

void ShiftUp_all_Zeros(Board *board)
{
	for (int i = 0; i < board->rows; i++)
	{
		int j = (board->rows) - 1;
		while (j >= 0)
		{
			if (board->table[j][i] == 0)
			{
				int m = j - 1;
				while (m >= 0)
				{
					if (board->table[m][i] != 0)
					{
						board->table[j][i] = board->table[m][i];
						board->table[m][i] = 0;
						break;
					}
					m--;
				}
			}
			j--;
		}
	}
}

void ShiftDown_all_Zeros(Board *board)
{
	for (int i = 0; i < board->rows; i++)
	{
		int j = 0;
		while (j < (board->rows)-1)
		{
			if (board->table[j][i] == 0)
			{
				int m = j + 1;
				while (m < board->rows)
				{
					if (board->table[m][i] != 0)
					{
						board->table[j][i] = board->table[m][i];
						board->table[m][i] = 0;
						break;
					}
					m++;
				}
			}
			j++;
		}
	}
}

void Save_Board(Board *board, User *u)
{
	char extension[6] = ".txt";
	char filename[40];
	strcpy(filename, u->name);
	strcat(filename, extension);
	FILE *fp = fopen(filename, "w");
	fprintf(fp, "%s;", u->name);
	for (int i = 0; i < board->rows; i++)
	{
		for (int j = 0; j < board->rows; j++)
		{
			fprintf(fp, "%d;", board->table[i][j]);
		}
	}
	fprintf(fp, "\n");
	fclose(fp);
}

void infinite_loop(Board *board,int *Fib,User *u)
{
	while (u->flag==0)	//Use a Loop which repeatedly takes input from User and calls playMove function ,till the Game is Won
	{
		if (checkBoard(board, Fib) == 0 && u->flag == 0)
		{
			char c = takeInput();
			if (c == 'p'||c=='P')
			{
				Save_Board(board, u);
				u->flag = 2;
				return;
			}
			playMove(board, u, c, Fib);
		}
		else if (u->flag == 0)
		{
			u->flag = -1;
			modifyMoveCountBasedOnProccessInput(u, 1);
			clearAndRedrawScreen(board);
			break;
		}
		else
			break;
	}
}
