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
	position queue[30];
	int taille;
};

typedef struct serpent serpent;

void gameover(char carte[largeurPlateau][hauteurPlateau], serpent serpent, int* typejeu); // menu gameover
void premierSerpentInter(char carte[largeurPlateau][hauteurPlateau], serpent serpent,int larg,int haut, int* typejeu);

void definePlateau(char carte[largeurPlateau][hauteurPlateau],int larg,int haut) {		//affichage plateau manuel
	system("cls");
	for (int y = 0; y < hauteurPlateau-haut; y++) {
		for (int x = 0; x < largeurPlateau-larg; x++) {
			if (y == 0 || x == 0 || y == (hauteurPlateau-haut) - 1 || x == (largeurPlateau-larg) - 1) {
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

void refreshPlateau(char carte[largeurPlateau][hauteurPlateau],serpent serpent, int temp,int larg,int haut, int* typejeu) {
	system("cls");
	int time =90 -(Timer() - temp);
	if (time <= 0) {	//temps à 0 = mort
		gameover(carte, serpent, &*typejeu);
	}
	for (int y = 0; y < (hauteurPlateau-haut); y++) {
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
	Gotoxy(52-larg,1);		//affichage temp et score
	printf("Score: %d", (serpent.taille)-3);
	Gotoxy(52-larg, 3);
	printf("Temps restant: %d sec",time);
}

int nbrealeatoire(int a, int b) {
	srand(time(NULL));
	return rand() % (b - a) + a;
}

void generateFruit(char carte[largeurPlateau][hauteurPlateau],position* fruit, serpent serpent,int larg,int haut) {
	while (true) {
		int fruitcheck = false;
		fruit->x = nbrealeatoire(1, (largeurPlateau-larg) - 1);
		fruit->y = nbrealeatoire(1, (hauteurPlateau-haut) - 1);
		for (int i = 0; i < serpent.taille; i++) { // on vérifie que le fruit n'apparaît pas sur le serpent
			if (fruit->x == serpent.queue[i].x && fruit->y == serpent.queue[i].y) {
				fruitcheck = true;
			}
		}
		if (fruitcheck == false) {
			carte[fruit->x][fruit->y] = 'O';
			break;
		}
	}
}

void queueDeplacement(char carte[largeurPlateau][hauteurPlateau], serpent* serpent,int direction,int larg,int haut, int* typejeu) {
	
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
			gameover(carte, *serpent, &*typejeu);
		}
		break;
	case 2 :
		serpent->queue[0].x--;
		if (serpent->queue[0].x == 0) {
			gameover(carte, *serpent, &*typejeu);
		}
		break;
	case 3 :
		serpent->queue[0].y++;
		if (serpent->queue[0].y == (hauteurPlateau-haut)-1) {
			gameover(carte, *serpent, &*typejeu);
		}
		break;
	case 4 :
		serpent->queue[0].x++;
		if (serpent->queue[0].x == (largeurPlateau-larg)-1) {
			gameover(carte, *serpent, &*typejeu);
		}
		break;
	}
	carte[serpent->queue[0].x][serpent->queue[0].y] = '@';
	carte[serpent->queue[serpent->taille - 1].x][serpent->queue[serpent->taille - 1].y] = ' ';
}

void deplacement(char carte[largeurPlateau][hauteurPlateau], serpent* serpent,position* fruit,int temp,int larg,int haut, int* typejeu) {
	int direction = 1;
	while (true) {
		switch (_getch()) {
		case HAUT:
			if (direction != 3) {
				direction = 1;
				queueDeplacement(carte, &*serpent, direction,larg,haut, &*typejeu);
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
		}
		
		//collision
		if (serpent->queue[0].x == fruit->x && serpent->queue[0].y == fruit->y) {
			serpent->taille++;
			generateFruit(carte, &*fruit, *serpent,larg,haut);
		}
		for (int i = 1; i < serpent->taille-1; i++) {
			if (serpent->queue[0].x == serpent->queue[i].x && serpent->queue[0].y == serpent->queue[i].y) {
				gameover(carte, *serpent, &*typejeu);
				break;
			}
		}
		refreshPlateau(carte, *serpent,temp,larg,haut, &*typejeu);
	}
}




void deplacementInter(char carte[largeurPlateau][hauteurPlateau], serpent* serpent, position* fruit,int temp,int *larg,int *haut,int deltaT, int* typejeu) {
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
				default:
					queueDeplacement(carte,&*serpent,direction,*larg,*haut, &*typejeu);
					break;
				}

			//collision fruit
			if (serpent->queue[0].x == fruit->x && serpent->queue[0].y == fruit->y) {
				serpent->taille++;
				generateFruit(carte, &*fruit,*serpent,*larg,*haut);
			}
			if(serpent->taille>=6){		//next level
				*haut = *haut+3;
				*larg = *larg+6;
				premierSerpentInter(carte,*serpent, *larg, *haut, &*typejeu);
			}
			//collision serpent
			for (int i = 1; i < serpent->taille - 1; i++) {
				if (serpent->queue[0].x == serpent->queue[i].x && serpent->queue[0].y == serpent->queue[i].y) {
					gameover(carte, *serpent, &*typejeu);
					break;
				}
			}
			refreshPlateau(carte, *serpent,temp,*larg,*haut, &*typejeu);
	}
}


void premierSerpent(char carte[largeurPlateau][hauteurPlateau], serpent serpent,int larg,int haut, int* typejeu) {
	position fruit;
	int temp = Timer();
	generateFruit(carte,&fruit, serpent,larg,haut);
		serpent.queue[0].x = largeurPlateau / 2;
		serpent.queue[0].y = hauteurPlateau / 2;
		serpent.taille = 3;
		for (int i = 1;i < serpent.taille-1 ;i++) {
			serpent.queue[i].x = serpent.queue[0].x;
			serpent.queue[i].y = serpent.queue[i-1].y + 1;
			carte[serpent.queue[i].x][serpent.queue[i].y] = '#';
		}
		carte[serpent.queue[0].x][serpent.queue[0].y] = '@';
		refreshPlateau(carte,serpent,temp,larg,haut, &*typejeu);
		deplacement(carte, &serpent,&fruit,temp,larg,haut, &*typejeu);

}

void premierSerpentInter(char carte[largeurPlateau][hauteurPlateau], serpent serpent,int larg,int haut, int* typejeu) {
	definePlateau(carte,larg,haut);
	position fruit;
	int temp = Timer();
	int deltaT =200-5*larg;
		
	generateFruit(carte, &fruit, serpent,larg,haut);
	serpent.queue[0].x = (largeurPlateau-larg) / 2;
	serpent.queue[0].y = (hauteurPlateau-haut) / 2;
	serpent.taille = 3;
	for (int i = 1; i < serpent.taille - 1; i++) {
		serpent.queue[i].x = serpent.queue[0].x;
		serpent.queue[i].y = serpent.queue[i - 1].y + 1;
		carte[serpent.queue[i].x][serpent.queue[i].y] = '#';
	}
	carte[serpent.queue[0].x][serpent.queue[0].y] = '@';
	refreshPlateau(carte, serpent,temp,larg,haut, &*typejeu);
	deplacementInter(carte, &serpent, &fruit,temp,&larg,&haut,deltaT, &*typejeu);
}

void initialisation(char carte[largeurPlateau][hauteurPlateau],serpent serpent, int* typejeu) {
	int larg = 0;
	int haut = 0;
	*typejeu = 1;
	definePlateau(carte,larg,haut);
	premierSerpent(carte,serpent,larg,haut, &*typejeu);
}


void initialisationinter(char carte[largeurPlateau][hauteurPlateau], serpent serpent, int* typejeu) {
	int larg=10;
	int haut=0;
	*typejeu = 2;
	premierSerpentInter(carte, serpent,larg,haut, &*typejeu);
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
	int typejeu = 1;
	Gotoxy(5, 10);
	printf("Bienvenue dans le Snake\n\n");
	printf("--------------------------------------------------------------\n\n");
	Gotoxy(5, 14);
	printf("Choisissez une option :\n\n");
	const char* tabchoix[] = { "Jouer (deplacement manuel)","Jouer (niveau intermediaire)","Quitter" }; // définition du tableau contenant les choix
	int c = menu(tabchoix, 3, 5, 16); // affichage menu en (5,16) et retour choix
	switch (c) { // selon le choix
	case 1:
		initialisation(carte, serpent, &typejeu); // on lance le jeu si choix 1
		break;
	case 2: // on lance le jeu intermediaire si choix 2
		initialisationinter(carte, serpent, &typejeu);
		break;
	case 3: // on quitte le jeu si choix 3
		system("cls");
		exit(1);
		break;
	}
}

void gameover(char carte[largeurPlateau][hauteurPlateau], serpent serpent, int* typejeu) { // menu gameover
	system("cls");
	Gotoxy(5, 10);
	printf("Vous avez perdu :(");
	Gotoxy(5, 12);
	printf("Votre score est de : %d", (serpent.taille) - 3);
	Gotoxy(5, 14);
	printf("Voulez-vous rejouer?");
	const char* tabchoix[] = { "Rejouer","Menu principal","Quitter" }; // choix menu
	int c = menu(tabchoix, 3, 5, 16); // retour choix menu
	switch (c) {
	case 1:
		switch (*typejeu) {
		case 1:
			initialisation(carte, serpent, &*typejeu); // rejouer
			break;
		case 2:
			initialisationinter(carte, serpent, &*typejeu);
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


int main(serpent serpent) {							
	char carte[largeurPlateau][hauteurPlateau];
	accueil(carte, serpent); // on lance l'accueil
	return 0;
}