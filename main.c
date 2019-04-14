#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include "fileOperations.h"
#include "generation.h"
#include "rules.h"

int main(int argc, char** argv) {
    if(argc != 4) {
        printf("Please launch the program with three arguments! Exiting program...\n");
        return(1);
    }
    //declaring variables from arguments
    char* inputfilename = (char*)malloc(30*sizeof(char));
    char* folderName = (char*)malloc(30*sizeof(char));
    inputfilename = argv[1];
    int genNumber = atoi(argv[2]);
    folderName = argv[3];
    mkdir(folderName,0700);

    //reading number of columns and rows from a file
    int r = 0, c = 0;
    int sizeResult = getSize(inputfilename, &r, &c);

    //creating states matrix, neighbours matrix and ascii format matrix
    int smatrix[r][c];
    int* smatrix_p = &smatrix[0][0];
    int nmatrix[r][c];
    int* nmatrix_p = &nmatrix[0][0];
    char ascii[r][c];
    char* ascii_p = &ascii[0][0];

    //filling states matrix
    int fillResult = fillStatesMatrix(inputfilename, smatrix_p, r, c);

    //if no errors occurred while filling the matrix, generate all the descendants
    if (fillResult == 0 && sizeResult==0 ) {
 	printf("starting generation.c ...\n");
        generateGeneration(smatrix_p, nmatrix_p, r, c, genNumber, ascii_p, folderName);
        //the final generation is saved both into ASCII format and binary
        saveFinalGrid(smatrix_p, r, c, folderName);
    }
    return 0;
}
