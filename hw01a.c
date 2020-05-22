/* hw1.c */
/* Name: Vishaal Kasinath (kasinv) */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>


/* Main Program */
int main(int argc, char* argv[]) {

	/* 
	** Need 5 arguments (the name of the module + 4 input values)
	** The 4 inputs (Row & Column sizes - R1, C1, R2 ,C2) should be +ve int
	** The Row size of Matrix 2 (R2) = Column size of Matrix 1 (C1)
	*/

	// define loop counters we will be using all through the module
	int i, j, k;

	if (argc != 5){
  		fprintf(stderr, "ERROR: Invalid inputs!\n");
    	return EXIT_FAILURE;
	}

	int R1 = atof(argv[1]);
	int C1 = atoi(argv[2]);
	int R2 = atoi(argv[3]);
	int C2 = atoi(argv[4]);

	if ((argc != 5) || (R1 < 1) || (C1 < 1) || (R2 < 1) || (C2 < 1) || (R2 != C1)){
  		fprintf(stderr, "ERROR: Invalid inputs!\n");
    	return EXIT_FAILURE;
	}

	// Create and initialize 
	// the first matrix of R1 x C1 as a 2-dimensional array
	// the second matrix of R2 x C2 as a 2-dimensional array
	// the result matrix MR = M1 x M2, as 2D array of size R1xC2
	int M1[R1][C1], M2[R2][C2], MR[R1][C2];

	/* Initialize each cell for M1, M2 and MR to 0 */
	for (i=0; i < R1; i++){
		for (j=0; j < C1; j++)
			M1[i][j] = 0;
	}

	for (i=0; i < R2; i++){
		for (j=0; j < C2; j++)
			M2[i][j] = 0;
	}

	for (i=0; i < R1; i++){
		for (j=0; j < C2; j++)
			MR[i][j] = 0;
	}

	// read input data for first matrix M1
	printf("Please enter the values for the first matrix (%dx%d):\n", R1, C1);
	for (i = 0; i < R1; i++) {
		for (j = 0; j < C1; j++)
			scanf("%d", &(M1[i][j]));
	}

	// read input data for first matrix M2
	printf("Please enter the values for the second matrix (%dx%d):\n", R2, C2);
	for (i = 0; i < R2; i++) {
		for (j = 0; j < C2; j++)
			scanf("%d", &(M2[i][j]));
	}
	printf("\n");

	// Calculate M1 x M2 and write results to MR
	for (i=0;i < R1; i++){
		for (j=0; j < C2; j++){
			for (k=0; k < C1; k++)
				MR[i][j] += M1[i][k] * M2[k][j];	// R2 pre-verified to be equal to C1
		}
	}

	// at this point we have M1, M2 and MR
	// to print out M1 with each column in a right-justified manner
	// we need to find the maximum digit size of each column
	// and store it in a one-dimensional array of size C1...
	// so that we can do a printf(%*d, max_col_size, value)

	// create 1-d array S1 of size C1(for M1), S2 of size C2(for M2), SR of size C2(for MR)

	int S1[C1], S2[C2], SR[C2]; 

	/* Scan matrix, and create a 1D array of max size for each column
	** the 1D array will have C1 elements, where C1 = # of columns in the matrix
	**
	** if the matrix is [ 1,  10,  1000
	**					 24, 400,    20
	**					 21,   2, 10000]
	**
	** the 1D array S1 will be [2, 3, 5]
	** first column size = 2  (max of 2 digits)
	** second column size = 3 (max of 3 digits)
	** third column size = 5  (max of 5 digits)
	*/
	for (i=0; i < C1; i++)
		S1[i] = 0;

	for (i = 0; i < R1; i++) {
		for (j = 0; j < C1; j++) {

			// take log of abs(cell value), truncate and add 1 to get # of digits
			// if cell value < 0, add 1 to cell_size (for the minus symbol)
			// store into S[j], the max of (cell_size, S[j])
			int cell_size = floor(log10(abs(M1[i][j])))+1;
			if (M1[i][j] < 0)	cell_size +=1;
			if (cell_size > S1[j]) S1[j] = cell_size;
		}
	}

	for (i=0; i < C2; i++)
		S2[i] = 0;

	for (i = 0; i < R2; i++) {
		for (j = 0; j < C2; j++) {

			// take log of abs(cell value), truncate and add 1 to get # of digits
			// if cell value < 0, add 1 to cell_size (for the - symbol)
			// store into S[j], the max of (cell_size, S[j])
			int cell_size = floor(log10(abs(M2[i][j])))+1;
			if (M2[i][j] < 0)	cell_size +=1;
			if (cell_size > S2[j]) S2[j] = cell_size;
		}
	}

	for (i=0; i < C2; i++)
		SR[i] = 0;

	for (i = 0; i < R1; i++) {
		for (j = 0; j < C2; j++) {

			// take log of abs(cell value), truncate and add 1 to get # of digits
			// if cell value < 0, add 1 to cell_size (for the - symbol)
			// store into S[j], the max of (cell_size, S[j])
			int cell_size = floor(log10(abs(MR[i][j])))+1;
			if (MR[i][j] < 0)	cell_size +=1;
			if (cell_size > SR[j]) SR[j] = cell_size;
		}
	}

	// Print out the results in the required format. M1 multiplied by M2 = MR
	for (i = 0; i < R1; i++) {
    	printf("[");
		for (j = 0; j < C1; j++) {
			printf("%*d", S1[j], M1[i][j]);
			if (j != C1 - 1) printf(" "); // if not last column, space-separate values
		}
		printf("]\n");
	}
	printf("multiplied by\n");

	for (i = 0; i < R2; i++) {
    	printf("[");
		for (j = 0; j < C2; j++) {
			printf("%*d", S2[j], M2[i][j]);
			if (j != C2 - 1) printf(" "); // if not last column, space-separate values
		}
		printf("]\n");
	}
	printf("equals\n");

	for (i = 0; i < R1; i++) {
    	printf("[");
		for (j = 0; j < C2; j++) {
			printf("%*d", SR[j], MR[i][j]);
			if (j != C2 - 1) printf(" "); // if not last column, space-separate values
		}
		printf("]\n");
	}

	return EXIT_SUCCESS;
}
