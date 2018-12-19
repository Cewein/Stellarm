#pragma once

double anomalieSolForSol(double T, char type);
double realAnomalieSol(double T);
double excentriciteForSol(double T, char type);
double centreSol(double T, double anomalie, char type);
double reallongitudeSol(double T);
double omegaSol(double T, char type);
double viewLongitudeSol(double T);
double DistanceTerreSol(double T);
double* ascensionDroiteSol(double longitude, double* oblique);
double* declinaisonSol(double longitude, double* oblique);
double azimutSol(double year, double month, double day, double hour, double min, double sec, double* latitude, double* longitude);
double hauteurSol(double year, double month, double day, double hour, double min, double sec, double* latitude, double* longitude);