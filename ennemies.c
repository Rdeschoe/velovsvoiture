#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#include "loadMap.h"
#include "player.h"
#include "ennemies.h"

//Initilisation de la liste des ennemis
liste_ennemis initialisation_ennemis()
{
	liste_ennemis listeE = malloc(sizeof(liste_ennemis));
	if(listeE==NULL)
	{
		exit(EXIT_FAILURE);
	}
	listeE->tete = NULL;
	
	return listeE;
}

//Ajouter un ennemi à la liste
void insertion_ennemi(liste_ennemis listeE)
{
	ennemi nouveau = malloc(sizeof(nouveau));
	if (nouveau == NULL)
	{
		exit(EXIT_FAILURE);
	}
	
	int y = rand()%18;  //La route fait 18 carrés de largeur et apparition aléatoire sur l'un de ces 18 carrés.
	
	nouveau->x = 1;   //Apparaît toujours sur la limite supérieure de la route
	nouveau->y = y+8; //+8 pour ne pas apparaître dans les 8 carrés de décors sur la gauche de la map
	nouveau->vivant = true; //Utilisé dans la fonction supprimant des ennemis de la liste
	
	nouveau->suivant = listeE->tete;
	listeE->tete = nouveau;
}

//Supprimer un ennemi de la liste
void supprimer_ennemi(liste_ennemis listeE, ennemi a_supprimer)
{
	if(listeE->tete == a_supprimer)
	{
		listeE->tete = listeE->tete->suivant;
		free(a_supprimer);
	}
	else
	{
		ennemi actuel = listeE->tete;
		while(actuel->suivant->vivant)
		{
			actuel = actuel->suivant;
		}
		actuel->suivant = a_supprimer->suivant;
		free(a_supprimer);
	}		
}

//Mouvement des ennemis
void mouvement_ennemi(liste_ennemis listeE)
{
	
	ennemi actuel = listeE->tete;
	while (actuel != NULL)
	{
		int mouvement = rand()%3; // 3 possibilités tous les X temps (voir timer 1)
		switch(mouvement)
		{
			case 0 :                           //Ne bouge pas
			break;
			
			case 1 :
			if(actuel->y+1 != 26)actuel->y++;  //Se déplace d'un carré vers la droite si possible
			break;
			
			case 2 :
			if(actuel->y-1 != 7)actuel->y--;   //Se déplace d'un carré vers la gauche si possible
			break;
		}
		actuel = actuel->suivant;
	}
}

//Scrolling ennemi
void scrolling_ennemi(liste_ennemis listeE, joueur j1)
{
	ennemi Eactuel = listeE->tete;
	while (Eactuel != NULL)
	{
		Eactuel->x++;
		if(Eactuel->x > 30)      //On supprime l'ennemi s'il atteint la limite inférieure de la map
		{
			Eactuel->vivant = false;
			supprimer_ennemi(listeE, Eactuel);
			j1->score -= 100; //Le joueur perd 100 points s'il laisse un ennemi sortir de la map
		}
		Eactuel = Eactuel->suivant;
	}
}
