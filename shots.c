#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "loadMap.h"
#include "shots.h"
#include "ennemies.h"
#include "player.h"

/*____________________________________________________________*/
/*______________________TIRS_JOUEUR___________________________*/
/*____________________________________________________________*/

//Initialiser la liste des tirs du joueur
liste_tirs_joueur initialisation_tirs_joueur()
{
	liste_tirs_joueur listeTJ = malloc(sizeof(liste_tirs_joueur));
	if(listeTJ==NULL)
	{
		exit(EXIT_FAILURE);
	}
	listeTJ->tete = NULL;
	
	return listeTJ;
}

//Ajouter un tir à la liste des tirs du joueur
void insertion_tirs_joueur(liste_tirs_joueur listeTJ, joueur j1)
{
	tirs_joueur nouveau = malloc(sizeof(nouveau));
	if (nouveau == NULL)
	{
		exit(EXIT_FAILURE);
	}
	
	nouveau->x = j1->x-1;  //Positionné juste au dessus du joueur
	nouveau->y = j1->y;
	nouveau->vivant = true; //Utilisé dans la fonction supprimant des tirs de la liste
	
	nouveau->suivant = listeTJ->tete;
	listeTJ->tete = nouveau;
}

//Avancer d'un cran les tirs du joueur
void avance_tirs_joueur(liste_tirs_joueur listeTJ, joueur j1)
{
	tirs_joueur actuel = listeTJ->tete;
	while (actuel != NULL)
	{
		actuel->x--;
		if(actuel->x < 0)      //Si le tir atteint le bord supérieur de la map, on le supprime
		{
			actuel->vivant = false;
			supprimer_tirs_joueur(listeTJ, actuel);
			j1->score -=1;  //Diminution du score de 1 si tir non précis
		}
		actuel = actuel->suivant;
	}
}

//Supprimer un tir du joueur
void supprimer_tirs_joueur(liste_tirs_joueur listeTJ, tirs_joueur a_supprimer)
{

	if(listeTJ->tete == a_supprimer)
	{
		listeTJ->tete = listeTJ->tete->suivant;
		free(a_supprimer);
	}
	else
	{
		tirs_joueur actuel = listeTJ->tete;
		while(actuel->suivant->vivant)
		{
			actuel = actuel->suivant;
		}
		actuel->suivant = a_supprimer->suivant;
		free(a_supprimer);
	}	
}

/*____________________________________________________________*/
/*______________________TIRS_ENNEMI___________________________*/
/*____________________________________________________________*/

//Initialiser la liste des tirs des ennemis
liste_tirs_ennemi initialisation_tirs_ennemi()
{
	liste_tirs_ennemi listeTE = malloc(sizeof(liste_tirs_ennemi));
	if(listeTE==NULL)
	{
		exit(EXIT_FAILURE);
	}
	listeTE->tete = NULL;
	
	return listeTE;
}
	
//Ajouter un tir à la liste des tirs des ennemis
void insertion_tirs_ennemi(liste_tirs_ennemi listeTE, ennemi tireur)
{
	tirs_ennemi nouveau = malloc(sizeof(nouveau));
	if (nouveau == NULL)
	{
		exit(EXIT_FAILURE);
	}
	
	nouveau->x = tireur->x+1; //Positionné juste en dessous de l'ennemi
	nouveau->y = tireur->y;
	nouveau->vivant = true;   //Utilisé dans la fonction supprimant des tirs de la liste
	
	nouveau->suivant = listeTE->tete;
	listeTE->tete = nouveau;
}

//Avancer d'un cran les tirs des ennemis
void avance_tirs_ennemi(liste_tirs_ennemi listeTE)
{
	tirs_ennemi actuel = listeTE->tete;
	while (actuel != NULL)
	{
		actuel->x++;
		if(actuel->x > 30) //Si le tir atteint le bord inférieur de la map, on le supprime
		{
			actuel->vivant = false;
			supprimer_tirs_ennemi(listeTE, actuel);
		}
		actuel = actuel->suivant;
	}
}

//Supprimer un tir ennemi
void supprimer_tirs_ennemi(liste_tirs_ennemi listeTE, tirs_ennemi a_supprimer)
{

	if(listeTE->tete == a_supprimer)
	{
		listeTE->tete = listeTE->tete->suivant;
		free(a_supprimer);
	}
	else
	{
		tirs_ennemi actuel = listeTE->tete;
		while(actuel->suivant->vivant)
		{
			actuel = actuel->suivant;
		}
		actuel->suivant = a_supprimer->suivant;
		free(a_supprimer);
	}	
}
