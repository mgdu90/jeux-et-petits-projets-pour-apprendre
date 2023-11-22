#include <stdio.h>
#include <stdlib.h>
#include "fonctions_generales.h"

int main(void)
{
	//demande a l'utilisateur le mode de jeu dans lequel il veut jouer
	printf("MENU PRINCIPAL\n");
	printf("dans quel mode de jeu voulez vous jouer :\n");
	printf("\"n\" pour normal, \"d\" pour duo, \"p\" pour puzzle\n");
	char reponse;
	scanf("%c", &reponse);
	fflush(stdin);
	if(reponse == 'n')
		normal();
	if(reponse == 'd')
		duo();
	if(reponse == 'p')
		printf("hello world\n");
		//puzzle();
	return 0;
}