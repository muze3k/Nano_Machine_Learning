#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "model.h"
#include "methods.h"


int matrix1[3][3]={
	{1,2,3},
	{1,2,3},
	{1,2,3}
};

int matrix2[3][3]={
	{1,2,3},
	{1,2,3},
	{1,2,3}
};

// a matrix multiplication function, takes in two matrices with their rows and columns
void matMul(int *matrixA, int rowsA, int colsA, int *matrixB, int rowsB, int colsB){
	/*
	for (int i = 0; i < rowsA; i++) {
    	for (int j = 0; j < colsA; j++) {
	      //printf(matrix[i][j]);
    		//printf("%d %d %d\n", i, cols, j);
	      	printf("%d ", *(matrixA + i * colsA + j));
	      	printf(" ");
    	}
    printf("\n");
	}
	*/

	if (colsA != rowsB) {
    printf("Matrix multiplication not possible\n\n");
    return;
  }


	int resultantMatrix[rowsA][colsB]; // Adjust size based on your matrices
	for (int i = 0; i < rowsA; i++) {
		for (int j = 0; j < colsB; j++) {
		  resultantMatrix[i][j] = 0; // Initialize elements to zero
		  for (int k = 0; k < colsA; k++) {
		    //resultantMatrix[i][j] += matrixA[i][k] * matrixB[k][j];
		  	resultantMatrix[i][j] += (*(matrixA + i * colsA + k)) * (*(matrixB + k * colsB + j));
		  }
		}
	}


	// print resultant matrix
	printf("\n");
	printf("\n");
	printf("\n");
	int total = sizeof(resultantMatrix)/sizeof(resultantMatrix[0][0]);
    int matrows = sizeof(resultantMatrix)/sizeof(resultantMatrix[0]);
    int matcols = total/matrows;
	for (int i = 0; i < matrows; i++) {
    	for (int j = 0; j < matcols; j++) {
	      printf("%d", resultantMatrix[i][j]);
    		//printf("%d %d %d\n", i, cols, j);
	      	//printf("%d ", *(resultantMatrix + i * colsA + j));
	      printf(" ");
    	}
    printf("\n");
	}
}


int main(int argc, char const *argv[])
{
    int numberOfLayers = 3;

    int total = sizeof(matrix1)/sizeof(matrix1[0][0]);
    int matrows = sizeof(matrix1)/sizeof(matrix1[0]);
    int matcols = total/matrows;

	int total1 = sizeof(matrix2)/sizeof(matrix2[0][0]);
    int matrows1 = sizeof(matrix2)/sizeof(matrix2[0]);
    int matcols1 = total1/matrows1;
	

    matMul(*matrix1, matrows, matcols, *matrix2, matrows1, matcols1);

    char data[] = "\x43\xad\xfc\x3e\x71\xa2\xe5\x3e\xa0\x61\x3f\x3d\xc5\x11\x07\x40\x00\x00\x00\x00\xd4\x60\x05\x40\x00\x00\x00\x00\x55\x44\x6b\x3f\x00\x00\x00\x00\x00\x00\x00\x00\xa6\x2f\xf5\x3e\x00\x00\x00\x00\xb2\xd6\x03\x3f\x00\x00\x00\x00\xde\x2a\xe6\x3d\x00\x00\x00\x00";
    int num_bytes = strlen(data);  // Get the number of bytes in the data

    // Assuming we know there are 16 floats (4x4 matrix)
    int num_elements = num_bytes / sizeof(float);  // Calculate the number of floats
    float *float_data = (float *)data;  // Interpret the data as floats

    // Print the matrix
    int nrows = 1, ncols = 16;  // Dimensions of the matrix
    printf("Matrix:\n");
    for (int i = 0; i < nrows; i++) {
        for (int j = 0; j < ncols; j++) {
            printf("%.5f ", float_data[i * ncols + j]);
        }
        printf("\n");
    }

    printf("---------Starting string parsing----------\n");
    //printf("this is %c", testing[1]);
    printf("this is length in main file %d\n", sizeof(testing));
    int lengthOfArray = sizeof(testing);
    //parseModel(testing, lengthOfArray);
    
    //char* address = getMemAddress(testing, 2, sizeof(testing));
    //printf("this is the mem address of second $ %c", *(address+2));
    int totalLayers = 5; // total number of dollar signs(layers)
    int* address = getMemAddress(testing, totalLayers, sizeof(testing));  // this array now holds the position of all dollar signs
    //printf("print value %d\n", address);
    //printf("print value %c", *(address));
    printf("------\n");
    for (int i = 1; i <= totalLayers; i++) {  // for some reason, i=0 is not working, meaning that address[0] gives faulty value, very strange
        printf("%d\n", address[i]);
    }
    getTensor(address[5], testing, lengthOfArray);
	return 0;
}

// issue is i cant find the correct syntax to write binary string

