
//Board Struct which holds all the data of the Puzzle

typedef struct Board{

	int **table;	//Stores the Actual table of all values

	int rows;	

	int cols;

	int emptyTileRow;  //Row postion of the emptyTile

	int emptyTileCol;  //Col postion of the emptyTile 
};

Board * createBoard(int rows, int cols){
	if (rows <= 0 || cols <= 0)
	{
		return NULL;
	}

	Board *board =(Board*)malloc(sizeof(Board));
	int **firstIndexArray=(int **)malloc(sizeof(int)*rows);
	for (int i = 0; i < rows; i++)
	{
		*(firstIndexArray + i) = (int *)malloc(sizeof(int)*cols);
	}

	board->table = firstIndexArray;
	board->rows = rows;
	board->cols = cols;
	board->emptyTileRow = 0;
	board->emptyTileCol = 0;
	return board;

}


void initializeBoard(Board * source, int *tobeCopiedArray, int rows, int cols){

	if (source != NULL&&rows>0&&cols>0&&tobeCopiedArray!=NULL)
	{
			for (int i = 0; i < rows; i++)
			{
				for (int j = 0; j < cols; j++, tobeCopiedArray++)
				{
					if (*tobeCopiedArray == 0)
					{
						source->emptyTileRow = i;
						source->emptyTileCol= j;
					}
					*(*(source->table + i) + j) = *tobeCopiedArray; 
				}
			}
			source->rows = rows;
			source->cols = cols;
	}

}


//Check if the Current board is in Win / Loss Condition . Return 1 if it is Win conditon , 0 if not .

int checkBoard(Board * board){
	if (board == NULL||board->table==NULL)
		return 0;
	int num = 1;
	for (int i = 0; i < board->rows; i++)
	{
		for (int j = 0; j < board->cols; j++)
		{
			if (*(*(board->table + i) + j) == num)
			{
				num++;
			}
			else if (num<board->rows*board->cols)
			{
				return 0;
			}
			else
			{
				return 1;
			}
		}
	}
}


void drawBoardOnScreen(Board *board){

	for (int i = 0; i <board->rows; i++)
	{
		for (int j = 0; j < board->cols; j++)
		{
			if (*(*(board->table + i) + j) != 0)
			{
				printf("%d\t", *(*(board->table + i) + j));
			}
			else
			{
				printf(" \t");
			}
		}
		printf("\n");
	}
	printf("\n----------[W] UP --- [S] Down --- [A] LEFT --- [D] Right--------------\n");

}


void clearScreen(){
	system("cls");
}


void clearAndRedrawScreen(Board * board){
	clearScreen();
	drawBoardOnScreen(board);
}
