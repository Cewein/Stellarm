#include "positionPlanet.h"
#include <stdio.h>
#include <stdlib.h>

// hourdecimal : Permite to convert a hour with minutes and seconds to an hour decimal (ex : 12h30 = 12,5)
double hourdecimal(int hour, int min, int sec) {
	double newMin = min / 60;
	double newSec = sec / 3600;
	double hourdec = hour + newMin + newSec;
	return hourdec;
}

// jourjulien : Permite to calcul julien day (it's the number of days after -4716)
double jourjulien(int year, int month, int day, double hour) {
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

// longitudeSol : Permite to calcul the longitude of the sun in degres or radian
double longitudeSol(double T, char type) {
	double longitude = 280.46646 + 36000.76983 * T + 0.0003032 * (T*T);
	int count = (int)longitude / 360;
	longitude = longitude - count * 360;
	if (type == 'r' || type == 'R')
		longitude = DEG2RAD(longitude);
	return longitude;
}

// anomalieSolForSol : Permite to calcul anomalie of the sun
double anomalieSolForSol(double T, char type) {
	double anomalie = 357.52911 + 35999.05029 * T - 0.0001537 * (T*T);
	int count = (int)anomalie / 360;
	anomalie = anomalie - count * 360;
	if (type == 'r' || type == 'R')
		anomalie = DEG2RAD(anomalie);
	return anomalie;
}

// excentriciteForSol : Permite to calcul excentricite of the sun
double excentriciteForSol(double T, char type) {
	double excentricite = 0.016708634 - 0.000042037 * T - 0.0000001267 * (T*T);
	if (type == 'r' || type == 'R')
		excentricite = DEG2RAD(excentricite);
	return excentricite;
}

// centreSol : 
double centreSol(double T, double anomalie, char type) {
	double centre = (1.914602 - 0.004817 * T - 0.000014 * (T*T)) * sin(anomalie) + (0.019993 - 0.000101 * T) * sin(2 * anomalie) + 0.000289 * sin(3 * anomalie);
	if (type == 'r' || type == 'R')
		centre = DEG2RAD(centre);
	return centre;
}

// reallongitudeSol : Permite to calcul the real longitude of the sun
double reallongitudeSol(double T) {
	double longitude = longitudeSol(T, 'd');
	double anomalie = anomalieSolForSol(T, 'r');
	double centre = centreSol(T, anomalie, 'd');
	double realLongitude = longitude + centre;
	return realLongitude;
}

// omegaSol : Return a value for calcul ecliptique longitude (just after this function)
double omegaSol(double T, char type) {
	double omega = 125.04 - 1934.136 * T;
	int count = (int)omega / 360;
	omega = omega - count * 360;
	if (type == 'r' || type == 'R')
		omega = DEG2RAD(omega);
	return omega;
}

// viewLongitudeSol : Permite to have ecliptique longitude of the sun
double viewLongitudeSol(double T) {
	double realLongitude = reallongitudeSol(T);
	double omega = omegaSol(T, 'r');
	double longitude = realLongitude - 0.00560 - 0.00478 * RAD2DEG(sin(omega));
	return longitude;
}

// realAnomalieSol : Permite to calcul the real anomalie of the sun
double realAnomalieSol(double T) {
	double anomalieReal;
	double anomalieMoy = anomalieSolForSol(T, 'r');
	double centre = centreSol(T, anomalieMoy, 'r');
	anomalieReal = anomalieMoy + centre;
	return anomalieReal;
}

// DistanceTerreSol : Return the distance between the earth and the sun
double distanceTerreSol(double T) {
	double e = excentriciteForSol(T, 'r');
	double v = realAnomalieSol(T);
	double distance = 1.000001018 * (1 - e * e) / (1 + e * cos(v));
	return distance;
}

void positionEarth(Planet *astre, struct tm now) {
	double hourdec = hourdecimal(now.tm_hour, now.tm_min, now.tm_sec);
	double julien = jourjulien(now.tm_year, now.tm_mon, now.tm_mday, hourdec);
	double T = t(julien);
	double longitudeView = viewLongitudeSol(T);
	longitudeView += 180;
	if (longitudeView >= 360) {
		longitudeView -= 360;
	}
	double distance = distanceTerreSol(T);
	astre->distance = distance;
	astre->latitude = 0;
	astre->longitude = longitudeView;
}

///////// FUNCTIONS FOR MOON ////////////

// longitudeMoonForMoon : Permite to have the longitude of the moon in radian or in degres
double longitudeMoonForMoon(double T, char type) {
	double longitude = 218.31644735 + 481267.88122838 * T - 0.00159944 * (T*T) + (T*T*T) / 538841;
	int count = (int)longitude / 360;
	longitude = longitude - count * 360;
	if (type == 'r' || type == 'R')
		longitude = DEG2RAD(longitude);
	return longitude;
}

// anomalieSolForMoon : Permite to have the anomalie of the sun in radian or in degres
double anomalieSolForMoon(double T, char type) {
	double anomalie = 357.5291092 + 35999.0502909 * T - 0.0001536 * (T*T) + (T*T*T) / 24490000;
	int count = (int)anomalie / 360;
	anomalie = anomalie - count * 360;
	if (type == 'r' || type == 'R')
		anomalie = DEG2RAD(anomalie);
	return anomalie;
}

// anomalieMoonForMoon : Permite to have the anomalie of the moon in radian or in degres
double anomalieMoonForMoon(double T, char type) {
	double anomalie = 134.96339622 + 477198.86750067 * T + 0.00872053 * (T*T) + (T*T*T) / 69699;
	int count = (int)anomalie / 360;
	anomalie = anomalie - count * 360;
	if (type == 'r' || type == 'R')
		anomalie = DEG2RAD(anomalie);
	return anomalie;
}

// elongationForMoon : Permite to have th elongation of the moon in radian or in degres
double elongationForMoon(double T, char type) {
	double elongation = 297.85019172 + 445267.11139756 * T - 0.00190272 * (T*T) + (T*T*T) / 545868;
	int count = (int)elongation / 360;
	elongation = elongation - count * 360;
	if (type == 'r' || type == 'R')
		elongation = DEG2RAD(elongation);
	return elongation;
}

// distanceForMoon : Permite to have distance between the moon and the ascendant node
double distanceForMoon(double T, char type) {
	double distance = 93.27209769 + 483202.01756053 * T + 0.00367481 * (T*T) + (T*T*T) / 3525955;
	int count = (int)distance / 360;
	distance = distance - count * 360;
	if (type == 'r' || type == 'R')
		distance = DEG2RAD(distance);
	return distance;
}

// a1, a2, a3 : Permite to calcul three arguments use for calcul sigmaL et sigmaB
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

// sigmaL, sigmaB : calcul two arguments use for the longitude and the latitude
double sigmaL(double T) {
	double longMoon = longitudeMoonForMoon(T, 'r');
	double anomalSol = anomalieSolForMoon(T, 'r');
	double anomalMoon = anomalieMoonForMoon(T, 'r');
	double elongation = elongationForMoon(T, 'r');
	double distance = distanceForMoon(T, 'r');
	double A1 = a1(T, 'r');
	double A2 = a2(T, 'r');
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
	double L = longitudeMoonForMoon(T, 'r');
	double Ms = anomalieSolForMoon(T, 'r');
	double Mm = anomalieMoonForMoon(T, 'r');
	double D = elongationForMoon(T, 'r');
	double F = distanceForMoon(T, 'r');
	double A1 = a1(T, 'r');
	double A3 = a3(T, 'r');
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

// longitudeEcliptique : Permite to calcul the longitude Ecliptique of the Moon
double longitudeEcliptiqueForMoon(double T) {
	double sigmal = sigmaL(T);
	double longMoon = longitudeMoonForMoon(T, 'd');
	double longitude = longMoon + sigmal / 1000000;
	return longitude;
}

// latitudeEcliptique : Permite to calcul the latitude Ecliptique of the Moon
double latitudeEcliptiqueForMoon(double T) {
	double sigmab = sigmaB(T);
	double latitude = sigmab / 1000000;
	return latitude;
}

// latitudeMoon : Permite to have the longitude, latitude and distance heliocentric of the moon
void positionMoon(Planet *astre, struct tm now) {
	double hourdec = hourdecimal(now.tm_hour, now.tm_min, now.tm_sec);
	double julien = jourjulien(now.tm_year, now.tm_mon, now.tm_mday, hourdec);
	double T = t(julien);
	astre->longitude = longitudeEcliptiqueForMoon(T);
	astre->latitude = latitudeEcliptiqueForMoon(T);
	astre->distance = 0.00256955529;
}

/////////////// PLANET FUNCTIONS (Mercure, Venus, Mars, Jupiter, Saturne, Uranus, Neptune) ////////////////

// equinoxePlanet : Permite to stock in a value every values of the array of equinoxe
void equinoxePlanet(MYSQL *mysql, char *planet, double** stock, double T) {

	char query[] = "SELECT * FROM ASTRE WHERE name='?'";
	char* newquery = malloc(strlen(query) + strlen(planet));
	newquery = valueInsert(query, planet);

	int a[3] = { 1, 2, 3 };
	int e[4] = { 4, 5, 6, 7 };
	int l[4] = { 8, 9, 10, 11 };
	int i[4] = { 12, 13, 14, 15 };
	int s[4] = { 16, 17, 18, 19 };
	int p[4] = { 20, 21, 22, 23 };
	int *fields[] = { a,e,l,i,s,p };
	int size[6] = { 3,4,4,4,4,4 };

	multiplyInValues(mysql, newquery, fields, stock, size, 6, T);
	if (**(stock + 2) > 360) {
		int count = (int)**(stock + 2) / 360;
		**(stock + 2) = **(stock + 2) - count * 360;
	}
}

// keplerPlanet : Permite to execute kepler formul and have the result
double keplerPlanet(double P, double L, double e) {
	int i;
	double M = L - P;
	if (P > L) {
		M = M + 360;
	}
	double E = DEG2RAD(M);
	M = DEG2RAD(M);
	for (i = 0; i < 10; i++) {
		E = E + (M + e * sin(E) - E) / (1 - e * cos(E));
	}
	E = RAD2DEG(E);
	return E;
}

// anomaliePlanet : Permite to have the realAnomalie of the planet
double anomaliePlanet(double excentricite, double kepler, double T) {
	double anomalie = sqrt((1 + excentricite) / (1 - excentricite)) * tan(DEG2RAD(kepler) / 2);
	anomalie = RAD2DEG(atan(anomalie)) * 2;
	return anomalie;
}

// distanceSolPlanet : Permite to have the distance between the sun and the planet
double distanceSolPlanet(double axe, double excentricite, double kepler) {
	double distance = axe * (1 - excentricite * cos(DEG2RAD(kepler)));
	return distance;
}

// longitudeHelioPlanet : Permite to calcul the longitude heliocentric of the planet
double longitudeHelioPlanet(double L, double anomalieReal, double P) {
	double anomalieMoy = L - P;
	if (P > L) {
		anomalieMoy = anomalieMoy + 360;
	}
	double argument = L + anomalieReal - anomalieMoy;
	if (argument < 0) {
		argument = argument + 360;
	}
	return argument;
}

// latitudeHelioPlanet : Return the heliocentrique latitude of the planet
double latitudeHelioPlanet(double argument, double i) {
	double latitude = sin(DEG2RAD(argument)) * sin(DEG2RAD(i));
	latitude = RAD2DEG(asin(latitude));
	if (latitude > 360) {
		int count = (int)latitude / 360;
		latitude = latitude - count * 360;
	}
	return latitude;
}

// positionPlanet : Permite to have longitude, latitude and distance heliocentric of the planet
void positionPlanet(MYSQL *mysql,Planet *astre, struct tm now) {
	double hourdec = hourdecimal(now.tm_hour, now.tm_min, now.tm_sec);
	double julien = jourjulien(now.tm_year, now.tm_mon, now.tm_mday, hourdec);
	double T = t(julien);
	double* A = (double*)malloc(sizeof(double));
	double* E = (double*)malloc(sizeof(double));
	double* L = (double*)malloc(sizeof(double));
	double* I = (double*)malloc(sizeof(double));
	double* O = (double*)malloc(sizeof(double));
	double* P = (double*)malloc(sizeof(double));
	double *stockValues[6] = { A,E,L,I,O,P };
	equinoxePlanet(mysql, astre->name, stockValues, T);
	double kepler = keplerPlanet(*P, *L, *E);
	double anomalieReal = anomaliePlanet(*E, kepler, T);
	double distance = distanceSolPlanet(*A, *E, kepler);
	double longitude = longitudeHelioPlanet(*L, anomalieReal, *P);
	double latitude = latitudeHelioPlanet(longitude + *O, *I);
	free(A);
	free(E);
	free(L);
	free(I);
	free(O);
	free(P);
	astre->longitude = longitude;
	astre->latitude = latitude;
	astre->distance = distance;
	return astre;
}

void giveName(Planet astre[]) {
	astre[0].name = "Soleil";
	astre[0].longitude = 0;
	astre[0].latitude = 0;
	astre[0].distance = 0;
	astre[1].name = "Terre";
	astre[2].name = "Lune";
	astre[3].name = "Mercure";
	astre[4].name = "Venus";
	astre[5].name = "Mars";
	astre[6].name = "Jupiter";
	astre[7].name = "Saturne";
	astre[8].name = "Uranus";
	astre[9].name = "Neptune";
}

int degresToPwm(double degrees) {
	double value;
	if (degrees <= 180) {
		value = degrees + 70;
		printf("nord");
	}
	else {
		value = degrees - 180 + 70;
		printf("sud");
	}
	int valueInt = (int)value;
	return valueInt;
}

int degresToPwm2(double degrees) {
	double value;
	if (degrees <= 0) {
		value = 77 * degrees / 90 + 60;
		printf("rouge");
	}
	else {
		value = 77 * degrees / 90 + 137;
		printf("bleu");
	}
	int valueInt = (int)value;
	return valueInt;
}

void position(Planet *astre) {
	double x = (astre->distance) * cos(DEG2RAD(astre->longitude));
	double y = sqrt((astre->distance) * (astre->distance) - x * x);
	double z = (astre->latitude) * COEFF;
	x = x * COEFF;
	y = y * COEFF;
	if (astre->longitude > 180) {
		y = -y;
	}
	astre->x = x;
	astre->y = y;
	astre->z = z;
}

void getPlanetPosition()
{
	time_t rawtime;
	struct tm info;
	time(&rawtime);
	gmtime_s(&info, &rawtime);
	info.tm_year = info.tm_year + 1900;
	info.tm_mon = info.tm_mon + 1;

	MYSQL *mysql = mysql_init(NULL);
	mysql_options(mysql, MYSQL_READ_DEFAULT_GROUP, "option");

	if (mysql_real_connect(mysql, "localhost", "root", "", "stellarm", 0, NULL, 0))
	{
		MYSQL *mysqlShow = mysql_init(NULL);
		mysql_options(mysqlShow, MYSQL_READ_DEFAULT_GROUP, "option");

		Planet planets[10];
		giveName(&planets);
		int count;
		for (count = 0; count < 10; count++) {
			if (strcmp("Soleil", planets[count].name) == 0) {

			}
			else if (strcmp("Lune", planets[count].name) == 0) {
				positionMoon(&planets[count], info);
			}
			else if (strcmp("Terre", planets[count].name) == 0) {
				positionEarth(&planets[count], info);
			}
			else {
				positionPlanet(mysql, &planets[count], info);
			}
			position(&planets[count]);
			printf("%s %lf %lf %lf \n", planets[count].name, planets[count].longitude, planets[count].latitude, planets[count].distance);
			printf("x: %lf y: %lf z: %lf\n", planets[count].x, planets[count].y, planets[count].z);
		}
	}
	else
	{
		printf("Une erreur s'est produite lors de la connexion a la BDD!");
	}
	mysql_close(mysql);
}