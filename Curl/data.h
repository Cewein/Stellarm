#pragma once

struct MemoryStruct {
	char *memory;
	unsigned int size;
};

const unsigned int WriteMemoryCallback(void *contents, unsigned int size, unsigned int nmemb, void *userp);