#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>

void display(int** mat, int abs, int ord, int* cursor)
{
	system("clear");
	for(int y = 0; y < ord; y++)
	{
		for(int x = 0; x < abs; x++)
		{
			if(x == cursor[0] && y == cursor[1])
			{
				if(mat[y][x] == 1)
				{
					printf("\x1b[31m@\x1b[0m "); // printing in color
				}
				else
				{
					printf("\x1b[31m.\x1b[0m "); // printing in color
				}
			}
			else
				if(mat[y][x] == 1)
				{
					printf("@ ");
				}
				else
				{
					printf(". ");
				}
		}
		printf("\n");
	}
	printf("\npress escape to exit\n");
	printf("press the ZQSD keys to move the cursor\n");
	printf("press enter to move on the next generation");
}

void next_geneartion(int** mat, int abs, int ord)
{
	int** temporary_matrix = malloc(ord * sizeof(int*));
	for(int i = 0; i < ord; i++)
	{
		temporary_matrix[i] = calloc(abs, sizeof(int));
	}

	for(int y = 0; y < ord; y++)
	{
		for(int x = 0; x < abs; x++)
		{
			int acc = 0;

			// treatment of the four corners
			if(y == 0 && x == 0)
			{
				if(mat[y+1][x] == 1) acc++;
				if(mat[y+1][x+1] == 1) acc++;
				if(mat[y][x+1] == 1) acc++;
			}
			if(y == 0 && x == abs-1)
			{
				if(mat[y+1][x] == 1) acc++;
				if(mat[y+1][x-1] == 1) acc++;
				if(mat[y][x-1] == 1) acc++;
			}
			if(y == ord-1 && x == 0)
			{
				if(mat[y][x+1] == 1) acc++;
				if(mat[y-1][x+1] == 1) acc++;
				if(mat[y-1][x] == 1) acc++;
			}
			if(y == ord-1 && x == abs-1)
			{
				if(mat[y-1][x] == 1) acc++;
				if(mat[y-1][x-1] == 1) acc++;
				if(mat[y][x-1] == 1) acc++;
			}

			// treatment of the four edges 
			if(y == 0 && x != abs-1 && x != 0)
			{
				if(mat[y][x-1] == 1) acc++;
				if(mat[y+1][x-1] == 1) acc++;
				if(mat[y+1][x] == 1) acc++;
				if(mat[y+1][x+1] == 1) acc++;
				if(mat[y][x+1] == 1) acc++;
			}
			if(y == ord-1 && x != abs-1 && x != 0)
			{
				if(mat[y][x-1] == 1) acc++;
				if(mat[y-1][x-1] == 1) acc++;
				if(mat[y-1][x] == 1) acc++;
				if(mat[y-1][x+1] == 1) acc++;
				if(mat[y][x+1] == 1) acc++;
			}
			if(x == 0 && y != ord-1 && y != 0)
			{
				if(mat[y-1][x] == 1) acc++;
				if(mat[y-1][x+1] == 1) acc++;
				if(mat[y][x+1] == 1) acc++;
				if(mat[y+1][x+1] == 1) acc++;
				if(mat[y+1][x] == 1) acc++;
			}
			if(x == abs-1 && y != ord-1 && y != 0)
			{
				if(mat[y-1][x] == 1) acc++;
				if(mat[y-1][x-1] == 1) acc++;
				if(mat[y][x-1] == 1) acc++;
				if(mat[y+1][x-1] == 1) acc++;
				if(mat[y+1][x] == 1) acc++;
			}

			// treatment of the center 
			if(x != 0 && x != abs-1 && y != 0 && y != ord-1)
			{
				if(mat[y-1][x] == 1) acc++;
				if(mat[y-1][x-1] == 1) acc++;
				if(mat[y-1][x+1] == 1) acc++;
				if(mat[y][x-1] == 1) acc++;
				if(mat[y][x+1] == 1) acc++;
				if(mat[y+1][x] == 1) acc++;
				if(mat[y+1][x-1] == 1) acc++;
				if(mat[y+1][x+1] == 1) acc++;
			}

			// applying the rules of the game
			if(mat[y][x] == 0 && acc == 3)
			{
				temporary_matrix[y][x] = 1;
			}
			else if(mat[y][x] == 1 && acc != 2 && acc != 3)
			{
				temporary_matrix[y][x] = 0;
			}
			else
			{
				temporary_matrix[y][x] = mat[y][x];
			}
		}
	}
	
	// copy the new matrix into the old to replace it
	for(int y = 0; y < ord; y++)
	{
		for(int x = 0; x < abs; x++)
		{
			mat[y][x] = temporary_matrix[y][x];
		}
	}

	// freeing the memory
	for(int y = 0; y < ord; y++)
	{
		free(temporary_matrix[y]);
	}
	free(temporary_matrix);
}

int main(void)
{
	int x, y;
	printf("enter the dimensions of the grid (greater than 3x3) in the form :\n<width> <height>\n");
	scanf("%d %d", &x, &y);

	int** matrix = malloc(y * sizeof(int*));
	for(int i = 0; i < y; i++)
	{
		matrix[i] = calloc(x, sizeof(int));
	}
	int* cursor = calloc(2, sizeof(int));

   	for(;;)
   	{
   		char ch;
		struct termios oldt, newt;

		// saving the terminal settings
		tcgetattr(STDIN_FILENO, &oldt);
		newt = oldt;
		newt.c_lflag &= ~(ICANON | ECHO);
		tcsetattr(STDIN_FILENO, TCSANOW, &newt);

		// character reading
		ch = getchar();

		// restoring terminal settings
		tcsetattr(STDIN_FILENO, TCSANOW, &oldt);

		// treatment of the key pressed
		switch (ch) 
		{
			case 'z':
				if(cursor[1] > 0)
				{
					cursor[1]--;
				}
				break;
			case 's':
				if(cursor[1] < y-1)
				{
					cursor[1]++;
				}
				break;
			case 'q':
				if(cursor[0] > 0)
				{
					cursor[0]--;
				}
				break;
			case 'd':
				if(cursor[0] < x-1)
				{
					cursor[0]++;
				}
				break;
			case ' ':
				if(matrix[cursor[1]][cursor[0]] == 0)
				{
					matrix[cursor[1]][cursor[0]] = 1;
				}
				else if(matrix[cursor[1]][cursor[0]] == 1)
				{
					matrix[cursor[1]][cursor[0]] = 0;
				}
				break;
			case 27: // escape character 
				printf("\n");
				for(int i = 0; i < y; i++)
				{
					free(matrix[i]);
				}
				free(matrix);
				return 0;
			case '\n':
				next_geneartion(matrix, x, y);
				break;
			default:
				break;
		}
		display(matrix, x, y, cursor);
	}
	return 0;
}