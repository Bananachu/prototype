/* CODE SOURCE DU "JEU" PROTOTYPE

Auteur : Bananachu

Pour plus d'informatios sur le projet, veuillez
consulter le repo GitHub :
https://www.github.com/Bananachu/prototype

Remerciements spéciaux à Alex Allain du site
https://www.cprogramming.com
pour ses cours de C et de C++, ainsi qu'à
la chaîne YouTube freeCodeCamp.org pour les 
même raisons

Ce code n'est publié sous aucune licence et est
totalement libre, vous pouvez l'utiliser comme 
bon vous semble, même si des crédits seraient
appréciés. 

Ce code a été écrit sur SublimeText et compilé
avec GCC, merci aux dévloppeurs de ces deux 
applications !*/


#include <stdio.h>
#include <string.h>


// Variables cachées
char input[12];	// Pour stocker l'input de l'utilisateur.
int zone; // Pour stocker le numéro de zone.
int sequel; // Pour stocker la progression des dialogues.


/*Fonctions "motrices"
Ces fonctions sont appelées à de nombreuses reprises et
servent au fonctionnement même du logiciel, elle ne représentent
pas forcément quelque chose de concret pour l'utilisateur.*/

// Supprime le \n à la fin de l'input
void purify(char *str, int size) {
	int i;
	for (i = 0; i < size; i++) {
		if (str[i] == '\n') {
			str[i] = '\0';
			return;
		}
	}
}


// Fonction affichant l'ASCII-art.
// Elle prend en paramètre le numéro de ligne du début 
// et de la fin dudit ASCII-art dans ./ressources/art.
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


// Idem pour les dialogues.
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


// Affiche le dialogue en fonction de la zone.
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


// Idem pour l'ASCII-art.
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


// Incrémente sequel de 100 en 100 pour permettre à dialogue() 
// d'afficher la suite des paragraphes quand il le faut.
int suite() {
	if (strcmp(input, "suite") == 0) {
		sequel = sequel + 100;
		tableau();
		dialogue();
	}
}


// Réinitialise sequel et affiche le début du dialogue.
void back() {
	if (strcmp(input, "retour") == 0) {
		sequel = zone;
		tableau();
		dialogue();
	}
}


// Appelée en cas d'évênement imprévu (message d'erreur).
void wrong() {
	sequel = zone;
	tableau();
	text(12, 17);
}


/*FIN DES FONCTIONS "MOTRICES"*/


// Cette fonction est un cas à part  : elle est appelée au lancement
// du logiciel et affiche l'écran titre. Elle n'est plus appelée par
// la suite.
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


/*Commandes
Ces fonctions correspondent à des commandes effectuables
par l'utilisateur.*/


// Affiche l'ASCII-art et la description de la zone actuelle.
void inspect() {
	if (strcmp(input, "inspecter") == 0) {
		sequel = zone;
		tableau();
		dialogue();
	}
}


// Affiche l'aide.
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


// Cette fonction change la valeur de la variable "zone" de manière à
// simuler un déplacement vers le nord du point de vue du joueur.
// Limité à 0 pour ne pas "sortir" de la carte.
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


//Idem pour le sud
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


//Idem pour l'est
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


//Idem pour l'ouest
void west() {
	if (strcmp(input, "ouest") == 0) {
		//Idem que pour l'est
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


/*FIN DES COMMANDES*/


// Liste des commandes faisable par l'utilisateur
// (pour éviter d'avoir un énorme if/else).
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
	start();	//Écran titre
	int k = 0;
	while (k < 1) {	//Cette boucle est ensuite répétée infiniment :
		fgets(input, 12, stdin);	// on récupère l'input
		purify(input, 12);				// on enlève le \n
		printf("\a \e[1;1H\e[2J");// on fait un bip et on nettoie le terminal
		actions();	// et enfin on effectue la commande.
		if (strcmp(input, "quitter") == 0) {
			return k = 1;		// Cette condition brise la boucle et fait quitter le jeu.
		}
		printf("[Zone:%d | Sequel:%d]> ", zone, sequel);		// Affiche le ">".
	}
}