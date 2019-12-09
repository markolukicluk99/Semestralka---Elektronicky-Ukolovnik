
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <iostream>
#include <Windows.h>
#include "elektronickyukolovnik.h"
#include <stdio.h>
#include <conio.h>


/*     NAVIGACE       */

void navigace() {

	system("cls");
	int pozice = 1;
	int zmacknuteTlacitko = 0;

	while (zmacknuteTlacitko != 13) {

		system("cls");
		klavesTady(1, pozice); printf("  AKTUALNI DEN\n");
		klavesTady(2, pozice); printf("  MINULE\n");
		klavesTady(3, pozice); printf("  BUDOUCI\n");
		klavesTady(4, pozice); printf("  PRIDEJ UKOL\n");
		klavesTady(5, pozice); printf("  ZOBRAZIT SEZNAM\n");

		zmacknuteTlacitko = _getch();

		if (zmacknuteTlacitko == 80 && pozice != 5) {
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

		printf("Jeste se zpracovava. Druha moznost.");
		break;

	case 3:

		printf("Jeste se zpracovava. Treti moznost.");
		break;

	case 4:

		pridejUkol();
		break;

	
	case 5:

		seznamUkolu();
		break;
	}
	

}

// Sipka

void klavesTady(int aktualniPozice, int sipkaPozice) {

	if (aktualniPozice == sipkaPozice) { //Pokud je nas vyber na tom
		printf("----->> - ");
	}
	else {
		printf("          "); //Pokud neni
	}

}

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

	fprintf(fp, "%s \n %s \n", nazev_ukolu, obsah_ukolu);
	fclose(fp);

}

void seznamUkolu() {

	FILE *fp;

	char seznam[500], c;

	fp = fopen("seznam.txt","r");

	if (fp == NULL) {
		printf("Seznam je prazdny.");
	}
	//zkust vratit to do hlavni navigace
	c = fgetc(fp);
	while (c != EOF)
	{
		printf("%c", c);
		c = fgetc(fp);
	}
	

}

void aktualniUkol() {

	printf("AKTUALNI - Udelejte si palacinky.");
	_getch();
}