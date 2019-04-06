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
	//filling states and neighbours matrix
	fillStatesMatrix(inputfilename, psmatrix, r, c);
	generateNeighbours(psmatrix, pnmatrix, r, c);
	//processing generation
	generateGeneration(psmatrix, pnmatrix, r, c, 1);
	system("pause");
	return 0;
}