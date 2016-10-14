/*
Copyleft: some rights reserved (CC), Jacopo Gobbi october 2011

Opera sottostante alla licenza Creative Commons "Attribuzione - Non commerciale - Condividi allo stesso modo 3.0 Italia (CC BY-NC-SA 3.0)".
Tu sei libero di:
1) Attribuzione — Devi attribuire la paternità dell'opera nei modi indicati dall'autore o da chi ti ha dato l'opera in licenza e in modo tale da non suggerire che essi avallino te o il modo in cui tu usi l'opera.
2) Non commerciale — Non puoi usare quest'opera per fini commerciali.
3) Condividi allo stesso modo — Se alteri o trasformi quest'opera, o se la usi per crearne un'altra, puoi distribuire l'opera risultante solo con una licenza identica o equivalente a questa.
Per ulteriori informazioni visitare la pagina web: http://creativecommons.org/licenses/by-nc-sa/3.0/it/deed.it
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "color.h"
#include "kbhit.c"

#define goToXY(x, y) printf("\033[%d;%dH", x, y)
#define SOPRA 65
#define SOTTO 66
#define DESTRA 67
#define SINISTRA 68
#define bomba '@'
#define maxtab 30
#define random(min, max) rand() % max + min
#define randomize srand((unsigned)time(NULL))
#define colora(colore) printf(colore)

unsigned short int ScriviN(unsigned short int, unsigned short int);
void printN(char);
void SetTermBackColor(char *);
void SetTermForeColor(char *);
void Difficolta(void);
void CreaPrato(void);
unsigned short int Gioca(void);
unsigned short int Controlla(unsigned short int, unsigned short int);
void AmpliaSpazio(unsigned short int, unsigned short int);


char matrice[maxtab][maxtab];
char matrice2[maxtab][maxtab];
char *stringa, stringa2[100];

unsigned short int Max, prob;
short int bombe;

int main() {
	randomize;
	do {
		system("clear");
		bombe = 0;
		colora(STANDARD);
		Difficolta();
		CreaPrato();
	} while(Gioca());
	system("clear");
	return 0;
}

void Difficolta() {
	unsigned short int dif;
	do {
		printf("Scegli la difficoltà (1-10), 11 per personalizzare:\n", maxtab);
		scanf("%hu", &dif);
	} while(dif > 11 || dif < 0);
	switch(dif) {
		case 1:
			Max = 15;
			prob = 10;
		break;
		case 2:
			Max = 20;
			prob = 10;
		break;
		case 3:
			Max = 22;
			prob = 12;
		break;
		case 4:
			Max = 24;
			prob = 14;
		break;
		case 5:
			Max = 25;
			prob = 16;
		break;
		case 6:
			Max = 26;
			prob = 18;
		break;
		case 7:
			Max = 27;
			prob = 21;
		break;
		case 8:
			Max = 28;
			prob = 22;
		break;
		case 9:
			Max = 30;
			prob = 25;
		break;
		case 10:
			Max = 30;
			prob = 30;
		break;
		case 11:
			do {
				printf("Scegli la dimensione del prato scrivendo il numero di righe e colonne (max: %d):\n", maxtab);
				scanf("%hu", &Max);
			} while(Max > maxtab || Max < 5);
			do {
				printf("Scrivi le probabilità (in percentuale) che ci sia una bomba in ogni casella:\n");
				scanf("%hu", &prob);
			} while(prob > 100 || prob < 0);
		break;
	}
}

void CreaPrato() {
	unsigned short int i, j;
	for(i = 0; i < Max; ++i)
		for(j = 0; j < Max; ++j) {
			if(((random(0, 100)) < prob) && (i > 1 && j > 1)) {
				matrice[i][j] = bomba;
				bombe++;
			}
			else
				matrice[i][j] = (48 + ScriviN(i, j));
			if(matrice[i][j] == '0')
				matrice[i][j] = ' ';
			matrice2[i][j] = '-';
		}
}

unsigned short Gioca() {
	char car;
	unsigned short int i, j, vinto = 0, perso = 0, x, y, ancora;
	x = 2; y = 2;
	while(!perso && !vinto) {
		printf("\n");
		system("clear");
		colora(STANDARD);
		goToXY(0, 0);
		for(i = 0; i < Max; ++i) {
			printf("\n|");
			for(j = 0; j < Max; ++j)
				printN(matrice2[i][j]);
			colora(STANDARD);
		}
		printf("\nMuoviti con le freccette e seleziona le bombe con la barra spaziatrice, controlla le caselle con INVIO(BOMBE RIMASTE: %hi)", bombe);
		goToXY(x, y);
		car = 'Z';
		while(car != ' ' && car != SOPRA && car != SOTTO && car != DESTRA && car != SINISTRA && car != '\n') {
			while(!kbhit());
			car = getchar();
		}
		switch(car) {
			case SOPRA:
				x = x-1;
			break;
			case SOTTO:
				x = x+1;
			break;
			case DESTRA:
				y = y+2;
			break;
			case SINISTRA:
				y = y-2;
			break;
			case ' ':
				if(matrice2[x-2][(y/2)-1] != '*') {
					matrice2[x-2][(y/2)-1] = '*';
					if(matrice[x-2][(y/2)-1] == bomba) bombe--;
				}
				else if(matrice2[x-2][(y/2)-1] == '*') {
					if(matrice[x-2][(y/2)-1] == '/')
						matrice2[x-2][(y/2)-1] = ' ';
					else
						matrice2[x-2][(y/2)-1] = '-';
					if(matrice[x-2][(y/2)-1] == bomba) bombe++;
				}

			break;
			case '\n':
				perso = Controlla(x, y);
			break;
		}
		if(bombe == 0) vinto = 1;
		if(x < 2) x = 2;
		if(y < 2) y = 2;
		if(x > (Max+1)) x = (Max+1);
		if((y/2) > (Max)) y = (Max*2);
	}
	system("clear");
	colora(STANDARD);
	for(i = 0; i < Max; ++i) {
		printf("\n|");
		for(j = 0; j < Max; ++j)
			printN(matrice[i][j]);
		colora(STANDARD);
	}
	if(vinto) printf("\nComplimenti!!!! HAI VINTO!");
	if(perso) printf("\nSpiacente!HAI PERSO!");
	printf("\nGiocare ancora? 1.Sì 0.No\n");
	scanf("%hu", &ancora);
	return ancora;
}

unsigned short Controlla(unsigned short righe, unsigned short colonne) {
	righe -= 2;
	colonne /= 2;
	colonne--;
	switch(matrice[righe][colonne]) {
		case bomba:
			return 1;
		break;
		case ' ':
			AmpliaSpazio(righe, colonne);
			return 0;
		break;
		case '/':
			return 0;
		break;
		default:
			matrice2[righe][colonne] = matrice[righe][colonne];
			return 0;
		break;
	}
}

void AmpliaSpazio(unsigned short righe, unsigned short colonne) {
	if((matrice[righe][colonne] != bomba) && (matrice[righe][colonne] != '/') && (matrice[righe][colonne] != '*')) {
		if(matrice[righe][colonne] == ' ') {
			matrice2[righe][colonne] = matrice[righe][colonne];
			matrice[righe][colonne] = '/';

			if((righe - 1) >= 0) {
				if((matrice[righe-1][colonne] != bomba) && (matrice[righe-1][colonne] != '/') && (matrice[righe-1][colonne] != '*')) {
					if(matrice[righe-1][colonne] == ' ')
						AmpliaSpazio((righe-1), colonne);
					else
						matrice2[righe-1][colonne] = matrice[righe-1][colonne];
				}
			}

			if((colonne - 1) >= 0) {
				if((matrice[righe][colonne-1] != bomba) && (matrice[righe][colonne-1] != '/') && (matrice[righe][colonne-1] != '*')) {
					if(matrice[righe][colonne-1] == ' ')
						AmpliaSpazio(righe, (colonne-1));
					else
						matrice2[righe][colonne-1] = matrice[righe][colonne-1];
				}
			}

			if(((colonne - 1) >= 0) && ((righe - 1) >= 0)) {
				if((matrice[righe-1][colonne-1] != bomba) && (matrice[righe-1][colonne-1] != '/') && (matrice[righe-1][colonne-1] != '*')) {
					if(matrice[righe-1][colonne-1] == ' ')
						AmpliaSpazio((righe-1), (colonne-1));
					else
						matrice2[righe-1][colonne-1] = matrice[righe-1][colonne-1];
				}
			}

			if((righe + 1) < Max) {
				if((matrice[righe+1][colonne] != bomba) && (matrice[righe+1][colonne] != '/') && (matrice[righe+1][colonne] != '*')) {
					if(matrice[righe+1][colonne] == ' ')
						AmpliaSpazio((righe+1), colonne);
					else
						matrice2[righe+1][colonne] = matrice[righe+1][colonne];
				}
			}

			if((colonne + 1) < Max) {
				if((matrice[righe][colonne+1] != bomba) && (matrice[righe][colonne+1] != '/') && (matrice[righe][colonne+1] != '*')) {
					if(matrice[righe][colonne+1] == ' ')
						AmpliaSpazio(righe, (colonne+1));
					else
						matrice2[righe][colonne+1] = matrice[righe][colonne+1];
				}
			}

			if(((colonne + 1) < Max) && ((righe + 1) < Max)) {
				if((matrice[righe+1][colonne+1] != bomba) && (matrice[righe+1][colonne+1] != '/') && (matrice[righe+1][colonne+1] != '*')) {
					if(matrice[righe+1][colonne+1] == ' ')
						AmpliaSpazio((righe+1), (colonne+1));
					else
						matrice2[righe+1][colonne+1] = matrice[righe+1][colonne+1];
				}
			}

			if(((colonne + 1) < Max) && ((righe - 1) >= 0)) {
				if((matrice[righe-1][colonne+1] != bomba) && (matrice[righe-1][colonne+1] != '/') && (matrice[righe-1][colonne+1] != '*')) {
					if(matrice[righe-1][colonne+1] == ' ')
						AmpliaSpazio((righe-1), (colonne+1));
					else
						matrice2[righe-1][colonne+1] = matrice[righe-1][colonne+1];
				}
			}

			if(((colonne - 1) >= 0) && ((righe + 1) < Max)) {
				if((matrice[righe+1][colonne-1] != bomba) && (matrice[righe+1][colonne-1] != '/') && (matrice[righe+1][colonne-1] != '*')) {
					if(matrice2[righe+1][colonne-1] == ' ')
						AmpliaSpazio((righe+1), (colonne-1));
					else
						matrice2[righe+1][colonne-1] = matrice[righe+1][colonne-1];
				}
			}
		}
	}
	return;
}

unsigned short ScriviN(unsigned short righe, unsigned short colonne) {
	unsigned short int n;
	n = 0;
	if((righe - 1) >= 0)
		if(matrice[righe-1][colonne] == bomba) n++;
	if((colonne - 1) >= 0)
		if(matrice[righe][colonne-1] == bomba) n++;
	if(((colonne - 1) >= 0) && ((righe - 1) >= 0))
		if(matrice[righe-1][colonne-1] == bomba) n++;

	if((righe + 1) < maxtab)
		if(matrice[righe+1][colonne] == bomba) n++;
	if((colonne + 1) < maxtab)
		if(matrice[righe][colonne+1] == bomba) n++;
	if(((colonne + 1) < maxtab) && ((righe + 1) < maxtab))
		if(matrice[righe+1][colonne+1] == bomba) n++;

	if(((colonne + 1) < maxtab) && ((righe - 1) >= 0))
		if(matrice[righe-1][colonne+1] == bomba) n++;
	if(((colonne - 1) >= 0) && ((righe + 1) < maxtab))
		if(matrice[righe+1][colonne-1] == bomba) n++;
	return n;
}

void printN(char point) {
/* STANDARD, BIANCO, ROSSO, VERDE, ARANCIO, BLU, VIOLA, GRIGIO, ROSSOCHIARO, VERDECHIARO, GIALLO, CELESTE, ROSA, AZZURRO
	SOTTOLINEATO, LAMPEGGIANTE, NEROSUGRIGIO, LAMPCOLORE, SOTTCOLORE, RIGA(ROSSA-VERDE-ARANCIO-BLU-VIOLA-AZZURRO) */
	switch(point) {
		case '1':
			colora(SOTTOLINEATO);
			colora(BLU);
		break;
		case '2':
			colora(SOTTOLINEATO);
			colora(VERDE);
		break;
		case '3':
			colora(SOTTOLINEATO);
			colora(ARANCIO);
		break;
		case '4':
			colora(SOTTOLINEATO);
			colora(VIOLA);
		break;
		case '5':
			colora(SOTTOLINEATO);
			colora(AZZURRO);
		break;
		case '6':
			colora(SOTTOLINEATO);
			colora(ROSA);
		break;
		case '7':
			colora(SOTTOLINEATO);
			colora(VERDECHIARO);
		break;
		case '8':
			colora(SOTTOLINEATO);
			colora(ROSSO);
		break;
		case bomba:
			colora(STANDARD);
		break;
		case '/':
			point = ' ';
			colora(CELESTE);
		break;
		case '-':
			colora(AZZURRO);
		break;
		case '*':
			colora(SOTTOLINEATO);
			colora(GRIGIO);
		break;
		default:
			colora(STANDARD);
		break;
	}
	printf("%c", point);
	colora(STANDARD);
	printf("|");
}
