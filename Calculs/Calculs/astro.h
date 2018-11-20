#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <corecrt_math_defines.h>

double hourdecimal(int hour, double min, double sec);
double* hourreal(double hour);
double jourjulien(int year, int month, int day, double hour);
double t(double julien);
double* sideralTime(double T,int hour, double min, double sec);
double longitudeSol(double T);
double longitudeMoon(double T);
double anomalieSol(double T);
double anomalieMoon(double T);
double longitudeNoeudMoon(double T);
double* obliquite(double T);
double longitudeMoonForMoon(double T);
double anomalieSolForMoon(double T);
double anomalieMoonForMoon(double T);
double elongationForMoon(double T);
double distanceForMoon(double T);
double a1(double T);
double a2(double T);
double a3(double T);
double sigmaL(double T);
double sigmaB(double T);
double longitudeEcliptique(double T);
double latitudeEcliptique(double T);
double TransformInLongitudeEquatorial(double longitude, double latitude, double* oblique);
double TransformInLatitudeEquatorial(double longitude, double latitude, double* oblique);
double azimut(double T);

