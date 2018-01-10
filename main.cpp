#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <Windows.h>

#define hauteurPlateau 25
#define largeurPlateau 100

#define HAUT 72
#define BAS 80
#define GAUCHE 75
#define DROITE 77 

struct position {
	int x;
	int y;
};

typedef struct position position;

struct serpent {
	position tete;
	position queue;
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
	printf("%d , %d\n", x, y);
	refreshPlateau(carte);
}

void init(char carte[largeurPlateau][hauteurPlateau], serpent serpent) {
	serpent.tete.x = largeurPlateau / 2;
	serpent.tete.y = hauteurPlateau / 2;
	serpent.queue.x = serpent.tete.x;
	serpent.queue.y = serpent.tete.y - 3;
	carte[serpent.tete.x][serpent.tete.y] = '@';
	carte[serpent.queue.x][serpent.queue.y] = '#';
}

void touche() {
	if (true/*_kbhit()*/) //If player clicks something

	{
		char key;
		key = _getch(); //Now this click is key
		switch (key)
		{
		case 'd':
		{
			printf("d\n");
			break;
		}

		case 'w':
		{
			printf("w\n");
			break;
		}

		case 'a':
		{
			printf("a\n");
			break;
		}

		case 's':
		{
			printf("s\n");
			break;
		}
		}
	}
}

void menu() {
	int choix;
	printf("Bienvenue dans le snake\n");
	printf("1. Jouer\n");
	printf("2. Quitter\n");
	scanf_s("%d", &choix);
	switch (choix) {
	case 1:
		printf("jeu\n");
		break;
	case 2:
		printf("fin\n");
		break;
	default:
		printf("ok\n");
		break;
	}
}

int main() {
	char carte[largeurPlateau][hauteurPlateau];
	definePlateau(carte);
	refreshPlateau(carte);
	generateFruit(carte);
	menu();
	touche();
	return 0;
}