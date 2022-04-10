#ifndef _LOADMAP_H_
#define _LOADMAP_H_

#include <stdbool.h>

#define Square_size 25.0 //Définition de la taille des carrés représentant les éléments du jeu

char **map; //Déclaration de la map

bool loadMap(int nb_lin, int nb_col); //Charge la map de manière dynamique

#endif
