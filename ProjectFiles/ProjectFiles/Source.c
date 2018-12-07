#include <stdlib.h>
#include <stdio.h>
#define _CRT_SECURE_NO_WARNINGS

int main(int argc, char **argv) {

	FILE *fp;
	int value[100];
	int size = 100;
	int i;
	errno_t err;
	err = fopen_s(&fp,"test.bin", "wb");
	if (err == 0)
	{
		printf("The file 'test.bin' was opened\n");
	}
	else
	{
		printf("The file 'test.bin' was not opened\n");
	}
	for (i = 0; i < size; i++) {
		value[i] = rand() % 256;
	}
	fwrite(value, sizeof(int), 100, fp);
	fclose(fp);
	system("pause");
	return 0;
}