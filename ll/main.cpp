#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <Windows.h>

#define hauteurPlateau 25
#define largeurPlateau 100

#define HAUT 72 
#define GAUCHE 75 
#define BAS 80		
#define DROITE 77

struct position {
	int x;
	int y;
};

typedef struct position position;

struct serpent {
	position tete;
	position queue[99];
	int taille;
};

typedef struct serpent serpent;

void definePlateau(char carte[largeurPlateau][hauteurPlateau]) {
	for (int y = 0; y < hauteurPlateau; y++) {
		for (int x = 0; x < largeurPlateau; x++) {
			if (y == 0 || x == 0 || y == hauteurPlateau - 1 || x == largeurPlateau - 1) {
				carte[x][y] = 219;
			}
			else {
				carte[x][y] = 32;
			}
		}
	}
}

void refreshPlateau(char carte[largeurPlateau][hauteurPlateau]) {
	system("cls");
	for (int y = 0; y < hauteurPlateau; y++) {
		for (int x = 0; x < largeurPlateau; x++) {
			printf("%c", carte[x][y]);
		}
		printf("\n");
	}
}

int nbrealeatoire(int a, int b) {
	srand(time(NULL));
	return rand() % (b - a) + a;
}


void generateFruit(char carte[largeurPlateau][hauteurPlateau]) {
	int x = nbrealeatoire(1, largeurPlateau - 1);
	int y = nbrealeatoire(1, hauteurPlateau - 1);
	carte[x][y] = 'O';
}

void premierSerpent(char carte[largeurPlateau][hauteurPlateau], serpent serpent) {
		serpent.tete.x = largeurPlateau / 2;
		serpent.tete.y = hauteurPlateau / 2;
		serpent.taille = 3;
		for (int i = 0;i < 3 ;i++) {
			serpent.queue[i].x = serpent.tete.x;
			serpent.queue[i].y = serpent.queue[i-1].y + 1;
			carte[serpent.queue[i].x][serpent.queue[i].y] = '#';
		}
		carte[serpent.tete.x][serpent.tete.y] = '@';
	
}

void initialisation(char carte[largeurPlateau][hauteurPlateau],serpent serpent) {
	definePlateau(carte);
	generateFruit(carte);
	premierSerpent(carte,serpent);
	refreshPlateau(carte);
}

void deplacement(char carte[largeurPlateau][hauteurPlateau], serpent serpent, int* pointeurkey) {
	printf("%d", *pointeurkey );

}

void touche(char carte[largeurPlateau][hauteurPlateau], serpent serpent) {
	int key;
	while (true) {
		switch (_getch()) {

			case DROITE:
				key = 4;
				deplacement(carte, serpent, &key);
				break;

			case HAUT:
				key = 1;
				deplacement(carte, serpent, &key);
				break;

			case GAUCHE:
				key = 2;
				deplacement(carte, serpent, &key);
				break;

			case BAS:
				key = 3;
				deplacement(carte, serpent, &key);
				break;

		}
	}
}

int main(serpent serpent) {
	char carte[largeurPlateau][hauteurPlateau];
	initialisation(carte,serpent);
	touche(carte,serpent);
	return 0;
}