#include <stdio.h>
#include <curl/curl.h>

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
		curl_easy_setopt(curl, CURLOPT_URL, "http://perdu.com/");

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
		//do stuff here
		printf("%s", chunk.memory);
	}

	curl_easy_cleanup(curl);
	free(chunk.memory);
	curl_global_cleanup();

	return 0;
}