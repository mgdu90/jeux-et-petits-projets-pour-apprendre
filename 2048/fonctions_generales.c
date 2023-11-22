#include <stdio.h>
#include "fonctions_generales.h"
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

int** init_matrix(int dim)
{
	// alloue un tableau de pointeurs, puis aloue chaque sous tableau
	int** matrix = (int**)malloc(dim * sizeof(int*));
	for(int i = 0; i < dim; i++)
	{
		matrix[i] = (int*)calloc(dim, sizeof(int));
	}
	return matrix;
}

void release_matrix(int** matrix, int dim)
{
	// libère chaque ligne/sous tableau, puis libère le tableau complet
	for(int i = 0; i < dim; i++)
	{
		free(matrix[i]);
	}
	free(matrix);
}

bool situation_bloquee(int** matrix, int dim)
{
	// l'idee est la suivante : 
	/*
	 * verifier qu'aucun coin n'est identique a une de ses valeur conitgue
	 * verifier que la grille n'a plus aucun 0
	 * verifier qu'aucune case du "tronc central" n'est identique a une de ses valeur conitgue
	 * verifier qu'aucune arete ne contient une case identique a une de ses valeur conitgue
	 */
	// il s'agit d'une tres grosse disjonction de cas, sa compréhension n'est pas utile a la compréhension 
	// du reste du code à part en cas de bug

	// coins
	if (   matrix[0][0] == matrix[0][1] || matrix[0][0] == matrix[1][0]
		|| matrix[0][dim-1] == matrix[0][dim-2] || matrix[0][dim-1] == matrix[1][dim-1]
		|| matrix[dim-1][0] == matrix[dim-1][1] || matrix[dim-1][0] == matrix[dim-2][0]
		|| matrix[dim-1][dim-1] == matrix[dim-1][dim-2] || matrix[dim-1][dim-1] == matrix[dim-2][dim-1])
	{
		return false;
	}

	// grille ne contint aucun 0
	for(int ord = 0; ord < dim; ord++)
	{
		for(int abs = 0; abs < dim; abs++)
		{
			if(matrix[ord][abs] == 0)
			{
				return false;
			}
		}
	}

	// "tronc central"
	for(int ord = 1; ord < dim-1; ord++)
	{
		for(int abs = 1; abs < dim-1; abs++)
		{
			if((	matrix[ord][abs] == matrix[ord+1][abs])
				|| (matrix[ord][abs] == matrix[ord-1][abs])
				|| (matrix[ord][abs] == matrix[ord][abs+1])
				|| (matrix[ord][abs] == matrix[ord][abs-1]))
			{
				return false;
			}
		}
	}

	// arêtes latérales
	for(int ord = 1; ord < dim-1; ord++)
	{
		if(	   matrix[ord][0] == matrix[ord][1] 
			|| matrix[ord][0] == matrix[ord-1][0]
			|| matrix[ord][0] == matrix[ord+1][0]
			|| matrix[ord][dim-1] == matrix[ord][dim-2] 
			|| matrix[ord][dim-1] == matrix[ord-1][dim-1]
			|| matrix[ord][dim-1] == matrix[ord+1][dim-1])
		{
			return false;
		}
	}

	// arêtes superieure et inferieure
	for(int abs = 1; abs < dim-1; abs++)
	{
		if(	   matrix[0][abs] == matrix[1][abs] 
			|| matrix[0][abs] == matrix[0][abs-1]
			|| matrix[0][abs] == matrix[0][abs+1]
			|| matrix[dim-1][abs] == matrix[dim-2][abs] 
			|| matrix[dim-1][abs] == matrix[dim-1][abs-1]
			|| matrix[dim-1][abs] == matrix[dim-1][abs+1])
		{
			return false;
		}
	}
	return true;
}

void affiche_grille(int** matrix, int dim)
{
	/*
	 * formattage de l'affichage en encadrant la grille, 
	 * en affichant pas les 0 et en mettant des separations
	 */
    printf("+----------------------------+\n");

    for (int i = 0; i < dim; i++)
    {
        printf("|");
        for (int j = 0; j < dim; j++)
        {
            if (matrix[i][j] == 0)
            {
                printf("     ");
            }
            else
            {
                printf("%-5d", matrix[i][j]);
            }
        }
        printf("|\n");
    }

    printf("+----------------------------+\n");
}

void affiche_2_grilles(int** matrix1, int** matrix2, int dim)
{
	/*
	 * formattage de l'affichage en encadrant les grilles, 
	 * en affichant pas les 0 et en mettant des separations
	 */
    printf("+---------------------------------------------------------------------------+\n");

    for (int i = 0; i < dim; i++)
    {
        printf("|");
        for (int j = 0; j < dim; j++)
        {
            if (matrix1[i][j] == 0)
            {
                printf("     ");
            }
            else
            {
                printf("%-5d", matrix1[i][j]);
            }
        }
        printf("|");
        printf("     ");
        printf("|");
        for (int j = 0; j < dim; j++)
        {
            if (matrix2[i][j] == 0)
            {
                printf("     ");
            }
            else
            {
                printf("%-5d", matrix2[i][j]);
            }
        }
        printf("|\n");
    }

    printf("+----------------------------------------------------------------------+\n");
}

void haut(int** matrix, int dim)
{
	// l'idee de l'algorithme est de sommer toutes les cases sommables sans se soucier de les "ecraser" en haut, puis de les "projeter" seulement ensuite
	for(int ord = 0; ord < dim; ord++) // parcourt de la grille de haut en bas pour traiter chaque ligne une a une
	{
		for(int abs = 0; abs < dim; abs++) // parcourt du sous tableau afin de traiter toutes les colonnes en meme temps
		{
			int case_courante = matrix[ord][abs];
			if(case_courante != 0)
			{
				int indice_case_suivante = ord+1;
				while(indice_case_suivante < dim)
				{
					int case_suivante = matrix[indice_case_suivante][abs];
					if(case_suivante != 0) // si on "trouve" une case non vide
					{
						if(case_courante == case_suivante) // si elle peut etre ajoutee a la precedente (case courante)
						{
							// on l'ajoute
							matrix[ord][abs] += matrix[indice_case_suivante][abs];
							matrix[indice_case_suivante][abs] = 0;
						}
						// et on passe a la case suivante (on traite d'abord les autres de la ligne)
						break;
					}
					// sinon on regarde celle d'apres ...
					indice_case_suivante++;
				}
			}
		}
	}

	// "projection orthogonale" des cases vers le haut
	for(int ord = 0; ord < dim-1; ord++)
	{
		for(int abs = 0; abs < dim; abs++)
		{
		int case_courante = matrix[ord][abs];
			if(case_courante == 0)
			{
				int indice_case_suivante = ord+1;
				while(indice_case_suivante < dim)
				{
					int case_suivante = matrix[indice_case_suivante][abs];
					if(case_suivante != 0)
					{
						matrix[ord][abs] = case_suivante;
						matrix[indice_case_suivante][abs] = 0;
						break;
					}
					indice_case_suivante++;
				}
			}
		}
	}
}

void gauche(int** matrix, int dim)
{
	/*
	 * l'idee etant la meme que dans la fonction move up, cette fonction et
	 * les 2 suivantes ne seront pas expliquees et commentees
	 */
	for(int i = 0; i < dim; i++)
	{
		for(int j = 0; j < dim; j++)
		{
			int case_courante = matrix[i][j];
			if(case_courante != 0)
			{
				int k = j+1;
				while(k < dim)
				{
					int case_suivante = matrix[i][k];
					if(case_suivante != 0)
					{
						if(case_courante == case_suivante)
						{
							matrix[i][j] += matrix[i][k];
							matrix[i][k] = 0;
						}
						break;
					}
					k++;
				}
			}
		}
	}

	for(int i = 0; i < dim; i++)
	{
		for(int j = 0; j < dim-1; j++)
		{
			int case_courante = matrix[i][j];
			if(case_courante == 0)
			{
				int k = j+1;
				while(k < dim)
				{
					int case_suivante = matrix[i][k];
					if(case_suivante != 0)
					{
						matrix[i][j] = case_suivante;
						matrix[i][k] = 0;
						break;
					}
					k++;
				}
			}
		}
	}
}

void droite(int** matrix, int dim)
{
	for(int i = 0; i < dim; i++)
	{
		for(int j = dim-1; j >= 0; j--)
		{
			int case_courante = matrix[i][j];
			if(case_courante != 0)
			{
				int k = j-1;
				while(k >= 0)
				{
					int case_suivante = matrix[i][k];
					if(case_suivante != 0)
					{
						if(case_courante == case_suivante)
						{
							matrix[i][j] += matrix[i][k];
							matrix[i][k] = 0;
						}
						break;
					}
					k--;
				}
			}
		}
	}

	for(int i = 0; i < dim; i++)
	{
		for(int j = dim-1; j > 0; j--)
		{
			int case_courante = matrix[i][j];
			if(case_courante == 0)
			{
				int k = j-1;
				while(k >= 0)
				{
					int case_suivante = matrix[i][k];
					if(case_suivante != 0)
					{
						matrix[i][j] = case_suivante;
						matrix[i][k] = 0;
						break;
					}
					k--;
				}
			}
		}
	}
}

void bas(int** matrix, int dim)
{
	for(int i = dim-1; i >= 0; i--)
	{
		for(int j = 0; j < dim; j++)
		{
			int case_courante = matrix[i][j];
			if(case_courante != 0)
			{
				int k = i-1;
				while(k >= 0)
				{
					int case_suivante = matrix[k][j];
					if(case_suivante != 0)
					{
						if(matrix[i][j] == matrix[k][j])
						{
							matrix[i][j]+=matrix[k][j];
							matrix[k][j]=0;
						}
						break;
					}
					k--;
				}
			}
		}
	}

	for(int i = dim-1; i > 0; i--)
	{
		for(int j = 0; j < dim; j++)
		{
			int case_courante = matrix[i][j];
			if(case_courante == 0)
			{
				int k = i-1;
				while(k >= 0)
				{
					int case_suivante = matrix[k][j];
					if(case_suivante != 0)
					{
						matrix[i][j]=case_suivante;
						matrix[k][j]=0;
						break;
					}
				k--;
				}
			}
		}
	}
}

void inserer_nombre(int** matrix, int dim)
{
	int availableSquares = 0;

	// compte les cases libres
	for(int ord = 0; ord < dim; ord++)
	{
		for(int abs = 0; abs < dim; abs++)
		{
			if(matrix[ord][abs] == 0)
			{
				availableSquares++;
			}
		}
	}

	// choisit aleatoirement une case libre
	int index = rand() % availableSquares;
	for(int ord = 0; ord < dim; ord++)
	{
		for(int abs = 0; abs < dim; abs++)
		{
			if(matrix[ord][abs] == 0)
			{
				if(index == 0)
				{
					if(rand() % 2 == 0)
					{
						matrix[ord][abs] = 4;
					}
					else
					{
						matrix[ord][abs] = 2;
					}
					return;
				}
				index--;
			}
		}
	}
}

bool partie_gagnee(int** matrix, int dim)
{
	bool gagne = false;
	for(int i = 0; i < dim; i++)
	{
		for(int j = 0; j < dim; j++)
		{
			if(matrix[i][j] == 2048)
			{
				gagne = true;
			}
		}
	}
	return gagne;
}

bool est_valid(int** matrix, int dim, char direction)
{
	bool valide = false;
	// creaton d'une matrice temporaire dans laquelle on copie la vraie grille et sur laquelle on va faire la transformation. on va ensuite comparer les 2 et si elles sont identiques, on retournera un booleen indiquant que le mouvement est invalide
	int** tmp_matrix = (int**)malloc(dim * sizeof(int*));
	for(int i = 0; i < dim; i++)
	{
		tmp_matrix[i] = (int*)calloc(dim, sizeof(int));
	}
	for(int i = 0; i < dim; i++)
	{
		for(int j = 0; j < dim; j++)
		{
			tmp_matrix[i][j] = matrix[i][j];
		}
	}

	// modification de la matrice temporaire
	// pas de default car la verification que la commande est valide a deja ete faite
	switch(direction)
	{
		case 'z':
		{
			haut(tmp_matrix, dim);
			break;
		}
		case 'q':
		{
			gauche(tmp_matrix, dim);
			break;
		}
		case 's':
		{
			bas(tmp_matrix, dim);
			break;
		}
		case 'd':
		{
			droite(tmp_matrix, dim);
			break;
		}
	}

	// comparaison des deux matrices
	for(int i = 0; i < dim; i++)
	{
		for(int j = 0; j < dim; j++)
		{
			if(tmp_matrix[i][j] != matrix[i][j])
			{
				valide = true; // si on trouve une case qui differe de l'autre grille, c'est que le mouvement a apporte une modification a la grille et que le mouvement etait valide
			}
		}
	}

	// liberation de la matrice temporaire
	for(int i = 0; i < dim; i++)
	{
		free(tmp_matrix[i]);
	}
	free(tmp_matrix);
	return valide;
}

bool normal()
{
	/*
	 * la fonction retourne un booleen indiquant si le joueur 
	 * ayant terminé sa partie veut rejouer
	 */

	// initialisation du generateur de nombres aleatoires
	srand(time(0));

	// demande de la taille de la grille à l'utilisateur sans message d'erreur
	printf("vous etes dans le mode normal\n");
	int taille;
	do
	{
		printf("veuillez entrer la taille de la grille sur laquelle vous voulez jouer, un entier naturel entre 4 et 9, bornes comprises\n");
		scanf("%d", &taille);
	}while(!(4 <= taille && taille<= 9));

	// initialisation de la grille
	int** grille = init_matrix(taille);

	// insertion des deux premiers nombres de la grille 
	inserer_nombre(grille, taille);
	inserer_nombre(grille, taille);

	system("clear"); // !! remplacer par cls sur windows !!
	// affichage de la premiere fenetre
	affiche_grille(grille, taille);

	while(!(situation_bloquee(grille, taille) || partie_gagnee(grille, taille)))
	{
		printf("veuillez indiquer la direction du deplacement (zqsd) : \n");
		char commande;
		getchar(); //finit de vider le buffer avans de lire un nouveau carater
		scanf("%c", &commande);
		fflush(stdin);
		if(est_valid(grille, taille, commande))
		{
			// traitement de la commande de l'utilisateur
			switch (commande)
			{
				case 'z':
				{
					system("clear"); // !! remplacer par cls sur windows !!
					haut(grille, taille);
					inserer_nombre(grille, taille);
					affiche_grille(grille, taille);
					break;
				}
				case 'q':
				{
					system("clear"); // !! remplacer par cls sur windows !!
					gauche(grille, taille);
					inserer_nombre(grille, taille);
					affiche_grille(grille, taille);
					break;
				}
				case 's':
				{
					system("clear"); // !! remplacer par cls sur windows !!
					bas(grille, taille);
					inserer_nombre(grille, taille);
					affiche_grille(grille, taille);
					break;
				}
				case 'd':
				{
					system("clear"); // !! remplacer par cls sur windows !!
					droite(grille, taille);
					inserer_nombre(grille, taille);
					affiche_grille(grille, taille);
					break;
				}
				default :
				{
					system("clear"); // !! remplacer par cls sur windows !!
					affiche_grille(grille, taille);
					printf("une entree valide est preferable au bon deroulement du jeu\n");
					break;
				}
			}
		}
		else
		{
			system("clear"); // !! remplacer par cls sur windows !!
			affiche_grille(grille, taille);
			printf("veuillez entrer une direction valide (faisant bouger des pieces)\n");
		}
	}

	// calcul du score
	int score = 0;
	for(int i = 0; i < taille; i++)
		for(int j = 0; j < taille; j++)
			score+=grille[i][j];

	// affichage de la victoire et de la defaite
	if(partie_gagnee(grille, taille))
	{
		printf("vous avez gagné, votre score est : %d\n", score);
	}
	else
	{
		printf("vous avez perdu :(, votre score est : %d\n", score);
	}

	// proposer une nouvelle partie en erournant sur un menu
	bool rejouer;
	printf("voulez vous rejouer ?\n1 : oui\n2 : non\n");
	int rejouer2;
	scanf("%d", &rejouer2);
	if (rejouer2 == 1)
		rejouer = true;
	else
		rejouer = false;

	// libération de la mémoire occupée
	release_matrix(grille, taille);
	return rejouer;
}

bool duo()
{
	/*
	 * la fonction retourne un booleen indiquant si le joueur 
	 * ayant terminé sa partie veut rejouer
	 */

	// initialisation du generateur de nombres aleatoires
	srand(time(0));

	// demande de la taille des grilles à l'utilisateur sans message d'erreur
	// les deux grilles auront les meme dimensions
	printf("vous etes dans le mode duo\n");
	int taille;
	do
	{
		printf("veuillez entrer la taille des grilles sur lesquelles vous voulez jouer, un entier naturel entre 4 et 9, bornes comprises\n");
		scanf("%d", &taille);
	}while(!(4 <= taille && taille<= 9));

	// initialisation des grilles
	int** grille1 = init_matrix(taille);
	int** grille2 = init_matrix(taille);

	// insertion des deux premiers nombres des grilles 
	inserer_nombre(grille1, taille);
	inserer_nombre(grille1, taille);
	inserer_nombre(grille2, taille);
	inserer_nombre(grille2, taille);

	system("clear"); // !! remplacer par cls sur windows !!
	// affichage de la premiere fenetre
	affiche_2_grilles(grille1, grille2, taille);

	while(!(situation_bloquee(grille1, taille) || partie_gagnee(grille1, taille) || 
		    situation_bloquee(grille2, taille) || partie_gagnee(grille2, taille)))
	{
		printf("veuillez indiquer la direction du deplacement (zqsd) : \n");
		char commande;
		getchar(); //finit de vider le buffer avans de lire un nouveau carater
		scanf("%c", &commande);
		fflush(stdin);
		if(est_valid(grille1, taille, commande) && est_valid(grille2, taille, commande))
		{
			// traitement de la commande de l'utilisateur
			switch (commande)
			{
				case 'z':
				{
					system("clear"); // !! remplacer par cls sur windows !!
					haut(grille1, taille);
					haut(grille2, taille);
					inserer_nombre(grille1, taille);
					inserer_nombre(grille2, taille);
					affiche_2_grilles(grille1, grille2, taille);
					break;
				}
				case 'q':
				{
					system("clear"); // !! remplacer par cls sur windows !!
					gauche(grille1, taille);
					gauche(grille2, taille);
					inserer_nombre(grille1, taille);
					inserer_nombre(grille2, taille);
					affiche_2_grilles(grille1, grille2, taille);
					break;
				}
				case 's':
				{
					system("clear"); // !! remplacer par cls sur windows !!
					bas(grille1, taille);
					bas(grille2, taille);
					inserer_nombre(grille1, taille);
					inserer_nombre(grille2, taille);
					affiche_2_grilles(grille1, grille2, taille);
					break;
				}
				case 'd':
				{
					system("clear"); // !! remplacer par cls sur windows !!
					droite(grille1, taille);
					droite(grille2, taille);
					inserer_nombre(grille1, taille);
					inserer_nombre(grille2, taille);
					affiche_2_grilles(grille1, grille2, taille);
					break;
				}
				default :
				{
					system("clear"); // !! remplacer par cls sur windows !!
					affiche_2_grilles(grille1, grille2, taille);
					printf("une entree valide est preferable au bon deroulement du jeu\n");
					break;
				}
			}
		}
		else
		{
			system("clear"); // !! remplacer par cls sur windows !!
			affiche_2_grilles(grille1, grille2, taille);
			printf("veuillez entrer une direction valide (faisant bouger des pieces sur les deux grilles)\n");
		}
	}

	// calcul du score
	int score1 = 0, score2 = 0;
	for(int i = 0; i < taille; i++)
	{
		for(int j = 0; j < taille; j++)
		{
			score1+=grille1[i][j];
			score2+=grille2[i][j];
		}
	}

	// affichage de la victoire et de la defaite
	if(partie_gagnee(grille1, taille))
	{
		printf("la grille 1 vous a fait gagner, les scores sont:\ngrille 1 : %d\ngrille 2 : %d\n", score1, score2);
	}
	else
	{
		printf("vous avez perdu :(, les scores sont:\ngrille 1 : %d\ngrille 2 : %d\n", score1, score2);
	}

	// proposer une nouvelle partie en erournant sur un menu
	bool rejouer;
	printf("voulez vous rejouer ?\n1 : oui\n2 : non\n");
	int rejouer2;
	scanf("%d", &rejouer2);
	if (rejouer2 == 1)
		rejouer = true;
	else
		rejouer = false;

	// libération de la mémoire occupée
	release_matrix(grille1, taille);
	release_matrix(grille2, taille);
	return rejouer;
}