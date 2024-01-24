#include "head.h"

int **auto_gen(){
	int **grid;
	grid = (int **)malloc(GRID * sizeof(int *));
	for(int i = 0; i < GRID; i++){
		grid[i] = (int *)malloc(GRID * sizeof(int));
	}
	int ran;
	srand((unsigned)time(NULL));
	for(i = 0; i < GRID; i++){
		for(int j = 0; j < GRID; j++){
			ran = rand() % 10;
			if(ran <= INCIDENCE) grid[i][j] = 1;
			else grid[i][j] = 0;
		}
	}
	printf("Input: \n");
	for(i = 0; i < GRID; i++){
		for(int j = 0; j < GRID; j++){
			if(i == SX && j == SY) printf("S ");
			else if(i == TX && j == TY) printf("T ");
			else if(grid[i][j] == 1) printf("B ");
			else printf(". ");
		}
		printf("\n");
	}
	return grid;
}