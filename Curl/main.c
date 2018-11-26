#pragma warning(disable : 4996)

#include <stdio.h>
#include <curl/curl.h>
#include <string.h>

#include "data.h"

int main(void)
{
	CURL *curl;
	CURLcode res;

	struct MemoryStruct chunk;
	
	chunk.memory = malloc(1);
	chunk.size = 0;


	curl_global_init(CURL_GLOBAL_DEFAULT);

	curl = curl_easy_init();
	if (curl) {
		curl_easy_setopt(curl, CURLOPT_URL, "https://theskylive.com/planetarium?obj=moon");

		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&chunk);

		res = curl_easy_perform(curl);
		curl_easy_cleanup(curl);
	}

	if (res != CURLE_OK) {
		fprintf(stderr, "curl_easy_perfm() failed: %s\n", curl_easy_strerror(res));
	}
	else
	{
		char * data;
		data = chunk.memory;

		data = strstr(data, "Object:");

		char *end = data;
		end = strstr(data, "</div>");
		
		printf("\n\n\nlength of data : %d\nlength of end : %d\n\n\n", strlen(data), strlen(end));

		unsigned int length = strlen(data) - strlen(end);

		printf("%d\n", length);

		int i = 0;
		while (i < length)
		{
			printf("%c", data[i]);
			i++;
		}
	}

	curl_easy_cleanup(curl);
	free(chunk.memory);
	curl_global_cleanup();

	return 0;
}