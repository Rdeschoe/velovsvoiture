#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "loadMap.h"
		

//Permet de charger la map contenue dans un fichier texte
bool loadMap(int nb_lin, int nb_col)
{
	map = malloc(sizeof(char *) * nb_lin);
	
	FILE *f = NULL;
	f = fopen("map1.txt", "r");
	if(f == NULL)
	{
		printf("Fichier vide");
		return false;
	}
	
	char c; //variable qui va permettre d'enregistrer les caractères situées dans le fichier .txt
	
	int i = 0;
	int j = 0;
	
	*(map+i) = malloc(sizeof(char *) * nb_col);
	for(i=0;i<nb_lin;i++)
	{
		*(map+i) = malloc(sizeof(char *) * nb_col);
		for(j=0;j<nb_col+1;j++)
		{
			c = fgetc(f);
			*(*(map+i)+j) = c;
		}
		fgetc(f);
	}
	fclose(f);
	
	return true;
}
		
