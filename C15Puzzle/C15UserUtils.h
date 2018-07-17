int total_Records(char *filename);
char **Split(char *Buf);

//Used to Store Name and His MovesCount , It will be later be used to generate High Scores Table

typedef struct User{
	char *name;
	int movesCount;
};


User * createUser(char *name){
	User *user =(User *)malloc(sizeof(User));
	user->name = name;
	user->movesCount = 0;
	return user;
}


void modifyMoveCountBasedOnProccessInput(User *user, int processInputOutCome){
	if (processInputOutCome == 1)
	{
		user->movesCount = (user->movesCount) + 1;
	}
}


void printUser(User *user){
	printf("\nHey %s , You have played %d Moves \n", user->name, user->movesCount);
}



void show_LeaderBoard(char *filename)
{
	FILE *fp = fopen(filename, "r");
	int lines = total_Records(filename);
	User *Records = (User*)malloc(sizeof(User)*lines);
	char Buf[64];
	for (int i = 0; i < lines; i++)
	{
		fscanf(fp, "%[^\n]",Buf);
		char dummy=fgetc(fp);
		char **values = Split(Buf);
		Records[i].name = values[0];
		Records[i].movesCount = atoi(values[1]);
	}
	fclose(fp);

	for (int i = 0; i < lines; i++)
	{
		for (int j = i + 1; j < lines; j++)
		{
			if (Records[j].movesCount < Records[i].movesCount)
			{
				User temp = Records[i];
				Records[i] = Records[j];
				Records[j] = temp;
			}
		}
	}
	printf("\nRank  Name\tMoves\n");
	for (int i = 0; i < lines; i++)
	{
		printf("\n  %d %s\t%d\n",i+1, Records[i].name, Records[i].movesCount);
	}
}

int total_Records(char *filename)
{
	FILE *fp = fopen(filename, "r");
	char ch;
	int lines = 0;
	while (!feof(fp))
	{
		ch = fgetc(fp);
		if (ch == '\n')
		{
			lines++;
		}
	}
	fclose(fp);
	return lines;
}


char **Split(char *Buf)
{
	char **result = (char **)malloc(sizeof(char*) * 2);
	char *name = (char *)malloc(sizeof(char) * 64);
	char *score = (char *)malloc(sizeof(char) * 4);
	int i = 0,j=0;
	while (Buf[i] != '\0'&&Buf[i]!=',')
	{
		name[i] = Buf[i];
		i++;
	}
	name[i++] = '\0';
	while (Buf[i] != '\0')
	{
		score[j] = Buf[i];
		i++;
		j++;
	}
	score[j] = '\0';
	result[0] = name;
	result[1] = score;
	return result;
}