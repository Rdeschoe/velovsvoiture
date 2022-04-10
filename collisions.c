#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "loadMap.h"
#include "collisions.h"
#include "shots.h"
#include "ennemies.h"
#include "player.h"

//Gère la collision entre les tirs joueur et les ennemis
void collision_tirJoueur_ennemi(liste_tirs_joueur listeTJ, liste_ennemis listeE, joueur j1)
{
	tirs_joueur TJactuel = listeTJ->tete;
	ennemi Eactuel;
	while (TJactuel != NULL)
	{
		Eactuel = listeE->tete;
		while(Eactuel != NULL)
		{
			if(TJactuel->x == Eactuel->x && TJactuel->y == Eactuel->y)
			{
				TJactuel->vivant = false;                       //Si un tir joueur touche 
				Eactuel->vivant = false;                        //un ennemi
				supprimer_tirs_joueur(listeTJ, TJactuel);       //les deux sont supprimés
				supprimer_ennemi(listeE, Eactuel);              //et le score du joueur
				j1->score +=100;                                //augmente de 100 points
			}
				
				Eactuel = Eactuel->suivant;
		}
			
		TJactuel = TJactuel->suivant;
	}
}

//Gère la collision entre le joueur et les ennemis
void collision_joueur_ennemi(joueur j1, liste_ennemis listeE)
{
	ennemi Eactuel = listeE->tete;
	while(Eactuel != NULL)
	{
		if(Eactuel->x == j1->x && Eactuel->y == j1->y)
		{
			Eactuel->vivant = false;              //Si le joueur touche un ennemi
			supprimer_ennemi(listeE, Eactuel);    //l'ennemi est supprimé
			j1->vie--;                            //le joueur perd 1 point de vie
			j1->score -= 250;                     //et le score diminue de 250 points
		}
		Eactuel = Eactuel->suivant;
	}
}

//Gère la collision entre les tirs ennemis et le joueur
void collision_tirEnnemi_joueur(liste_tirs_ennemi listeTE, joueur j1)
{
	tirs_ennemi TEactuel = listeTE->tete;
	while(TEactuel != NULL)
	{
		if(TEactuel->x == j1->x && TEactuel->y == j1->y) 
		{
			TEactuel->vivant = false;                   //Si un tir ennemi touche le joueur
			supprimer_tirs_ennemi(listeTE, TEactuel);   //le tir ennemi est supprimé
			j1->vie--;                                  //le joueur perd 1 point de vie
			j1->score -= 250;                           //et le score diminue de 250 points
		}
		TEactuel = TEactuel->suivant;
	}
}

//Collision entre les tirs ennemis et les tirs joueur
void collision_tirJoueur_tirEnnemi(liste_tirs_joueur listeTJ, liste_tirs_ennemi listeTE)
{
	tirs_joueur TJactuel = listeTJ->tete;
	tirs_ennemi TEactuel;
	while (TJactuel != NULL)
	{
		TEactuel = listeTE->tete;
		while(TEactuel != NULL)
		{
			if((TJactuel->x == TEactuel->x || TJactuel->x - TEactuel->x == 1) && TJactuel->y == TEactuel->y)
			{
				TJactuel->vivant = false;                    //Si un tir joueur rencontre un tir ennemi
				supprimer_tirs_joueur(listeTJ, TJactuel);    //le tir joueur est supprimé et 
			}                                                   //le tir ennemi continue sa route
				
				TEactuel = TEactuel->suivant;
		}
			
		TJactuel = TJactuel->suivant;
	}
}

//Fonction comprenant toutes les fonctions de collision
void collisions(liste_tirs_joueur listeTJ, liste_ennemis listeE, joueur j1, liste_tirs_ennemi listeTE)
{
	collision_tirJoueur_ennemi(listeTJ, listeE, j1);   //Vérification des
	collision_joueur_ennemi(j1, listeE);               //collisions sur une seule fonction
	collision_tirEnnemi_joueur(listeTE, j1);           //afin de ne pas surcharger
	collision_tirJoueur_tirEnnemi(listeTJ, listeTE);   //la fonction game dans game.c
}	                                                   
