#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <iostream>
#include <Windows.h>
#include "elektronickyukolovnik.h"
#include <stdio.h>
#include <conio.h>
#include <time.h>


/*     NAVIGACE       */

void navigace() {

	system("cls");
	int pozice = 1;
	int zmacknuteTlacitko = 0;

	while (zmacknuteTlacitko != 13) {

		system("cls");
		klavesTady(1, pozice); printf("  AKTUALNI UKOL\n");
		klavesTady(2, pozice); printf("  MINULY\n");
		klavesTady(3, pozice); printf("  BUDOUCI\n");
		klavesTady(4, pozice); printf("  PRIDEJ UKOL\n");
		klavesTady(5, pozice); printf("  ZOBRAZIT SEZNAM\n");
		klavesTady(6, pozice); printf("  SMAZAT SEZNAM\n");
		klavesTady(7, pozice); printf("  UKONCIT PROGRAM\n");

		zmacknuteTlacitko = _getch();

		if (zmacknuteTlacitko == 80 && pozice != 7) {
			pozice++;
		}
		else if (zmacknuteTlacitko == 72 && pozice != 1) {
			pozice--;
		}
		else {
			pozice = pozice;
		}

	}

	switch (pozice) {
	case 1:
		aktualniUkol();
	break;
	case 2:
		printf("Vas minuly ukol: \n\n");
		minulyUkol();
		break;
	case 3:
		printf("Vas budouci ukol: \n\n");
		minulyUkol();
		break;
	case 4:
		pridejUkol();
		break;
	case 5:
		seznamUkolu();
		break;
	case 6:
		smazatSeznam(); //Jsou moznosti pro mazani jeden po druhem
		break;
	case 7:
		ukoncitProgram();
		break;
	}
	

}

void klavesTady(int aktualniPozice, int sipkaPozice) { //Sipka v navigaci

	if (aktualniPozice == sipkaPozice) { //Pokud je nas vyber na tom
		printf("------> ");
	}
	else {
		printf("          "); //Pokud neni
	}

}

/*   KONEC NAVIGACE   */


/*    MANIPULACE S UKOLY   */

// PRIDAT UKOL
void pridejUkol() { 

	FILE* fp;

	char nazev_ukolu[25];

	char obsah_ukolu[500];

	if((fp = fopen("seznam.txt", "a")) == NULL)
		return;

	printf("Napiste nazev ukolu (Pouzivejte jenom slovesa!) .\n");
	scanf_s("%[^\n]%*c", &nazev_ukolu, 25);

	printf("Napiste ukol (Pouzivejte jenom slovesa!) .\n");
	scanf_s("%[^\n]%*c", &obsah_ukolu, 500);

	//VLOZENI DO DATABAZE
	fprintf(fp, "  NAZEV: %s   ||   OBSAH: %s   || \n", nazev_ukolu, obsah_ukolu);
	aktualniCas();
	fclose(fp);

	_getch();
	navigace();
}

// CAS VLOZENI UKOLU
void aktualniCas() {

	FILE* fp;
	if ((fp = fopen("seznam.txt", "a")) == NULL)
		return;

	time_t t = time(NULL);
	struct tm tm = *localtime(&t);
	printf("Cas vlozeni: %d-%d-%d %d:%d:%d\n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);

	//VLOZENI DO DATABAZE
	fprintf(fp, "||  Cas vlozeni: %d-%d-%d %d:%d:%d  ||", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
	fclose(fp);
}

// ZOBRAZENI VSECH UKOLU
void seznamUkolu() { 

	FILE *fp;

	char seznam[500], c;

	fp = fopen("seznam.txt","r");

	if (fp == NULL) {
		printf("Seznam je prazdny.");

		_getch();

		navigace();
	}
	
	c = fgetc(fp);
	while (c != EOF)
	{
		printf("%c", c);
		c = fgetc(fp);
	}

	_getch();
	navigace();
}


// ZOBRAZENI AKTUALNIHO UKOLU
void aktualniUkol() { 

	FILE* fp = fopen("seznam.txt", "r");


	if (fp == NULL)
	{
		printf("Seznam je prazdny!\n");
	}
	else {
		printf("Vas aktualni ukol je: \n");
		FILE* fp;

		char tmp[1024];

		fp = fopen("seznam.txt", "r");

		while (!feof(fp))
			fgets(tmp, 1024, fp);

		printf("%s \n \n", tmp);

	}

	char odpoved;
	printf("Chcete nastavit prioritu tohoto ukolu?\n \n");
	printf("Stisknete ENTER pro ANO.\n");
	printf("Napiste N pro NE.\n");
	odpoved = fgetc(stdin);

	if (odpoved == 0x0A) {
		priorita();
	}
	else {
		navigace();
	}
	_getch();

}

//NASTAVENI PRIORITY
void priorita() {

	system("cls");

	int pozice = 1;
	int zmacknuteTlacitko = 0;

	while (zmacknuteTlacitko != 13) {

		system("cls");
		klavesTady(1, pozice); printf("  Oznacit jako hotov.\n");
		klavesTady(2, pozice); printf("  Oznacit jako neudelan.\n");

		zmacknuteTlacitko = _getch();

		if (zmacknuteTlacitko == 80 && pozice != 2) {
			pozice++;
		}
		else if (zmacknuteTlacitko == 72 && pozice != 1) {
			pozice--;
		}
		else {
			pozice = pozice;
		}

	}

	switch (pozice) {

	case 1:

		printf("Vas aktualni ukol jste oznacil jako hotov: \n");
		FILE* fp;

		char tmp[1024];

		fp = fopen("seznam.txt", "r");

		while (!feof(fp))
			fgets(tmp, 1024, fp);
		cervenaBarva();
		printf("%s", tmp);
		break;

	case 2:
		resetBarev();
	}
	
}

/* BARVY PRO OZNACENI UKONCENI UKOLU */
void cervenaBarva() {
	printf("\033[1;31m");
}

void resetBarev() {
	printf("\033[0m");
}

// ZOBRAZENI MINULEHO UKOLU
void minulyUkol() { 

	FILE* fp;

	char tmp[1024];

	fp = fopen("seznam.txt", "r");

	while (!feof(fp))
		fgets(tmp, 1024, fp);

	printf("%s", tmp);

	_getch();
	navigace();
}

//Smazat vsechno v souboru seznam.txt
void smazatSeznam() {

	FILE* fp;

	fp = fopen("seznam.txt", "r");

	char odpoved;
	printf("Chcete smazat cely seznam?\n");
	printf("Stisknete ENTER pro ANO\n");
	printf("Stisknete N pro NE\n");

	odpoved = fgetc(stdin);

	if ( odpoved == 0x0A) {

		fp = freopen("seznam.txt", "w", stdout);

		fclose(fp);
		navigace();
	}
	else {
		navigace();
	}

}

/*KONEC*/
void ukoncitProgram() {

	char odpoved;
	printf("Chcete ukoncit program?\n \n");
	printf("Stisknete ENTER pro ANO.\n");
	printf("Napiste N pro NE.\n");
	odpoved = fgetc(stdin);

	if (odpoved == 0x0A) {
		exit(0);
	}
	else {
		navigace();
	}

}