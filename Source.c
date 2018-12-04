#include "astro.h"

int main(int argc, char **argv) {
	double day = 27;
	double month = 11;
	double year = 2018;
	double hour = 9;
	double min = 0;
	double sec = 0;
	double *longitude, *latitude;	
	longitude = (double*)malloc(sizeof(double) * 3);
	latitude = (double*)malloc(sizeof(double) * 3);
	*latitude = 49;
	*(latitude + 1) = 4;
	*(latitude + 2) = 52;
	*longitude = 1;
	*(longitude + 1) = 55;
	*(longitude + 2) = 21;
	char astre[10] = "soleil";
	double azmt = azimut(astre, year, month, day, hour, min, sec,latitude,longitude);
	double ht = hauteur(astre, year, month, day, hour, min, sec, latitude, longitude);
	free(latitude);
	free(longitude);
	system("pause");
	return 0;
}