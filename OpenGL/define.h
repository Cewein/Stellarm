#pragma once
#include <corecrt_math_defines.h>

#define COEFF 200
#define RAD2DEG(x) x / (M_PI /180)
#define DEG2RAD(x) x * (M_PI/180)
#define HOUR2DEG(x) x * 15 
#define DEG2HOUR(x) x / 15
#define LF2POINT(x) LfToPoint(x)

typedef struct Planet Planet;
struct Planet {
	char *name;
	double longitude;
	double latitude;
	double distance;
	double x;
	double y;
	double z;
};

typedef struct Servo Servo;
struct Servo {
	char *name;
	double degrees;
	int pwm;
};