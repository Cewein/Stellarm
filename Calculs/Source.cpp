#include "astro.h"

int main(int argc, char **argv) {
	int day = 18;
	int month = 11;
	int year = 2018;
	int hour = 20;
	int min = 0;
	int sec = 0;
	double hourdec = hourdecimal(hour, min, sec);
	double julien = jourjulien(year, month, day, hourdec);
	double T = t(julien);
	double* sideral = sideralTime(T,hour,min,sec);
	double* oblique = obliquite(T);
	double longitude = longitudeEcliptique(T);
	double latitude = latitudeEcliptique(T);
	double newLongitude = TransformInLongitudeEquatorial(longitude, latitude, oblique);
	double newLatitude = TransformInLatitudeEquatorial(longitude, latitude, oblique);
	printf("%lf \n", newLongitude);
	free(sideral);
	free(oblique);
	system("pause");
	return 0;
}