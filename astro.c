#include "astro.h"
#include "define.h"
#include <math.h>
#include <string.h>

//FONCTIONS DE CONVERSION

double hourdecimal(double hour, double min, double sec) {
	double newMin = min / 60;
	double newSec = sec / 3600;
	double hourdec = hour + newMin + newSec;
	return hourdec;
}

double* hourreal(double hour) {
	double* entHour;
	entHour = (double *)malloc(sizeof(double) * 3);
	*entHour = (int)hour;
	double entMin = (hour - *entHour) * 60;
	*(entHour+1) = (int)entMin;
	*(entHour+2) = (entMin - *(entHour+1)) * 60;
	return entHour;
}

double* lfToPoint(double value) {
	double* point;
	point = (double *)malloc(sizeof(double) * 3);
	*point = (int)value;
	*(point + 1) = (value - *point) * 100;
	*(point + 2) = (*(point + 1) - ((int) *(point + 1))) * 100;
	return point;
}

double* HourdegreesInRealHour(double degrees, double min, double sec){
	double val = hourdecimal(degrees, min, sec);
	val = DEG2HOUR(val);
	double *val2;
	val2 = (double*)malloc(sizeof(double) * 3);
	val2 = hourreal(val);
	return val2;
}

double* degreesInRealHour(double degrees) {
	double val = DEG2HOUR(degrees);
	double *val2;
	val2 = (double*)malloc(sizeof(double) * 3);
	val2 = hourreal(val);
	return val2;
}

double RealHourInDegrees(double hour, double min, double sec) {
	double val = hourdecimal(hour, min, sec);
	val = HOUR2DEG(val);
	return val;
}

// FONCTIONS pour T

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

double t(double julien) {
	double T;
	T = (julien - 2451545.0) / 36525;
	return T;
}

//FONCTION SIDERAL TIME

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

double longitudeSol(double T, char type) {
	double longitude = 280.46646 + 36000.76983 * T + 0.0003032 * (T*T);
	int count = (int)longitude / 360;
	longitude = longitude - count * 360;
	if (type == 'r' || type == 'R')
		longitude = DEG2RAD(longitude);
	return longitude;
}

double longitudeMoon(double T, char type) {
	double longitude = 218.3164 + 481267.8812 * T + 0.001599 * (T*T);
	int count = (int)longitude / 360;
	longitude = longitude - count * 360;
	if (type == 'r' || type == 'R')
		longitude = DEG2RAD(longitude);
	return longitude;
}

double anomalieSol(double T, char type) {
	double anomalie = 357.52911 + 35999.05029 * T + 0.0001537 * (T*T);
	int count = (int)anomalie / 360;
	anomalie = anomalie - count * 360;
	if (type == 'r' || type == 'R')
		anomalie = DEG2RAD(anomalie);
	return anomalie;
}

double anomalieMoon(double T, char type) {
	double anomalie = 134.9634 + 477198.8675 * T + 0.008721 * (T*T);
	int count = (int)anomalie / 360;
	anomalie = anomalie - count * 360;
	if (type == 'r' || type == 'R')
		anomalie = DEG2RAD(anomalie);
	return anomalie;
}

double longitudeNoeudMoon(double T, char type) {
	double longitude = 125.0443 - 1934.1363 * T + 0.002075 * (T*T);
	int count = (int)longitude / 360;
	longitude = longitude - count * 360;
	if (type == 'r' || type == 'R')
		longitude = DEG2RAD(longitude);
	return longitude;
}

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

// FONCTIONS LUNE

double longitudeMoonForMoon(double T, char type) {
	double longitude = 218.31644735 + 481267.88122838 * T - 0.00159944 * (T*T) + (T*T*T) / 538841;
	int count = (int)longitude / 360;
	longitude = longitude - count * 360;
	if (type == 'r' || type == 'R')
		longitude = DEG2RAD(longitude);
	return longitude;
}

double anomalieSolForMoon(double T, char type) {
	double anomalie = 357.5291092 + 35999.0502909 * T - 0.0001536 * (T*T) + (T*T*T) / 24490000;
	int count = (int)anomalie / 360;
	anomalie = anomalie - count * 360;
	if (type == 'r' || type == 'R')
		anomalie = DEG2RAD(anomalie);
	return anomalie;
}

double anomalieMoonForMoon(double T, char type) {
	double anomalie = 134.96339622 + 477198.86750067 * T + 0.00872053 * (T*T) + (T*T*T) / 69699;
	int count = (int)anomalie / 360;
	anomalie = anomalie - count * 360;
	if (type == 'r' || type == 'R')
		anomalie = DEG2RAD(anomalie);
	return anomalie;
}

double elongationForMoon(double T, char type) {
	double elongation = 297.85019172 + 445267.11139756 * T - 0.00190272 * (T*T) + (T*T*T) / 545868;
	int count = (int)elongation / 360;
	elongation = elongation - count * 360;
	if (type == 'r' || type == 'R')
		elongation = DEG2RAD(elongation);
	return elongation;
}

double distanceForMoon(double T, char type) {
	double distance = 93.27209769 + 483202.01756053 * T + 0.00367481 * (T*T) + (T*T*T) / 3525955;
	int count = (int)distance / 360;
	distance = distance - count * 360;
	if (type == 'r' || type == 'R')
		distance = DEG2RAD(distance);
	return distance;
}

double a1(double T, char type) {
	double A1 = 119.75 + 131.849 * T;
	int count = (int)A1 / 360;
	A1 = A1 - count * 360;
	if (type == 'r' || type == 'R')
		A1 = DEG2RAD(A1);
	return A1;
}

double a2(double T, char type) {
	double A2 = 53.09 + 479264.290 * T;
	int count = (int)A2 / 360;
	A2 = A2 - count * 360;
	if (type == 'r' || type == 'R')
		A2 = DEG2RAD(A2);
	return A2;
}

double a3(double T, char type) {
	double A3 = 313.45 + 481266.484 * T;
	int count = (int)A3 / 360;
	A3 = A3 - count * 360;
	if (type == 'r' || type == 'R')
		A3 = DEG2RAD(A3);
	return A3;
}

double sigmaL(double T) {
	double longMoon = longitudeMoonForMoon(T,'r');
	double anomalSol = anomalieSolForMoon(T,'r');
	double anomalMoon = anomalieMoonForMoon(T,'r');
	double elongation = elongationForMoon(T,'r');
	double distance = distanceForMoon(T,'r');
	double A1 = a1(T,'r');
	double A2 = a2(T,'r');
	double E = 1 - 0.002516 * T - 0.0000074 * (T*T);
	double l = 6.288774 * sin(anomalMoon);
	l += 1.274027 * sin(2 * elongation - anomalMoon);
	l += 0.658314 * sin(2 * elongation);
	l += 0.213618 * sin(2 * anomalMoon);
	l -= (0.185116 * sin(anomalSol)) * E;
	l -= 0.114332 * sin(2 * distance);
	l += 0.058793 * sin(2 * elongation - 2 * anomalMoon);
	l += (0.057066 * sin(2 * elongation - anomalSol - anomalMoon)) * E;
	l += 0.053322 * sin(2 * elongation + anomalMoon);
	l += (0.045758 * sin(2 * elongation - anomalSol)) * E;
	l -= (0.040923 * sin(anomalSol - anomalMoon)) * E;
	l -= 0.034720 * sin(elongation);
	l -= (0.030383 * sin(anomalSol + anomalMoon)) * E;
	l += 0.015327 * sin(2 * elongation - 2 * distance);
	l -= 0.012528 * sin(anomalMoon + 2 * distance);
	l += 0.010980 * sin(anomalMoon - 2 * distance);
	l += 0.010675 * sin(4 * elongation - anomalMoon);
	l += 0.010034 * sin(3 * anomalMoon);
	l += 0.008548 * sin(4 * elongation - 2 * anomalMoon);
	l -= (0.007888 * sin(2 * elongation + anomalSol - anomalMoon)) * E;
	l -= (0.006766 * sin(2 * elongation + anomalSol)) * E;
	l -= 0.005163 * sin(elongation - anomalMoon);
	l += (0.004987 * sin(elongation + anomalSol)) * E;
	l += (0.004036 * sin(2 * elongation - anomalSol + anomalMoon)) * E;
	l += 0.003994 * sin(2 * elongation + 2 * anomalMoon);
	l += 0.003861 * sin(4 * elongation);
	l += 0.003665 * sin(2 * elongation - 3 * anomalMoon);
	l -= (0.002689 * sin(anomalSol - 2 * anomalMoon)) * E;
	l -= 0.002602 * sin(2 * elongation - anomalMoon + 2 * distance);
	l += (0.002390 * sin(2 * elongation - anomalSol - 2 * anomalMoon)) * E;
	l -= 0.002348 * sin(elongation + anomalMoon);
	l += (0.002236 * sin(2 * elongation + 2 * anomalSol)) * (E*E);
	l -= (0.002120 * sin(anomalSol + 2 * anomalMoon)) * E;
	l -= (0.002069 * sin(2 * anomalSol)) * (E*E);
	l += (0.002048 * sin(2 * elongation - 2 * anomalSol - anomalMoon)) * (E*E);
	l -= 0.001773 * sin(2 * elongation + anomalMoon - 2 * distance);
	l -= 0.001595 * sin(2 * elongation + 2 * distance);
	l += (0.001215 * sin(4 * elongation - anomalSol - anomalMoon)) * E;
	l -= 0.001110 * sin(2 * anomalMoon + 2 * distance);
	l -= 0.000892 * sin(3 * elongation - anomalMoon);
	l -= (0.000810 * sin(2 * elongation + anomalSol + anomalMoon)) * E;
	l += (0.000759 * sin(4 * elongation - anomalSol - 2 * anomalMoon)) * E;
	l -= (0.000713 * sin(2 * anomalSol - anomalMoon)) * (E*E);
	l -= (0.000700 * sin(2 * elongation + 2 * anomalSol - anomalMoon)) * (E*E);
	l += (0.000691 * sin(2 * elongation + anomalSol - 2 * anomalMoon)) * E;
	l += (0.000596 * sin(2 * elongation - anomalSol - 2 * distance)) * E;
	l += 0.000549 * sin(4 * elongation + anomalMoon);
	l += 0.000537 * sin(4 * anomalMoon);
	l += (0.000520 * sin(4 * elongation - anomalSol)) * E;
	l -= 0.000487 * sin(elongation - 2 * anomalMoon);
	l -= (0.000399 * sin(2 * elongation + anomalSol - 2 * distance)) * E;
	l -= 0.000381 * sin(2 * anomalMoon - 2 * distance);
	l += (0.000351 * sin(elongation + anomalSol + anomalMoon)) * E;
	l -= 0.000340 * sin(3 * elongation - 2 * anomalMoon);
	l += 0.000330 * sin(4 * elongation - 3 * anomalMoon);
	l += (0.000327 * sin(2 * elongation - anomalSol + 2 * anomalMoon)) * E;
	l -= (0.000323 * sin(2 * anomalSol + anomalMoon)) * (E*E);
	l += (0.000299 * sin(elongation + anomalSol - anomalMoon)) * E;
	l += 0.000294 * sin(2 * elongation + 3 * anomalMoon);
	l -= 0.000275 * sin(2 * elongation + anomalMoon + 2 * distance);
	l += 0.003958 * sin(A1);
	l += 0.001962 * sin(longMoon - distance);
	l += 0.000318 * sin(A2);
	return RAD2DEG(l);
}

double sigmaB(double T) {
	double L = longitudeMoonForMoon(T,'r');
	double Ms = anomalieSolForMoon(T,'r');
	double Mm = anomalieMoonForMoon(T,'r');
	double D = elongationForMoon(T,'r');
	double F = distanceForMoon(T,'r');
	double A1 = a1(T,'r');
	double A3 = a3(T,'r');
	double E = 1 - 0.002516 * T - 0.0000074 * (T*T);
	double b = 5.128122 * sin(F);
	b += 0.280602 * sin(Mm + F);
	b += 0.277693 * sin(Mm - F);
	b += 0.173237 * sin(2 * D - F);
	b += 0.055413 * sin(2 * D - Mm + F);
	b += 0.046271 * sin(2 * D - Mm - F);
	b += 0.032573 * sin(2 * D + F);
	b += 0.017198 * sin(2 * Mm + F);
	b += 0.009266 * sin(2 * D + Mm - F);
	b += 0.008822 * sin(2 * Mm - F);
	b += (0.008216 * sin(2 * D - Ms - F)) * E;
	b += 0.004324 * sin(2 * D - 2 * Mm - F);
	b += 0.004200 * sin(2 * D + Mm + F);
	b -= (0.003359 * sin(2 * D + Ms - F)) * E;
	b += (0.002463 * sin(2 * D - Ms - Mm + F)) * E;
	b += (0.002211 * sin(2 * D - Ms + F)) * E;
	b += (0.002065 * sin(2 * D - Ms - Mm - F)) * E;
	b -= (0.001870 * sin(Ms - Mm - F)) * E;
	b += 0.001828 * sin(4 * D - Mm - F);
	b -= (0.001794 * sin(Ms + F)) * E;
	b -= 0.001749 * sin(3 * F);
	b -= (0.001565 * sin(Ms - Mm + F)) * E;
	b -= 0.001491 * sin(D + F);
	b -= (0.001475 * sin(Ms + Mm + F)) * E;
	b -= (0.001410 * sin(Ms + Mm - F)) * E;
	b -= (0.001344 * sin(Ms - F)) * E;
	b -= 0.001335 * sin(D - F);
	b += 0.001107 * sin(3 * Mm + F);
	b += 0.001021 * sin(4 * D - F);
	b += 0.000833 * sin(4 * D - Mm + F);
	b += 0.000777 * sin(Mm - 3 * F);
	b += 0.000671 * sin(4 * D - 2 * Mm + F);
	b += 0.000607 * sin(2 * D - 3 * F);
	b += 0.000596 * sin(2 * D + 2 * Mm - F);
	b += (0.000491 * sin(2 * D - Ms + Mm - F)) * E;
	b -= 0.000451 * sin(2 * D - 2 * Mm + F);
	b += 0.000439 * sin(3 * Mm - F);
	b += 0.000422 * sin(2 * D + 2 * Mm + F);
	b += 0.000421 * sin(2 * D - 3 * Mm - F);
	b -= (0.000366 * sin(2 * D + Ms - Mm + F)) * E;
	b -= (0.000351 * sin(2 * D + Ms + F)) * E;
	b += 0.000331 * sin(4 * D + F);
	b += (0.000315 * sin(2 * D - Ms + Mm + F)) * E;
	b += (0.000302 * sin(2 * D - 2 * Ms - F)) * (E*E);
	b -= 0.000283 * sin(Mm + 3 * F);
	b -= (0.000229 * sin(2 * D + Ms + Mm - F)) * E;
	b += (0.000223 * sin(D + Ms - F)) * E;
	b += (0.000223 * sin(D + Ms + F)) * E;
	b -= (0.000220 * sin(Ms - 2 * Mm - F)) * E;
	b -= (0.000220 * sin(2 * D + Ms - Mm - F)) * E;
	b -= 0.000185 * sin(D + Mm + F);
	b += (0.000181 * sin(2 * D - Ms - 2 * Mm - F)) * E;
	b -= (0.000177 * sin(Ms + 2 * Mm + F)) * E;
	b += 0.000176 * sin(4 * D - 2 * Mm - F);
	b += (0.000166 * sin(4 * D - Ms - Mm - F)) * E;
	b -= 0.000164 * sin(D + Mm - F);
	b += 0.000132 * sin(4 * D + Mm - F);
	b -= 0.000119 * sin(D - Mm - F);
	b += (0.000115 * sin(4 * D - Ms - F)) * E;
	b += (0.000107 * sin(2 * D - 2 * Ms + F)) * (E*E);
	b -= 0.002235 * sin(L);
	b += 0.000382 * sin(A3);
	b += 0.000175 * sin(A1 - F);
	b += 0.000175 * sin(A1 + F);
	b += 0.000127 * sin(L - Mm);
	b -= 0.000115 * sin(L + Mm);
	return RAD2DEG(b);
}
double longitudeEcliptique(double T) {
	double sigmal = sigmaL(T);
	double longMoon = longitudeMoonForMoon(T,'d');
	double longitude = longMoon + sigmal / 1000000;
	return longitude;
}

double latitudeEcliptique(double T) {
	double sigmab = sigmaB(T);
	double latitude = sigmab / 1000000;
	return latitude;
}

// FONCTIONS SOLEIL

double anomalieSolForSol(double T, char type) {
	double anomalie = 357.52911 + 35999.05029 * T - 0.0001537 * (T*T);
	int count = (int)anomalie / 360;
	anomalie = anomalie - count * 360;
	if (type == 'r' || type == 'R')
		anomalie = DEG2RAD(anomalie);
	return anomalie;
}
/*
double excentriciteForSol(double T, char type) {
	double excentricite = 0.016708634 - 0.000042037 * T - 0.0000001267 * (T*T);
	if (type == 'r' || type == 'R')
		excentricite = DEG2RAD(excentricite);
	return excentricite;
}
*/

double centreSol(double T, double anomalie, char type) {
	double centre = (1.914602 - 0.004817 * T - 0.000014 * (T*T)) * sin(anomalie) + (0.019993 - 0.000101 * T) * sin(2 * anomalie) + 0.000289 * sin(3* anomalie);
	if (type == 'r' || type == 'R')
		centre = DEG2RAD(centre);
	return centre;
}

double reallongitudeSol(double T) {
	double longitude = longitudeSol(T, 'd');
	double anomalie = anomalieSolForSol(T, 'r');
	double centre = centreSol(T, anomalie, 'd');
	double realLongitude = longitude + centre;
	return realLongitude;
}

double omegaSol(double T, char type) {
	double omega = 125.04 - 1934.136 * T;
	int count = (int)omega / 360;
	omega = omega - count * 360;
	if (type == 'r' || type == 'R')
		omega = DEG2RAD(omega);
	return omega;
}

double viewLongitudeSol(double T) {
	double realLongitude = reallongitudeSol(T);
	double omega = omegaSol(T, 'r');
	double longitude = realLongitude - 0.00560 - 0.00478 * RAD2DEG(sin(omega));
	return longitude;
}

double* ascensionDroiteSol(double longitude, double* oblique) {
	longitude = DEG2RAD(longitude);
	double count = (int)(longitude / M_PI);
	double obli = DEG2RAD((*oblique + (*(oblique + 1) / 100) + (*(oblique + 2) / 1000)));
	double ascensionDroite = cos(obli) * tan(longitude);
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

double* declinaisonSol(double longitude, double* oblique) {
	longitude = DEG2RAD(longitude);
	double obli = DEG2RAD((*oblique + (*(oblique + 1) / 100) + (*(oblique + 2) / 1000)));
	double declinaison = sin(obli) * sin(longitude);
	declinaison = asin(declinaison);
	declinaison = RAD2DEG(declinaison);
	double* hourDeclinaison = hourreal(declinaison);
	return hourDeclinaison;
}


// FONCTIONS GENERALES POSITION

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
//	printf("ascension droite : %lfh %lfmin %lfsec \n", *hourAscensionDroite, *(hourAscensionDroite + 1), *(hourAscensionDroite + 2));
	return hourAscensionDroite;
}

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

double azimut(char* astre, double year, double month, double day, double hour, double min, double sec,double* latitude, double* longitude) {
	double hourdec = hourdecimal(hour, min, sec);
	double julien = jourjulien(year, month, day, hourdec);
	double T = t(julien);
	double* sideral = sideralTime(T, hour, min, sec);
	double* oblique = obliquite(T);
	if (strcmp("lune", astre) == 0) {
		double longitudeEclip = longitudeEcliptique(T);
		double latitudeEclip = latitudeEcliptique(T);
		double* ascensionDroite = TransformInLongitudeEquatorial(longitudeEclip, latitudeEclip, oblique);
		double* declinaison = TransformInLatitudeEquatorial(longitudeEclip, latitudeEclip, oblique);
		double angleHoraire = horaireAngle(ascensionDroite, longitude, sideral);
		double azimut = 0;
		double decl = DEG2RAD(hourdecimal(*declinaison, *(declinaison + 1), *(declinaison + 2)));
		angleHoraire = DEG2RAD(angleHoraire);
		double lat = DEG2RAD(hourdecimal(*latitude, *(latitude + 1), *(latitude + 2)));
		azimut = sin(angleHoraire) / (cos(angleHoraire) * sin(lat) - tan(decl) * cos(lat));
		double count = (int)(azimut / M_PI);
	//	printf("uno  azimut : %lf \n", azimut);
		azimut = RAD2DEG(atan(azimut));
	//	printf("dos  azimut : %lf \n", azimut);
		/*if (azimut < 0) {
			azimut = 360 + azimut;
			if (count == 0)
				azimut = azimut - 180;
		}
		else {
			if (count == 1)
				azimut = azimut + 180;
		}  */
			//	if (azimut < 0)
			//		azimut = 360 + azimut;
			//	azimut = azimut + 180;
		azimut = azimut + 180;
		if (azimut < 0)
			azimut = 180 + azimut;
		else if (azimut > 360)
			azimut = azimut - 360;
		printf("%s azimut : %lf \n",astre, azimut);
		free(sideral);
		free(oblique);
		free(ascensionDroite);
		free(declinaison);
		return azimut;
	}
	else if (strcmp("soleil", astre) == 0) {
		double longitudeView = viewLongitudeSol(T);
		double* ascensionDroite = ascensionDroiteSol(longitudeView, oblique);
		double* declinaison = declinaisonSol(longitudeView, oblique);
		double angleHoraire = horaireAngle(ascensionDroite, longitude, sideral);
		double azimut = 0; 
		double decl = DEG2RAD(hourdecimal(*declinaison, *(declinaison + 1), *(declinaison + 2)));
		angleHoraire = DEG2RAD(angleHoraire);
		double lat = DEG2RAD(hourdecimal(*latitude, *(latitude + 1), *(latitude + 2)));
		azimut = sin(angleHoraire) / (cos(angleHoraire) * sin(lat) - tan(decl) * cos(lat));
		azimut = RAD2DEG(atan(azimut));
		azimut = azimut + 180;
		if (azimut < 0)
			azimut = 360 + azimut;
		printf("%s azimut : %lf \n",astre, azimut);
		free(sideral);
		free(oblique);
		free(ascensionDroite);
		free(declinaison);
	}
	else {
		printf("error");
		free(sideral);
		free(oblique);
		return 0;
	}
}

double hauteur(char* astre, double year, double month, double day, double hour, double min, double sec, double* latitude, double* longitude) {
	double hourdec = hourdecimal(hour, min, sec);
	double julien = jourjulien(year, month, day, hourdec);
	double T = t(julien);
	double* sideral = sideralTime(T, hour, min, sec);
	double* oblique = obliquite(T);

	if (strcmp("lune", astre) == 0) {
		double longitudeEclip = longitudeEcliptique(T);
		double latitudeEclip = latitudeEcliptique(T);
		double* ascensionDroite = TransformInLongitudeEquatorial(longitudeEclip, latitudeEclip, oblique);
		double* declinaison = TransformInLatitudeEquatorial(longitudeEclip, latitudeEclip, oblique);
		double angleHoraire = horaireAngle(ascensionDroite, longitude, sideral);
		double hauteur = 0;
		double decl = DEG2RAD(hourdecimal(*declinaison, *(declinaison + 1), *(declinaison + 2)));
		angleHoraire = DEG2RAD(angleHoraire);
		double lat = DEG2RAD(hourdecimal(*latitude, *(latitude + 1), *(latitude + 2)));
		hauteur = sin(lat) * sin(decl) + cos(lat) * cos(decl) * cos(angleHoraire);
		hauteur = RAD2DEG(asin(hauteur));
		printf("%s hauteur : %lf \n",astre, hauteur);
		free(sideral);
		free(oblique);
		free(ascensionDroite);
		free(declinaison);
		return hauteur;
	}
	else if (strcmp("soleil", astre) == 0) {
		double longitudeView = viewLongitudeSol(T);
		double* ascensionDroite = ascensionDroiteSol(longitudeView, oblique);
		double* declinaison = declinaisonSol(longitudeView, oblique);
		double angleHoraire = horaireAngle(ascensionDroite, longitude, sideral);
		double hauteur = 0;
		double decl = DEG2RAD(hourdecimal(*declinaison, *(declinaison + 1), *(declinaison + 2)));
		angleHoraire = DEG2RAD(angleHoraire);
		double lat = DEG2RAD(hourdecimal(*latitude, *(latitude + 1), *(latitude + 2)));
		hauteur = sin(lat) * sin(decl) + cos(lat) * cos(decl) * cos(angleHoraire);
		hauteur = RAD2DEG(asin(hauteur));
		printf("%s hauteur : %lf \n", astre, hauteur);
		free(sideral);
		free(oblique);
		free(ascensionDroite);
		free(declinaison);
		return hauteur;
	}
	else {
		free(sideral);
		free(oblique);
		printf("error");
		return 0;
	}
}