#ifndef _DRAWMAP_H_
#define _DRAWMAP_H_


#include "decor.h"
#include "shots.h"
#include "ennemies.h"


void afficher_map(int nb_lin, int nb_col, liste_decor listeD); //afficher la map
void afficher_joueur(joueur j1);                               //afficher le joueur
void afficher_tirs_joueur(liste_tirs_joueur listeTJ);          //afficher les tirs joueurs
void afficher_tirs_ennemi(liste_tirs_ennemi listeT_E);         //afficher les tirs ennemis
void afficher_ennemis(liste_ennemis listeE);                   //afficher les ennemis
void afficher_decor(liste_decor listeD);                       //afficher les décors
void affichage_score(joueur j1);                               //affichage du score du joueur
void affichage_vie(joueur j1);                                 //affichage de la vie du joueur

//Fonction comprenant toutes les fonctions d'affichage
void maj_affichage(int nb_lin, int nb_col, liste_decor listeD, joueur j1, liste_tirs_joueur listeTJ, liste_ennemis listeE, liste_tirs_ennemi listeTE);

#endif
