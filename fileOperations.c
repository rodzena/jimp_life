#include <stdio.h>
#include <stdlib.h>
#include<ctype.h>


int getSize(char* inputfilename,int* r, int* c)
{
    FILE* f = fopen(inputfilename, "r");

    char* temp_rows = malloc ( 10*sizeof (temp_rows) );
    char* temp_columns = malloc ( 10*sizeof (temp_columns) );

    int i = 0;
    int errors = 0;
    char* inv_char = malloc (10*sizeof inv_char);
    int temp = getc(f);

//check the validity of the characters in the first line
    while ( temp != '\n' && temp != EOF)
    {
        if( !(isdigit(temp)) && (!(isspace(temp))) )
        {
            inv_char[errors] = temp;
            errors++;
        }
        temp = getc(f);
    }
    inv_char[errors] = '\0';
    rewind(f);

//attempt to read the size only if there aren't any invalid characters
    if( errors != 0)
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
    return 0;
}


void fillStatesMatrix (char* inputfilename, int* matrix, int* r, int* c)
{
    int temp;
    FILE* f = fopen(inputfilename, "r");
    do
        {
            temp = getc(f);
        }
     while (temp != '\n');

    //temp = getc(f);

    //while (temp != -38) {
      //  temp = getc(file) - 48;
    //}

    for(int i = 0; i < *r; i++) {
        for(int j = 0; j < *c; j++) {
            temp = getc(f);
            *matrix = temp - '0';
            matrix++;
        }
        temp = getc(f);
    }
    fclose(f);
}




int main(int argc, char** argv)
{
    int r=0;
    int c=0;

    int result = getSize("test.txt", &r,  &c);

    int smatrix[r][c];
    int* smatrix_p = &smatrix[0][0];





    if(!result)
        printf("%d %d\n", r, c);

    fillStatesMatrix ("test.txt", smatrix_p, &r, &c);

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

