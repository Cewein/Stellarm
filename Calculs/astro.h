#pragma once
#include <stdlib.h>
#include <stdio.h>

double hourdecimal(double hour, double min, double sec);
double* hourreal(double hour);
double* LfToPoint(double value);
double* HourdegreesInRealHour(double degrees, double min, double sec);
double* degreesInRealHour(double degrees);
double RealHourInDegrees(double hour, double min, double sec);
double jourjulien(int year, int month, int day, double hour);
double t(double julien);
double* sideralTime(double T,double hour, double min, double sec);
double longitudeSol(double T, char type);
double longitudeMoon(double T, char type);
double anomalieSol(double T, char type);
double anomalieMoon(double T, char type);
double longitudeNoeudMoon(double T, char type);
double* obliquite(double T);
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
double longitudeEcliptique(double T);
double latitudeEcliptique(double T);
double* TransformInLongitudeEquatorial(double longitude, double latitude, double* oblique);
double* TransformInLatitudeEquatorial(double longitude, double latitude, double* oblique);
double horaireAngle(double* ascension, double* longitudeDeg, double* sideral);
double azimut(char* astre, int year, int month, int day, double hour, double min, double sec, double* latitude, double* longitude);
double hauteur(char* astre, int year, int month, int day, double hour, double min, double sec, double* latitude, double* longitude);

