#include <stdio.h>
#include <stdlib.h>
#include "rules.h"
#include "fileOperations.h"
#include "generation.h"
#include "main.h"

#include <sys/stat.h>
#include <sys/types.h>

int main(int argc, char** argv)
{
    printf("Halko odbjur\n");
    //declaring variables
    char inputfilename[] = "test.txt";
    int r = 0, c = 0;
    int generations;
    char* filename;
    char* exitfolder;
    readArguments(argc, argv, &filename, &generations, &exitfolder);

    //reading number of columns and rows from a file
    getSize(inputfilename, &r, &c);

    //creating states and neighbours matrix
    int smatrix[r][c];
    int nmatrix[r][c];
    int* smatrix_p = &smatrix[0][0];
    int* nmatrix_p = &nmatrix[0][0];

    //filling states matrix
    int fillResult = fillStatesMatrix(inputfilename, smatrix_p, r, c);

    /*if (fillResult == 0)
    {
        printf("states matrix read from file:\n");
        showMatrix(smatrix_p, r, c);
        generateGeneration(smatrix_p, nmatrix_p, r, c, 10);
    }
    system("pause");*/
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

void readArguments(int argc, char** argv, char* filename, int* generations, char* exitfoldername) {
    if(argc != 4) {
        printf("Please launch the program with precisely three arguments! Exiting program...\n");
        system("pause");
        exit(0);
    }
    //filename[char]
    filename = argv[1];
    printf("Fetching states matrix from %s.\n", argv[1]);
    //generations[int]
    generations = atoi(argv[2]);
    printf("generating %d generations.\n", argv[2]);
    //exitfoldername[]
    exitfoldername = argv[3];
    printf("Saving generations in folder %s.\n", argv[3]); 

}