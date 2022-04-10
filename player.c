#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "player.h"
#include "loadMap.h"

//Créer le personnage joueur
joueur creer_joueur(int nb_lin, int nb_col)
{
	joueur j1;
	j1 = malloc(sizeof(joueur));
	j1->vie = 3;
	j1->score = 0;
	
	int x,y;

	for(x=0;x<nb_lin;x++)
	{
		for(y=0;y<nb_lin;y++)
		{
			if(*(*(map + x) + y) == 'p')  //récupérer la position grâce au caractère "p" chargé dans la map
			{
				j1->x = x;
				j1->y = y;
			}
		}
	}

	return j1;
}

//Déplacer le joueur vers la gauche
void mouvement_gauche(joueur j1)
{
	if(j1->y-1 != 7)j1->y--;  //Limite gauche de la route
}

//Déplacer le joueur vers la droite
void mouvement_droite(joueur j1)
{
	if(j1->y+1 != 26)j1->y++; //Limite droite de la route
}

//Déplacer le joueur vers le haut
void mouvement_haut(joueur j1)
{
	if(j1->x-1 != 0)j1->x--;  //Limite supérieure de la route
}

//Déplacer le joueur vers le bas
void mouvement_bas(joueur j1)
{
	if(j1->x+1 != 31)j1->x++; //Limite inférieure de la route
}	
