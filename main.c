#include <stdio.h>
#include <stdlib.h>
#include "fileOperations.h"
#include "generation.h"
#include "rules.h"
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>


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
    int fillResult = fillStatesMatrix(inputfilename, smatrix_p, r, c);
    //showing states matrix


    if (fillResult == 0)
    {
        printf("states matrix read from file:\n");
        //showMatrix(smatrix_p, r, c);

        generateGeneration(smatrix_p, nmatrix_p, r, c, 1);

    }

    //robi ascii, dzia³a yey!!!
    char ascii[r][c];
    char* ascii_p = &ascii[0][0];

    printf("\n\n");
    convertASCII(smatrix_p, ascii_p, r,c);



    char nazwafolderu[] = "folderWNero";
    mkdir(nazwafolderu);

    saveToTxt(ascii_p, r, c, 2, nazwafolderu);




    return 0;
}
