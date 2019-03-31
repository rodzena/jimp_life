#include <stdio.h>
#include <stdlib.h>
#include<ctype.h>

static int rows, columns;

int readFileBetter(char* inputfilename)
{
    FILE* f = fopen(inputfilename, "r");
    char* temp_rows = malloc(sizeof(temp_rows));
    char* temp_columns = malloc(sizeof(temp_rows));
    char* inv_char = malloc(sizeof (inv_char));

    int *rows_p = &rows;
    int *columns_p = &columns;
    int i = 0;
    int c = getc(f);
    int errors = 0;


    while(isspace(c))                               //skips through any eventual spaces before the size of grid
        c = getc(f);

    while(c != EOF)
    {
        while (c>= '0' && c<= '9')                      //reads the numbers
        {
            temp_rows[i]=c;
            c=getc(f);
        }

        if (!(c>= '0' && c<= '9') && !(isspace(c)))     //checks for invalid characters
        {
            inv_char[errors] = c;
            errors++;
        }

        *rows_p = atoi(temp_rows);

        c=getc(f);

        while(isspace(c))                                   //skips through any eventual spaces before the size of grid
            c = getc(f);

        while (c>= '0' && c<= '9')                          //reads the numbers
        {
            temp_columns[i]=c;
            c=getc(f);
        }

        if (!(c>= '0' && c<= '9') && !(isspace(c)))         //checks for invalid characters
        {

            inv_char[errors]=c;
            errors++;
        }

        *columns_p = atoi(temp_columns);

        if(errors != 0)
        {
            printf("Found %d invalid characters while opening the file: %s", errors, inv_char);
            return errors;
        }

        else
            return 0;
    }
}



int main(int argc, char** argv)
{
    //int rows, columns;
    //FILE* f;
    //f = fopen("test.txt", "r");
    //int rows, columns;
    //fscanf(f, "%d %d", &rows, &columns);

    //readFile("test.txt");

    if(readFileBetter("test.txt") == 0)
    printf("%d %d", rows, columns);


    //int g = getchar();
    return 0;
}

