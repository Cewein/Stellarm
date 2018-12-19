#include "astro.h"
#include "define.h"
#include <math.h>
#include <string.h>

#include "moon.h"
#include "sol.h"
#include "planet.h"

//ERROR SIDERAL TIME MOYEN ? DECALAGE ET CHANGEMENT HORAIRE ? PRESICION SIGMA LUNE / PRECSION COORDONNES

///////// FUNCTIONS CAN USE FOR EVERY PLANET, SUN AND MOON ///////////

// CONVERSION FUNCTIONS

// hourdecimal : Permite to convert a hour with minutes and seconds to an hour decimal (ex : 12h30 = 12,5)
double hourdecimal(double hour, double min, double sec) {
	double newMin = min / 60;
	double newSec = sec / 3600;
	double hourdec = hour + newMin + newSec;
	return hourdec;
}

// hourreal : Permite to convert a hour decimal in a real hour, it's the opposite of the first function
double* hourreal(double hour) {
	double* entHour;
	entHour = (double *)malloc(sizeof(double) * 3);
	*entHour = (int)hour;
	double entMin = (hour - *entHour) * 60;
	*(entHour+1) = (int)entMin;
	*(entHour+2) = (entMin - *(entHour+1)) * 60;
	return entHour;
}

// lfToPoint : Change a double value to a pointer with three double value 
double* lfToPoint(double value) {
	double* point;
	point = (double *)malloc(sizeof(double) * 3);
	*point = (int)value;
	*(point + 1) = (value - *point) * 100;
	*(point + 2) = (*(point + 1) - ((int) *(point + 1))) * 100;
	return point;
}

// HourdegreesInRealHour : Convert Hour degres to a Real hour
double* HourdegreesInRealHour(double degrees, double min, double sec){
	double val = hourdecimal(degrees, min, sec);
	val = DEG2HOUR(val);
	double *val2;
	val2 = (double*)malloc(sizeof(double) * 3);
	val2 = hourreal(val);
	return val2;
}

// degreesInRealHour : Convert degres to a Real hour
double* degreesInRealHour(double degrees) {
	double val = DEG2HOUR(degrees);
	double *val2;
	val2 = (double*)malloc(sizeof(double) * 3);
	val2 = hourreal(val);
	return val2;
}

// RealHourInDegrees : Convert a real hour to degres, it's the opposite of the previous function
double RealHourInDegrees(double hour, double min, double sec) {
	double val = hourdecimal(hour, min, sec);
	val = HOUR2DEG(val);
	return val;
}

// TIME FUNCTIONS

// jourjulien : Permite to calcul julien day (it's the number of days after -4716)
double jourjulien(double year, double month, double day, double hour) {
	double newDay = day + hour / 24;
	if (month <= 2) {
		year = year - 1;
		month = month + 12;
	}
	int a = (int)year / 100;
	int b = 2 - a + (int)a / 4;
	double julien = ((int)(365.25*(year + 4716))) + ((int)(30.60001 * (month + 1))) + newDay + b - 1524.5;
	return julien;
}

// t : Time use for every functions of this project
double t(double julien) {
	double T;
	T = (julien - 2451545.0) / 36525;
	return T;
}

// sideralTime : Permite to calcul local sideral Time
double* sideralTime(double T, double hour, double min, double sec) {
	double sideralTimeGreenwich = 100.46061837 + 36000.770053608 * T + 0.000387933 * (T*T) - (T*T*T) / 38710000;
	int count = (int)sideralTimeGreenwich / 360;
	sideralTimeGreenwich = sideralTimeGreenwich - count * 360;
	sideralTimeGreenwich = sideralTimeGreenwich / 15;
	double* hourAtMinuit = hourreal(sideralTimeGreenwich);
	double* sideralHourGreenwich;
	sideralHourGreenwich = (double *)malloc(sizeof(double) * 3);
	double seconds = 1.00273 * (hour * 3600 + min * 60 + sec);
	seconds = seconds / 3600;
	double* hourlocal = hourreal(seconds);
	for (int i = 0; i < 3; i++) {
		*(sideralHourGreenwich+i) = *(hourAtMinuit + i) + *(hourlocal + i);
	}
	free(hourAtMinuit);
	free(hourlocal);
	if (*sideralHourGreenwich >= 24)
		*sideralHourGreenwich = *sideralHourGreenwich - 24;
	return sideralHourGreenwich;
}

// FONCTIONS OBLIQUITE

// longitudeSol : Permite to calcul the longitude of the sun in degres or radian
double longitudeSol(double T, char type) {
	double longitude = 280.46646 + 36000.76983 * T + 0.0003032 * (T*T);
	int count = (int)longitude / 360;
	longitude = longitude - count * 360;
	if (type == 'r' || type == 'R')
		longitude = DEG2RAD(longitude);
	return longitude;
}

// longitudeMoon : Permite to calcul the longitude of the moon in degres or radian
double longitudeMoon(double T, char type) {
	double longitude = 218.3164 + 481267.8812 * T + 0.001599 * (T*T);
	int count = (int)longitude / 360;
	longitude = longitude - count * 360;
	if (type == 'r' || type == 'R')
		longitude = DEG2RAD(longitude);
	return longitude;
}

// anomalieSol : Permite to calcul the anomalie of the sun in degres or radian
double anomalieSol(double T, char type) {
	double anomalie = 357.52911 + 35999.05029 * T + 0.0001537 * (T*T);
	int count = (int)anomalie / 360;
	anomalie = anomalie - count * 360;
	if (type == 'r' || type == 'R')
		anomalie = DEG2RAD(anomalie);
	return anomalie;
}

// anomalieMoon : Permite to calcul the anomalie of the moon in degres or radian
double anomalieMoon(double T, char type) {
	double anomalie = 134.9634 + 477198.8675 * T + 0.008721 * (T*T);
	int count = (int)anomalie / 360;
	anomalie = anomalie - count * 360;
	if (type == 'r' || type == 'R')
		anomalie = DEG2RAD(anomalie);
	return anomalie;
}

// longitudeNoeudMoon : Permite to calcul longitude of moon's node in degres or radian
double longitudeNoeudMoon(double T, char type) {
	double longitude = 125.0443 - 1934.1363 * T + 0.002075 * (T*T);
	int count = (int)longitude / 360;
	longitude = longitude - count * 360;
	if (type == 'r' || type == 'R')
		longitude = DEG2RAD(longitude);
	return longitude;
}

// obliquite : Use 5 last functions for calcul the real obliquite (moy + nutation)
double* obliquite(double T) {
	double* oblique;
	oblique = (double *)malloc(sizeof(double) * 3);
	*oblique = 23;
	*(oblique + 1) = 26;
	*(oblique + 2) = 21.448 - 46.8150 * T - 0.00059 * (T*T) + 0.001813 * (T*T*T);
	double longSol = longitudeSol(T,'r');
	double longMoon = longitudeMoon(T,'r');
	double anomalSol = anomalieSol(T,'r');
	double anomalMoon = anomalieMoon(T,'r');
	double longNoeudMoon = longitudeNoeudMoon(T,'r');
	double nutationOblique = (9.2025 + 0.00089 * T) * cos(longNoeudMoon);
	nutationOblique += (0.5736 - 0.00031 * T) * cos(2 * longSol);
	nutationOblique += 0.0977 * cos(2 * longMoon);
	nutationOblique -= 0.0895 * cos(2 * longNoeudMoon);
	nutationOblique += 0.0224 * cos(2 * longSol + anomalSol);
	nutationOblique += 0.0200 * cos(2 * longMoon - longNoeudMoon);
	nutationOblique += 0.0129 * cos(2 * longMoon + anomalMoon);
	nutationOblique -= 0.0095 * cos(2 * longSol - anomalSol);
	nutationOblique -= 0.0070 * cos(2 * longSol - longNoeudMoon);
	*(oblique + 2) = *(oblique + 2) + nutationOblique;
	return oblique;
}

// POSITIONS FUNCTIONS

// TransformInLongitudeEquatorial : Permite to transform an ecliptique longitude in a equatorial longitude
double* TransformInLongitudeEquatorial(double longitude, double latitude, double* oblique) {
	longitude = DEG2RAD(longitude);
	latitude = DEG2RAD(latitude);
	double count = (int)(longitude / M_PI);
	double obli = DEG2RAD(hourdecimal(*oblique , (*(oblique + 1) / 100) , (*(oblique + 2) / 1000)));
	double ascensionDroite = (sin(longitude) * cos(obli) - tan(latitude) * sin(obli)) / cos(longitude);
	ascensionDroite = atan(ascensionDroite);
	ascensionDroite = RAD2DEG(ascensionDroite);
	if (ascensionDroite < 0) {
		ascensionDroite = 360 + ascensionDroite;
		if (count == 0)
			ascensionDroite = ascensionDroite - 180;
	}
	else {
		if (count == 1)
			ascensionDroite = ascensionDroite + 180;
	}
	double* hourAscensionDroite = degreesInRealHour(ascensionDroite);
	return hourAscensionDroite;
}

// TransformInLatitudeEquatorial : Permite to transform an ecliptique latitude in a equatorial latitude
double* TransformInLatitudeEquatorial(double longitude, double latitude, double* oblique) {
	longitude = DEG2RAD(longitude);
	latitude = DEG2RAD(latitude);
	double obli = DEG2RAD(hourdecimal(*oblique, (*(oblique + 1) / 100), (*(oblique + 2) / 1000)));
	double declinaison = (sin(latitude) * cos(obli)) + (cos(latitude) * sin(obli) * sin(longitude));
	declinaison = asin(declinaison);
	declinaison = RAD2DEG(declinaison);
	double* hourDeclinaison = hourreal(declinaison);
	return hourDeclinaison;
}

// horaireAngle : Permite to calcul the angle Horaire, it's use for azimut and height
double horaireAngle(double* ascension, double* longitudeDeg, double* sideral ) {
	double* H;
	H = (double*)malloc(sizeof(double) * 3);
	double* longitude = HourdegreesInRealHour(*longitudeDeg, *(longitudeDeg + 1), *(longitudeDeg + 2));
	*H = *sideral - *longitude - *ascension;
	*(H + 1) = *(sideral+1) - *(longitude+1) - *(ascension+1);
	*(H + 2) = *(sideral+2) - *(longitude+2) - *(ascension+2);
	double angle = RealHourInDegrees(*H, *(H + 1), *(H + 2));
	free(H);
	free(longitude);
	return angle;
}

// azimut : Permite to calcul azimut of any astre
double azimut(MYSQL *mysql, char* astre, double year, double month, double day, double hour, double min, double sec,double* latitude, double* longitude) {
	double azimut = 0;
	if (strcmp("Lune", astre) == 0) {
		azimut = azimutMoon(year, month, day, hour, min, sec, latitude, longitude);
		return azimut;
	}
	else if (strcmp("Soleil", astre) == 0) {
		azimut = azimutSol(year, month, day, hour, min, sec, latitude, longitude);
		return azimut;
	}
	else {
		azimut = azimutPlanet(mysql, astre, year, month, day, hour, min, sec, latitude, longitude);
		return azimut;
	}
}

// hauteur : Permite to calcul height of any astre
double hauteur(MYSQL *mysql, char* astre, double year, double month, double day, double hour, double min, double sec, double* latitude, double* longitude) {
	double hauteur = 0;
	if (strcmp("Lune", astre) == 0) {
		hauteur = hauteurMoon(year, month, day, hour, min, sec, latitude, longitude);
		return hauteur;
	}
	else if (strcmp("Soleil", astre) == 0) {
		hauteur = hauteurSol(year, month, day, hour, min, sec, latitude, longitude);
		return hauteur;
	}
	else {
		hauteur = hauteurPlanet(mysql, astre, year, month, day, hour, min, sec, latitude, longitude);
		return hauteur;
	}
}