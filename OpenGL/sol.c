#include "astro.h"
#include "sol.h"
#include <math.h>
#include <time.h>

////////// FUNCTIONS FOR SUN /////////////

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

// realAnomalieSol : Permite to calcul the real anomalie of the sun
double realAnomalieSol(double T) {
	double anomalieReal;
	double anomalieMoy = anomalieSolForSol(T, 'r');
	double centre = centreSol(T, anomalieMoy, 'r');
	anomalieReal = anomalieMoy + centre;
	return anomalieReal;
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

// DistanceTerreSol : Return the distance between the earth and the sun
double DistanceTerreSol(double T) {
	double e = excentriciteForSol(T, 'r');
	double v = realAnomalieSol(T);
	double distance = 1.000001018 * (1 - e * e) / (1 + e * cos(v));
	return distance;
}

// ascensionDroiteSol : Return right ascension of the sun (is like equatorial longitude)
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

// declinaisonSol : Return declinaison of the sun (is like equatorial latitude)
double* declinaisonSol(double longitude, double* oblique) {
	longitude = DEG2RAD(longitude);
	double obli = DEG2RAD((*oblique + (*(oblique + 1) / 100) + (*(oblique + 2) / 1000)));
	double declinaison = sin(obli) * sin(longitude);
	declinaison = asin(declinaison);
	declinaison = RAD2DEG(declinaison);
	double* hourDeclinaison = hourreal(declinaison);
	return hourDeclinaison;
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
	double distance = DistanceTerreSol(T);
	astre->distance = distance;
	astre->latitude = 0;
	astre->longitude = longitudeView;
}

// azimutSol : Use previous functions for find azimut of the sun
double azimutSol(double year, double month, double day, double hour, double min, double sec, double* latitude, double* longitude) {
	double hourdec = hourdecimal(hour, min, sec);
	double julien = jourjulien(year, month, day, hourdec);
	double T = t(julien);
	double* sideral = sideralTime(T, hour, min, sec);
	double* oblique = obliquite(T);
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
	printf("Soleil azimut : %lf \n", azimut);
	free(sideral);
	free(oblique);
	free(ascensionDroite);
	free(declinaison);
	return azimut;
}

// hauteurSol : Use previous functions for find height of the sun
double hauteurSol(double year, double month, double day, double hour, double min, double sec, double* latitude, double* longitude) {
	double hourdec = hourdecimal(hour, min, sec);
	double julien = jourjulien(year, month, day, hourdec);
	double T = t(julien);
	double* sideral = sideralTime(T, hour, min, sec);
	double* oblique = obliquite(T);
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
	printf("Soleil hauteur : %lf \n", hauteur);
	free(sideral);
	free(oblique);
	free(ascensionDroite);
	free(declinaison);
	return hauteur;
}