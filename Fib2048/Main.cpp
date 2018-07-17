#define _CRT_SECURE_NO_WARNINGS
#include "MovesUtils.h"
#include"Utils.h"
#include<math.h>

void main()
{
	char str[100];
	int Fib[32] = { 0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 144, 233, 377, 610, 987, 1597, 2584, 4181, 6765, 10946, 17711, 28657, 46368, 75025, 121393, 196418, 317811, 514229, 832040, 1346269 };

	printf("Enter Username:\t");
	User *u;
	scanf("%[^\n]s", &str);			

	while (1)
	{
		printf("Enter 0.exit,1.Play Game,2.Replay Last Saved Game,3.View LeaderBoard\n");
		int choice, rows;
		scanf("%d", &choice);

		if (choice == 1 || choice==2)
		{
			Board *board;
			if (choice == 1)
			{
				printf("Enter either '2' or '4' for Playing 2x2 or 4x4 Boards Respectively\n");
				scanf("%d", &rows);
				board = createBoard(rows);
				u = createUser(str, rows);
				initializeBoard(board, rows);
			}
			else
			{
				char extension[6] = ".txt";
				char filename[40];
				u = createUser(str, 0);
				str_cpy(u->name, filename);
				strcat(filename, extension);
				FILE *fp = fopen(filename, "r");
				char data[100];
				if (Transfer_data(fp, data))
				{
					int len = 0;
					char **field = split_data(data, &len);
					board = createBoard((int)sqrt((len - 1)*1.0));
					Reload_Game(board, field, len);
					u->Board_Type = getType((int)sqrt((len - 1)*1.0));
				}
				else
				{
					printf("\nNo previous Game saved on this username\n\n");
					continue;
				}
			}
			//Show Board for player to Play
			drawBoardOnScreen(board);
			//Take continues input from User.
			infinite_loop(board, Fib, u);
			printUser(u);
			if (u->flag != 0||u->flag==2)
			{
				//Store Details in LeaderBoard
				FILE *fp = fopen("Fib2048_LeaderBoard.txt", "a+");
				fseek(fp, 0, SEEK_END);
				fprintf(fp, "%s,%d,%d\n", u->name, u->movesCount,u->flag);
				fclose(fp);

				//show LeaderBoard
				show_LeaderBoard("Fib2048_LeaderBoard.txt");
				printf("\n");
			}
		}
		else if (choice == 3)
		{
			system("cls");
			show_LeaderBoard("Fib2048_LeaderBoard.txt");
			printf("\n");
		}
		else if (choice == 0)
			break;
	}

	system("pause");
	return;
}