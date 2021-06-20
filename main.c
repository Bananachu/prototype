#include <stdio.h>
#include <string.h>


char input[12]; //Cette variable stocke l'input de l'utilisateur
int zone;       //Celle-là stocke la zone (cette valeur n'est pas montrée en jeu
								//mais est utilisée pour simuler les déplacements)

//Fonction permettant de "purifier" l'input en supprimant le saut de ligne à la fin
void purify(char *str, int size) {
	int i;
	for (i = 0; i < size; i++) {
		if (str[i] == '\n') {
			str[i] = '\0';
			return;
		}
	}
}


//Fonction affichant la partie "dessin" de l'output
//(elle prend en paramètre le numéro de ligne du début et de la fin du dessin dans le fichier)
int art(int begin, int end) {
	FILE *pepe = fopen ("./ressources/arts", "r");
  char line[255];
  for (int l = 0; l < end; l++) {
    fgets(line, sizeof(line), pepe);
    if (l >= begin && l < end) {
    	printf("%s", line);
    }
  }
  fclose(pepe);
}


//Fonction affichant la partie texte de l'output (même fonctionnement que la fonction au-dessus)
int text(int intro, int outro) {
	FILE *sans = fopen ("./ressources/verbose", "r");
  char vers[255];
  for (int m = 0; m < outro; m++) {
    fgets(vers, sizeof(vers), sans);
    if (m >= intro && m < outro) {
    	printf("%s", vers);
    }
  }
  fclose(sans);
}


//Pour afficher l'art + le texte (prend en )
int display() {
	switch (zone) {
		case 1:
			break;
		case 2:
			//description salle 2
			break;
		case 42:
			art(23, 40);
			text(23, 28);
			break;
		default:
			//inventer
			break;
		}
}


//Fonction appelée au début du jeu, finie à partir du premier tableau
int start() {
	printf("\e[1;1H\e[2J");
	art(0, 22);
	printf("\x1b[94m> ");
	int j = 0;
	for (j = 0; j < 2; j++) {
		fgets( input, 12, stdin );
		purify( input, 12 );
		printf("\a");
		if (strcmp(input, "start") == 0) {
				printf( "\x1b[0m \e[1;1H\e[2J" );
				zone = 42;
				display(42);
				printf("\x1b[94m> ");
				return j = 3;
		} else {
				printf( "\x1b[0mMerci d'entrer \x1b[92m\x1b[1mstart\x1b[0m pour démarrer.\n\x1b[94m> " );
		}
	}
}


//Affiche l'art et la description de la zone actuelle
int inspect() {
	if (strcmp(input, "inspecter") == 0) {
		display(zone);
	}
}


//Pour afficher l'aide
int help() {
	if (strcmp(input, "aide") == 0) {
		text(0, 22);
	}
}


//Cette fonction change la valeur de la variable "zone" de manière à
//simuler un déplacement vers le nord du point de vue du joueur.
//on limite ça à 0 pour éviter de sortir de la map
int nord() {
	if (strcmp(input, "nord") == 0) {
		if ((zone - 10) >= 0) {
			zone = zone - 10;
			printf("salle n°%d", zone);
		} else {
			printf("Vous ne pouvez pas aller plus loin.");
		}
	}
}

//Même chose pour le sud
int sud() {
	if (strcmp(input, "sud") == 0) {
		if ((zone + 10) <= 99) {
			zone = zone + 10;
			printf("salle n°%d", zone );
		} else {
			printf("Vous ne pouvez pas aller plus loin.");
		}
	}
}

//Même chose pour l'est
int east() {
	if (strcmp(input, "est") == 0) {
		//La ligne suivante ne me plaît pas mais j'ai pas encore trouvé mieux :/
		if (zone == 9 || zone == 19 || zone == 29 || zone == 39 || zone == 49 || zone == 59 || zone == 69 || zone == 79 || zone == 89 || zone == 99) {
			printf("Vous ne pouvez pas aller plus loin.");
		} else {
			zone = zone + 1;
			printf("salle n°%d", zone);
		}
	}
}

//Même chose pour l'est
int west() {
	if (strcmp(input, "ouest") == 0) {
		//Idem que pour l'ouest
		if (zone == 0 || zone == 10 || zone == 20 || zone == 30 || zone == 40 || zone == 50 || zone == 60 || zone == 70 || zone == 80 || zone == 90) {
			printf("Vous ne pouvez pas aller plus loin.");
		} else {
			zone = zone - 1;
			printf("salle n°%d", zone);
		}
	}
}


//Liste des commandes faisable par l'utilisateur
int actions() {
	help();
	inspect();
	nord();
	sud();
	east();
	west();
}



//Fonction principale, "moteur" du jeu
int main() {
	start();	//Fonction affichant l'écran titre et démarrant le jeu
	int k = 0;
	while (k < 1) {	//cette boucle est ensuite répétée infiniment :
		fgets(input, 12, stdin);	//on récupère la commande (input)
		purify(input, 12);				//on la "purifie" (voir début du code)
		printf("\a \x1b[0m \e[1;1H\e[2J");	//ici on fait un bip + on enlève les couleurs + on nettoie le terminal
		actions();	//et enfin on effectue la commande
		if (strcmp(input, "quitter") == 0) {
			return k = 1;		//cette condition brise la boucle et fait quitter le jeu
		}
		printf("\x1b[94m> ");		//on imprime le ">" en bleu pour faire comprendre qu'on attend une action de la part de l'utilisateur
	}
}
