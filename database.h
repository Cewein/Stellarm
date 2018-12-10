#pragma once
#include <winsock.h>
#include <MYSQL/mysql.h>


char* valuesInsert(char* query, char** value, int size);
char* valueInsert(char* query, char* value);
void seeResult(MYSQL *mysql, char* query);
void stockInt(MYSQL *mysql, char* query, int numberField, int* stock);
void stockDouble(MYSQL *mysql, char* query, int numberField, double* stock);
void stockString(MYSQL *mysql, char* query, int numberField, char* stock);
void stockValues(MYSQL *mysql, char* query, int *numberField, char **stock, char **type, int size);
void multiplyInValue(MYSQL *mysql, char* query, int* numberField, double* stock, int size, double parameter);
void multiplyInValues(MYSQL *mysql, char *query, int **numberField, double **stock, int *size, int iteration, double parameter);