#include <stdio.h>
#include <stdlib.h>
#include "rules.h"
#include "fileOperations.h"
#include "generation.h"
#include "main.h"

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

    if (fillResult == 0)
    {
        printf("states matrix read from file:\n");
        showMatrix(smatrix_p, r, c);

        generateGeneration(smatrix_p, nmatrix_p, r, c, 3);

    }
    system("pause");
    return 0;
}

void showMatrix (int* matrix, int r, int c) {
    for(int i = 0; i < r; i++) {
        for(int j = 0; j < c; j++) {
            printf("%d ", *(matrix + i * r + j));
        }
        printf("\n");
    }
}

void readArguments(int argc, char** argv) {
    printf("siemaa\n");
    for(int i = 1; i < argc; i++) {
        printf("argument %d: %s\n", i, argv[i]);
    }
}