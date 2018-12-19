#pragma once

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
double azimutMoon(double year, double month, double day, double hour, double min, double sec, double* latitude, double* longitude);
double hauteurMoon(double year, double month, double day, double hour, double min, double sec, double* latitude, double* longitude);