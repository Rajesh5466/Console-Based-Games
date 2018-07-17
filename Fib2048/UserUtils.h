#define _CRT_SECURE_NO_WARNINGS
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>

typedef struct User User;
struct User{
	char *name;
	int movesCount;
	int flag=0;//1 for win ,-1 for loss; 2 for pause
	char *Date;
	char *Board_Type;
};

void modifyMoveCountBasedOnProccessInput(User *user, int processInputOutCome);

char* getDate(){

	SYSTEMTIME t;
	GetSystemTime(&t);
	char *date = (char *)malloc(sizeof(char) * 11);
	date[0] = (t.wDay / 10) + '0';
	date[1] = (t.wDay % 10) + '0';
	date[2] = '-';
	date[3] = (t.wMonth / 10) + '0';
	date[4] = (t.wMonth % 10) + '0';
	date[5] = '-';
	date[6] = (t.wYear / 1000) + '0';
	date[7] = ((t.wYear / 100) % 10) + '0';
	date[8] = ((t.wYear / 10) % 100) + '0';
	date[9] = (t.wYear % 10) + '0';
	date[10] = '\0';
	return date;
}

//store type of board i.e., 4x4 or 2x2
char *getType(int rows)
{
	char *type = (char *)malloc(sizeof(char) * 4);
	type[0] = rows + '0';
	type[1] = 'x';
	type[2] = rows + '0';
	type[3] = '\0';
	return type;
}

User * createUser(char *name, int rows){

	User *user = (User *)malloc(sizeof(User) * 1);
	user->name = name;
	user->movesCount = 0;
	user->flag = 0;
	user->Date = getDate();
	user->Board_Type = getType(rows);
	return user;
}

void modifyMoveCountBasedOnProccessInput(User *user, int processInputOutCome){
	if (processInputOutCome == 1)
	{
		user->movesCount = (user->movesCount) + 1;
	}
}


/*
At the end of the game, Along with final board either display either of 2 msgs.
“Your_name  has lost the game in 10 moves” or “Your_Name won the game in 15 moves”
*/
void printUser(User *user){

	if (user->flag == -1)
	{
		printf("\n%s has lost the game in %d moves\n\nTotal Required to win:\t1346269(4x4)\t13(2x2)\n\n", user->name, user->movesCount);
	}
	if (user->flag==1)
	{
		printf("\n%s won the game in %d moves\n", user->name, user->movesCount);
	}
	system("pause");
}

//Splitting Each Record in Leaderboard
char **Split(char *Buf)
{
	char **result = (char **)malloc(sizeof(char*) * 3);
	char *name = (char *)malloc(sizeof(char) * 64);
	char *score = (char *)malloc(sizeof(char) * 4);
	char *flag = (char*)malloc(sizeof(char) * 4);
	int i = 0, j = 0;
	while (Buf[i] != '\0'&&Buf[i] != ',')
	{
		name[i] = Buf[i];
		i++;
	}
	name[i++] = '\0';
	while (Buf[i] != '\0'&&Buf[i] != ',')
	{
		score[j] = Buf[i];
		i++;
		j++;
	}
	score[j] = '\0';
	int k = 0;
	i++;
	while (Buf[i] != '\0')
	{
		flag[k] = Buf[i];
		i++;
		k++;
	}
	flag[k] = '\0';
	result[0] = name;
	result[1] = score;
	result[2] = flag;
	return result;
}

//Total number of Records in LeaderBoard
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

void show_LeaderBoard(char *filename)
{
	FILE *fp = fopen(filename, "r");
	if (fp == NULL)
		return;
	int lines = total_Records(filename);
	User *Records = (User*)malloc(sizeof(User)*lines);
	char Buf[64];
	for (int i = 0; i < lines; i++)
	{
		fscanf(fp, "%[^\n]", Buf);
		char dummy = fgetc(fp);
		char **values = Split(Buf);
		Records[i].name = values[0];
		Records[i].movesCount = atoi(values[1]);
		Records[i].flag = atoi(values[2]);
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
	printf("\n------Rank------------Username-------Moves--------Status----------\n");
	char status[10];
	for (int i = 0; i < lines; i++)
	{
		if (Records[i].flag == 1)
			strcpy(status,"Won");
		else if (Records[i].flag == -1)
			strcpy(status,"Lost");
		else if (Records[i].flag == 2)
			strcpy(status,"Paused");
		printf("\n-------%d------------%s----------%d------------%s---------\n", i + 1, Records[i].name, Records[i].movesCount, status);
	}
}




