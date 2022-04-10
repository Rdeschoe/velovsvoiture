#ifdef __APPLE_CC__
#include <OpenGL/OpenGL.h>
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "loadMap.h"
#include "mainGame.h"
#include "drawMap.h"
#include "decor.h"
#include "shots.h"
#include "ennemies.h"
#include "player.h"
#include "collisions.h"

/*-----------Variables gérées par le clavier----------*/

bool HAUT = false;               // Variables utilisées
bool GAUCHE = false;             // pour contrôler
bool DROITE = false;             // les
bool BAS = false;                // actions du
bool TIR = false;                // personnage joueur


/*-----------Variables gérées par les timers----------*/

bool TIR_DISPO = true;           //Variable permettant de réguler la cadence de tir du joueur
bool AVANCE_TIRS_JOUEUR = false; //Variable permettant de réguler l'avancement des tirs du joueur
/*----------------------------------------------------*/
bool AJOUT_ENNEMI = false;       //Variable permettant de réguler l'ajout d'ennemis   
bool MOUVEMENT_ENNEMI = false;   //Variable permettant de réguler les mouvements ennemis
/*-----------------------------------------------------*/
bool TIR_ENNEMI = false;         //Variable permettant de réguler l'ajout de tirs ennemis
bool AVANCE_TIRS_ENNEMI = false; //Variable permettant de réguler l'avancement des tirs ennemis
/*----------------------------------------------------*/
bool SCROLLING_ENNEMI = false;   //Variable permettant de réguler le scrolling des ennemis
bool SCROLLING_DECOR = false;    //Variable permettant de réguler le scrolling du décor
/*----------------------------------------------------*/

//Assignation des touches du clavier aux actions du joueur
void clavier(unsigned char key, int x, int y)
{
	switch(key)
	{

		case'z':
			HAUT = true;
			break;

		case'q':
			GAUCHE = true;
			break;

		case'd':
			DROITE = true;
			break;

		case'x':
			BAS = true;
			break;
		
		case' ':
			TIR = true;
			break;
	}	
}	

//Activation des variables de type bool par les timers
void timer(int theTimer)
{
	switch(theTimer)
	{
		case 0 :
		AVANCE_TIRS_JOUEUR = true;
		AVANCE_TIRS_ENNEMI = true;
		glutTimerFunc(60, timer, 0);	
		break;
		
		case 1 :
		AJOUT_ENNEMI = true;
		MOUVEMENT_ENNEMI = true;
		TIR_ENNEMI = true;
		glutTimerFunc(1000, timer, 1);
		break;
		
		case 2 :
		SCROLLING_DECOR = true;
		glutTimerFunc(80, timer, 2);
		break;
		
		case 3 :
		TIR_DISPO = true;
		glutTimerFunc(100, timer, 3);
		break;
		
		case 4 :
		SCROLLING_ENNEMI = true;
		glutTimerFunc(550, timer, 4);
		break;
	}	
}

//Fonction principale du jeu. Appelle toutes les fonctions nécessaires au déroulement de celui-ci.
void game(int nb_lin, int nb_col, joueur j1, liste_tirs_joueur listeTJ, liste_ennemis listeE, liste_decor listeD, liste_tirs_ennemi listeTE)
{
	maj_affichage(nb_lin, nb_col, listeD, j1, listeTJ, listeE, listeTE); //Gère la mise à jour de tous les affichages
	collisions(listeTJ, listeE, j1, listeTE);                            //Gère l'ensemble des collisions si nécessaire

	if(GAUCHE) {mouvement_gauche(j1) ; GAUCHE = false;} //Déplacer le joueur vers la gauche
	if(DROITE) {mouvement_droite(j1) ; DROITE = false;} //Déplacer le joueur vers la droite
	if(HAUT  ) {mouvement_haut(j1)   ;   HAUT = false;} //Déplacer le joueur vers le haut
	if(BAS   ) {mouvement_bas(j1)    ;    BAS = false;} //Déplacer le joueur vers le bas

	if(TIR && TIR_DISPO) {insertion_tirs_joueur(listeTJ, j1); TIR = false; TIR_DISPO = false;}//TIR et TIR_DISPO doivent tous les deux être "true" pour pouvoir ajouter un tir joueur             

	if(AJOUT_ENNEMI)
	{
		int test; //Permet d'ajouter de l'aléatoire
		if(listeE->tete == NULL){test = rand()%2;}   //Une chance sur 2 d'ajouter un ennemi (tous les X temps, voir timer 1) si la liste des ennemis est vide
		else                    {test = rand()%4;}   //Une chance sur 4 d'ajouter un ennemi si la liste des ennemis n'est pas vide

		if(test == 0){insertion_ennemi(listeE);}     //ajout d'un ennemi si test = 0
		AJOUT_ENNEMI = false;
	}
	
	if(MOUVEMENT_ENNEMI) {mouvement_ennemi(listeE); MOUVEMENT_ENNEMI = false;} //Déplacement des ennemis
	
	if(TIR_ENNEMI)
	{
		int test; //Permet d'ajouter de l'aléatoire
		ennemi actuel = listeE->tete;
		while(actuel != NULL)
		{
			test = rand()%4;//Pour chaque ennemi présent sur la map, une chance sur 4 de tirer (tous les X temps, voir timer 1)
			if(test == 0){insertion_tirs_ennemi(listeTE, actuel);} //Ajout d'un tir pour l'ennemi actuel si test = 0
			actuel = actuel->suivant;
		}
		TIR_ENNEMI = false;
	}

	if(SCROLLING_ENNEMI) {scrolling_ennemi(listeE, j1); SCROLLING_ENNEMI = false;} //Scrolling des ennemis.
	if(SCROLLING_DECOR ) {scrolling_decor(listeD)     ;  SCROLLING_DECOR = false;} //Scrolling du décor.

	if(AVANCE_TIRS_JOUEUR){avance_tirs_joueur(listeTJ, j1); AVANCE_TIRS_JOUEUR = false;} //Fait avancer les tirs du joueur sur la map
	if(AVANCE_TIRS_ENNEMI){avance_tirs_ennemi(listeTE)    ; AVANCE_TIRS_ENNEMI = false;} //Fait avancer les tirs ennemis sur la map

	if(j1->score < 0){j1->score = 0;}           //le score ne peut être négatif
	
	glutKeyboardFunc(clavier);
	glutPostRedisplay();
}
