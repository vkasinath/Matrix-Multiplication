/* hw1.c */
/* Name: Vishaal Kasinath (kasinv) */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


/*
** Function to free up memory allocated for a Matrix
** Matrix M = R pointer of pointers
** In a loop, free each R pointer
** finally, free M
*/
void CleanUpMatrix(int** M, int R){

	for (int i=0; i < R; i++)
		free(M[i]);
	free (M);
}


/*
** Function to create and initialize a matrix M of size R x C
** M is an array of pointers to pointer of integers, of size R
** For each R pointer, allocate a pointer of integer of size C
** Initialize each cell to 0
*/
int** InitializeMatrix(int R, int C){

	int** M = (int **)malloc(R * sizeof(int*));
	for (int i=0; i<R; i++){
		M[i] = (int *)malloc(C * sizeof(int)); 
		for (int j=0; j < C; j++)
			M[i][j] = 0;
	}

	return M;
}


/*
** Function to print out the matrix, nicely
** separated by space, right justified (based on S)
** S is the 1D array that contains the max size to justify
** for each column of matrix M of size RxC
*/ 
void PrintMatrix(int** M, int* S, int R, int C){

	for (int i = 0; i < R; i++) {
    	printf("[");
		for (int j = 0; j < C; j++) {
			printf("%*d", S[j], M[i][j]);

			if (j != C - 1) printf(" "); //if not last column, space-separate cells
		}
		printf("]\n");
	}

}


/*
** Function to reads/scanf input integer data for matrix of size RxC
** and store it in the matrix M
*/ 
void ReadData(char* MString, int** M, int R, int C){

	printf("Please enter the values for the %s matrix (%dx%d):\n", MString, R, C);
	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++)
			scanf("%d", &(M[i][j]));
	}
}


/* Function to scan matrix, and create a 
** 1D array of max size for each column
** the 1D array will have C1 elements, 
** where C1 is the # of columns in the matrix
** if the matrix is [ 1,  10,  1000
**					 24, 400,    20
**					 21,   2, 10000]
** the 1D array S1 will be [2, 3, 5]
** first column size = max of 2 digits
** second column size = max of 3 digits
** third column size = max of 5 digits
*/
void StoreColumnSizes(int* S, int R, int C, int ** M){
	for (int i=0; i < C; i++)
		S[i] = 0;

	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) {
			// take log of abs(cell value), truncate and add 1 to get # of digits
			// if cell value < 0, add 1 to cell_size (for the - symbol)
			// store into S[J], the max of (cell_size, S[j])
			int cell_size = floor(log10(abs(M[i][j])))+1;
			if (M[i][j] < 0)	cell_size +=1;
			if (cell_size > S[j])	S[j] = cell_size;
		}
	}
}


/* Function to check validity of input values
** The 4 inputs (Row & Column sizes) should be positive integers
** The Row size of Matrix 2 (R2) = Column size of Matrix 1 (C1)
** If validity fails, return 0
** if all validity checks pass, return 1
*/
int ValidityCheck(int R1, int C1, int R2, int C2){

	// check positive, non-zero values of R1, C1, R2, C2
	if ((R1 < 1) || (C1 < 1) || (R2 < 1) || (C2 < 1))
    	return 0;

	// Check if the two matrices can be multiplied.
	// for matrix mult R2 should be equal to C1.
	// if R2 <> C1, return error
	if (R2 != C1)
		return 0;

    // if we are here, all good. so return 1
    return 1;
}


/* Main Program */
int main(int argc, char* argv[]) {

	//Need 5 arguments (the name of the module + 4 input values)
	if (argc != 5){
  		fprintf(stderr, "ERROR: Invalid inputs!\n");
    	return EXIT_FAILURE;
	}

	int R1 = atoi(argv[1]);
	int C1 = atoi(argv[2]);
	int R2 = atoi(argv[3]);
	int C2 = atoi(argv[4]);

	int vc = ValidityCheck(R1, C1, R2, C2);

	if (vc == 0) {
  		fprintf(stderr, "ERROR: Invalid inputs!\n");
    	return EXIT_FAILURE;
	}

	// define loop counters we will be using all through the module
	int i, j, k;

	// Create and initialize 
	// the first matrix of R1 x C1 as a 2-dimensional array
	// the second    matrix of R2 x C2 as a 2-dimensional array
	// the result    matrix of R1 x C2 as a 2-dimensional array
	// result matrix MR will store the results of M1 x M2

	int** M1 = InitializeMatrix(R1, C1);
	int** M2 = InitializeMatrix(R2, C2);
	int** MR = InitializeMatrix(R1, C2);

	// read input data for first matrix M1 and the second matrix M2
	ReadData("first",  M1, R1, C1);
	ReadData("second", M2, R2, C2);
	printf("\n");

	// Calculate M1 x M2 and write results to MR
	for (i=0;i < R1; i++){
		for (j=0; j < C2; j++){
			for (k=0; k < C1; k++)
				MR[i][j] += M1[i][k] * M2[k][j];	// R2 already verified to be equal to C1
		}
	}

	// at this point we have M1, M2 and MR
	// to print out M1 with each column in a right-justified manner
	// we need to find the maximum digit size of each column
	// and store it in a one-dimensional array of size C1...
	// so that we can do a printf(%*d, max_col_size, value)

	// we take the log of the cell, truncate and add 1 to get the # of digits in the cell
	// store max col sizes for M1, M2, MR and initialize to 0
	// create 1-d array S1 of size C1(for M1), S2 of size C2(for M2), SR of size C2(for MR)

	int* S1 = (int *)malloc(C1 * sizeof(int)); 
	int* S2 = (int *)malloc(C2 * sizeof(int)); 
	int* SR = (int *)malloc(C2 * sizeof(int)); 

	StoreColumnSizes(S1, R1, C1, M1);
	StoreColumnSizes(S2, R2, C2, M2);
	StoreColumnSizes(SR, R1, C2, MR);

	// Print out the results in the required format. M1 multiplied by M2 = MR
	PrintMatrix(M1, S1, R1, C1);
	printf("multiplied by\n");
	PrintMatrix(M2, S2, R2, C2);
	printf("equals\n");
	PrintMatrix(MR, SR, R1, C2);

	CleanUpMatrix(M1, R1);
	CleanUpMatrix(M2, R2);
	CleanUpMatrix(MR, R1);

	free(S1);
	free(S2);
	free(SR);

	return EXIT_SUCCESS;
}
