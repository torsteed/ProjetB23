#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <Windows.h>

#define hauteurPlateau 25
#define largeurPlateau 70

#define HAUT 72 
#define GAUCHE 75 
#define BAS 80		
#define DROITE 77

void color(int t, int f)
{
	HANDLE H = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(H, f * 16 + t);
}

void Gotoxy(int column, int row) {
	COORD c;
	c.X = column;
	c.Y = row;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
} 

struct position {
	int x;
	int y;
};

typedef struct position position;

struct serpent {
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
			if (carte[x][y] == '@') {
				color(2, 0);
				printf("%c", carte[x][y]);
			}
			else if (carte[x][y] == '#') {
				color(2, 2);
				printf("%c", carte[x][y]);
			}
			else if (carte[x][y] == 'O') {
				color(12, 0);
				printf("%c", carte[x][y]);
			}
			else {
				color(15, 0);
				printf("%c", carte[x][y]);
			}
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
void gameover() {

}
void queueDeplacement(char carte[largeurPlateau][hauteurPlateau], serpent* serpent) {
	for (int y = serpent->taille; y > 1; y--) {  //queue qui bouge
		serpent->queue[y].x = serpent->queue[y - 1].x;
		serpent->queue[y].y = serpent->queue[y - 1].y;
		carte[serpent->queue[y].x][serpent->queue[y].y] = '#';
	}
	carte[serpent->queue[serpent->taille - 1].x][serpent->queue[serpent->taille - 1].y] = ' ';
	refreshPlateau(carte);
	printf("%d %d\n", serpent->queue[0].x, serpent->queue[0].y);
	printf("%d %d", serpent->queue[1].x, serpent->queue[1].y);
	printf("%d %d", serpent->queue[4].x, serpent->queue[4].y);
}

void deplacement(char carte[largeurPlateau][hauteurPlateau], serpent* serpent) {
	while (true) {
		switch (_getch()) {
		case HAUT :
			serpent->queue[0].y--;
			carte[serpent->queue[0].x][serpent->queue[0].y] = '@';
			queueDeplacement(carte,&*serpent);
			break;

		case GAUCHE :
			serpent->queue[0].x--;
			carte[serpent->queue[0].x][serpent->queue[0].y] = '@';
			queueDeplacement(carte,&*serpent);
			break;

		case BAS :
			serpent->queue[0].y++;
			carte[serpent->queue[0].x][serpent->queue[0].y] = '@';
			queueDeplacement(carte,&*serpent);
			break;

		case DROITE :
			serpent->queue[0].x = serpent->queue[0].x + 1;
			carte[serpent->queue[0].x][serpent->queue[0].y] = '@';
			queueDeplacement(carte,&*serpent);
			break;
		}

	}
}


void premierSerpent(char carte[largeurPlateau][hauteurPlateau], serpent serpent) {
		serpent.queue[0].x = largeurPlateau / 2;
		serpent.queue[0].y = hauteurPlateau / 2;
		serpent.taille = 7;
		for (int i = 1;i < serpent.taille ;i++) {
			serpent.queue[i].x = serpent.queue[0].x;
			serpent.queue[i].y = serpent.queue[i-1].y + 1;
			carte[serpent.queue[i].x][serpent.queue[i].y] = '#';
		}
		carte[serpent.queue[0].x][serpent.queue[0].y] = '@';
		refreshPlateau(carte);
		deplacement(carte, &serpent);
}

void initialisation(char carte[largeurPlateau][hauteurPlateau],serpent serpent) {
	definePlateau(carte);
	generateFruit(carte);
	premierSerpent(carte,serpent);
}

int main(serpent serpent) {							
	char carte[largeurPlateau][hauteurPlateau];
	initialisation(carte,serpent);
	return 0;
}