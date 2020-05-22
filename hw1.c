/* hw1.c */
/* NAME: Vishaal Kasinath */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void free_matrix(int **matrix, unsigned int r){

	for(unsigned int i=0; i < r; i++)
		free(matrix[i]);
	

	free(matrix);

}

void print_matrix(int **matrix, unsigned int r, unsigned int c){

	int max_d = 0;

	for(int i=0; i < r; i++)
    {
        for(int j=0; j < c; j++)
        {
        	max_d = matrix[i][j];
        	if (matrix[i][j] > max_d)
        		max_d = matrix[i][j];
        }
    }



    //unsigned int num_spaces = floor(log10(max_d)) + 1;

    for(unsigned int i=0; i < r; i++)
    {
    	printf("[");
        for(unsigned int j=0; j < c; j++)
        {
        	if (j < c -1)
            	//printf("%*d ", num_spaces, matrix[i][j]);
            	printf("%d ", matrix[i][j]);
        	else
        		//printf("%*d", num_spaces, matrix[i][j]);	
        		printf("%d", matrix[i][j]);
        }

        printf("]\n");
    }
}

void print_final(int **matrix1, unsigned int m1r1, int **matrix2, unsigned int m2c2, unsigned int r2c1){

	int **fmatrix = (int**) calloc(m1r1, sizeof(int*));

	for(unsigned int i=0; i < m1r1; i++){

		fmatrix[i] = (int*) calloc(m2c2, sizeof(int));
		for (unsigned int j=0; j < m2c2; j++)
			fmatrix[i][j] = 0;

	}

	for(unsigned int i=0; i < m1r1; i++){

		for(unsigned int j=0; j < m2c2; j++){

			for(unsigned int k=0; k < r2c1; k++){

				fmatrix[i][j] +=  matrix1[i][k]*matrix2[k][j];

			}
		}
	}

	print_matrix(fmatrix, m1r1, m2c2);

	free_matrix(fmatrix, m1r1);

}

int main( int argc, char * argv[] )
{

	/* Ensure we have the correct number of command-line arguments */
	if ( argc != 5 ){

		fprintf( stderr, "ERROR: Invalid inputs!\n" );
		return EXIT_FAILURE;
	}

	unsigned int m1_r = atoi(argv[1]);  
    unsigned int m1_c = atoi(argv[2]);
	unsigned int m2_r = atoi(argv[3]);  
    unsigned int m2_c = atoi(argv[4]);

	if (m1_c != m2_r){
		fprintf(stderr, "ERROR: Invalid inputs!\n" );
		return EXIT_FAILURE;
	}

	int **matrix1 = (int**) calloc(m1_r, sizeof(int*));

	printf("Please enter the values for the first matrix (%dx%d):\n", m1_r, m1_c);

	for(unsigned int i=0; i < m1_r; i++)
    {
    	matrix1[i] = (int*) calloc(m1_c, sizeof(int));
        for(unsigned int j=0; j < m1_c; j++)
        {
        	
            scanf("%d", &matrix1[i][j]);
        }
    }

    int **matrix2 = (int**) calloc(m2_r, sizeof(int*));

	printf("Please enter the values for the second matrix (%dx%d):\n", m2_r, m2_c);

	for(unsigned int i=0; i < m2_r; i++)
    {
    	matrix2[i] = (int*) calloc(m2_c, sizeof(int));
        for(unsigned int j=0; j < m2_c; j++)
        {
        	
            scanf("%d", &matrix2[i][j]);
        }
    }

    printf("\n");

	print_matrix(matrix1, m1_r, m1_c);

    printf("multiplied by\n");

	print_matrix(matrix2, m2_r, m2_c);

	printf("equals\n");

	print_final(matrix1, m1_r, matrix2, m2_c, m1_c);

	free_matrix(matrix1, m1_r);

	free_matrix(matrix2, m2_r);

return EXIT_SUCCESS;
}

