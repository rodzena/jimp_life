#include <stdio.h>
#include <stdlib.h>
#include "rules.h"
#include "fileOperations.h"
#include "generation.h"
#include <sys/stat.h>
#include <sys/types.h>

int main(int argc, char** argv)
{
    if(argc != 5)
    {
        printf("Please launch the program with three arguments! Exiting program...\n");
        system("pause");
        exit(0);
    }
    else
    {
        //declaring variables
        char* inputfilename = (char*)malloc(30*sizeof(char));
        inputfilename = argv[1];

        int genNumber = atoi(argv[2]);

        char* folderName = (char*)malloc(30*sizeof(char));
        folderName = argv[3];
        mkdir(folderName);

        int pause = atoi(argv[4]);
        int r = 0, c = 0;

        //reading number of columns and rows from a file
        getSize(inputfilename, &r, &c);

        //creating states matrix, neighbours matrix and ascii format matrix
        //int smatrix[r][c];
        int* smatrix_p = (int*)malloc(10000*sizeof(int));
        //int nmatrix[r][c];
        int* nmatrix_p = (int*)malloc(10000*sizeof(int));


        //int* nmatrix_p = &nmatrix[0][0];
        char ascii[r][c];
        char* ascii_p = &ascii[0][0];

        //filling states matrix
        int fillResult = fillStatesMatrix(inputfilename, smatrix_p, r, c);

        //if no errors occurred while filling the matrix, generate all the descendants
        if (fillResult == 0)
        {
            generateGeneration(smatrix_p, nmatrix_p, r, c, genNumber, ascii_p, folderName, pause);

            //the final generation is saved both into ASCII format and binary
            saveFinalGrid(smatrix_p, r, c, folderName);
        }

        printf("\n\n");


    }
    system("pause");
    return 0;
}
