#include <stdio.h>
#include <stdlib.h>
#include "fileOperation.c"
#include "generation.c"

int main() {
	printf("Halko odbjur\n");
	//declaring variables
	char inputfilename[] = "test.txt";
    int r = 0, c = 0;
	//reading number of columns and rows from a file
	readFile(inputfilename, &r, &c);
	printf("r(ows) = %d\n", r);
	printf("c(olumns) = %d\n", c);
	//creating states and neighbours matrix
	int smatrix[r][c];
	int nmatrix[r][c];
	int* psmatrix = &smatrix[0][0];
	int* pnmatrix = &nmatrix[0][0];
	//filling states matrix
	fillStatesMatrix(inputfilename, psmatrix, &r, &c);
	//showing states matrix
	printf("states matrix read from file:\n");
	for(int i = 0; i < r; i++) {
		for(int j =0 ; j < c; j++) {
			printf("%d ", smatrix[i][j]);
		}
		printf("\n");
	}
	//filling neighbours matrix
	generateNeighbours(psmatrix, pnmatrix, r, c);
	//showing neighbours matrix
	printf("neighbours matrix:\n");
	for(int k = 0; k < r; k++) {
		for(int l =0 ; l < c; l++) {
			printf("%d ", nmatrix[k][l]);
		}
		printf("\n");
	}
	//overwriting states matrix with new generation
	generateGeneration(psmatrix, pnmatrix, r, c);
	//showing new generation matrix
	printf("new neighbours matrix:\n");
	for(int m = 0; m < r; m++) {
		for(int n = 0; n < c; n++) {
			printf("%d ", smatrix[m][n]);
		}
	printf("\n");
	}
	system("pause");
	return 0;
}