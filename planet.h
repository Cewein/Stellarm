#pragma once
#include "database.h"

void equinoxePlanet(MYSQL *mysql, char *planet, double** stock, double T);
double keplerPlanet(double P, double L, double e);
double anomaliePlanet(double excentricite, double kepler, double T);
double distanceSolPlanet(double axe, double excentricite, double kepler);
double argumentLatitudePlanet(double L, double anomalieReal, double P, double O);
double longitudeHelioPlanet(double omega, double i, double argument);
double latitudeHelioPlanet(double argument, double i);
double NPlanet(double distance, double latitude, double longitude, double longitudeSol);
double DPlanet(double distance, double latitude, double longitude, double longitudeSol, double rayonSol);
double longitudeGeoPlanet(double distance, double latitude, double longitude, double longitudeSol, double rayonSol);
double distanceEarthPlanet(double distance, double latitude, double longitude, double longitudeSol, double rayonSol);
double latitudeGeoPlanet(double distance, double latitude, double distanceGeo);
double azimutPlanet(MYSQL *mysql, char* astre, double year, double month, double day, double hour, double min, double sec, double* latitude, double* longitude);
double hauteurPlanet(MYSQL *mysql, char* astre, double year, double month, double day, double hour, double min, double sec, double* latitude, double* longitude);