#include <stdio.h>
#include <stdlib.h>
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