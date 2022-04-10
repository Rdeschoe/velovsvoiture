#ifndef _DECOR_H_
#define _DECOR_H_

#include <stdio.h>
#include <stdlib.h>


/*Structures utilisées pour la liste chainée des décors*/
struct decor
{
	int x;
	int y;
	char id; //Permettra de déterminer quel décor doit être affiché
	struct decor *suivant;
};

struct liste_decor
{
	struct decor *tete;
};

typedef struct decor *decor;
typedef struct liste_decor *liste_decor;
/*-----------------------------------------------------*/

liste_decor initialisation_decor();                              //Initialiser la liste des décors
void insertion_decor(liste_decor listeD, int x, int y, char id); //Ajouter un décor à la liste
void scrolling_decor(liste_decor listeD);                        //effectuer le scrolling des decors

#endif
