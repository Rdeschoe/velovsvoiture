#ifndef _ENNEMIES_H_
#define _ENNEMIES_H_

#include <stdbool.h>

/*Structures utilisées pour la liste chainée des ennemis*/
struct ennemi
{
	int x;
	int y;
	bool vivant; //variable utilisée dans la fonction supprimant les ennemis
	struct ennemi *suivant;
};

struct liste_ennemis
{
	struct ennemi *tete;
};

typedef struct ennemi *ennemi;
typedef struct liste_ennemis *liste_ennemis;
/*------------------------------------------------------*/



liste_ennemis initialisation_ennemis();                          //Initialisé la liste des ennemis
void insertion_ennemi(liste_ennemis listeE);                     //Ajouter un ennemi à la liste
void supprimer_ennemi(liste_ennemis listeE, ennemi a_supprimer); //Supprimer un ennemi de la liste                  
void mouvement_ennemi(liste_ennemis listeE);                     //Déplacements des ennemis
void scrolling_ennemi(liste_ennemis listeE, joueur j1);          //effectuer le scrolling des ennemis


#endif
