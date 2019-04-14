#include <stdio.h>
#include "generation.h"
#include "rules.h"
#include "fileOperations.h"
#include <sys/stat.h>
#include <sys/types.h>


void generateGeneration(int* states, int* neighbours, int r, int c, int genNumber, char* ascii_p, char* folderName) {
    int t = 0;
    int genQuantity = genNumber;
    while(genNumber-- != 0) {
        generateNeighbours(states, neighbours, r, c);
        decideCellsState(states, neighbours, r, c);
        printf("======== Generation #%d ========\n\n\n", t + 1);
        //showMatrix(states, r, c);
        convertASCII(states, ascii_p, r,c);
        printf("\n\n\n");
        saveToTxt(ascii_p, r, c, genQuantity - genNumber, folderName);

        t++;
    }

    //saveToTxt(states, r, c, 000, folderName );
}

void generateNeighbours (int* states, int* neighbours, int r, int c) {
    for(int i = 0; i < r; i++) {
        for(int j = 0; j < c; j++) {
            *(neighbours + r * i + j) = countNeighbours(states, r, c, i, j);
        }
    }
}

int countNeighbours (int* states, int r, int c, int x, int y) {
    int count = 0;
    //Top right
    if(x > 0 && y < (c - 1))
        count += *(states + (x - 1) * r + y + 1);
    //Right
    if(y < (c - 1))
        count += *(states + x * r + y + 1);
    //Bottom right
    if(x < (r - 1) && y < (c - 1))
        count += *(states + (x + 1) * r + y + 1);
    //Bottom
    if(x < (r - 1))
        count += *(states + (x + 1) * r + y);
    //Bottom left
    if(x < (r - 1) && y > 0)
        count += *(states + (x + 1) * r + y - 1);
    //Left
    if(y > 0)
        count += *(states + x * r + y - 1);
    //Top left
    if(x > 0 && y > 0)
        count += *(states + (x - 1) * r + y - 1);
    //Top
    if(x > 0)
        count += *(states + (x - 1) * r + y);
    return count;
}
