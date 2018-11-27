#include "astro.h"
#include "define.h"
#include <math.h>

int main(int argc, char **argv) {
	int day = 22;
	int month = 11;
	int year = 2018;
	int hour = 23;
	int min = 30;
	int sec = 0;
	double *longitude, *latitude;
	longitude = (double*)malloc(sizeof(double) * 3);
	latitude = (double*)malloc(sizeof(double) * 3);
	*latitude = 49;
	*(latitude + 1) = 4;
	*(latitude + 2) = 52;
	*longitude = 1;
	*(longitude + 1) = 55;
	*(longitude + 2) = 21;
	char astre[10] = "lune";
	double azmt = azimut(astre, year, month, day, hour, min, sec,latitude,longitude);
	double ht = hauteur(astre, year, month, day, hour, min, sec, latitude, longitude);
	free(latitude);
	free(longitude);
	//printf("%lf", azmt);
	system("pause");
	return 0;
}