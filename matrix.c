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
void matMult(int *matrixA, int rowsA, int colsA, int *matrixB, int rowsB, int colsB){

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
    

    int total = sizeof(matrix1)/sizeof(matrix1[0][0]);
    int matrows = sizeof(matrix1)/sizeof(matrix1[0]);
    int matcols = total/matrows;

	int total1 = sizeof(matrix2)/sizeof(matrix2[0][0]);
    int matrows1 = sizeof(matrix2)/sizeof(matrix2[0]);
    int matcols1 = total1/matrows1;
	

    //matMul(*matrix1, matrows, matcols, *matrix2, matrows1, matcols1);

    int lengthOfArray = sizeof(testing);
    //printf("\n\nheavy tests ----------------------------------\n\n");
    //parseModel(testing, lengthOfArray);
    //printf("\n\nheavy tests ----------------------------------\n\n");
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
    float testData[] = {0.72779332,  1.12606976, -0.31331522, -0.05345183, -0.02599893};
    float* testDataPointer = testData;
    //getTensor(address[2], testing, lengthOfArray);
    float* weightArray = getWeightTensor(address[1], testing, lengthOfArray, 5, 16);
    //printf("--> in main program: %0.5f\n", weightArray[0 * 16 + 1]);
    float* biasArray = getBiasTensor(address[1], testing, lengthOfArray, 16, 1);
    
    float* result = matMul(testDataPointer, 1, 5, weightArray, 5, 16);
    // get a known array of (5,5), test the values using python and then test matMul here
    float* result1 = (float*)malloc(16*sizeof(float));
    for (int i = 0; i < 16; i++) {
        result1[i] = result[i] + biasArray[i];
    }

    // a very crude ReLu
    for (int i = 0; i < 16; i++) {
        if(result1[i]<0){
            result1[i] = 0;
        }
    }

    for (int i = 0; i < 16; i++) {
        printf("%0.5f ", result1[i]);
    }
    
    
    free(result);
    free(result1);
    free(biasArray);
    free(weightArray);
    //free(result);

	return 0;
}

