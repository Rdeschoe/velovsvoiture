#ifndef _SHOTS_H_
#define _SHOTS_H_

#include <stdbool.h>

#include "player.h"
#include "ennemies.h"

/*Structures utilisées pour la liste chainée des tirs joueur*/
struct tirs_joueur
{
	int x;
	int y;
	bool vivant; //Utiliser dans la fonction supprimant des tirs de la liste
	struct tirs_joueur *suivant;
};

struct liste_tirs_joueur
{
	struct tirs_joueur *tete;
};

typedef struct tirs_joueur *tirs_joueur;
typedef struct liste_tirs_joueur *liste_tirs_joueur;



/*Structures utilisées pour la liste chainée des tirs ennemis*/

struct tirs_ennemi
{
	int x;
	int y;
	bool vivant; //Utiliser dans la fonction supprimant des tirs de la liste
	struct tirs_ennemi *suivant;
};

struct liste_tirs_ennemi
{
	struct tirs_ennemi *tete;
};

typedef struct tirs_ennemi *tirs_ennemi;
typedef struct liste_tirs_ennemi *liste_tirs_ennemi;



liste_tirs_joueur initialisation_tirs_joueur();                                 //Initialise la liste des tirs joueur
void insertion_tirs_joueur(liste_tirs_joueur listeTJ,joueur j1);                //Ajouter un tir à la liste des tirs joueur
void supprimer_tirs_joueur(liste_tirs_joueur listeTJ, tirs_joueur a_supprimer); //Supprime un tir de la liste des tirs joueur
void avance_tirs_joueur(liste_tirs_joueur listeTJ, joueur j1);                  //Avance d'un carré les tirs joueur


liste_tirs_ennemi initialisation_tirs_ennemi();                                 //Initialise la liste des tirs ennemis
void insertion_tirs_ennemi(liste_tirs_ennemi listeTE, ennemi actuel);           //Ajouter un tir à la liste des tirs ennemis
void avance_tirs_ennemi(liste_tirs_ennemi listeTE);                             //Supprime un tir de la liste des tirs ennemis
void supprimer_tirs_ennemi(liste_tirs_ennemi listeTE, tirs_ennemi a_supprimer); //Avance d'un carré les tirs ennemis


#endif
