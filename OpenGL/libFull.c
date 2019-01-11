#pragma warning(disable : 4996)
#include "libFull.h"

//return the size of a file for malloc into a char *
long fsize(FILE * fp)
{
	long bytes;
	fseek(fp, 0, SEEK_END);
	bytes = ftell(fp);
	rewind(fp);
	//printf("%ld", bytes);
	return bytes;
}

char * freadInArray(FILE * fp)
{
	char * buffer = malloc(sizeof(char) * 250);
	char * fileArray = calloc(1, fsize(fp) + 1); //we calloc because we need a empty array (or at least filled with 0)

	while (fgets(buffer, 250, fp) != NULL)
	{
		strcat(fileArray, buffer);
	}

	free(buffer);
	
	return fileArray;
}

void logInFile(char * description, char * name, int type, FILE * fp)
{
	if (fp == NULL) fp = fopen("log.txt", "a");
	switch (type)
	{
		case 1:
			fputs("[warning]", fp);
			break;
		case 2:
			fputs("[ error ]", fp);
			break;
		default:
			fputs("[default]", fp);
			break;
	}

	time_t t = time(NULL);
	struct tm tm = *localtime(&t);

	fprintf(fp, " - %d-%d-%d %d:%d:%d - %s : %s\n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec, name, description);
	fclose(fp);
}

char * removeEnter(char * text)
{
	int i = 0;
	printf("\n");
	while (text[i] != '\n')
	{
		printf("indice %d : %c\n", i, text[i]);
		i++;
	}
	text[i] = '\0';
	return text;
}