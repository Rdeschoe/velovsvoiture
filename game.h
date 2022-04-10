#ifndef _GAME_H_
#define _GAME_H_

#include <stdio.h>
#include <stdlib.h>

#include "player.h"
#include "shots.h"
#include "ennemies.h"
#include "decor.h"


//Fonction principale du jeu. Appelle toutes les fonctions nécessaires au déroulement de celui-ci.
void game(int nb_lin, int nb_col, joueur j1, liste_tirs_joueur listeTJ, liste_ennemis listeE, liste_decor listeD, liste_tirs_ennemi listeTE); 

//Gestion des timers
void timer(int theTimer);


#endif
