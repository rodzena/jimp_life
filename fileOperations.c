#include <stdio.h>
#include <stdlib.h>
#include<ctype.h>
#include <string.h>
#include "fileOperations.h"
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>







int getSize(char* inputfilename, int* r, int* c)
{
    FILE* f = fopen(inputfilename, "r");

    char* temp_rows = malloc ( 10*sizeof (temp_rows) );
    char* temp_columns = malloc ( 10*sizeof (temp_columns) );

    int i = 0;
    int er_count = 0;
    char* inv_char = malloc (5*sizeof inv_char);                //lokuje na wartosc; czy er_count => rozmiartablicy; inv_char realloc(inv_char, 2*er_count*sizeof char)
    int temp = getc(f);

//check the validity of the characters in the first line
    while ( temp != '\n' && temp != EOF)
    {
        if( !(isdigit(temp)) && (!(isspace(temp))) )
        {
            inv_char[er_count] = temp;
            er_count++;
        }
        temp = getc(f);
    }
    inv_char[er_count] = '\0';
    rewind(f);

//attempt to read the size only if there aren't any invalid characters
    if( er_count != 0)
    {
        printf("Error occurred while reading the grid size. \nCharacters: %s are invalid and should not appear in the first line of the file. \nMake sure the grid size consists only of integrals.\n", inv_char);
        return 1;
    }
    else
    {
        temp = getc(f);

//skips spaces
        while(isspace(temp))
            temp = getc(f);
        i=0;

//saves digits of row numbers to temporary string
        while(temp >= '0' && temp <= '9')
        {
            temp_rows[i] = temp;
            i++;
            temp = getc(f);
        }
        *r = atoi(temp_rows);

//skips spaces
        while(isspace(temp))
            temp = getc(f);
        i=0;

//saves digits of column numbers to temporary string
        while(temp >= '0' &&  temp <= '9')
        {
            temp_columns[i] = temp;
            i++;
            temp = getc(f);
        }
        *c = atoi(temp_columns);

//skips spaces
        while(isspace(temp)&& temp != '\n')
            temp = getc(f);

//checks if there are any numbers after the spaces following the column number
        if ( temp == '\n' || temp == EOF)
            return 0;
        else
        {
            printf("Size of grid is not specified correctly. Edit the file to contain 2 numbers.\n");
            return 1;
        }
    }
    fclose(f);
    return 0;
}

int fillStatesMatrix(char*inputfilename, int* matrix, int r, int c)
{
    FILE* f = fopen(inputfilename, "r");

    int temp = getc(f);

    while (temp != '\n' && temp != EOF)
        temp = getc(f);

    if(temp!= EOF)
    temp = getc(f);
    else
    {
        printf("No grid!\n");
        return 1;
    }

    if ( temp != EOF)
    {
        for (int i = 0; i < r; i++)
        {
            for (int j = 0; j < c; j++)
            {
                if ( temp != EOF && temp != '\n')
                {
                    *matrix = (temp - '0');
                    matrix++;
                }
                else
                {
                    printf("Line %d is too short. Make sure it contains %d characters.\n", i+1, c);
                    return 1;
                }
                 temp = getc(f);
            }
            if (temp != '\n' && temp != EOF)
            {
                printf("Line %d is too long. Make sure it contains %d characters.\n", i+1, c);
                return 1;
            }
            else if (temp == EOF && i < r -1)
            {
                printf("Not enough verses. Make sure there are %d verses.\n", r);
                return 1;
            }
            else if( temp == '\n' && i == r-1)
            {
                printf("Too many rows. Make sure there are %d of them.\n", r);
                return 1;
            }
            else
                temp = getc(f);
        }
    }
    return 0;
}


void convertASCII (int* matrix_p, char* ascii_p, int r, int c)
{
    //printf("===========Current generation===========\n");
    printf("+");
    for (int i = 0; i < 2*c +1; i++)
        printf("-");
    printf("+\n");

    for (int i = 0; i < r; i++)
    {
        printf("| ");
        for (int j = 0; j < c; j++)
        {
            int
            c = *(matrix_p + r*i + j);
            if (c == 0)
                *(ascii_p + r*i +j) = 'O';
            else
                *(ascii_p + r*i +j) = 'X';

               printf("%c ", *(ascii_p + r*i +j));
        }
        printf("|\n");
    }
    printf("+");
    for (int i = 0; i < 2*c +1; i++)
        printf("-");
    printf("+\n");
}

int saveToTxt(char* matrix_p, int r, int c, int n, char* folderName) //n - nr generacji jbkc
{

    char* path = malloc(30* sizeof(char));

    sprintf(path, "%s/gen_%d.txt", folderName,n );
    FILE *outF = fopen(path,"w");

    fprintf(outF,"+");
    for(int i = 0; i < 2*c + 1 ; i ++)
        fprintf(outF,"-");
     fprintf(outF,"+\n");


     for(int i = 0; i < r; i++)
     {
        fprintf(outF,"| ");
         for (int j = 0; j < c; j++)
         {
             fprintf(outF, "%c ", *(matrix_p + i*r + j));
         }
         fprintf(outF, "|\n");
     }

     fprintf(outF,"+");
      for(int i = 0; i < 2*c + 1; i ++)
        fprintf(outF,"-");

      fprintf(outF,"+");



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

void saveFinalGrid(int* matrix, int r, int c, char* folderName)
{

    char* path = malloc(30* sizeof(char));

    sprintf(path, "%s/final_grid.txt", folderName);
    FILE *outF = fopen(path,"w");

    fprintf(outF, "%d %d\n",r,c);
    for(int i = 0; i<r; i++)
    {
        for (int j = 0; j<c; j++)
        {
            fprintf(outF, "%d",*(matrix + r*i + j));
        }
            fprintf(outF, "\n");
    }
}
