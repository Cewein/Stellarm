#pragma once
#include <corecrt_math_defines.h>

#define RAD2DEG(x) x / (M_PI /180)
#define DEG2RAD(x) x * (M_PI/180)
#define HOUR2DEG(x) x * 15 
#define DEG2HOUR(x) x / 15
#define LF2POINT(x) LfToPoint(x)