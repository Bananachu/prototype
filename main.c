#include <stdio.h>
#include <string.h>


char input[12]; //Cette variable stocke l'input de l'utilisateur
int zone;       //Celle-là stocke la zone (cette valeur n'est pas montrée en jeu
int sequel;			//mais est utilisée pour simuler les déplacements)

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
void art(int begin, int end) {
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
void text(int intro, int outro) {
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


//Pour afficher l'art + le texte (chaque cas est défini par la zone)
//OBSOLÈTE, À DIVISER EN DEUX POUR SÉPARER LE TEXTE DE L'IMAGE
void dialogue() {
	switch (sequel) {
		case 42:
			text(64, 69);
			break;
		case 100:
			text(18, 40);
			break;
		case 142:
			text(70, 75);
			break;
		case 200:
			text(41, 63);
			break;
		case 242:
			text(76, 81);
			sequel = -58;
			break;
		default:
			text(12, 17);
			break;
		}
}


//Pour afficher l'art + le texte (chaque cas est défini par la zone)
//OBSOLÈTE, À DIVISER EN DEUX POUR SÉPARER LE TEXTE DE L'IMAGE
int tableau() {
	switch (sequel) {
		case 42:
			art(18, 35);
			break;
		case 100:
			break;
		case 142:
			art(18, 35);
			break;
		case 200:
			break;
		case 242:
			art(18, 35);
			break;
		default:
			art(36, 53);
			break;
		}
}


//Pour afficher la suite de la description, chaque cas est défini par une variable
//elle-même ayant la valeur de la zone lors de chaque déplacement puis de elle-même + 100.
int suite() {
	if (strcmp(input, "suite") == 0) {
		sequel = sequel + 100;
		tableau();
		dialogue();
	}
}


void back() {
	if (strcmp(input, "retour") == 0) {
		sequel = zone;
		tableau();
		dialogue();
	}
}


void wrong() {
	sequel = zone;
	tableau();
	text(12, 17);
}


//Fonction appelée au début du jeu, finie à partir du premier tableau
int start() {
	printf("\e[1;1H\e[2J");
	art(0, 17);
	text(0, 5);
	printf("[Zone:%d | Sequel:%d]> ", zone, sequel);
	int j = 0;
	for (j = 0; j < 2; j++) {
		fgets( input, 12, stdin );
		purify( input, 12 );
		printf("\a");
		if (strcmp(input, "start") == 0) {
			printf( "\e[1;1H\e[2J" );
			zone = 42;
			sequel = zone;
			tableau();
			dialogue();
			printf("[Zone:%d | Sequel:%d]> ", zone, sequel);
			return j = 3;
		} else {
			art(0, 17);
			text(6, 11);
		}
	}
}


//Affiche l'art et la description de la zone actuelle
void inspect() {
	if (strcmp(input, "inspecter") == 0) {
		sequel = zone;
		tableau();
		dialogue();
	}
}


void help() {
	if (strcmp(input, "aide") == 0) {
		sequel = 100;
		dialogue();
	}
}


/*Pour afficher l'aide OBSOLÈTE, À MIGRER VERS CAS -1 DE DISPLAY
void help() {
	if (strcmp(input, "aide") == 0) {
		sequel = zone;
		text(12, 34);
		printf("> ");
		fgets(input, 12, stdin);
		purify(input, 12);
		if (strcmp(input, "plus") == 0) {
			printf("\a \x1b[0m \e[1;1H\e[2J");
			text(35, 57);
		} else if (strcmp(input, "retour") == 0) {
			printf("\a \x1b[0m \e[1;1H\e[2J");
			display(zone);
		} else {
			printf("Vous ne pouvez pas faire ça ici.");
		}
	}
}*/


//Cette fonction change la valeur de la variable "zone" de manière à
//simuler un déplacement vers le nord du point de vue du joueur.
//on limite ça à 0 pour éviter de sortir de la map
void north() {
	if (strcmp(input, "nord") == 0) {
		if ((zone - 10) >= 0) {
			zone = zone - 10;
			sequel = zone;
			tableau();
			dialogue();
		} else {
			printf("Vous ne pouvez pas aller plus loin.");
		}
	}
}

//Même chose pour le sud
void south() {
	if (strcmp(input, "sud") == 0) {
		if ((zone + 10) <= 99) {
			zone = zone + 10;
			sequel = zone;
			tableau();
			dialogue();
		} else {
			printf("Vous ne pouvez pas aller plus loin.");
		}
	}
}

//Même chose pour l'est
void east() {
	if (strcmp(input, "est") == 0) {
		//La ligne suivante ne me plaît pas mais j'ai pas encore trouvé mieux :/
		if (zone == 9 || zone == 19 || zone == 29 || zone == 39 || zone == 49 || zone == 59 || zone == 69 || zone == 79 || zone == 89 || zone == 99) {
			printf("Vous ne pouvez pas aller plus loin.");
		} else {
			zone = zone + 1;
			sequel = zone;
			tableau();
			dialogue();
		}
	}
}

//Même chose pour l'est
void west() {
	if (strcmp(input, "ouest") == 0) {
		//Idem que pour l'ouest
		if (zone == 0 || zone == 10 || zone == 20 || zone == 30 || zone == 40 || zone == 50 || zone == 60 || zone == 70 || zone == 80 || zone == 90) {
			printf("Vous ne pouvez pas aller plus loin.");
		} else {
			zone = zone - 1;
			sequel = zone;
			tableau();
			dialogue();
		}
	}
}


//Liste des commandes faisable par l'utilisateur
void actions() {
	help();
	inspect();
	north();
	south();
	east();
	west();
	suite();
	back();
}


//Fonction principale, "moteur" du jeu
int main() {
	start();	//Fonction affichant l'écran titre et démarrant le jeu
	int k = 0;
	while (k < 1) {	//cette boucle est ensuite répétée infiniment :
		fgets(input, 12, stdin);	//on récupère la commande (input)
		purify(input, 12);				//on la "purifie" (voir début du code)
		printf("\a \e[1;1H\e[2J");	//ici on fait un bip + on nettoie le terminal
		actions();	//et enfin on effectue la commande
		if (strcmp(input, "quitter") == 0) {
			return k = 1;		//cette condition brise la boucle et fait quitter le jeu
		}
		printf("[Zone:%d | Sequel:%d]> ", zone, sequel);		//on imprime le ">" en bleu pour faire comprendre qu'on attend une action de la part de l'utilisateur
	}
}
