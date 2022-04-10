#ifdef __APPLE_CC__
#include <OpenGL/OpenGL.h>
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>


#include "loadMap.h"
#include "shots.h"
#include "ennemies.h"
#include "drawMap.h"
#include "game.h"
#include "player.h"
#include "collisions.h"

//Permet d'afficher la map chargée
void afficher_map(int nb_lin, int nb_col, liste_decor listeD)			
{
	int i, j;
	for (j =0;j<nb_lin;j++)
	{
		for (i=0;i<nb_col;i++)
		{
			if(*(*(map + j) + i) == 'w')  //Lignes blanches sur les côtés de la route
			{
				glMatrixMode(GL_MODELVIEW);
				glLoadIdentity();
				if(i < Square_size/2)
				{
					glTranslatef(i*Square_size,j*Square_size,0);       // Ligne blanche du côté gauche de la route
				}
				else
				{
					glTranslatef(i*Square_size+18.75,j*Square_size,0); // Ligne blanche du côté droit de la route
				}

				glBegin(GL_QUADS);
				glColor3f(1,1,1);
				glVertex3f(0, 0, 0);
				glVertex3f(Square_size/4, 0, 0);
				glVertex3f(Square_size/4,Square_size, 0);
				glVertex3f(0,Square_size, 0);
				glEnd();
			}
			if(*(*(map + j) + i) == 'l')    //Ligne du milieu
			{
				insertion_decor(listeD, j, i, 'l'); //Ajout à la liste chainée des décors. Celle-ci sera gérée ailleurs pour le scrolling.
				*(*(map + j) + i) = ' ';            //On remet un espace à la place du 'l', afin de réafficher un carré de route.
			}                                             
			if(*(*(map +j) + i) == '2')     //Décor sur le coté de la route. 
			{
				insertion_decor(listeD, j, i, '2'); //Ajout à la liste chainée des décors. Ce décor sera géré ailleurs pour le scrolling.
				*(*(map + j) + i) = '1';            //On remet un "1" à la place du "2", afin de réafficher la couleur du sol.
			}
			if(*(*(map + j) + i) == '1') //Couleur représentant le sol de chaque côté de la route.
			{	
				glMatrixMode(GL_MODELVIEW);
				glLoadIdentity();
				glTranslatef(i*Square_size,j*Square_size,0);
				
				glBegin(GL_QUADS);
				glColor3f(0.5,1,0.5);
				glVertex3f(0, 0, 0);
				glVertex3f(Square_size, 0, 0);
				glVertex3f(Square_size,Square_size, 0);
				glVertex3f(0,Square_size, 0);
				glEnd();
			
			}
			if(*(*(map + j) + i) == 'm')  //Bande noire entourant la map.
			{	
				glMatrixMode(GL_MODELVIEW);
				glLoadIdentity();
				glTranslatef(i*Square_size,j*Square_size,0);
				
				glBegin(GL_QUADS);
				glColor3f(0,0,0);
				glVertex3f(0, 0, 0);
				glVertex3f(Square_size, 0, 0);
				glVertex3f(Square_size,Square_size, 0);
				glVertex3f(0,Square_size, 0);
				glEnd();
			}
		}
	}
}

//Afficher le joueur
void afficher_joueur(joueur j1)
{
	glColor3f(0,0,1);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(j1->y*Square_size,j1->x*Square_size,0);
	
	glBegin(GL_QUADS);
	glVertex3f(0, 0, 0);
	glVertex3f(Square_size, 0, 0);
	glVertex3f(Square_size,Square_size, 0);
	glVertex3f(0,Square_size, 0);

	glEnd();	
}

//Afficher les tirs joueurs
void afficher_tirs_joueur(liste_tirs_joueur listeTJ)
{
	tirs_joueur actuel = listeTJ->tete;
	while (actuel != NULL)
	{
		glColor3f(1,0.8,0.2);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glTranslatef(actuel->y*Square_size,actuel->x*Square_size,0);

		glBegin(GL_QUADS);
		glVertex3f(12.5, 8, 0);
		glVertex3f(13.5, 8, 0);
		glVertex3f(13.5,Square_size, 0);
		glVertex3f(12.5,Square_size, 0);
		glEnd();
		
		actuel = actuel->suivant;
	}
}

//Afficher les ennemis
void afficher_ennemis(liste_ennemis listeE)
{
	ennemi actuel = listeE->tete;
	while (actuel != NULL)
	{
		glColor3f(1,0,0);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glTranslatef(actuel->y*Square_size,actuel->x*Square_size,0);

		glBegin(GL_QUADS);
		glVertex3f(0, 0, 0);
		glVertex3f(Square_size, 0, 0);
		glVertex3f(Square_size,Square_size, 0);
		glVertex3f(0,Square_size, 0);
		glEnd();
		
		actuel = actuel->suivant;
	}
}

//Afficher les tirs ennemis
void afficher_tirs_ennemi(liste_tirs_ennemi listeT_E)
{
	tirs_ennemi actuel = listeT_E->tete;
	while (actuel != NULL)
	{
		glColor3f(1,0.5,0.1);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glTranslatef(actuel->y*Square_size,actuel->x*Square_size,0);

		glBegin(GL_QUADS);
		glVertex3f(10.5, 0, 0);
		glVertex3f(15.5, 0, 0);
		glVertex3f(15.5,Square_size, 0);
		glVertex3f(11.5,Square_size, 0);
		glEnd();
		
		actuel = actuel->suivant;
	}
}

//Afficher les décors
void afficher_decor(liste_decor listeD)
{
	decor actuel = listeD->tete;
	while (actuel != NULL)
	{
		if(actuel->id == 'l')  //ligne au milieu de la route
		{
			glColor3f(1,1,1);
			glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();
			glTranslatef(actuel->y*Square_size,actuel->x*Square_size,0);

			glBegin(GL_QUADS);
			glVertex3f(8, 0, 0);
			glVertex3f(12, 0, 0);
			glVertex3f(12,Square_size, 0);
			glVertex3f(8,Square_size, 0);
			glEnd();
		}
		else if(actuel->id == '2') //décors sur les côtés de la route
		{
			glColor3f(0.24,0.48,0);
			glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();
			glTranslatef(actuel->y*Square_size,actuel->x*Square_size,0);

			glBegin(GL_QUADS);
			glVertex3f(7, 0, 0);
			glVertex3f(18, 0, 0);
			glVertex3f(18,20, 0);
			glVertex3f(7,20, 0);
			glEnd();
		}
		actuel = actuel->suivant;
		
	}
}

//Affichage graphique du score
void affichage_score(joueur j1)
{
	char score[15]={'\0'}; //Chaine de caractère dans laquelle on convertira l'entier correspondant au score du joueur
	sprintf(score, "score : %d", j1->score); //conversion de l'entier en chaine de caractère
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	glColor3f(1,1,1);
	glRasterPos2f(65,20); //Position dans la fenêtre graphique
	int i;
	for(i=0; score[i]!='\0'; i++)
	{
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15, score[i]);
	}
}

void affichage_vie(joueur j1)
{
	char vie[20]={'\0'};    //Chaine de caractère dans laquelle on convertira l'entier coorrespondant à la vie du joueur
	
	if(j1->vie < 1)
	{ 
		glRasterPos2f(395,405);    //Position dans la fenêtre graphique
		sprintf(vie, "game over"); //temporaire, pour la phase 2 de remise du projet
	}
	else
	{
		glRasterPos2f(710,20);              //Position dans la fenêtre graphique
		sprintf(vie, "%d vie(s)", j1->vie); //conversion de l'entier en chaine de caractère
	}
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	glColor3f(1,1,1);
	int i;
	for(i=0; vie[i]!='\0'; i++)
	{
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15, vie[i]);
	}
}

//Fonction comprenant toutes les fonctions d'affichage
void maj_affichage(int nb_lin, int nb_col, liste_decor listeD, joueur j1, liste_tirs_joueur listeTJ, liste_ennemis listeE, liste_tirs_ennemi listeTE)
{
	afficher_map(nb_lin, nb_col, listeD);      //Mise à jour de
	afficher_decor(listeD);                    //l'affichage sur une seule
	afficher_tirs_joueur(listeTJ);             //fonction afin de ne pas
	afficher_tirs_ennemi(listeTE);             //surcharger
	afficher_ennemis(listeE);                  //la fonction game
	afficher_joueur(j1);                       //dans game.c
	affichage_score(j1);
	affichage_vie(j1);
}
