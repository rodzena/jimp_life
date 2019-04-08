#include <stdio.h>
#include <stdlib.h>
//#include "fileOperations.c"
//#include "generation.c"
#include "rules.h"
#include "fileOperations.h"
#include "generation.h"

void readArguments(int argc, char** argv) {
    printf("siemaa\n");
    for(int i = 1; i < argc; i++) {
        printf("argument %d: %s\n", i, argv[i]);
    }
}

int main(int argc, char** argv)
{
    readArguments(argc, argv);
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
    int fillResult = fillStatesMatrix(inputfilename, smatrix_p, r, c);
    //showing states matrix

    if (fillResult == 0)
    {
        printf("states matrix read from file:\n");
        for(int i = 0; i < r; i++)
        {
            for(int j =0 ; j < c; j++)
            {
                printf("%d ", smatrix[i][j]);
            }
            printf("\n");
        }

        //filling neighbours matrix
        generateNeighbours(smatrix_p, nmatrix_p, r, c);

        //showing neighbours matrix
        printf("neighbours matrix:\n");
        for(int k = 0; k < r; k++)
        {
            for(int l =0 ; l < c; l++)
            {
                printf("%d ", nmatrix[k][l]);
            }
            printf("\n");
        }
        //overwriting states matrix with new generation
        generateGeneration(smatrix_p, nmatrix_p, r, c);

        //showing new generation matrix
        printf("new neighbours matrix:\n");
        for(int m = 0; m < r; m++)
        {
            for(int n = 0; n < c; n++)
            {
                printf("%d ", smatrix[m][n]);
            }
            printf("\n");
        }
    }
    system("pause");
    return 0;
}
