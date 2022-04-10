#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "loadMap.h"
#include "decor.h"

//Initialiser la liste des décors
liste_decor initialisation_decor()
{
	liste_decor listeD = malloc(sizeof(liste_decor));
	if(listeD==NULL)
	{
		exit(EXIT_FAILURE);
	}
	listeD->tete = NULL;
	
	return listeD;
}

//Ajouter un décor à la liste
void insertion_decor(liste_decor listeD, int x, int y, char id)
{
	decor nouveau = malloc(sizeof(nouveau));
	if (nouveau == NULL)
	{
		exit(EXIT_FAILURE);
	}
	
	nouveau->x = x;
	nouveau->y = y;
	nouveau->id = id; //id permettant de déterminer quel type de décor afficher
	
	nouveau->suivant = listeD->tete;
	listeD->tete = nouveau;
}

//Scrolling decor
void scrolling_decor(liste_decor listeD)
{
	decor Dactuel = listeD->tete;
	while (Dactuel != NULL)
	{
		Dactuel->x++;
		if(Dactuel->x == 31)
		{
			Dactuel->x = 1;  //S'il arrive en bas de l'écran, le décor est remonté en haut de l'écran.
		}
		Dactuel = Dactuel->suivant;
	}
}

