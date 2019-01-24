#pragma once
#include <corecrt_math_defines.h>


#define COEFF 100
#define RAD2DEG(x) x / (M_PI /180)
#define DEG2RAD(x) x * (M_PI/180)
#define HOUR2DEG(x) x * 15 
#define DEG2HOUR(x) x / 15

typedef struct Planet Planet;
struct Planet{
	char *name;
	double longitude;
	double latitude;
	double distance;
	double x;
	double y;
	double z;
};