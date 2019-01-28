#include "moon.h"
#include "astro.h"
#include <math.h>
#include <time.h>

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

// positionMoon : Permite to have the longitude, latitude and distance heliocentric of the moon
void positionMoon(Planet *astre, struct tm now) {
	double hourdec = hourdecimal(now.tm_hour, now.tm_min, now.tm_sec);
	double julien = jourjulien(now.tm_year, now.tm_mon, now.tm_mday, hourdec);
	double T = t(julien);
	astre->longitude = longitudeEcliptiqueForMoon(T);
	astre->latitude = latitudeEcliptiqueForMoon(T);
	astre->distance = 0.00256955529;
}

// azimutMoon : Use many fonctions of astro.c and moon.c for have the azimut of the moon
double azimutMoon(double year, double month, double day, double hour, double min, double sec, double* latitude, double* longitude) {
	double hourdec = hourdecimal(hour, min, sec);
	double julien = jourjulien(year, month, day, hourdec);
	double T = t(julien);
	double* sideral = sideralTime(T, hour, min, sec);
	double* oblique = obliquite(T);
	double longitudeEclip = longitudeEcliptiqueForMoon(T);
	double latitudeEclip = latitudeEcliptiqueForMoon(T);
	double* ascensionDroite = TransformInLongitudeEquatorial(longitudeEclip, latitudeEclip, oblique);
	double* declinaison = TransformInLatitudeEquatorial(longitudeEclip, latitudeEclip, oblique);
	double angleHoraire = horaireAngle(ascensionDroite, longitude, sideral);
	double azimut = 0;
	double decl = DEG2RAD(hourdecimal(*declinaison, *(declinaison + 1), *(declinaison + 2)));
	angleHoraire = DEG2RAD(angleHoraire);
	double lat = DEG2RAD(hourdecimal(*latitude, *(latitude + 1), *(latitude + 2)));
	azimut = sin(angleHoraire) / (cos(angleHoraire) * sin(lat) - tan(decl) * cos(lat));
	double count = (int)(azimut / M_PI);
	azimut = RAD2DEG(atan(azimut));
	if (azimut < 0)
		azimut = 180 + azimut;
	else if (azimut > 360)
		azimut = azimut - 360;
	printf("Lune azimut : %lf \n", azimut);
	free(sideral);
	free(oblique);
	free(ascensionDroite);
	free(declinaison);
	return azimut;

}

// hauteurMoon : Use many fonctions of astro.c and moon.c for have the height of the moon
double hauteurMoon(double year, double month, double day, double hour, double min, double sec, double* latitude, double* longitude) {
	double hourdec = hourdecimal(hour, min, sec);
	double julien = jourjulien(year, month, day, hourdec);
	double T = t(julien);
	double* sideral = sideralTime(T, hour, min, sec);
	double* oblique = obliquite(T);
	double longitudeEclip = longitudeEcliptiqueForMoon(T);
	double latitudeEclip = latitudeEcliptiqueForMoon(T);
	double* ascensionDroite = TransformInLongitudeEquatorial(longitudeEclip, latitudeEclip, oblique);
	double* declinaison = TransformInLatitudeEquatorial(longitudeEclip, latitudeEclip, oblique);
	double angleHoraire = horaireAngle(ascensionDroite, longitude, sideral);
	double hauteur = 0;
	double decl = DEG2RAD(hourdecimal(*declinaison, *(declinaison + 1), *(declinaison + 2)));
	angleHoraire = DEG2RAD(angleHoraire);
	double lat = DEG2RAD(hourdecimal(*latitude, *(latitude + 1), *(latitude + 2)));
	hauteur = sin(lat) * sin(decl) + cos(lat) * cos(decl) * cos(angleHoraire);
	hauteur = RAD2DEG(asin(hauteur));
	printf("Lune hauteur : %lf \n",hauteur);
	free(sideral);
	free(oblique);
	free(ascensionDroite);
	free(declinaison);
	return hauteur;
}