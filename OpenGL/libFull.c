#include "libFull.h"

//return the size of a file for malloc into a char *
long fsize(FILE * fp)
{
	long bytes;
	fseek(fp, 0, SEEK_END);
	bytes =  ftell(fp);
	rewind(fp);
	printf("%ld", bytes);
	return bytes;
}