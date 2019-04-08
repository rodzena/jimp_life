#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
/*#include "fileOperations.h"
#include "generation.h"
#include "rules.h"*/

int getSize(char* inputfilename,int* r, int* c)
{
    FILE* f = fopen(inputfilename, "r");

    char* temp_rows = (char*) malloc ( 10*sizeof (temp_rows) );
    char* temp_columns = (char*) malloc ( 10*sizeof (temp_columns) );

    int i = 0;
    int er_count = 0;
    char* inv_char = (char*) malloc (5*sizeof inv_char);                //lokuje na wartosc; czy er_count => rozmiartablicy; inv_char realloc(inv_char, 2*er_count*sizeof char)
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
        printf("Error occurred while reading the grid size. \nCharacters: %s are invalid and should not appear in the first line of the file.\n", inv_char);
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

    temp = getc(f);

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
            printf("Po skonczeniu %d linii: %d\n",i+1, temp);
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

/*void fillStatesMatrix (char* inputfilename, int* matrix, int* r, int* c)
{
    int c;
    FILE* f = fopen(inputfilename, "r");

//skip the first line - the size is already loaded
    do
    {
        c = getc(f);
    }
    while (c != '\n');
    printf("znak nowego wiersza elko elkooooo %d", '\n' );


    c = getc(f);

    for(int i = 0; i < *r; i++)
    {
        for(int j = 0; j < *c; j++)
        {
            while(c != '\n')
            {
                c = getc(f);
                *matrix = c - '0';
                matrix++;
            }
        }
        c = getc(f);
        printf("<<%c>>\n",c);
        if(c != '\n')
        {
            printf("Loaded grid is of incorrect size. Line %d is too long. \nExpected length: %d\n",i+1,*r);
        }
    }
    fclose(f);
}
*/




/*int main(int argc, char** argv)
{
    int r=0;
    int c=0;

    int result = getSize("test.txt", &r,  &c);

    int smatrix[r][c];
    int* smatrix_p = &smatrix[0][0];

    if(!result)
        printf("%d %d\n", r, c);

    fillStatesMatrix ("test.txt", smatrix_p, &r, &c);


//drukuje macierz 1 - docelowo w innej funkcji
    for (int i = 0; i<r; i++)
    {
        for (int j = 0; j<c; j++)
        {
            printf("%d", smatrix[i][j]);
        }
        printf("\n");

    }




    return 0;
}
*/

