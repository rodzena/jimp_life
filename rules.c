#include <stdio.h>

int decideCellState(int* states, int* neighbours, int r, int c, int x, int y) {
    int s = *(states + x * r + y);
    int n = *(neighbours + x * r + y);
    switch (s) {
        case (0):
        if(n == 3) 
            return 1;
        else
            return 0;
        break;
        case (1):
            if(n == 2 || n == 3)
                return 1;
            else
                return 0;
        break;
        default: printf("blad!\n");
    }
 return -1;
}