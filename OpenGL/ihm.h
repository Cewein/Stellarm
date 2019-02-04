#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "database.h"
#include "astro.h"
#include "moon.h"
#include "sol.h"
#include "planet.h"

#pragma comment(lib, "ws2_32.lib")

int InterfaceArm(char *serveur);
char *InterfaceCity(char *serveur);
int InterfaceTime(char *serveur, char *city);
int mainIHM();