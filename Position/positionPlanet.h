#pragma once
#include <math.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include "database.h"
#include "define.h"

double hourdecimal(int hour, int min, int sec);
double jourjulien(int year, int month, int day, double hour);
double t(double julien);
double anomalieSolForSol(double T, char type);
double excentriciteForSol(double T, char type);
double centreSol(double T, double anomalie, char type);
double reallongitudeSol(double T);
double omegaSol(double T, char type);
double viewLongitudeSol(double T);
double realAnomalieSol(double T);
double distanceTerreSol(double T);
void positionEarth(Planet *astre, struct tm now);

double longitudeMoonForMoon(double T, char type);
double anomalieSolForMoon(double T, char type);
double anomalieMoonForMoon(double T, char type);
double elongationForMoon(double T, char type);
double distanceForMoon(double T, char type);
double a1(double T, char type);
double a2(double T, char type);
double a3(double T, char type);
double sigmaL(double T);
double sigmaB(double T);
double longitudeEcliptiqueForMoon(double T);
double latitudeEcliptiqueForMoon(double T);
void positionMoon(Planet *astre, struct tm now);

void equinoxePlanet(MYSQL *mysql, char *planet, double** stock, double T);
double keplerPlanet(double P, double L, double e);
double anomaliePlanet(double excentricite, double kepler, double T);
double distanceSolPlanet(double axe, double excentricite, double kepler);
double longitudeHelioPlanet(double L, double anomalieReal, double P);
double latitudeHelioPlanet(double argument, double i);
void positionPlanet(MYSQL *mysql, Planet *astre, struct tm now);

void giveName(Planet astre[]);
void position(Planet *astre);
void getPlanetPosition();

int degresToPwm(double degrees);
int degresToPwm2(double degrees);