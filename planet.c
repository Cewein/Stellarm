#include "planet.h"
#include "astro.h"
#include "sol.h"
#include <math.h>
#include "define.h"

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
	anomalie = RAD2DEG(atan(anomalie * 2));
	return anomalie;
}

// distanceSolPlanet : Permite to have the distance between the sun and the planet
double distanceSolPlanet(double axe, double excentricite, double kepler) {
	double distance = axe * (1 - excentricite * cos(DEG2RAD(kepler)));
	return distance;
}

// argumentLatitudePlanet : Permite to calcul the argument of the latitude of the planet
double argumentLatitudePlanet(double L, double anomalieReal, double P, double O) {
	double anomalieMoy = L - P;
	if (P > L) {
		anomalieMoy = anomalieMoy + 360;
	}
	double argument = L + anomalieReal - anomalieMoy - O;
	if (argument < 0) {
		argument = argument + 360; 
	}
	printf("argument : %lf \n", argument);
	return argument;
}

// le reste est a verifier
// longitudeHelioPlanet : Return the heliocentrique longitude of the planet
double longitudeHelioPlanet(double omega, double i, double argument) {
	double longitude = cos(DEG2RAD(i)) * tan(DEG2RAD(argument));
	longitude = RAD2DEG(atan(longitude + DEG2RAD(omega)));
	if (longitude > 360) {
		int count = (int)longitude / 360;
		longitude = longitude - count * 360;
	}
	if (longitude < 0) {
		longitude = longitude + 360;
	}
	return longitude;
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

// NPlanet, DPlanet : Permite to calcul two arguments for next functions
double NPlanet(double distance, double latitude, double longitude, double longitudeSol) {
	double N = distance * cos(DEG2RAD(latitude)) * sin(DEG2RAD(longitude) - DEG2RAD(longitudeSol));
	printf("N : %lf \n", N);
	return N;
}

double DPlanet(double distance, double latitude, double longitude, double longitudeSol, double rayonSol) {
	double D = distance * cos(DEG2RAD(latitude)) * cos(DEG2RAD(longitude) - DEG2RAD(longitudeSol)) + rayonSol;
	printf("D : %lf \n", D);
	return D;
}

// longitudeGeoPlanet : Return the geocentrique longitude of the planet
double longitudeGeoPlanet(double distance, double latitude, double longitude, double longitudeSol, double rayonSol) {
	double N = NPlanet(distance, latitude, longitude, longitudeSol);
	double D = DPlanet(distance, latitude, longitude, longitudeSol, rayonSol);
	double longitudeGeo = N / D;
	longitudeGeo = RAD2DEG(atan(longitudeGeo + DEG2RAD(longitudeSol)));
	return longitudeGeo;
}

// distanceEarthPlanet : Return the distance between the earth and the planet
double distanceEarthPlanet(double distance, double latitude, double longitude, double longitudeSol, double rayonSol) {
	double N = NPlanet(distance, latitude, longitude, longitudeSol);
	double D = DPlanet(distance, latitude, longitude, longitudeSol, rayonSol);
	double distanceGeo = N * N + D * D + (distance * sin(DEG2RAD(latitude))) * (distance * sin(DEG2RAD(latitude)));
	distanceGeo = sqrt(distanceGeo);
	return distanceGeo;
}

// latitudeGeoPlanet : Return the geocentrique latitude of the planet
double latitudeGeoPlanet(double distance, double latitude, double distanceGeo) {
	double latitudeGeo = (distance / distanceGeo) * sin(DEG2RAD(latitude));
	return latitudeGeo;
}

// azimutPlanet : Use previous functions for find azimut of the planet
double azimutPlanet(MYSQL *mysql, char* astre, double year, double month, double day, double hour, double min, double sec, double* latitude, double* longitude) {
	double hourdec = hourdecimal(hour, min, sec);
	double julien = jourjulien(year, month, day, hourdec);
	double T = t(julien);
	double* sideral = sideralTime(T, hour, min, sec);
	double* oblique = obliquite(T);

	double* A = (double*)malloc(sizeof(double));
	double* E = (double*)malloc(sizeof(double));
	double* L = (double*)malloc(sizeof(double));
	double* I = (double*)malloc(sizeof(double));
	double* O = (double*)malloc(sizeof(double));
	double* P = (double*)malloc(sizeof(double));
	double *stockValues[6] = { A,E,L,I,O,P };
	equinoxePlanet(mysql, astre, stockValues, T);
	double kepler = keplerPlanet(*P, *L, *E);
	double anomalieReal = anomaliePlanet(*E, kepler, T);
	double distance = distanceSolPlanet(*A, *E, kepler);
	double argumentLat = argumentLatitudePlanet(*L, anomalieReal, *P, *O);
	double longitudeEclipt = longitudeHelioPlanet(*O, *I, argumentLat);
	double latitudeEclipt = latitudeHelioPlanet(argumentLat, *I);
	
	double longitudeSol = viewLongitudeSol(T);
	double distanceSol = DistanceTerreSol(T);
	double longitudeGeo = longitudeGeoPlanet(distance, latitudeEclipt, longitudeEclipt, longitudeSol, distanceSol);
	double distanceGeo = distanceEarthPlanet(distance, latitudeEclipt, longitudeEclipt, longitudeSol, distanceSol);
	double latitudeGeo = latitudeGeoPlanet(distance, latitudeEclipt, distanceGeo);

	printf("distanceGeo = %lf \n \n", distanceGeo);
	printf("longitudeHelio = %lf \n", longitudeEclipt);
	printf("longitudeGeo = %lf \n", longitudeGeo);
	printf("latitudeHelio = %lf \n", latitudeEclipt);
	printf("latitudeGeo = %lf \n", latitudeGeo);

	double* ascensionDroite = TransformInLongitudeEquatorial(longitudeGeo, latitudeGeo, oblique);
	double* declinaison = TransformInLatitudeEquatorial(longitudeGeo, latitudeGeo, oblique);
	double angleHoraire = horaireAngle(ascensionDroite, longitude, sideral);
	double azimut = 0;
	double decl = DEG2RAD(hourdecimal(*declinaison, *(declinaison + 1), *(declinaison + 2)));
	angleHoraire = DEG2RAD(angleHoraire);
	double lat = DEG2RAD(hourdecimal(*latitude, *(latitude + 1), *(latitude + 2)));
	azimut = sin(angleHoraire) / (cos(angleHoraire) * sin(lat) - tan(decl) * cos(lat));
	double count = (int)(azimut / M_PI);
	azimut = RAD2DEG(atan(azimut));
	azimut = azimut + 180;
	if (azimut < 0)
		azimut = 180 + azimut;
	else if (azimut > 360)
		azimut = azimut - 360;
	printf("%s azimut : %lf \n", astre, azimut);
	free(A);
	free(E);
	free(L);
	free(I);
	free(O);
	free(P);
	free(sideral);
	free(oblique);
	free(ascensionDroite);
	free(declinaison);
	return azimut;
}

// hauteurPlanet : Use previous functions for find height of the planet
double hauteurPlanet(MYSQL *mysql, char* astre, double year, double month, double day, double hour, double min, double sec, double* latitude, double* longitude) {
	double hourdec = hourdecimal(hour, min, sec);
	double julien = jourjulien(year, month, day, hourdec);
	double T = t(julien);
	double* sideral = sideralTime(T, hour, min, sec);
	double* oblique = obliquite(T);

	double* A = (double*)malloc(sizeof(double));
	double* E = (double*)malloc(sizeof(double));
	double* L = (double*)malloc(sizeof(double));
	double* I = (double*)malloc(sizeof(double));
	double* O = (double*)malloc(sizeof(double));
	double* P = (double*)malloc(sizeof(double));
	double *stockValues[6] = { A,E,L,I,O,P };
	equinoxePlanet(mysql, astre, stockValues, T);
	double kepler = keplerPlanet(*P, *L, *E);
	double anomalieReal = anomaliePlanet(*E, kepler, T);
	double distance = distanceSolPlanet(*A, *E, kepler);
	double argumentLat = argumentLatitudePlanet(*L, anomalieReal, *P, *O);
	double longitudeEclipt = longitudeHelioPlanet(*O, *I, argumentLat);
	double latitudeEclipt = latitudeHelioPlanet(argumentLat, *I);

	double longitudeSol = viewLongitudeSol(T);
	double distanceSol = DistanceTerreSol(T);

	double longitudeGeo = longitudeGeoPlanet(distance, latitudeEclipt, longitudeEclipt, longitudeSol, distanceSol);
	double distanceGeo = distanceEarthPlanet(distance, latitudeEclipt, longitudeEclipt, longitudeSol, distanceSol);
	double latitudeGeo = latitudeGeoPlanet(distance, latitudeEclipt, distanceGeo);

	double* ascensionDroite = TransformInLongitudeEquatorial(longitudeGeo, latitudeGeo, oblique);
	double* declinaison = TransformInLatitudeEquatorial(longitudeGeo, latitudeGeo, oblique);
	double angleHoraire = horaireAngle(ascensionDroite, longitude, sideral);
	double hauteur = 0;
	double decl = DEG2RAD(hourdecimal(*declinaison, *(declinaison + 1), *(declinaison + 2)));
	angleHoraire = DEG2RAD(angleHoraire);
	double lat = DEG2RAD(hourdecimal(*latitude, *(latitude + 1), *(latitude + 2)));
	hauteur = sin(lat) * sin(decl) + cos(lat) * cos(decl) * cos(angleHoraire);
	hauteur = RAD2DEG(asin(hauteur));
	printf("%s hauteur : %lf \n", astre, hauteur);
	free(A);
	free(E);
	free(L);
	free(I);
	free(O);
	free(P);
	free(sideral);
	free(oblique);
	free(ascensionDroite);
	free(declinaison);
	return hauteur;
}