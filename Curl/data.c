#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include "data.h"

const unsigned int WriteMemoryCallback(void *contents, unsigned int size, unsigned int nmemb, void *userp)
{
	unsigned int realsize = size * nmemb;
	struct MemoryStruct *mem = (struct MemoryStruct *)userp;

	char *ptr = realloc(mem->memory, mem->size + realsize + 1);
	if (ptr == NULL)
	{
		printf("Out of memory");
		return 0;
	}

	mem->memory = ptr;
	memcpy(&(mem->memory[mem->size]), contents, realsize);
	mem->size += realsize;
	mem->memory[mem->size] = 0;

	return realsize;
}

void printInfo(char * memory, char * name)
{
	char * data;
	data = memory;

	data = strstr(data, "Object:");
	char * end = data;
	end = strstr(data, "</div>");

	unsigned int length = strlen(data) - strlen(end);

	int i = 0;
	int printing = 1;
	while (i < length)
	{
		if (data[i - 1] == '>' || (data[i - 1] == 9 && data[i] != 9)) printing = 1;
		if (data[i] == '<' || data[i] == 9) printing = 0;
		if (printing == 1) printf("%c", data[i]);

		i++;
	}
}