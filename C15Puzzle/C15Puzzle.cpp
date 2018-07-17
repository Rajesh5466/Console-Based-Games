#include "C15Headers.h"

void main(){

	//Create a User and store it in user.
	char str[100];
	printf("Enter Your Name\n");
	scanf("%s", &str);
	User *u=createUser(str);

	//Declaring two variables called rows&cols
	int rows, cols;
	printf("Enter rows and Colums\n");
	scanf("%d %d", &rows, &cols);

	//Declare a 2D Array ,and assign some values to it .Let this array be table . [Make sure the Values you are entering is a solvable version of the Board ]
	int *Arr = (int *)malloc(sizeof(int)*(rows*cols));
	for (int i = 0; i < rows*cols; i++)
	{
		scanf("%d", &Arr[i]);
	}

	//Create a board using rows and cols
	Board *board=createBoard(rows,cols);

	//Initalize the board with table ,Pass it as (int *)table
	initializeBoard(board, Arr, rows, cols);

	//First Clear and Redraw the Screen ,First Time we need to show the board right ?
	drawBoardOnScreen(board);

	//Also call printUser , You also need to show ,his name and movesCount.
	printUser(u);

	//Use a Loop which repeatedly takes input from User and calls playMove function ,till the Game is Won .
	while(1)
	{
		if (checkBoard(board) == 0)
		{
			char c = takeInput();
			playMove(board,u,c);
		}
		else
		{
			break;
		}
	}
	
	//Showing total moves made by user to win Game.
	printf("\n\nGame is completed in %d Moves, Good work %s\n\n",u->movesCount,u->name);

	//Store Details in LeaderBoard
	FILE *fp = fopen("C15_LeaderBoard.txt", "a+");
	fseek(fp, 0, SEEK_END);
	fprintf(fp, "%s,%d\n", u->name, u->movesCount);
	fclose(fp);

	//show LeaderBoard
	show_LeaderBoard("C15_LeaderBoard.txt");
	printf("\n");

	system("pause");
}
