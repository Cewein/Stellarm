#pragma warning(disable : 4996)
#include <stdlib.h>
#include <stdio.h>
#include "database.h"

///////////  FONCTIONS FOR USE MYSQL MORE EASYLY /////////////

// FUNCTIONS FOR INSERT VALUES IN A STRING
// valuesInsert : Permite to insert many values in a string
char *valuesInsert(char *query, char **value, int size) {
	int i = 0;
	char* res = NULL;
	int resSize = sizeof(char) * (strlen(query) + strlen(value));
	res = (char*)malloc(resSize);
	strcpy_s(res, strlen(query) + 1, query);
	for (i; i < size; i++) {
		res = valueInsert(res, *(value + i));
	}
	return res;
}

// valueInsert : Permite to insert one value in a string
char* valueInsert(char* query, char* value) {
	char* res = NULL;
	int size = sizeof(char) * (strlen(query) + strlen(value));
	res = (char*)malloc(size);
	strcpy_s(res, size, query);
	char* startPoint = strchr(res, '?');
	int start = strlen(query) - strlen(startPoint);
	int end = start + 1;
	char* recup = NULL;
	int sizeEnd = sizeof(char) * ((strlen(query) - end) + 1);
	recup = (char*)malloc(sizeEnd);
	strcpy_s(recup, sizeEnd, res + end);
	strcpy_s(res + start, strlen(value) + 1, value);
	int ajoute = start + strlen(value);
	strcpy_s(res + ajoute, strlen(recup) + 1, recup);
	return res;
}

// FUNCTIONS WITH SELECT
// seeResult : Permite to see the fields of the query
int seeResult(MYSQL *mysql, char* query) {
	mysql_query(mysql, query);
	MYSQL_RES *result = mysql_store_result(mysql);
	int num_fields = mysql_num_fields(result);
	int count = 0;
	MYSQL_ROW row;

	while ((row = mysql_fetch_row(result)))
	{
		for (int i = 0; i < num_fields; i++)
		{
			printf("%s ", row[i] ? row[i] : "NULL");
			count++;
		}
		printf("\n");
	}
	return count;
}

int seeResultExist(MYSQL *mysql, char* query) {
	mysql_query(mysql, query);
	MYSQL_RES *result = mysql_store_result(mysql);
	int num_fields = mysql_num_fields(result);
	int count = 0;
	MYSQL_ROW row;

	while ((row = mysql_fetch_row(result)))
	{
		for (int i = 0; i < num_fields; i++)
		{
			count++;
		}
	}
	return count;
}


// stockInt : Stock a int of the bdd in a pointer
void stockInt(MYSQL *mysql, char* query, int numberField, int* stock) {
	mysql_query(mysql, query);
	MYSQL_RES *result = mysql_store_result(mysql);
	MYSQL_ROW row;
	row = mysql_fetch_row(result);
	*stock = atoi(row[numberField]);
	mysql_free_result(result);
}

// stockDouble : Stock a double of the bdd in a pointer
void stockDouble(MYSQL *mysql, char* query, int numberField, double* stock) {
	mysql_query(mysql, query);
	MYSQL_RES *result = mysql_store_result(mysql);
	MYSQL_ROW row;
	row = mysql_fetch_row(result);
	*stock = atof(row[numberField]);
	mysql_free_result(result);
}

// stockString : Stock a string of the bdd in a pointer
void stockString(MYSQL *mysql, char* query, int numberField, char* stock) {
	mysql_query(mysql, query);
	MYSQL_RES *result = mysql_store_result(mysql);
	MYSQL_ROW row;
	row = mysql_fetch_row(result);
	strcpy(stock, row[numberField]);
	mysql_free_result(result);
}

// stockValues : Stock many values of the bdd in many pointers
void stockValues(MYSQL *mysql, char* query, int *numberField, char **stock, char **type, int size) {
	int i;
	for (i = 0; i < size; i++) {
		if (_stricmp(*(type + i), "int") == 0) {
			stockInt(mysql, query, *(numberField + i), *(stock + i));
		}
		else if ((_stricmp(*(type + i), "double") == 0) || (_stricmp(*(type + i), "float") == 0)) {
			stockDouble(mysql, query, *(numberField + i), *(stock + i));
		}
		else if ((_stricmp(*(type + i), "char") == 0) || (_stricmp(*(type + i), "string") == 0)) {
			printf("%s %d %s \n", query, numberField, *stock);
			stockString(mysql, query, *(numberField + i), *(stock + i));
		}
		else {
			printf("Ce type n'est pas inclu dans la fonction");
		}
	}
}

// FUNCTIONS FOR PLANETS
// multiplyInValue : Register the result of many fields of Astre for the equinoxe in one value
void multiplyInValue(MYSQL *mysql, char* query, int* numberField, double* stock, int size, double parameter) {
	int i;
	double *buffer = (double*)malloc(sizeof(double) * size);
	for (i = 0; i < size; i++) {
		stockDouble(mysql, query, *(numberField + i), stock);
		*(buffer + i) = *stock;
	}
	*stock = 0;
	double value = 1;
	for (i = 0; i < size; i++) {
		*stock += *(buffer + i) * value;
		value *= parameter;
	}
}

// multiplyInValues : Register results of many fields of Astre for the equinoxe in many values
void multiplyInValues(MYSQL *mysql, char *query, int **numberField, double **stock, int *size, int iteration, double parameter) {
	int i;
	for (i = 0; i < iteration; i++) {
		multiplyInValue(mysql, query, *(numberField + i), *(stock + i), *(size + i), parameter);
	}
}