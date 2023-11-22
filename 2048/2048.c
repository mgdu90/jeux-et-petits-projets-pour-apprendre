#include <stdio.h>
#include <stdlib.h>
#include "normal.h"
#include "duo.h"
#include "puzzle.h"
 
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
		puzzle();
	return 0;
}
