#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <Arduino.h>
#include "operations.h"

// matrix multiplication of two 2D arrays
float* matMul(float* matrixA, int matrixArows, int matrixAcols, float* matrixB, int matrixBrows, int matrixBcols){
  //Serial.printf("inside matMul\n");
  if (matrixAcols != matrixBrows) {
    //printf("Matrix multiplication not possible\n\n");
    return NULL;
  }

  float* resultantMatrix = (float*)malloc(matrixArows * matrixBcols * sizeof(float));
  if (resultantMatrix == NULL) {
    return NULL;
  }
  
  //Serial.println("Matrix A");
  // for (int i = 0; i < matrixArows; i++) {
  //   for (int j = 0; j < matrixAcols; j++) {
  //       //printf("%.5f ", matrixA[i * matrixAcols + j]);
  //       //Serial.print(matrixA[i * matrixAcols + j]);
  //       //Serial.print(" ");
  //   }
  //   //Serial.println("");
  // }

  //Serial.println("Matrix B");
  // for (int i = 0; i < matrixBrows; i++) {
  //   for (int j = 0; j < matrixBcols; j++) {
  //       Serial.print(matrixB[i * matrixAcols + j]);
  //       Serial.print(" ");
  //   }
  //   //Serial.println("");
  // }

	for (int i = 0; i < matrixArows; i++) {
		for (int j = 0; j < matrixBcols; j++) {
      //Serial.printf("i:%d, j:%d\n", i, j);
      resultantMatrix[i *matrixBcols +j] = 0;
		  for (int k = 0; k < matrixAcols; k++) {
          //Serial.printf("this: %0.5f  multiply this: %0.5f ", (*(matrixA + i * matrixAcols + k)), (*(matrixB + k * matrixBcols + j)));
          resultantMatrix[i *matrixBcols +j] += (*(matrixA + i * matrixAcols + k)) * (*(matrixB + k * matrixBcols + j));
          //Serial.printf("val:%0.5f\n", resultantMatrix[i *matrixBcols +j]);
          //resultantMatrix[i *matrixBcols +j] = result;
		  }
		}
	}

  //Serial.println("resultant matrix");
  // for (int i = 0; i < matrixArows; i++) {
  //   for (int j = 0; j < matrixBcols; j++) {
  //       //printf("%.5f ", matrixA[i * matrixAcols + j]);
  //       //Serial.printf("%0.5f ", resultantMatrix[i * matrixBcols + j]);
  //       //Serial.print(" ");
  //   }
  //   Serial.printf("\n");
  // }
  return resultantMatrix;
}

// basic matrix addition of two 1 dimensional matrices
float* matAdd(float* matrixA, int matrixArows, int matrixAcols, float* matrixB, int matrixBrows, int matrixBcols){
  //Serial.printf("inside matAdd\n");
  float* result = (float*)malloc((matrixAcols)*sizeof(float) );
  for (int i = 0; i < matrixAcols; i++) {
        result[i] = matrixA[i] + matrixB[i];
  }
  return result;
}

// basic ReLU layer
float* ReLU(float* matrixA, int matrixArows, int matrixAcols){
  //Serial.printf("inside ReLU\n");
  float* result = (float*)malloc(matrixAcols*sizeof(float));
  for (int i = 0; i < matrixAcols; i++) {
    if(matrixA[i]<0){
        result[i] = 0.0;
    }
    else
      result[i] = matrixA[i];
  }
  return result;
}


