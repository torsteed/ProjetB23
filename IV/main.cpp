#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <Windows.h>

#define hauteurPlateau 20
#define largeurPlateau 50

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

void gameover(char carte[largeurPlateau][hauteurPlateau], serpent serpent); // menu gameover

void definePlateau(char carte[largeurPlateau][hauteurPlateau]) {		//affichage plateau manuel
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

int Timer() {
	int Time;		//timer 
	clock_t t1;
	t1 = clock()/ CLOCKS_PER_SEC;
	t1;
	return  t1;
}

void refreshPlateau(char carte[largeurPlateau][hauteurPlateau],serpent serpent, int temp) {
	system("cls");
	int time =90 -(Timer() - temp);
	if (time <= 0) {	//temps à 0 = mort
		gameover(carte, serpent);
	}
	for (int y = 0; y < hauteurPlateau; y++) {
		for (int x = 0; x < largeurPlateau; x++) {		//coloriage et affichage
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
	Gotoxy(52,1);		//affichage temp et score
	printf("Score: %d", (serpent.taille)-7);
	Gotoxy(52, 3);
	printf("Temps restant: %d sec",time);
}

int nbrealeatoire(int a, int b) {
	srand(time(NULL));
	return rand() % (b - a) + a;
}

void generateFruit(char carte[largeurPlateau][hauteurPlateau],position* fruit, serpent serpent) {
	generate:
	fruit->x = nbrealeatoire(1, largeurPlateau - 1);
	fruit->y = nbrealeatoire(1, hauteurPlateau - 1);
	for (int i = 0; i < serpent.taille; i++) { // on vérifie que le fruit n'apparaît pas sur le serpent
		if (fruit->x == serpent.queue[i].x && fruit->y == serpent.queue[i].y) {
			goto generate;
		}
	}
	carte[fruit->x][fruit->y] = 'O';
}

void queueDeplacement(char carte[largeurPlateau][hauteurPlateau], serpent* serpent,int direction) {
	
	for (int y = serpent->taille-1; y >= 1; y--) {  //queue qui bouge
		serpent->queue[y].x = serpent->queue[y - 1].x;
		serpent->queue[y].y = serpent->queue[y - 1].y;
		carte[serpent->queue[y].x][serpent->queue[y].y] = '#';
	}
	switch (direction)
	{
	case 1 :
		serpent->queue[0].y--;
		if (serpent->queue[0].y == 0) {
			gameover(carte, *serpent);
		}
		break;
	case 2 :
		serpent->queue[0].x--;
		if (serpent->queue[0].x == 0) {
			gameover(carte, *serpent);
		}
		break;
	case 3 :
		serpent->queue[0].y++;
		if (serpent->queue[0].y == hauteurPlateau-1) {
			gameover(carte, *serpent);
		}
		break;
	case 4 :
		serpent->queue[0].x++;
		if (serpent->queue[0].x == largeurPlateau-1) {
			gameover(carte, *serpent);
		}
		break;
	}
	carte[serpent->queue[0].x][serpent->queue[0].y] = '@';
	carte[serpent->queue[serpent->taille - 1].x][serpent->queue[serpent->taille - 1].y] = ' ';
}

void deplacement(char carte[largeurPlateau][hauteurPlateau], serpent* serpent,position* fruit,int temp) {
	int direction = 0;
	while (true) {
		switch (_getch()) {
		case HAUT:
			if (direction != 3) {
				direction = 1;
				queueDeplacement(carte, &*serpent, direction);
			}
			break;

		case GAUCHE:
			if (direction != 4) {
				direction = 2;
				queueDeplacement(carte, &*serpent, direction);
			}
			break;

		case BAS:
			if (direction != 1) {
				direction = 3;
				queueDeplacement(carte, &*serpent, direction);
			}
			break;

		case DROITE:
			if (direction != 2) {
				direction = 4;
				queueDeplacement(carte, &*serpent, direction);
			}
			break;
		}
		
		//collision
		if (serpent->queue[0].x == fruit->x && serpent->queue[0].y == fruit->y) {
			serpent->taille++;
			generateFruit(carte, &*fruit, *serpent);
		}
		for (int i = 1; i < serpent->taille-1; i++) {
			if (serpent->queue[0].x == serpent->queue[i].x && serpent->queue[0].y == serpent->queue[i].y) {
				gameover(carte, *serpent);
				break;
			}
		}
		refreshPlateau(carte, *serpent,temp);
	}
}

void deplacementInter(char carte[largeurPlateau][hauteurPlateau], serpent* serpent, position* fruit,int temp) {
	int direction = 0;
	while (true) {
		switch (_getch()) {
		case HAUT:
			if (direction != 3) {
				direction = 1;
				queueDeplacement(carte, &*serpent, direction);
			}
			break;

		case GAUCHE:
			if (direction != 4) {
				direction = 2;
				queueDeplacement(carte, &*serpent, direction);
			}
			break;

		case BAS:
			if (direction != 1) {
				direction = 3;
				queueDeplacement(carte, &*serpent, direction);
			}
			break;

		case DROITE:
			if (direction != 2) {
				direction = 4;
				queueDeplacement(carte, &*serpent, direction);
			}
			break;
		}

		//collision
		if (serpent->queue[0].x == fruit->x && serpent->queue[0].y == fruit->y) {
			serpent->taille++;
			generateFruit(carte, &*fruit, *serpent);
		}
		for (int i = 1; i < serpent->taille - 1; i++) {
			if (serpent->queue[0].x == serpent->queue[i].x && serpent->queue[0].y == serpent->queue[i].y) {
				gameover(carte, *serpent);
				break;
			}
		}
		refreshPlateau(carte, *serpent,temp);
	}
}

void premierSerpent(char carte[largeurPlateau][hauteurPlateau], serpent serpent) {
	position fruit;
	int temp = Timer();
	generateFruit(carte,&fruit, serpent);
		serpent.queue[0].x = largeurPlateau / 2;
		serpent.queue[0].y = hauteurPlateau / 2;
		serpent.taille = 7;
		for (int i = 1;i < serpent.taille-1 ;i++) {
			serpent.queue[i].x = serpent.queue[0].x;
			serpent.queue[i].y = serpent.queue[i-1].y + 1;
			carte[serpent.queue[i].x][serpent.queue[i].y] = '#';
		}
		carte[serpent.queue[0].x][serpent.queue[0].y] = '@';
		refreshPlateau(carte,serpent,temp);
		deplacement(carte, &serpent,&fruit,temp);

}

void premierSerpentInter(char carte[largeurPlateau][hauteurPlateau], serpent serpent) {
	position fruit;
	int temp = Timer();
	generateFruit(carte, &fruit, serpent);
	serpent.queue[0].x = largeurPlateau / 2;
	serpent.queue[0].y = hauteurPlateau / 2;
	serpent.taille = 7;
	for (int i = 1; i < serpent.taille - 1; i++) {
		serpent.queue[i].x = serpent.queue[0].x;
		serpent.queue[i].y = serpent.queue[i - 1].y + 1;
		carte[serpent.queue[i].x][serpent.queue[i].y] = '#';
	}
	carte[serpent.queue[0].x][serpent.queue[0].y] = '@';
	refreshPlateau(carte, serpent,temp);
	deplacementInter(carte, &serpent, &fruit,temp);

}

void initialisation(char carte[largeurPlateau][hauteurPlateau],serpent serpent) {
	definePlateau(carte);
	premierSerpent(carte,serpent);
}


void initialisationinter(char carte[largeurPlateau][hauteurPlateau], serpent serpent) {
	definePlateau(carte);
	premierSerpentInter(carte, serpent);
}

int menu(const char* ch[], int taille, int x, int y) { // fonction pour créer un menu et renvoie le numéro du choix
	int i, curs = 0;
	Gotoxy(x, y); // on place les éléments du menu
	int y2 = y;
	for (i = 0; i < taille; i++) { // pour chaque élément on place les choix les uns en dessous des autres
		printf("  %s\n", ch[i]);
		y2++;
		Gotoxy(x, y2);
	}
	Gotoxy(x, y);
	while (1) // on vérifie les touches pour faire déplacer le curseur
	{
		int touche = _getch();
		if (touche == 0x50 && curs < taille - 1)
			curs++;
		if (touche == 0x48 && curs > 0)
			curs--;
		if (touche == 0x0D) // si touche entrée : retour du numéro du choix
			return curs + 1;
		int y3 = y;
		Gotoxy(x, y);
		for (i = 0; i < taille; i++) { // on place le curseur
			printf("%c\n", (i == curs) ? '>' : ' ');
			y3++;
			Gotoxy(x, y3);
		}
	}
	return 0;
}

void accueil(char carte[largeurPlateau][hauteurPlateau], serpent serpent) { // affichage du menu accueil
	Gotoxy(5, 10);
	printf("Bienvenue dans le Snake\n\n");
	printf("--------------------------------------------------------------\n\n");
	Gotoxy(5, 14);
	printf("Choisissez une option :\n\n");
	const char* tabchoix[] = { "Jouer (deplacement manuel)","Jouer (niveau intermediaire)","Quitter" }; // définition du tableau contenant les choix
	int c = menu(tabchoix, 3, 5, 16); // affichage menu en (5,16) et retour choix
	switch (c) { // selon le choix
	case 1:
		initialisation(carte, serpent); // on lance le jeu si choix 1
		break;
	case 2: // on lance le jeu intermediaire si choix 2
		initialisationinter(carte, serpent);
		break;
	case 3: // on quitte le jeu si choix 3
		system("cls");
		exit(1);
		break;
	}
}

void gameover(char carte[largeurPlateau][hauteurPlateau], serpent serpent) { // menu gameover
	//_getch();
	system("cls");
	Gotoxy(5, 10);
	printf("Vous avez perdu :(");
	Gotoxy(5, 12);
	printf("Votre score est de %d", (serpent.taille) - 7);
	Gotoxy(5, 14);
	printf("Voulez-vous rejouer?");
	const char* tabchoix[] = { "Rejouer","Menu principal","Quitter" }; // choix menu
	int c = menu(tabchoix, 3, 5, 16); // retour choix menu
	switch (c) {
	case 1:
		initialisation(carte, serpent); // rejouer
		break;
	case 2:
		system("cls");
		accueil(carte, serpent); // retour accueil
		break;
	case 3: // quitter
		system("cls");
		exit(1);
		break;
	}
}


int main(serpent serpent) {
	char carte[largeurPlateau][hauteurPlateau];
	accueil(carte, serpent); // on lance l'accueil
	return 0;
}