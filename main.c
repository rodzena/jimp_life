#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include "fileOperations.h"
#include "generation.h"
#include "rules.h"
#define MAX_FILE_NAME
#define MAXDIM 100

int main(int argc, char** argv) {
    if(argc != 4) {
        printf("Please launch the program with three arguments!\n");
        return(1);
    }
    else{
    char **p= (char**)calloc(10, sizeof(char));
    int x = strtol(argv[2] , p, 10); 
    int  genNumber = atoi(argv[2]);
    int i = 0;
    while(**p != '\0')
    {
	    if (**p == '0')
	    {
		    p++;
	    }
	    else
	    {
	   	 printf("Incorrect number of generations.\n");
	   	 return 1;
	    }
    }	

    free(p);
    //creates folder for output
    mkdir(argv[3],0700);

    //reading number of columns and rows from a file
    int r=0, c = 0;

    int sizeResult = getSize(argv[1], &r, &c);
    if (sizeResult == -1)
    {
	    return 1;
    }


    //reserving memory for states matrix, neighbours matrix and ascii format matrix
    int* smatrix = (int*)calloc(MAXDIM*MAXDIM,sizeof(smatrix));
    int* smatrix_p = smatrix;
    int* nmatrix = (int*)calloc(MAXDIM*MAXDIM,sizeof(nmatrix));
    int* nmatrix_p = nmatrix;
    char* ascii = (char*)calloc(MAXDIM*MAXDIM, sizeof(ascii));
    char* ascii_p = ascii;

    //filling states matrix
    int fillResult = fillStatesMatrix(argv[1], smatrix_p, r, c);

    //if no errors occurred while filling the matrix, generate all the descendants
    if (fillResult == 0 && sizeResult==0 ) {
        generateGeneration(smatrix_p, nmatrix_p, r, c, genNumber, ascii_p, argv[3]);

        //the final generation is saved both into ASCII format and binary
        saveFinalGrid(smatrix_p, r, c, argv[3]);
    }

    else{
	   return 1;
    }

    free(smatrix);
    free(ascii); 
    free(nmatrix);



    return 0;
    }
}

