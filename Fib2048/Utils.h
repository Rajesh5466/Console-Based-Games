#include<stdio.h>

int OrderOfBoard(char *Buffer)
{
	int count = 0, i = 0;
	while (Buffer[i] != '\0')
	{
		if (Buffer[i] == ' ')
		{
			count++;
		}
		i++;
	}
	return count;
}

int str_len(char *str)
{
	int i = 0;
	while (str[i] != '\0')
	{
		i++;
	}
	return i;
}

void str_cpy(char *s1, char *s2)
{
	int i = 0;
	while (s1[i] != '\0')
	{
		s2[i] = s1[i];
		i++;
	}
	s2[i] = '\0';
}

//Split using Space delimiter
char* EachField(char *Buffer, int *index)
{
	char *str = (char *)malloc(sizeof(char) * 100);
	int i = 0;
	while (Buffer[*index] != ' '&&Buffer[*index] != '\0')
	{
		str[i] = Buffer[*index];
		i++;
		(*index)++;
	}
	str[i] = '\0';
	if (Buffer[*index] == ' ')
		(*index)++;
	return str;
}

//Similar to atoi
int Str_Int(char *str)
{
	int len = str_len(str), mul = 10, result = 0;
	for (int i = 0; i < len; i++)
	{
		result = (result * 10) + (str[i] - '0');
	}
	return result;
}

void Convert_Record_toStructure(char *Buffer,Board *board, int *index)
{
	for (int i = 0; i < board->rows; i++)
	{
		for (int j = 0; j < board->rows; j++)
		{
			board->table[i][j] = Str_Int(EachField(Buffer, index));
		}
	}
}

void Converter(char *Buffer, Board *board, int *index)
{
	while (Buffer[*index] != '\0')
	{
		Convert_Record_toStructure(Buffer, board, index);
	}
}

//Total number of Records in Data.
int count_Fields(char *data)
{
	int count = 0;
	int i = 0;
	while (data[i] != '\0')
	{
		if (data[i] == ';')
		{
			count++;
		}
		i++;
	}
	return count;
}

//Storing Entire Leaderboard in Two dimensional Array.
char **split_data(char *data,int *len)
{
	int total_fields = count_Fields(data);
	char **result = (char **)malloc(sizeof(char*)*total_fields);
	int k = 0;
	for (int i = 0; i < total_fields; i++)
	{
		result[i] = (char*)malloc(sizeof(char) * 20);
		int j = 0;
		while (data[k] != ';')
		{
			result[i][j] = data[k];
			j++;
			k++;
		}
		result[i][j] = '\0';
		k++;
	}
	*len = total_fields;
	return result;
}

//Transfering entire file data into Buffer
int Transfer_data(FILE *fp, char* data)
{
	char ch;
	int i = 0;
	if (fp == NULL)
		return 0;
	while ((ch = fgetc(fp)) != EOF)
	{
		data[i] = ch;
		i++;
	}
	data[i] = '\0';
	fclose(fp);
	return 1;
}