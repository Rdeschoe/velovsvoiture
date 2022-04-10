#ifndef _COLLISIONS_H_
#define _COLLISIONS_H_

#include <stdio.h>
#include <stdlib.h>

#include "shots.h"
#include "ennemies.h"
#include "player.h"


void collision_tirJoueur_ennemi(liste_tirs_joueur listeTJ, liste_ennemis listeE, joueur j1); //Gère les collisions entre les tirs joueur et les tirs ennemis
void collision_joueur_ennemi(joueur j1, liste_ennemis listeE);                               //Gère les collisions entre le joueur et les ennemis
void collision_tirEnnemi_joueur(liste_tirs_ennemi listeT_E, joueur j1);                      //Gère les collisions entre les tirs ennemis et le joueur
void collision_tirJoueur_tirEnnemi(liste_tirs_joueur listeTJ, liste_tirs_ennemi listeT_E);   //Gère les collisions entre les tirs joueur et les tirs ennemis

//Fonction comprenant toutes les fonctions de collision
void collisions(liste_tirs_joueur listeTJ, liste_ennemis listeE, joueur j1, liste_tirs_ennemi listeTE);



#endif
