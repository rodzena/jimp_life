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
    
    //declaring variables
    char inputfilename[] = "test.txt";
    int r = 0, c = 0;

    //nie działa, do naprawy:
    //int generations = 0;
    //int* pg = &generations;
    //char* filename = (char*) malloc (sizeof (char) * 40);
    //char* exitfolder = (char*) malloc (sizeof (char) * 40);
    //readArguments(argc, argv, filename, pg, exitfolder);

    printf("Halko odbjur\n");
    //reading number of columns and rows from a file
    getSize(inputfilename, &r, &c);

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
        generateGeneration(smatrix_p, nmatrix_p, r, c, 10);
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
/*
void readArguments(int argc, char** argv, char* f, int* g, char* e) {
    if(argc != 4) {
        printf("Please launch the program with three arguments! Exiting program...\n");
        system("pause");
        exit(0);
    }
    *f = *(argv[1]);
    printf("f: %s\n", f);
}*/