#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include "fileOperations.h"

int getSize(char* inputfilename, int* r, int* c) {
	FILE* f = fopen(inputfilename, "r");
	if( f == NULL){
		printf("File \"%s\" could not be open.\n", inputfilename);
		return -1;
	}

	char* temp_rows = (char*)malloc ( 10*sizeof (temp_rows) );
	char* temp_columns = (char*)malloc ( 10*sizeof (temp_columns) );

	int i = 0;
	int er_count = 0;
	char* inv_char = (char*)malloc (5*sizeof inv_char);          //allocates memory for invalid characters array
	int temp = getc(f);

	//check the validity of the characters in the first line
	while ( temp != '\n' && temp != EOF) {
		if( !(isdigit(temp)) && (!(isspace(temp))) && temp != '\n' ) {
			inv_char[er_count] = temp;
			er_count++;
		}
		temp = getc(f);
	}
	inv_char[er_count] = '\0';
	rewind(f);
	free(inv_char);

	//attempt to read the size only if there aren't any invalid characters
	if( er_count != 0) {
		printf("Error occurred while reading the grid size. \nCharacters: %s" 
			"are invalid and should not appear in the first line of the file. \n"
			"Make sure the grid size consists only of integrals.\n", inv_char);

		return 1;
	} 
	else {
		
		temp = getc(f);
		//skips spaces
		while(isspace(temp))
			temp = getc(f);
		i=0;
		
		//saves digits of row numbers to temporary string
		while(temp >= '0' && temp <= '9') {
			temp_rows[i] = temp;
			i++;
			temp = getc(f);
		}
		char* end;
		//*r = strtol(temp_rows,&end,10);
		*r = atoi(temp_rows);
		free(temp_rows);
		//skips spaces
		while(isspace(temp))
			temp = getc(f);
		i=0;
		//saves digits of column numbers to temporary string
		while(temp >= '0' &&  temp <= '9') {
			temp_columns[i] = temp;
			i++;
			temp = getc(f);
		}
		//*c = strtol(temp_columns,&end,10);
		*c = atoi(temp_columns);
		free(temp_columns);

		//skips spaces
		while(isspace(temp)&& temp != '\n')
			temp = getc(f);

		//checks if there are any numbers after the spaces following the column number
		if ( temp == '\n' || temp == EOF)
		{
			fclose(f);
			return 0;
		}
		else {
			printf("Size of grid is not specified correctly. Edit the file to contain 2 numbers.\n");
			fclose(f);
			return 1;
		}
	}
	
}

int fillStatesMatrix(char*inputfilename, int* matrix, int r, int c) {
	FILE* f = fopen(inputfilename, "r");
	int temp = getc(f);
	while(temp != '\n' && temp != EOF)
		temp = getc(f);
	temp = getc(f);
	while(temp != EOF) {
		if (temp != '0' && temp != '1' && temp != '\n') {
			fclose(f);
			return 1;
		} else {
			temp = getc(f);
		}
	}

	rewind(f);
	temp = getc(f);

	while (temp != '\n' && temp != EOF)
		temp = getc(f);

	if ( temp != EOF)
	{
		temp = getc(f);
		if (temp != EOF)
		{
			int i = 0, j = 0;

			for (i = 0; i < r; i++)
			{
				for (j = 0; j < c; j++)
				{
					if ( temp != EOF && temp != '\n')
					{
						*matrix = (temp - '0');
						matrix++;
					}
					else
					{
						printf("Incorrect size of grid. Make sure it is %dx%d\n", r,c); 
						fclose(f);
						return 1;
					}
					temp = getc(f);
				}
				if (temp != '\n' && temp != EOF || temp == EOF && i < r-1 )
				{
					printf("Incorrect size of grid. Make sure it is %dx%d\n", r,c);
					fclose(f);
					return 1;
				}

				else if( temp == '\n' && i == (r-1))
				{
					temp = getc(f);

					if(temp == EOF){
						fclose(f);
						return 0;
					}
					
					else 
					{
						printf("Incorrect size of grid. Make sure it is %dx%d\n", r, c);
						fclose(f);
						return 1;
					}
				}
				else {
					temp = getc(f);
				}
			}
		}
	}

}


void convertASCII (int* matrix_p, char* ascii_p, int r, int c)
{
	printf("+");
	for (int i = 0; i < 2*c +1; i++)
		printf("-");
	printf("+\n");

	for (int i = 0; i < r; i++)
	{
		printf("| ");
		for (int j = 0; j < c; j++)
		{
			int c = *(matrix_p + r*i + j);
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

int saveToTxt(char* matrix_p, int r, int c, int n, char* folderName) 
{

	char* path = (char*)malloc(30* sizeof(char));

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
	free(path);
	fclose(outF);
				
				
				
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
		fclose(outF);
		free(path);
}
