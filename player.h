#ifndef _PLAYER_H_
#define _PLAYER_H_
#include <stdbool.h> 

//Structure caractérisant le joueur
struct joueur
{
	int x;
	int y;
	int vie;
	int score;
};
typedef struct joueur *joueur;



joueur creer_joueur(int nb_lin, int nb_col); //Créer le joueur
void mouvement_gauche(joueur j1);            //Déplacer le joueur vers la gauche
void mouvement_droite(joueur j1);            //Déplacer le joueur vers la droite
void mouvement_haut(joueur j1);              //Déplacer le joueur vers le haut
void mouvement_bas(joueur j1);               //Déplacer le joueur vers le bas

#endif
