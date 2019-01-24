#include <stdio.h>
#include <stdlib.h>
#include "positionPlanet.h"

//void delay(unsigned int mseconds)
//{
//	clock_t goal = mseconds + clock();
//	while (goal > clock());
//}

//int main(int argc, char **argv) {
//	int value = 0;
//	for (;;) {
//		delay(10000);
//		system("..\\..\\String\\Debug\\String.exe");
//		printf("%d \n", value);
//		value++;
//		if (value == 3) {
//			return 0;
//		}
//	}
//}
/*
int main(int argc, char **argv) {
	time_t rawtime;
	struct tm info;
	time(&rawtime);
	gmtime_s(&info, &rawtime);
	info.tm_year = info.tm_year + 1900;
	info.tm_mon = info.tm_mon + 1;

	MYSQL *mysql = mysql_init(NULL);
	mysql_options(mysql, MYSQL_READ_DEFAULT_GROUP, "option");

	if (mysql_real_connect(mysql, "localhost", "root", "", "stellarm", 0, NULL, 0))
	{
		MYSQL *mysqlShow = mysql_init(NULL);
		mysql_options(mysqlShow, MYSQL_READ_DEFAULT_GROUP, "option");

		Planet planets[10];
		giveName(&planets);
		int count;
		for (count = 0; count < 10; count++) {
			if (strcmp("Soleil", planets[count].name) == 0) {

			}
			else if (strcmp("Lune", planets[count].name) == 0) {
				positionMoon(&planets[count], info);
			}
			else if (strcmp("Terre", planets[count].name) == 0) {
				positionEarth(&planets[count],info);
			}
			else {
				positionPlanet(mysql, &planets[count], info);
			}
			position(&planets[count]);
			printf("%s %lf %lf %lf \n", planets[count].name, planets[count].longitude, planets[count].latitude, planets[count].distance);
			printf("x: %lf y: %lf z: %lf\n", planets[count].x, planets[count].y, planets[count].z);
		}
	}
	else
	{
		printf("Une erreur s'est produite lors de la connexion a la BDD!");
	}
	mysql_close(mysql);
	system("pause");
	return(0);
}
*/