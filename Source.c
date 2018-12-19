#include "moon.h"
#include "sol.h"
#include "planet.h"
#include "database.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "astro.h"

int main(int argc, char **argv) {

	double *longitude;
	double *latitude;
	longitude = (double*)malloc(sizeof(double) * 3);
	latitude = (double*)malloc(sizeof(double) * 3);
	double *yearUser = (double*)malloc(sizeof(double));
	double *monthUser = (double*)malloc(sizeof(double));
	double *dayUser = (double*)malloc(sizeof(double));
	double *hourUser = (double*)malloc(sizeof(double));
	double *minUser = (double*)malloc(sizeof(double));
	double *secUser = (double*)malloc(sizeof(double));
	char *place = (char*)malloc(20);
	char *planet = (char*)malloc(10);

	MYSQL *mysql = mysql_init(NULL);
	mysql_options(mysql, MYSQL_READ_DEFAULT_GROUP, "option");

	if (mysql_real_connect(mysql, "localhost", "root", "", "stellarm", 0, NULL, 0))
	{
		MYSQL *mysqlShow = mysql_init(NULL);
		mysql_options(mysqlShow, MYSQL_READ_DEFAULT_GROUP, "option");

	//	char *queryUser = "SELECT * FROM USER ORDER BY id DESC";
		char queryUser[] = "SELECT * FROM USER WHERE planet = 'Mars'";
		char *tab[] = { yearUser, monthUser, dayUser, hourUser, minUser, secUser, place, planet };
		int fieldsUser[8] = { 1, 2, 3, 4, 5, 6, 8, 9 };
		char *typeUser[] = { "double", "double", "double", "double", "double", "double", "string", "string" };
		stockValues(mysql, queryUser, fieldsUser, tab, typeUser, 8);

		char query[] = "SELECT * FROM CITY WHERE name='?'";
		char *newquery = malloc(strlen(query) + strlen(place));
		newquery = valueInsert(query, place);
		int fields[2] = { 1, 2 };
		char *cordonnees[] = { latitude, longitude };
		char *type[] = { "double", "double" };
		stockValues(mysql, newquery, fields, cordonnees, type, 2);
		longitude = hourreal(*longitude);
		latitude = hourreal(*latitude);

		double azimut = 0;
		double hauteur = 0;
		if (strcmp("Lune", planet) == 0) {
			azimut = azimutMoon(*yearUser, *monthUser, *dayUser, *hourUser, *minUser, *secUser, latitude, longitude);
			hauteur = hauteurMoon(*yearUser, *monthUser, *dayUser, *hourUser, *minUser, *secUser, latitude, longitude);
		}
		else if (strcmp("Soleil", planet) == 0) {
			azimut = azimutSol(*yearUser, *monthUser, *dayUser, *hourUser, *minUser, *secUser, latitude, longitude);
			hauteur = hauteurSol(*yearUser, *monthUser, *dayUser, *hourUser, *minUser, *secUser, latitude, longitude);
		}
		else {
			azimut = azimutPlanet(mysql, planet, *yearUser, *monthUser, *dayUser, *hourUser, *minUser, *secUser, latitude, longitude);
			hauteur = hauteurPlanet(mysql, planet, *yearUser, *monthUser, *dayUser, *hourUser, *minUser, *secUser, latitude, longitude);
		}
	}
	else
	{
		printf("Une erreur s'est produite lors de la connexion a la BDD!");
	}
	free(latitude);
	free(longitude);
	free(yearUser);
	free(monthUser);
	free(dayUser);
	free(hourUser);
	free(minUser);
	free(secUser);
	system("pause");
	return 0;
}