#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <Windows.h>

<<<<<<< HEAD
#define hauteurPlateau 25
#define largeurPlateau 70
=======
// définition de la taille du plateau
#define hauteurPlateau 20
#define largeurPlateau 50
>>>>>>> 8ef9ba2bae7008c1689bfa9d8576b02e376aa1c3

// définition des codes ASCII des flèches directionnelles
#define HAUT 72 
#define GAUCHE 75 
#define BAS 80		
#define DROITE 77

<<<<<<< HEAD
void color(int t, int f)
{
=======
void color(int t, int f) { // procédure de coloration des caractères
>>>>>>> 8ef9ba2bae7008c1689bfa9d8576b02e376aa1c3
	HANDLE H = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(H, f * 16 + t);
}

<<<<<<< HEAD
void Gotoxy(int column, int row) {
=======
void Gotoxy(int column, int row) { // procédure pour déplacer le curseur selon des coordonnées
>>>>>>> 8ef9ba2bae7008c1689bfa9d8576b02e376aa1c3
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
<<<<<<< HEAD
	position queue[99];
=======
	position queue[99]; // tableau des coordonnées de la queue
>>>>>>> 8ef9ba2bae7008c1689bfa9d8576b02e376aa1c3
	int taille;
};

typedef struct serpent serpent;

void definePlateau(char carte[largeurPlateau][hauteurPlateau]) { // procédure d'initialisation du plateau
	for (int y = 0; y < hauteurPlateau; y++) {
		for (int x = 0; x < largeurPlateau; x++) {
			if (y == 0 || x == 0 || y == hauteurPlateau - 1 || x == largeurPlateau - 1) {
				carte[x][y] = 219; // placement des murs
			}
			else {
				carte[x][y] = 32; // placement d'un caractère vide
			}
		}
	}
}

void refreshPlateau(char carte[largeurPlateau][hauteurPlateau]) { // procédure de rafraichissement plateau
	system("cls"); // on efface l'écran
	for (int y = 0; y < hauteurPlateau; y++) {
		for (int x = 0; x < largeurPlateau; x++) {
<<<<<<< HEAD
			if (carte[x][y] == '@') {
				color(2, 0);
				printf("%c", carte[x][y]);
			}
			else if (carte[x][y] == '#') {
				color(2, 2);
				printf("%c", carte[x][y]);
			}
			else if (carte[x][y] == 'O') {
=======
			if (carte[x][y] == '@') { // si tête du serpent : couleur verte
				color(2, 0);
				printf("%c", carte[x][y]);
			}
			else if (carte[x][y] == '#') { // si ??? : couleur
				color(2, 2);
				printf("%c", carte[x][y]);
			}
			else if (carte[x][y] == 'O') { // si fruit : rouge
>>>>>>> 8ef9ba2bae7008c1689bfa9d8576b02e376aa1c3
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

int nbrealeatoire(int a, int b) { // fonction de génération de nombres aléatoire
	srand(time(NULL));
	return rand() % (b - a) + a;
}

void generateFruit(char carte[largeurPlateau][hauteurPlateau]) { // génération de coordonnées de fruit
	int x = nbrealeatoire(1, largeurPlateau - 1);
	int y = nbrealeatoire(1, hauteurPlateau - 1);
	carte[x][y] = 'O'; // on envoie les coordonnées du fruit dans la carte
}
void gameover() {

<<<<<<< HEAD
}
void queueDeplacement(char carte[largeurPlateau][hauteurPlateau], serpent* serpent) {
	for (int y = serpent->taille; y > 1; y--) {  //queue qui bouge
=======
void queueDeplacement(char carte[largeurPlateau][hauteurPlateau], serpent* serpent) { // fonction de déplacement de la queue
	carte[serpent->queue[serpent->taille].x][serpent->queue[serpent->taille].y] = ' ';
	for (int y = serpent->taille; y > 0; y--) {  //queue qui bouge
>>>>>>> 8ef9ba2bae7008c1689bfa9d8576b02e376aa1c3
		serpent->queue[y].x = serpent->queue[y - 1].x;
		serpent->queue[y].y = serpent->queue[y - 1].y;
		carte[serpent->queue[y].x][serpent->queue[y].y] = '#';
	}
<<<<<<< HEAD
	carte[serpent->queue[serpent->taille - 1].x][serpent->queue[serpent->taille - 1].y] = ' ';
=======
	carte[serpent->queue[0].x][serpent->queue[0].y] = '@';
>>>>>>> 8ef9ba2bae7008c1689bfa9d8576b02e376aa1c3
	refreshPlateau(carte);
	printf("%d %d\n", serpent->queue[0].x, serpent->queue[0].y);
	printf("%d %d", serpent->queue[1].x, serpent->queue[1].y);
	printf("%d %d", serpent->queue[4].x, serpent->queue[4].y);
}

<<<<<<< HEAD
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

=======
void deplacement(char carte[largeurPlateau][hauteurPlateau], serpent* serpent) { // fonction récupérant les touches pour déplacement
	while (true) {
		switch (_getch()) { // on récupère la touche appuyée
		case HAUT: // si flèche haut
			serpent->queue[0].y--; // on modifie les coordonnées de la queue
			queueDeplacement(carte, &*serpent); // on fait déplacer la queue
			break;

		case GAUCHE: // si flèche gauche
			serpent->queue[0].x--;
			queueDeplacement(carte, &*serpent);
			break;

		case BAS: // si flèche bas
			serpent->queue[0].y++;
			queueDeplacement(carte, &*serpent);
			break;

		case DROITE: // si flèche droite
			serpent->queue[0].x = serpent->queue[0].x + 1;
			queueDeplacement(carte, &*serpent);
			break;
		}

	}
}

void premierSerpent(char carte[largeurPlateau][hauteurPlateau], serpent serpent) { // initialisation serpent
	serpent.queue[0].x = largeurPlateau / 2; // on définit arbitrairement les coordonnées du serpent de base
	serpent.queue[0].y = hauteurPlateau / 2;
	serpent.taille = 7; // on définit une taille pour le serpent
	for (int i = 1; i < serpent.taille; i++) { // construction du serpent sur la carte
		serpent.queue[i].x = serpent.queue[0].x;
		serpent.queue[i].y = serpent.queue[i - 1].y + 1;
		carte[serpent.queue[i].x][serpent.queue[i].y] = '#';
	}
	carte[serpent.queue[0].x][serpent.queue[0].y] = '@'; // tête du serpent
	refreshPlateau(carte); // on rafraichit le plateau pour faire afficher le serpent
	deplacement(carte, &serpent); // on lance la fonction qui gère le déplacement
}

void initialisation(char carte[largeurPlateau][hauteurPlateau], serpent serpent) { // on initialise le jeu
	definePlateau(carte); // initialisation tableau
	generateFruit(carte); // génération fruit
	premierSerpent(carte, serpent); // construction du premier serpent (comprend le rafraichissement écran)
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
>>>>>>> 8ef9ba2bae7008c1689bfa9d8576b02e376aa1c3
	}
}

<<<<<<< HEAD

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
=======
void accueil(char carte[largeurPlateau][hauteurPlateau], serpent serpent) { // affichage du menu accueil
	Gotoxy(5, 10);
	printf("Bienvenue dans le Snake\n\n");
	printf("--------------------------------------------------------------\n\n");
	Gotoxy(5, 14);
	printf("Choisissez une option :\n\n");
	const char* tabchoix[] = {"Jouer (deplacement manuel)","Quitter"}; // définition du tableau contenant les choix
	int c = menu(tabchoix, 2, 5, 16); // affichage menu en (5,16) et retour choix
	switch (c) { // selon le choix
	case 1:
		initialisation(carte, serpent); // on lance le jeu si choix 1
		break;
	case 2: // on quitte le jeu si choix 2
		system("cls");
		exit(1);
		break;
	}
}

void gameover(char carte[largeurPlateau][hauteurPlateau], serpent serpent) { // menu gameover
	_getch();
	system("cls");
	Gotoxy(5, 10);
	printf("Vous avez perdu :(");
	Gotoxy(5, 12);
	printf("Voulez-vous rejouer?");
	const char* tabchoix[] = { "Rejouer","Menu principal","Quitter" }; // choix menu
	int c = menu(tabchoix, 3, 5, 14); // retour choix menu
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
	char carte[largeurPlateau][hauteurPlateau]; // on définit le tableau du plateau
	accueil(carte, serpent); // on lance l'accueil
>>>>>>> 8ef9ba2bae7008c1689bfa9d8576b02e376aa1c3
	return 0;
}