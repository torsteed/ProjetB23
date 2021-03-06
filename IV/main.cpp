#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <Windows.h>

// définition taille plateau
#define hauteurPlateau 20
#define largeurPlateau 50

// définition code ascii des touches du clavier
#define HAUT 72 
#define GAUCHE 75 
#define BAS 80
#define DROITE 77
#define ENTREE 13
#define ECHAP 27  

// procédure permettant de colorer le texte
void color(int t, int f)
{
	HANDLE H = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(H, f * 16 + t);
}

// procédure permettant de placer le curseur à des coordonnées entrées en paramètre
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
	position queue[30]; // tableau de structures contenant les positions des élements de la queue
	int taille; // taille de la queue
};

typedef struct serpent serpent;

// on définit certains prototypes pour faciliter leur appel
void gameover(char carte[largeurPlateau][hauteurPlateau], serpent serpent, int* typejeu,int haut); // menu gameover
void premierSerpentInter(char carte[largeurPlateau][hauteurPlateau], serpent serpent,int larg,int haut, int* typejeu);
void accueil(char carte[largeurPlateau][hauteurPlateau], serpent serpent); // affichage du menu accueil
void printregles(char carte[largeurPlateau][hauteurPlateau], serpent serpent); // affichage des règles

void definePlateau(char carte[largeurPlateau][hauteurPlateau],int larg,int haut) {		// définition du plateau
	system("cls"); // on efface la console
	for (int y = 0; y < hauteurPlateau-haut; y++) {
		for (int x = 0; x < largeurPlateau-larg; x++) { // taille du tableau = taille max - hauteur
			if (y == 0 || x == 0 || y == (hauteurPlateau-haut) - 1 || x == (largeurPlateau-larg) - 1) { // sur les bords
				carte[x][y] = 219; // on place un mur
			}
			else {
				carte[x][y] = 32; // on place du vide sinon
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

void refreshPlateau(char carte[largeurPlateau][hauteurPlateau],serpent serpent, int temp,int larg,int haut, int* typejeu) { // rafraichissement affichage
	system("cls");
	int time =60 -(Timer() - temp); // décompteur
	if (time <= 0) {	//temps à 0 = mort
		gameover(carte, serpent, &*typejeu,haut);
	}
	for (int y = 0; y < (hauteurPlateau-haut); y++) { // balayage du plateau et remplissage des cases
		for (int x = 0; x < (largeurPlateau-larg); x++) {		//coloriage et affichage
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
	if(*typejeu==2){ // si mode de jeu intermediaire
		Gotoxy(52-larg,1);		//affichage temps et score
		printf("Niveau: %d Score: %d",(haut/3)+1,(serpent.taille)-3);
	}
	else{ // mode manuel
		Gotoxy(52-larg,1);	
		printf("Score: %d", (serpent.taille)-3);
	}
	Gotoxy(52-larg, 3); // affichage temps restant
	printf("Temps restant: %d sec",time);
}

int nbrealeatoire(int a, int b) { // fonction générant des nombres aléatoires
	srand(time(NULL));
	return rand() % (b - a) + a;
}

void generateFruit(char carte[largeurPlateau][hauteurPlateau],position* fruit, serpent serpent,int larg,int haut) { // génération du fruit
	while (true) {
		int fruitcheck = false; // on définit la vérification fruit sur serpent à faux
		fruit->x = nbrealeatoire(1, (largeurPlateau-larg) - 1); // on génère les coordonnées
		fruit->y = nbrealeatoire(1, (hauteurPlateau-haut) - 1);
		for (int i = 0; i < serpent.taille; i++) { // on vérifie que le fruit n'apparaît pas sur le serpent
			if (fruit->x == serpent.queue[i].x && fruit->y == serpent.queue[i].y) {
				fruitcheck = true; 
			}
		}
		if (fruitcheck == false) { // on affiche le fruit seulement si fruitcheck est à faux, sinon retour début
			carte[fruit->x][fruit->y] = 'O';
			break;
		}
	}
}

void queueDeplacement(char carte[largeurPlateau][hauteurPlateau], serpent* serpent,int direction,int larg,int haut, int* typejeu) {
	// fonction déplaçant les éléments de la queue
	for (int y = serpent->taille-1; y >= 1; y--) {  // on repasse tous les éléments en parlant de la fin
		serpent->queue[y].x = serpent->queue[y - 1].x; // l'élément prend les coordonnées de l'élément précédent
		serpent->queue[y].y = serpent->queue[y - 1].y;
		carte[serpent->queue[y].x][serpent->queue[y].y] = '#';
	}
	switch (direction) // on modifie les éléments de la queue en fonction de la direction du serpent
	{
	case 1 :
		serpent->queue[0].y--;
		if (serpent->queue[0].y == 0) { // on vérifie si le serpent arrive dans le mur
			gameover(carte, *serpent, &*typejeu,haut);
		}
		break;
	case 2 :
		serpent->queue[0].x--;
		if (serpent->queue[0].x == 0) {
			gameover(carte, *serpent, &*typejeu,haut);
		}
		break;
	case 3 :
		serpent->queue[0].y++;
		if (serpent->queue[0].y == (hauteurPlateau-haut)-1) {
			gameover(carte, *serpent, &*typejeu,haut);
		}
		break;
	case 4 :
		serpent->queue[0].x++;
		if (serpent->queue[0].x == (largeurPlateau-larg)-1) {
			gameover(carte, *serpent, &*typejeu,haut);
		}
		break;
	}
	carte[serpent->queue[0].x][serpent->queue[0].y] = '@'; // on réecrit la tête au nouvel emplacement
	carte[serpent->queue[serpent->taille - 1].x][serpent->queue[serpent->taille - 1].y] = ' '; // on efface l'ex-dernier élement de la queue
}

void deplacement(char carte[largeurPlateau][hauteurPlateau], serpent* serpent,position* fruit,int temp,int larg,int haut, int* typejeu) {
	// fonction gérant les déplacements en fonction des touches
	int direction = 1;
	while (true) { // on fait une boucle vérifiant la touche appuyée
		switch (_getch()) {
		case HAUT: // si la touche pressée est le haut
			if (direction != 3) { // on vérifie que le serpent ne va pas vers le bas pour ne pas revenir sur lui-même
				direction = 1; // on reconfigure la direction
				queueDeplacement(carte, &*serpent, direction,larg,haut, &*typejeu); // on lance le déplacement graphique du serpent
			}
			break;

		case GAUCHE:
			if (direction != 4) {
				direction = 2;
				queueDeplacement(carte, &*serpent, direction,larg,haut, &*typejeu);
			}
			break;

		case BAS:
			if (direction != 1) {
				direction = 3;
				queueDeplacement(carte, &*serpent, direction,larg,haut, &*typejeu);
			}
			break;

		case DROITE:
			if (direction != 2) {
				direction = 4;
				queueDeplacement(carte, &*serpent, direction,larg,haut, &*typejeu);
			}
			break;
		case ECHAP: // si on appuie sur echap, on quitte la partie et on retourne au menu principal
			system("cls");
			accueil(carte,*serpent);
			break;
		}
		
		//collision
		if (serpent->queue[0].x == fruit->x && serpent->queue[0].y == fruit->y) { // on vérifie si la tête du serpent rencontre un fruit
			serpent->taille++;
			generateFruit(carte, &*fruit, *serpent,larg,haut);
		}
		for (int i = 1; i < serpent->taille-1; i++) { // on vérifie si le serpent mort sa queue
			if (serpent->queue[0].x == serpent->queue[i].x && serpent->queue[0].y == serpent->queue[i].y) {
				gameover(carte, *serpent, &*typejeu,haut);
				break;
			}
		}
		refreshPlateau(carte, *serpent,temp,larg,haut, &*typejeu);
	}
}


void deplacementInter(char carte[largeurPlateau][hauteurPlateau], serpent* serpent, position* fruit,int temp,int *larg,int *haut,int deltaT, int* typejeu) {
	// même fonction que deplacement mais pour le niveau intermediaire
	int direction = 1;
	int key=HAUT;
	while(true){
			Sleep(deltaT);
			if(_kbhit()!=0){		//detection touche de clavier
			key = _getch();
			}
			switch (key) {
				case HAUT:
					if (direction != 3) {
						direction = 1;
						queueDeplacement(carte,&*serpent,direction,*larg,*haut, &*typejeu);
					}
					else{
						direction = 3;
						queueDeplacement(carte,&*serpent,direction,*larg,*haut, &*typejeu);
					}
					break;

				case GAUCHE:
					if (direction != 4) {
						direction = 2;
						queueDeplacement(carte,&*serpent,direction,*larg,*haut, &*typejeu);
					}
					else{
						direction = 4;
						queueDeplacement(carte,&*serpent,direction,*larg,*haut, &*typejeu);
					}
					break;

				case BAS:
					if (direction != 1) {
						direction = 3;
						queueDeplacement(carte,&*serpent,direction,*larg,*haut, &*typejeu);
					}
					else{
						direction = 1;
						queueDeplacement(carte,&*serpent,direction,*larg,*haut, &*typejeu);
					}
					break;

				case DROITE:
					if (direction != 2) {
						direction = 4;
						queueDeplacement(carte,&*serpent,direction,*larg,*haut, &*typejeu);
					}
					else{
						direction = 2;
						queueDeplacement(carte,&*serpent,direction,*larg,*haut, &*typejeu);
					}
					break;
				case ECHAP:
					system("cls");
					accueil(carte,*serpent);
					break;
				default:
					queueDeplacement(carte,&*serpent,direction,*larg,*haut, &*typejeu);
					break;
				}

			//collision fruit
			if (serpent->queue[0].x == fruit->x && serpent->queue[0].y == fruit->y) {
				serpent->taille++;
				generateFruit(carte, &*fruit,*serpent,*larg,*haut);
			}
			if(serpent->taille>=8){		//next level à un certain score
				*haut = *haut+3;
				*larg = *larg+6;
				premierSerpentInter(carte,*serpent, *larg, *haut, &*typejeu); // on redemarre le jeu pour le niveau suivant
			}
			//collision serpent
			for (int i = 1; i < serpent->taille - 1; i++) {
				if (serpent->queue[0].x == serpent->queue[i].x && serpent->queue[0].y == serpent->queue[i].y) {
					gameover(carte, *serpent, &*typejeu,*haut);
					break;
				}
			}
			refreshPlateau(carte, *serpent,temp,*larg,*haut, &*typejeu);
	}
}


void premierSerpent(char carte[largeurPlateau][hauteurPlateau], serpent serpent,int larg,int haut, int* typejeu) {
	// initialisation du serpent - mode manuel
	position fruit;
	int temp = Timer();
	generateFruit(carte,&fruit, serpent,larg,haut); // on génère un fruit
	serpent.queue[0].x = largeurPlateau / 2; // on définit les paramètres initiaux du serpent
	serpent.queue[0].y = hauteurPlateau / 2;
	serpent.taille = 3;
	for (int i = 1;i < serpent.taille-1 ;i++) { // on affiche le premier serpent
		serpent.queue[i].x = serpent.queue[0].x;
		serpent.queue[i].y = serpent.queue[i-1].y + 1;
		carte[serpent.queue[i].x][serpent.queue[i].y] = '#';
	}
	carte[serpent.queue[0].x][serpent.queue[0].y] = '@';
	refreshPlateau(carte,serpent,temp,larg,haut, &*typejeu); // on rafraichit l'affichage
	deplacement(carte, &serpent,&fruit,temp,larg,haut, &*typejeu); // on lance le jeu

}

void premierSerpentInter(char carte[largeurPlateau][hauteurPlateau], serpent serpent,int larg,int haut, int* typejeu) {
	// initialisation du serpent - mode intermédiaire
	definePlateau(carte,larg,haut); // on configure le tableau de base
	position fruit;
	int temp = Timer();
	int deltaT =200-5*larg; // vitesse du serpent proportionnelle au level
	generateFruit(carte, &fruit, serpent,larg,haut); // on génère un fruit
	serpent.queue[0].x = (largeurPlateau-larg) / 2; // paramètres initiaux serpent
	serpent.queue[0].y = (hauteurPlateau-haut) / 2;
	serpent.taille = 3;
	for (int i = 1; i < serpent.taille - 1; i++) { // on print les éléments du serpent
		serpent.queue[i].x = serpent.queue[0].x;
		serpent.queue[i].y = serpent.queue[i - 1].y + 1;
		carte[serpent.queue[i].x][serpent.queue[i].y] = '#';
	}
	carte[serpent.queue[0].x][serpent.queue[0].y] = '@';
	refreshPlateau(carte, serpent,temp,larg,haut, &*typejeu);
	deplacementInter(carte, &serpent, &fruit,temp,&larg,&haut,deltaT, &*typejeu);
}

void initialisation(char carte[largeurPlateau][hauteurPlateau],serpent serpent, int* typejeu) {
	// on initialise le jeu pour le mode manuel
	int larg = 0;
	int haut = 0;
	*typejeu = 1; // on sauvegarde le type du jeu pour le choix rejouer du menu gameover
	definePlateau(carte,larg,haut);
	premierSerpent(carte,serpent,larg,haut, &*typejeu);
}


void initialisationinter(char carte[largeurPlateau][hauteurPlateau], serpent serpent, int* typejeu) {
	// on initialise le jeu pour le mode intermédiaire
	int larg=10;
	int haut=0;
	*typejeu = 2;
	premierSerpentInter(carte, serpent,larg,haut, &*typejeu);
}

int menu(const char* ch[], int taille, int x, int y) { // fonction pour créer un menu et renvoie le numéro du choix
	int i, curseur = 0;
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
		if (touche == BAS && curseur < taille - 1)
			curseur++;
		if (touche == HAUT && curseur > 0)
			curseur--;
		if (touche == ENTREE) // si touche entrée : retour du numéro du choix
			return curseur + 1;
		int y3 = y;
		Gotoxy(x, y);
		for (i = 0; i < taille; i++) { // on place le curseur
			printf("%c\n", (i == curseur) ? '>' : ' ');
			y3++;
			Gotoxy(x, y3);
		}
	}
	return 0;
}

void accueil(char carte[largeurPlateau][hauteurPlateau], serpent serpent) { // affichage du menu accueil
	int typejeu = 1;
	Gotoxy(5, 24);
	printf("Un programme de DELECLUSE Raphael et PYNTHE Thomas"); // copyright
	Gotoxy(5, 10);
	printf("Bienvenue dans le Snake\n\n");
	printf("--------------------------------------------------------------\n\n");
	Gotoxy(5, 14);
	printf("Choisissez une option :\n\n");
	const char* tabchoix[] = { "Jouer (deplacement manuel)","Jouer (niveau intermediaire)","Regles du jeu","Quitter" }; // définition du tableau contenant les choix
	int c = menu(tabchoix, 4, 5, 16); // affichage menu en (5,16) et retour choix
	switch (c) { // selon le choix
	case 1:
		initialisation(carte, serpent, &typejeu); // on lance le jeu si choix 1
		break;
	case 2: // on lance le jeu intermediaire si choix 2
		initialisationinter(carte, serpent, &typejeu);
		break;
	case 3:
		printregles(carte, serpent);
		break;
	case 4: // on quitte le jeu si choix 4
		system("cls");
		exit(1);
		break;
	}
}

void gameover(char carte[largeurPlateau][hauteurPlateau], serpent serpent, int* typejeu,int haut) { // menu gameover
	system("cls");
	Gotoxy(5, 10);
	printf("Vous avez perdu :(");
	if(*typejeu==2){ // on configure l'affichage de fin en fonction du type de jeu
		Gotoxy(5, 12);
		printf("Highscore: Nieau: %d Score: %d",(haut/3)+1, (serpent.taille) - 3);
	}
	else{
		Gotoxy(5, 12);
		printf("Votre score est de : %d", (serpent.taille) - 3);
	}
	Gotoxy(5, 14);
	printf("Voulez-vous rejouer?");
	const char* tabchoix[] = { "Rejouer","Menu principal","Quitter" }; // choix menu
	int c = menu(tabchoix, 3, 5, 16); // retour choix menu
	switch (c) {
	case 1:
		switch (*typejeu) { // en fonction du mode joué
		case 1:
			initialisation(carte, serpent, &*typejeu); // rejouer le mode manuel
			break;
		case 2:
			initialisationinter(carte, serpent, &*typejeu); // rejouer le mode intermed
			break;
		}
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

void printregles(char carte[largeurPlateau][hauteurPlateau], serpent serpent) { // affichage des règles
	system("cls");
	Gotoxy(5, 3);
	printf("REGLES DU JEU DU SNAKE");
	Gotoxy(5, 5);
	printf("Vous controlez un serpent evoluant sur un plateau de jeu. Votre but est de manger le plus");
	Gotoxy(5, 6);
	printf("de fruits possibles dans le temps imparti. Lorsque vous mangez un fruit, votre queue s'allonge.");
	Gotoxy(5, 7);
	printf("Attention, la partie prend fin lorsque le temps imparti est ecoule, lorsque vous foncez dans un mur,");
	Gotoxy(5, 8);
	printf("ou lorsque vous tenez de manger votre propre queue. Votre score correspond alors a la taille de votre queue.");
	Gotoxy(5, 9);
	printf("Pour controler votre serpent, utilisez les touches directionnelles de votre clavier.");
	Gotoxy(5, 11);
	printf("MODES DE JEU");
	Gotoxy(5, 13);
	printf("Mode de jeu manuel : dans ce mode, le serpent avance lorsque vous appuyez sur les fleches.");
	Gotoxy(5, 14);
	printf("Attrapez le plus de fruits possibles en 60 secondes !");
	Gotoxy(5, 16);
	printf("Mode de jeu intermediaire : dans ce mode, le serpent avance automatiquement. Vous n'avez le controle que ");
	Gotoxy(5, 17);
	printf("de la direction. Attrapez 3 fruits et passez au niveau superieur, dont la difficulte est accrue. Vous avez");
	Gotoxy(5, 18);
	printf("60 secondes a chaque niveau.");
	Gotoxy(5, 20);
	printf("Appuyez sur une touche pour revenir a l'accueil");
	_getch();
	system("cls");
	accueil(carte, serpent);
}

int main(serpent serpent) {							
	char carte[largeurPlateau][hauteurPlateau]; // on définit un tableau qui stocke la carte
	accueil(carte, serpent); // on lance l'accueil
	return 0;
}