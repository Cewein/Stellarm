#pragma once

#include "database.h"
#include "define.h"

double hourdecimal(double hour, double min, double sec);
double* hourreal(double hour);
double* lfToPoint(double value);
double* HourdegreesInRealHour(double degrees, double min, double sec);
double* degreesInRealHour(double degrees);
double RealHourInDegrees(double hour, double min, double sec);
double jourjulien(double year, double month, double day, double hour);
double t(double julien);
double* sideralTime(double T,double hour, double min, double sec);
double longitudeSol(double T, char type);
double longitudeMoon(double T, char type);
double anomalieSol(double T, char type);
double anomalieMoon(double T, char type);
double longitudeNoeudMoon(double T, char type);
double* obliquite(double T);

double* TransformInLongitudeEquatorial(double longitude, double latitude, double* oblique);
double* TransformInLatitudeEquatorial(double longitude, double latitude, double* oblique);
double horaireAngle(double* ascension, double* longitudeDeg, double* sideral);
double azimut(MYSQL *mysql, char* astre, double year, double month, double day, double hour, double min, double sec, double* latitude, double* longitude);
double hauteur(MYSQL *mysql, char* astre, double year, double month, double day, double hour, double min, double sec, double* latitude, double* longitude);

void giveName(Planet astre[]);
void position(Planet *astre);
void getPlanetPosition(Planet * planets);

void degresToPwm(Servo *servo);
void degresToPwm2(Servo *servo);
int sizeForString(int value);
int checkMonth(int day, int month, int year);
int convertToLocalTime(double *longitude, int *hour, int *minutes, int *day, int *month, int *year);
int convertToUTCTime(double *longitude, double *hour, double *minutes, double *day, double *month, double *year);

double getSize(int x);
