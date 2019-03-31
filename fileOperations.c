#include <stdio.h>
#include <stdlib.h>
#include<ctype.h>

static int rows, columns;

int readFileBetter(char* inputfilename)
{
    FILE* f = fopen(inputfilename, "r");

    char* temp_rows = malloc ( sizeof (temp_rows) );
    char* temp_columns = malloc ( sizeof (temp_columns) );
    char* inv_char = malloc ( sizeof (inv_char) );

    int *rows_p = &rows;
    int *columns_p = &columns;
    int i = 0;
    int c = getc(f);
    int errors = 0;

    while ( c != '\n' && c != EOF)
    {
        if( !(isdigit(c)) && !(isspace(c)) )
        {
            inv_char[errors] = c;
            errors++;
        }
        c = getc(f);
    }

    rewind(f);

    if( errors != 0)
    {
        printf("Error occurred while reading the grid size. \nCharacters: \"%s\" are invalid and should not appear in the first line of the file.\n", inv_char);
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



    /*while(isspace(c))                                               //skips through any eventual spaces before the grid size
        c = getc(f);

    while(c != EOF)
    {

        while (c>= '0' && c<= '9')                           //reads the numbers
        {
            temp_rows[i]=c;
            c=getc(f);
        }
        *rows_p = atoi(temp_rows);

        if ( !(c>= '0' && c<= '9') && !(isspace(c)) )     //checks for invalid characters
        {
            inv_char[errors] = c;
            errors++;
        }



        c = getc(f);

        while ( isspace(c) )                                   //skips through any eventual spaces before the size of grid
            c = getc(f);

        while (c>= '0' && c<= '9')                          //reads the numbers
        {
            temp_columns[i] = c;
            c = getc(f);
        }

        if ( !(c>= '0' && c<= '9') &&  !( isspace(c) ) )         //checks for invalid characters
        {

            inv_char[errors] = c;
            errors++;
        }

        *columns_p = atoi(temp_columns);
    }


        if (errors != 0)
        {
            printf ("Found %d invalid characters while opening the file: %s", errors, inv_char);
            return errors;
        }

        else
            return 0;

} */



int main(int argc, char** argv)
{
    //int rows, columns;
    //FILE* f;
    //f = fopen("test.txt", "r");
    //int rows, columns;
    //fscanf(f, "%d %d", &rows, &columns);

    //readFile("test.txt");

    readFileBetter("test.txt");
    printf("%d %d", rows, columns);


    //int g = getchar();
    return 0;
}

