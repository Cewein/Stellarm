#pragma warning(disable : 4996)
#include "ihm.h"

int InterfaceArm(char *serveur) {
	char *follow = malloc(6);
	char *planet = malloc(10);
	int checkPlanet = 1;
	printf("/////////////STELLARM///////////////\n");
	printf("Bienvenue sur l'interface de controle du bras robot de Stellarm, rentrez vos informations pour que le bras vous retourne la position de l'astre dans le ciel\n");
	printf("Quelle astre voulez voir ? \n1.Soleil \n2.Lune \n3.Mercure \n4.Venus \n5.Mars \n6.Jupiter \n7.Saturne \n8.Uranus \n9.Neptune\n");
	do {
		gets(planet, 10);
		if (_stricmp(planet, "Soleil") == 0 || strcmp(planet, "1") == 0) {
			planet = "Soleil";
			checkPlanet = 0;
		}
		else if (_stricmp(planet, "Lune") == 0 || strcmp(planet, "2") == 0) {
			planet = "Lune";
			checkPlanet = 0;
		}
		else if (_stricmp(planet, "Mercure") == 0 || strcmp(planet, "3") == 0) {
			planet = "Mercure";
			checkPlanet = 0;
		}
		else if (_stricmp(planet, "Venus") == 0 || strcmp(planet, "4") == 0) {
			planet = "Venus";
			checkPlanet = 0;
		}
		else if (_stricmp(planet, "Mars") == 0 || strcmp(planet, "5") == 0) {
			planet = "Mars";
			checkPlanet = 0;
		}
		else if (_stricmp(planet, "Jupiter") == 0 || strcmp(planet, "6") == 0) {
			planet = "Jupiter";
			checkPlanet = 0;
		}
		else if (_stricmp(planet, "Saturne") == 0 || strcmp(planet, "7") == 0) {
			planet = "Saturne";
			checkPlanet = 0;
		}
		else if (_stricmp(planet, "Uranus") == 0 || strcmp(planet, "8") == 0) {
			planet = "Uranus";
			checkPlanet = 0;
		}
		else if (_stricmp(planet, "Neptune") == 0 || strcmp(planet, "9") == 0) {
			planet = "Neptune";
			checkPlanet = 0;
		}
		else {
			printf("Mauvaise valeur veuillez rentrer le nom de la planete ou son numero associe\n");
			checkPlanet = 1;
		}
	} while (checkPlanet);

	printf("\nDe ou voulez-voir la planete ? (si votre ville n'est pas disponible tapez other)\n");
	MYSQL *mysql = mysql_init(NULL);
	mysql_options(mysql, MYSQL_READ_DEFAULT_GROUP, "option");

	if (mysql_real_connect(mysql, serveur, "root", "", "stellarm", 0, NULL, 0))
	{
		char *place = malloc(20);
		int verifCity = 0;

		char *queryCity = "SELECT name FROM CITY ORDER BY name ASC";
		seeResult(mysql, queryCity);
		do {
			gets(place, 20);

			if (_stricmp(place, "other") == 0) {
				printf("\n");
				place = InterfaceCity(serveur);
			}

			char* queryVerifCity = "SELECT name FROM CITY WHERE name = '?'";
			char* insertPlace[] = { place };
			queryVerifCity = valuesInsert(queryVerifCity, insertPlace, 1);
			verifCity = seeResultExist(mysql, queryVerifCity);

			if (!verifCity) {
				printf("Mauvaise valeur veuillez rentrer le nom d'une des villes ou ajoutez celle que vous souhaitez avec 'other'\n");
			}
		} while (!verifCity);

		char *local = malloc(5);
		char *year = malloc(6);
		char *month = malloc(6);
		char *day = malloc(6);
		char *hour = malloc(6);
		char *minutes = malloc(6);

		printf("\nVoulez vous utilisez l'heure actuelle (oui/non) ?\n");
		do {
			gets(local, 4);
		} while (!(_stricmp(local, "oui") == 0 || _stricmp(local, "non") == 0));

		if (_stricmp(local, "oui") == 0) {
			follow = "0";
			time_t rawtime;
			struct tm localTime;
			time(&rawtime);
			gmtime_s(&localTime, &rawtime);
			localTime.tm_year = localTime.tm_year + 1900;
			localTime.tm_mon = localTime.tm_mon + 1;
			sprintf_s(year, 6, "%d", localTime.tm_year);
			sprintf_s(month, 6, "%d", localTime.tm_mon);
			sprintf_s(day, 6, "%d", localTime.tm_mday);
			sprintf_s(hour, 6, "%d", localTime.tm_hour);
			sprintf_s(minutes, 6, "%d", localTime.tm_min);
		}
		else {
			
			int verifYear = -4717;
			int verifMonth = 0;
			int verifDay = 0;
			int verifHour = 25;
			int verifMinutes = 61;
			char *typeHour = malloc(15);
			int typeHourAgain = 0;
			char *seeInterfaceTime = malloc(6);

			do {
				printf("\nVoulez vous utilisez l'heure : \n1.Universelle (Greenwich) \n2.Locale \n");
				gets(typeHour, 15);
				if (_stricmp(typeHour, "Universelle") == 0 || strcmp(typeHour, "1") == 0) {
					follow = "0";
					typeHourAgain = 0;
				}
				else if (_stricmp(typeHour, "Locale") == 0 || strcmp(typeHour, "2") == 0) {
					follow = "1";
					typeHourAgain = 0;
					printf("\nAttention ! L'heure utilise dans votre ville ou pays n'est pas forcement la vraie heure locale, voulez voir la vraie heure de votre ville pour la comparer avec la votre et pouvoir l'utiliser? (oui/non)\n");
					do {
						gets(seeInterfaceTime, 5);
						if (_stricmp(seeInterfaceTime, "oui") == 0) {
							printf("\n");
							InterfaceTime(serveur,place);
						}
					} while (!(_stricmp(seeInterfaceTime, "oui") == 0 || _stricmp(seeInterfaceTime, "non") == 0));
				}
				else {
					typeHourAgain = 1;
				}
			} while (typeHourAgain);

			printf("\nRentrez la date a laquelle vous voulez voir la planete \n");
			printf("Veuillez saisir une annee entre -4716 et 3000 : \n");
			do {
				gets(year, 6);
				sscanf_s(year, "%d", &verifYear);
			} while (verifYear < -4716 || verifYear > 3000);
		

			printf("Veuillez saisir un mois entre 1 et 12 : \n");
			do {
				gets(month, 6);
				sscanf_s(month, "%d", &verifMonth);
			} while (verifMonth < 1 || verifMonth > 12);

			printf("Veuillez saisir un jour entre 1 et 31 : \n");
			do {
				gets(day, 6);
				sscanf_s(day, "%d", &verifDay);
				if (verifDay > 28) {
					if (!checkMonth(verifDay, verifMonth, verifYear)) {
						printf("Le jour rentre doit coincider avec le mois\n");
					}
				}
			} while (verifDay < 1 || verifDay > 31 || (verifDay > 28 && !checkMonth(verifDay, verifMonth, verifYear)));

			printf("Veuillez saisir une heure entre 0 et 24 : \n");
			do {
				gets(hour, 6);
				sscanf_s(hour, "%d", &verifHour);
				if (verifHour == 24) {
					hour = "0";
				}
			} while (verifHour < 0 || verifHour > 24);

			printf("Veuillez saisir les minutes entre 0 et 60 : \n");
			do {
				gets(minutes, 6);
				sscanf_s(minutes, "%d", &verifMinutes);
				if (verifMinutes == 60) {
					minutes = "0";
				}
			} while (verifMinutes < 0 || verifMinutes > 60);
		}

		printf("\n");

		char* query = "INSERT INTO USER(year, month, day, hour, minutes, seconds, follow, place, planet) VALUES( ?, ?, ?, ?, ?, 0, ?, '?', '?')";
		char* insert[] = { year, month, day, hour, minutes, follow, place, planet };
		char* res;
		res = valuesInsert(query, insert, 8);
		mysql_query(mysql, res);
	}
	else {
		printf("La connexion a la BDD a echoue");
		return 0;
	}
	mysql_close(mysql);
	return 1;
}

char *InterfaceCity(char *serveur) {
	MYSQL *mysql = mysql_init(NULL);
	mysql_options(mysql, MYSQL_READ_DEFAULT_GROUP, "option");
	char *place = malloc(20);

	if (mysql_real_connect(mysql, serveur, "root", "", "stellarm", 0, NULL, 0))
	{
		char *longitude = malloc(20);
		char *latitude = malloc(20);
		double verifLongitude;
		double verifLatitude;
		int count = 0;
		printf("Bienvenue sur l'interface d'ajout de villes\n");
		printf("Donnez le nom de la ville :\n");
		gets(place, 20);
		printf("Donnez la longitude de la ville :\n");
		do {
			if (count > 0) {
				printf("La longitude doit etre comprise entre -180 et 180\n");
			}
			gets(longitude, 20);
			sscanf_s(longitude, "%lf", &verifLongitude);
			count++;
		} while (verifLongitude < -180 || verifLongitude > 180);

		count = 0;
		printf("Donnez la latitude de la ville : \n");
		do {
			if (count > 0) {
				printf("La latitude doit etre comprise entre -90 et 90\n");
			}
			gets(latitude, 20);
			sscanf_s(latitude, "%lf", &verifLatitude);
			count++;
		} while (verifLatitude < -90 || verifLatitude > 90);
		
		char* query = "INSERT INTO CITY(name, latitude, longitude) VALUES('?', ?, ?)";
		char* insert[] = { place, latitude, longitude };
		query = valuesInsert(query, insert, 3);
		mysql_query(mysql, query);
	}
	else{
		printf("La connexion a la BDD a echoue");
		return NULL;
	}
	mysql_close(mysql);
	return place;
}

int InterfaceTime(char *serveur, char *city) {
	MYSQL *mysql = mysql_init(NULL);
	mysql_options(mysql, MYSQL_READ_DEFAULT_GROUP, "option");
	char *place = malloc(20);

	if (mysql_real_connect(mysql, serveur, "root", "", "stellarm", 0, NULL, 0))
	{
		if (_strcmpi(city, "") == 0) {
			int count = 0;
			printf("Bienvenue sur l'interface permettant de connaitre le decalage horaire depuis Greenwich (+0)\n");
			char *queryCity = "SELECT name FROM CITY ORDER BY name ASC";
			seeResult(mysql, queryCity);
			printf("\nDonnez le nom de la ville dont vous voulez connaitre l'heure reelle :\n");
			gets(place, 20);
		}
		else {
			place = city;
		}

		double *longitude = malloc(sizeof(double));
		char* query = "SELECT * FROM CITY WHERE name = '?'";
		char* insertPlace[] = { place };
		query = valuesInsert(query, insertPlace, 1);
		int verifCity = seeResultExist(mysql, query);

		if (!verifCity) {
			printf("Mauvaise valeur veuillez rentrez le nom d'une des villes ou ajoutez celle que vous souhaitez\n");
			return 0;
		}
		stockDouble(mysql, query, 2, longitude);

		time_t rawtime;
		struct tm UtcTime;
		time(&rawtime);
		gmtime_s(&UtcTime, &rawtime);
		UtcTime.tm_year = UtcTime.tm_year + 1900;
		UtcTime.tm_mon = UtcTime.tm_mon + 1;

		convertToLocalTime(longitude, &UtcTime.tm_hour, &UtcTime.tm_min, &UtcTime.tm_mday, &UtcTime.tm_mon, &UtcTime.tm_year);
		printf("A %s il est actuellement %dh %dmin et nous sommes le %d/%d/%d\n", place, UtcTime.tm_hour, UtcTime.tm_min, UtcTime.tm_mday, UtcTime.tm_mon, UtcTime.tm_year);
	}
	else {
		printf("La connexion a la BDD a echoue");
		return 0;
	}
	mysql_close(mysql);
	return 1;
}

int mainIHM()
{
	int error = 1;
	error = InterfaceArm("localhost");
	if (error == 0) {
		system("pause");
		return 0;
	}

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
	int *follow = (int*)malloc(sizeof(int));
	char *place = (char*)malloc(20);
	char *planet = (char*)malloc(10);
	double azimut = -1;
	double hauteur = -1;

	MYSQL *mysql = mysql_init(NULL);
	mysql_options(mysql, MYSQL_READ_DEFAULT_GROUP, "option");

	if (mysql_real_connect(mysql, "localhost", "root", "", "stellarm", 0, NULL, 0))
	{
		MYSQL *mysqlShow = mysql_init(NULL);
		mysql_options(mysqlShow, MYSQL_READ_DEFAULT_GROUP, "option");

		char *queryUser = "SELECT * FROM USER ORDER BY id DESC";
		char *tab[] = { yearUser, monthUser, dayUser, hourUser, minUser, secUser, follow, place, planet };
		int fieldsUser[9] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
		char *typeUser[] = { "double", "double", "double", "double", "double", "double", "int", "string", "string" };
		stockValues(mysql, queryUser, fieldsUser, tab, typeUser, 9);

		char query[] = "SELECT * FROM CITY WHERE name='?'";
		char *newquery = malloc(strlen(query) + strlen(place));
		newquery = valueInsert(query, place);
		int fields[2] = { 1, 2 };
		char *cordonnees[] = { latitude, longitude };
		char *type[] = { "double", "double" };
		stockValues(mysql, newquery, fields, cordonnees, type, 2);

		if (*follow == 1) {
			convertToUTCTime(longitude, hourUser, minUser, dayUser, monthUser, yearUser);
		}

		longitude = hourreal(*longitude);
		latitude = hourreal(*latitude);

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
		printf("Une erreur s'est produite lors de la connexion a la BDD!\n");
	}
	free(latitude);
	free(longitude);
	free(yearUser);
	free(monthUser);
	free(dayUser);
	free(hourUser);
	free(minUser);
	free(secUser);
	free(follow);
	mysql_close(mysql);

	if (azimut != -1 || hauteur != -1) {
		Servo horizontal;
		Servo vertical;
		horizontal.degrees = azimut;
		vertical.degrees = hauteur;
		degresToPwm(&horizontal);
		degresToPwm2(&vertical);
		int size = sizeForString(horizontal.pwm) + sizeForString(vertical.pwm);
		printf("\nRegardez la partie %s de l'axe horizontal et la couleur %s de son axe vertical \n", horizontal.name, vertical.name);

		WSADATA WSAData;
		SOCKET sock;
		SOCKET csock;
		SOCKADDR_IN sin;
		SOCKADDR_IN csin;
		WSAStartup(MAKEWORD(2, 0), &WSAData);
		sock = socket(AF_INET, SOCK_STREAM, 0);
		sin.sin_addr.s_addr = INADDR_ANY;
		sin.sin_family = AF_INET;
		sin.sin_port = htons(23);
		bind(sock, (SOCKADDR *)&sin, sizeof(sin));
		listen(sock, 5);
		int stop = -1;
		char *string = malloc(size + 2);
		sprintf_s(string, size + 2, "%d %d", horizontal.pwm, vertical.pwm);
		printf("Envoi de donnees en cours \nLancez './project' qui se trouve dans le repertoire de l'utilisateur pi (mdp : luffy)\n");
		while (stop == -1)
		{
			int sinsize = sizeof(csin);
			if ((csock = accept(sock, (SOCKADDR *)&csin, &sinsize)) != INVALID_SOCKET)
			{
				stop = send(csock, string, size + 2, 0);
				closesocket(csock);
			}
		}
		printf("Envoi de donnees reussi \nVeuillez attendre 30sec pour que le bras se remette a sa position initiale (si vous n'avez pas attendu lancez le script './init.sh' avant une nouvelle manipulation\n");
	}
	else {
		printf("Les valeurs de l'azimut et de l'altitude de la planete sont mauvaises\n");
	}
	return 0;
}
