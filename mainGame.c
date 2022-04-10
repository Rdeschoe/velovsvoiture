#ifdef __APPLE_CC__
#include <OpenGL/OpenGL.h>
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "mainGame.h"
#include "game.h"
#include "shots.h"
#include "player.h"
#include "ennemies.h"
#include "decor.h"
#include "loadMap.h"



int nb_lin = 32;  //Nombre de lignes de la map
int nb_col = 34;  //Nombre de colonnes de la map

joueur j1;        //Déclaration du personnage joueur

liste_tirs_joueur listeTJ; //Déclaration
liste_ennemis listeE;      //des différentes
liste_decor listeD;        //listes
liste_tirs_ennemi listeTE; //chainées

void initRendering()
{
	glEnable(GL_DEPTH_TEST);
}

void handleResize(int width,int heigth)
{
	glViewport(0, 0, width, heigth);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, width, heigth, 0);
}

void Display()
{
	
	glClearColor(0.14f,0.3f,0.3f,0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	game(nb_lin, nb_col, j1, listeTJ, listeE, listeD, listeTE);  //Appel de la fonction game qui gère l'entiereté du jeu
	
	glFlush();
}

//Fonction qui gère GLUT pour la partie jeu du programme
int main_game(int argc, char *argv[])
{
	srand(time(NULL));
	
	listeD = initialisation_decor();         //Initialisation 
	listeTJ = initialisation_tirs_joueur();  //des
	listeE = initialisation_ennemis();       //différentes
	listeTE = initialisation_tirs_ennemi();  //listes chainées
	
	loadMap(nb_lin, nb_col);                 //Chargement de la map
	
	j1 = creer_joueur(nb_lin, nb_col);       //Création du joueur

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);

	glutInitWindowSize(nb_col*Square_size, nb_lin*Square_size);
	glutInitWindowPosition(500,50);

	glutCreateWindow("VeloVsVoiture");
	initRendering();

	glutDisplayFunc(Display);
	glutReshapeFunc(handleResize);
	
	/*________________Liste des timers____________________*/
	
	glutTimerFunc(60, timer, 0);    //vitesse tirs joueur
	glutTimerFunc(1000, timer, 1);  //ajout ennemi, mouvement ennemi et tir ennemi
	glutTimerFunc(80, timer, 2);    //scrolling decor
	glutTimerFunc(100, timer, 3);   //cadence de tir
	glutTimerFunc(550, timer, 4);   //scrolling ennemi
	/*____________________________________________________*/
	
	glutMainLoop();

	return 0;
}
