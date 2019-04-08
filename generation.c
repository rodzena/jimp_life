#include <stdio.h>
#include "generation.h"
#include "rules.h"

void generateGeneration(int* states, int* neighbours, int r, int c, int n) {
    int t = 0;
    while(n-- != 0) {
        generateNeighbours(states, neighbours, r, c);
        //printf("=== neighbours matrix #%d ===\n", t);
        //showMatrix(neighbours, r, c);
        decideCellsState(states, neighbours, r, c);
        printf("===== states matrix #%d =====\n", t + 1);
        showMatrix(states, r, c);
        t++;
    }
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
