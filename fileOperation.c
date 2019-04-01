#include <stdio.h>

void readFile (char* inputfilename, int* r, int* c) {
	FILE* file = fopen(inputfilename, "r");
	int temp = 0;
	//  ---WCZYTYWANIE LICZBY RZEDÓW---
    temp = getc(file) - 48;
    while (temp != -16) {
        *r = *r * 10;
        *r += temp;
        temp = getc(file) - 48;
    }
    //  WCZYTYWANIE LICZBY KOLUMN---
    temp = getc(file) - 48;
    while (temp != -38) {
        *c = *c * 10;
        *c += temp;
        temp = getc(file) - 48;
    }
    fclose(file);
}

void fillStatesMatrix (char* inputfilename, int* matrix, int* r, int* c) {
    int temp;
    FILE* file = fopen(inputfilename, "r");

    temp = getc(file) - 48;
    while (temp != -16) {
        temp = getc(file) - 48;
    }
    temp = getc(file);
    while (temp != -38) {
        temp = getc(file) - 48;
    }

    for(int i = 0; i < *r; i++) {
        for(int j = 0; j < *c; j++) {
            temp = getc(file) - 48;
            *matrix = temp;
            matrix++;
        }
        temp = getc(file);
    }
    fclose(file);
}