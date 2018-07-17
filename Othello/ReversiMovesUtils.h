
void func(ReversiGame *game, char c, int x, int y);
int isvalidCoordinate(ReversiGame *game, int x, int y);
void printWinner(ReversiGame *game);
int ret_Val;
/*
This struct denotes the move played by user, X means the x cordinate and Y means y cordinate.
*/
typedef struct ReversiMove {
	int x, y;
}ReversiMove;

/*
Create a ReversiMove struct (malloc/calloc etc) and return it.
Assign parameters x and y to its fields.
*/
ReversiMove *createMove(int x, int y) {
	ReversiMove *Cord = (ReversiMove*)malloc(sizeof(ReversiMove));
	Cord->x = x;
	Cord->y = y;
	return Cord;
}

/*
	Take Only Valid Input x, y two integers . If Invalid input is entered ,Take input again . Keep Taking input until its valid
	Hint : Use While Loop and isValidInput function
	Cordinates are 1 indexed. Ie first row/column is denoted by 1 while giving input.
*/

ReversiMove *inputMove(ReversiGame *game) {
	while (1)
	{
		int x, y;
		scanf_s("%d %d", &x, &y);
		if (isvalidCoordinate(game, x, y) == 1)
		{
		return createMove(x, y);
		}
	}
}


/*
	To check the validity of coordinate on the board 
*/

int isvalidCoordinate(ReversiGame *game, int x, int y) {
	if (x <= 0 || x > game->rows || y <= 0 || y > game->cols)
		return 0;
	else
		return 1;
}

/*
Check if the move can be placed, if its going to make a valid capture to the opponent coins
*/

int isValidMove(ReversiGame *game, ReversiMove *move) {
	char opp='w',ply='b';
	if (game->turn == 1)
	{
		 opp= 'b';
		 ply = 'w';
	}
	//FOR DOWN
	int x = (move->x)-1;
	int y = (move->y)-1;
	int z = 0;
	if (x < 0 || y < 0||game->board[y][x]!=' ')
	{
		return 0;
	}
	  ret_Val = 0;
	  if (y < (game->rows - 2) && game->board[y + 1][x] == opp)
	  {
			y=y+2;
			while (y < game->rows)
			{
				if (game->board[y][x] == ply)
				{
					z = 1;
					ret_Val = 5;
					break;
				}
				y++;
			}
	  }
	  //FOR RIGHT SIDE
	  x = (move->x)-1;
	  y = (move->y)-1;
	  if (x < (game->cols) - 2 && game->board[y][x + 1] == opp)
	  {
		  x = x + 2;
		  while (x < game->cols)
		  {
			  if (game->board[y][x] == ply)
			  {
				  z = 1;
				  ret_Val =(ret_Val*10)+3;
				  break;
			  }
			  x++;
		  }
	  }
	  //FOR UPWARD
	  x = (move->x) - 1;
	  y = (move->y) - 1;
	  if (y >= 2 && game->board[y - 1][x] == opp)
	  {
		  y = y -2;
		  while (y >=0)
		  {
			  if (game->board[y][x] == ply)
			  {
				  z = 1;
				  ret_Val = (ret_Val*10)+1;
				  break;
			  }
			  y--;
		  }
	  }
	  //FOR LEFT 
	  x = (move->x) - 1;
	  y = (move->y) - 1;
	  if (x >= 2 && game->board[y][x - 1] == opp)
	  {
		  x = x - 2;
		  while (x >=0)
		  {
			  if (game->board[y][x] == ply)
			  {
				  z = 1;
				  ret_Val = (ret_Val * 10) + 7;
				  break;
			  }
			  x--;
		  }
	  }
	  //FOR 2nd QUADRANT
	  x = (move->x) - 1;
	  y = (move->y) - 1;
	  if (y >= 2 && x >= 2 && (game->board[y - 1][x - 1] == opp))
	  {
		  x=x-2;
		  y=y-2;
		  while (x >= 0&&y>=0)
		  {
			  if (game->board[y][x] == ply)
			  {
				  z = 1;
				  ret_Val = (ret_Val * 10) + 8;
				  break;
			  }
			  x--;
			  y--;
		  }
	  }
	  //FOR 1ST QUADRANT
	  x = (move->x) - 1;
	  y = (move->y) - 1;
	  if (x < (game->cols) - 2 && y >= 2 && (game->board[y - 1][x + 1] == opp))
	  {
		  x = x + 2;
		  y = y - 2;
		  while (x < game->cols)
		  {
			  if (game->board[y][x] == ply)
			  {
				  z = 1;
				  ret_Val = (ret_Val * 10) + 2;
				  break;
			  }
			  x++;
			  y--;
		  }
	  }
	  //FOR 3rd QUADRANT
	  x = (move->x) - 1;
	  y = (move->y) - 1;
	  if (y < game->rows - 2 && x >= 2 && (game->board[y + 1][x - 1] == opp))
	  {
		  x = x - 2;
		  y = y + 2;
		  while (y<game->cols)
		  {
			  if (game->board[y][x] == ply)
			  {
				  z = 1;
				  ret_Val = (ret_Val * 10) + 6;
				  break;
			  }
			  x--;
			  y++;
		  }
	  }
	  //FOR 4th QUADRANT
	  x = (move->x) - 1;
	  y = (move->y) - 1;
	  if (y <game->rows-2 && x <game->cols-2 && (game->board[y + 1][x + 1] == opp))
	  {
		  x = x + 2;
		  y = y + 2;
		  while (y<game->rows)
		  {
			  if (game->board[y][x] == ply)
			  {
				  z = 1;
				  ret_Val = (ret_Val * 10) +4;
				  break;
			  }
			  x++;
			  y++;
		  }
	  }
	return z;
}

/*
Check if the player can move , if the player is not able to move, he looses the turn
and the opponent gets the chance to play.
If both players are not able to make a move, then the game ends.
*/

int hasMove(ReversiGame *game){
	if (game->blackCount == 0||game->whiteCount==0)
	{
		return 0;
	}
		for (int i = 0; i <game->rows; i++)
		{
			for (int j = 0; j <game->cols; j++)
			{
				if (game->board[i][j] == ' ')
				{
					ReversiMove *move = (ReversiMove*)malloc(sizeof(ReversiMove));
					move->x = j+1;
					move->y = i+1;
					if (isValidMove(game, move) == 1)
					{
						return 1;
					}
				}
			}
		}
	return 0;
}

/*
Increment the number of moves in ReversiGame struct.
*/
void incrementMoves(ReversiGame *game) {
		game->NumberofMoves=(game->NumberofMoves)+1;
}

/*
Toggle the turn in Reversi Game.
This function is to be called when you want to change the turn.
*/
void modifyTurn(ReversiGame *game) {
	if (game->turn == 1)
	{
		game->turn = -1;
	}
	else if (game->turn == -1)
	{
		game->turn = 1;
	}
}

/*
End Reversi Game.
Populate game->winner field accordingly with who won. 1 for white, -1 for black.
This function is to be called when the game is ended.
*/
void endGame(ReversiGame *game) {
	if (game->blackCount>game->whiteCount)
	{
		game->winner = -1;
	}
	if (game->whiteCount>game->blackCount)
	{
		game->winner = 1;
	}
	game->state = 1;
	printWinner(game);
}

/*
	Wrapper function you will call only modify to increment moves and modify the turn.
*/

void modify(ReversiGame *game) {
	incrementMoves(game);
	modifyTurn(game);
}


/*
	This function performs move action on the board
	Note : call validity check performs using above functions before making a move
	returns :
	true on move sucess
	false if move is invalid
*/

bool playMove(ReversiGame *game, ReversiMove *move) {
	int num = isValidMove(game, move);
	if (num == 0)
		return false;
	if (num == 1)
	{
		num = ret_Val;
		char c = 'b';
		if (game->turn == 1)
		{
			c = 'w';
			(game->whiteCount) = (game->whiteCount) + 1;
		}
		else
		{
			game->blackCount = (game->blackCount) + 1;
		}
		game->NumberofMoves = (game->NumberofMoves) + 1;
		game->board[move->y - 1][move->x - 1] = c;
		while (num != 0)
		{
			int x = (move->x) - 1;
			int y = (move->y) - 1;
			int n = num % 10;
			num = num / 10;
			if (n == 1)
			{
				while (game->board[--y][x] != c)
				{
					func(game, c, x, y);
				}
			}
			else if (n == 2)
			{
				while (game->board[--y][++x] != c)
				{
					func(game, c, x, y);
				}
			}
			else if (n == 3)
			{
				while (game->board[y][++x] != c)
				{
					func(game, c, x, y);
				}
			}
			else if (n == 4)
			{
				while (game->board[++y][++x] != c)
				{
					func(game, c, x, y);
				}
			}
			else if (n == 5)
			{
				while (game->board[++y][x] != c)
				{
					func(game, c, x, y);
				}
			}
			else if (n == 6)
			{
				while (game->board[++y][--x] != c)
				{
					func(game, c, x, y);
				}
			}
			else if (n == 7)
			{
				while (game->board[y][--x] != c)
				{
					func(game, c, x, y);
				}
			}
			else if (n == 8)
			{
				while (game->board[--y][--x] != c)
				{
					func(game, c, x, y);
				}
			}
		}
		modifyTurn(game);
	}
	int i = hasMove(game);
	if (i == 0)
	{
		modifyTurn(game);
	}
		return true;
}


void printWinner(ReversiGame *game) {
	/*
	Sample output :
	Result Praveen has won. / Game is Drawn.
	*/
	if (game->winner == 1)
	{
		printf("%s has won.",game->player1name);
	}
	else if (game->winner == -1)
	{
		printf("%s has won.", game->player2name);
	}
	else if (game->winner==0)
	{
		printf("Game is Drawn");
	}
}

void func(ReversiGame *game,char c,int x,int y)
{
	game->board[y][x] = c;
	if (c == 'w')
	{
		game->whiteCount = (game->whiteCount) + 1;
		game->blackCount=(game->blackCount)-1;
	}
	else
	{
		game->blackCount=(game->blackCount)+1;
		game->whiteCount = (game->whiteCount) - 1;
	}
}
