#include <stdio.h>
#include <stdlib.h>
#include<ctype.h>

static int rows, columns;

int getSize(char* inputfilename)
{
    FILE* f = fopen(inputfilename, "r");

    char* temp_rows = malloc ( sizeof (temp_rows) );
    char* temp_columns = malloc ( sizeof (temp_columns) );

    int *rows_p = &rows;
    int *columns_p = &columns;
    int i = 0;
    int errors = 0;
    char* inv_char = calloc (1000,sizeof (inv_char));
    printf("%s", inv_char);


    int c = getc(f);
    while ( c != '\n' && c != EOF)                                                      //check the validity of the characters in the first line
    {
        if( !(isdigit(c)) && (!(isspace(c))) )
        {
            inv_char[errors] = c;
            errors++;

        }
        c = getc(f);
    }


    rewind(f);
    if( errors != 0)                                                                               //attempt to read the size only if there aren't any invalid characters
    {
        printf("Error occurred while reading the grid size. \nCharacters: %s are invalid and should not appear in the first line of the file.\n", inv_char);
        return 1;
    }
    else
    {
        c = getc(f);
        while(isspace(c))
            c = getc(f);

        i=0;
        while(c >= '0' && c <= '9')
        {
            temp_rows[i] = c;
            i++;
            c = getc(f);
        }
         *rows_p = atoi(temp_rows);

        while(isspace(c))
            c = getc(f);

         i=0;
        while(c >= '0' && c <= '9')
        {
            temp_columns[i] = c;
            i++;
            c = getc(f);
        }
         *columns_p = atoi(temp_columns);

         while(isspace(c)&& c != '\n')
            c = getc(f);

           if ( c == '\n' || c == EOF)
                return 0;
           else
           {
               printf("Size of grid is not specified correctly. Edit the file to contain 2 numbers.\n");
               return 1;
           }
    }
    return 0;
}







int main(int argc, char** argv)
{
    if(!getSize("test.txt"))
    printf("%d %d", rows, columns);

    return 0;
}

