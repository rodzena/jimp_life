#include <stdio.h>
#include <stdlib.h>
#include "fileOperations.h"
#include "generation.h"
#include "rules.h"


int main()
{
    printf("Halko odbjur\n");
    //declaring variables
    char inputfilename[] = "test.txt";
    int r = 0, c = 0;

    //reading number of columns and rows from a file
    getSize(inputfilename, &r, &c);

    printf("r(ows) = %d\n", r);
    printf("c(olumns) = %d\n", c);


    //creating states and neighbours matrix
    int smatrix[r][c];
    int nmatrix[r][c];
    int* smatrix_p = &smatrix[0][0];
    int* nmatrix_p = &nmatrix[0][0];

    //filling states matrix
    int fillResult = fillStatesMatrix(inputfilename, smatrix_p, &r, &c);
    //showing states matrix

    if (fillResult == 0)
    {
        //filling states and neighbours matrix
	fillStatesMatrix(inputfilename, psmatrix, r, c);
	generateNeighbours(psmatrix, pnmatrix, r, c);
	//processing generation
	generateGeneration(psmatrix, pnmatrix, r, c, 1);
    }
    system("pause");
    return 0;
}
