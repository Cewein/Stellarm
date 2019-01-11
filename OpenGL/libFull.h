#pragma once

#include <stdio.h>
#include <time.h>

long fsize(FILE * fp);

char * freadInArray(FILE * fp);

void logInFile(char * description, char * name, int type, FILE * tf);

char * removeEnter(char * text);