#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "methods.h"
#include <Arduino.h>

// get the number of position of $ in model file. Basically this list will hold the position of every layer
int* getMemAddress(char* str, int n, int size){
  //Serial.println("inside getMemAddress");
  int* dollarSign = (int*)malloc(n * sizeof(int));  // in c++, a more appropriate way is to use "int* dollarSign = new int[n];" instead of malloc and then use "delete[] dollarSign;" instead of free
  if (dollarSign == NULL) {
      //fprintf(stderr, "Memory allocation failed while creating array in getMemAddress\n");
      //exit(1);
      return NULL;
  }
  int count = 0;
  int counter = 0;
  while (counter <= size) {
      //Serial.print("start of while, count :-->");
      //Serial.println(count);
      //printf("%c,", *str);
      if (*str == '$' && *(str+1)=='[') {
          dollarSign[count] = counter;  // populate array with $ position in string
          count++;
          //Serial.print("inside if statement, count :-->");
          //Serial.println(count);
          //Serial.print("at position :-->");
          //Serial.println(counter);
      }
      // if (count == n){ // i thought the problem was with str++, but maybe not, since counter value above 1100 gives the error too
      //   return dollarSign;
      // }
      str++;
      counter++;
      //break;
  }
  return dollarSign;
}

// get the weight tensor for the layer
float* getWeightTensor(int posOfDollar, char* testing, int lengthOrig, int finalRows, int finalCols){
    
    //Serial.printf("inside getWeightTensor function\n");
    char *sstart, *eend, *ccurrent;
    int length = lengthOrig - 1;
    int position = 0;
    ccurrent = testing;
    sstart = (char*)memchr(ccurrent+posOfDollar, '$', length - (ccurrent - testing));
    eend = (char*)memchr(sstart+1, '$', length - ((sstart+1) - testing));
    //Serial.printf("debugger --> %c%c%c%c \n", *(sstart), *(sstart+1), *(sstart+2), *(sstart+3));
    //Serial.printf("debugger --> %c%c \n", *(eend), *(eend-1));

    int val = 0;
    while(val==0){
        if (eend != NULL && *(eend+1) == '['){
            val = 1;
            break;
        }
        else{
            char *temporary = (char*)memchr(eend+1, '$', (length - ((eend) - sstart)) );
            eend = temporary;
        } 
    }
  
    if (eend != NULL){
        position = eend - sstart - 1;
        char *tempstring = (char*)malloc(position + 1);
        memcpy(tempstring, sstart + 1, position);
        char *floatstart, *floatend, *floatmarker;
        int floatlength = (position + 1) - 1;
        char *weightShapeIndicatorEnd = strchr(tempstring, ']');
        char *weightShape = (char*)malloc(weightShapeIndicatorEnd - tempstring);
        
        strncpy(weightShape, tempstring+1, ((weightShapeIndicatorEnd - tempstring) - 1 ) );
        char *weightCommaIndicator = strchr(weightShape, ',');
        char *weightMatrixRows = (char*)malloc( (weightCommaIndicator - weightShape) );
        strncpy(weightMatrixRows, weightShape, (weightCommaIndicator - weightShape));
        char *fakeWeightMatrixCols = (char*)malloc( sizeof(int) );
        char *weightMatrixCols = fakeWeightMatrixCols;                                              // later on i need to free weightMatrixCols malloc, but because the original pointer will be altered, im saving original pointer so that it can be freed later
        weightMatrixCols = weightCommaIndicator+1;
        int intWeightMatrixRows = atoi(weightMatrixRows);
        int intWeightMatrixCols = atoi(weightMatrixCols);
        floatstart = weightShapeIndicatorEnd+1;
        floatmarker = (char*)memchr(tempstring, '^', (floatlength));
        int valid = 0;
        while(valid==0){
            if (floatmarker != NULL && *(floatmarker+1) == '['){                                    // the reason i'm dereferencing floatmaker is because floatmaker only has the pointer to whole mem ad, but to check '[' we need to compare char to char, therefore,  i dereference floatmaker which gives me char at that point
                valid = 1;
                break;
            }
            else{
                char *temp = (char*)memchr(floatmarker+1, '^', (floatlength - (floatmarker-tempstring)) );
                floatmarker = temp;
            }  
        }
        
        floatend = floatstart  + floatlength;
        int floatposition = (floatmarker - floatstart - 1) + 1;
        char *weightMatrix = (char*)malloc(floatposition+1);
        memcpy(weightMatrix, floatstart, ((floatmarker - floatstart)));
        weightMatrix[floatposition] = '\0';
        float *removelater = (float *)weightMatrix;

        char *biasShapeIndicatorEnd = strchr((floatmarker+1), ']');
        char *biasShape = (char*)malloc(biasShapeIndicatorEnd - (floatmarker+1));
        strncpy(biasShape, floatmarker+2, ((biasShapeIndicatorEnd - (floatmarker + 1)) - 1 ));
        char *biasCommaIndicator = strchr(biasShape, ',');
        char *biasMatrixRows = (char*)malloc( (biasCommaIndicator - biasShape) );
        strncpy(biasMatrixRows, biasShape, (biasCommaIndicator - biasShape));
        char *fakeBiasMatrixCol = (char*)malloc(sizeof(int) );                                            // later on i need to free biasMatrixCols malloc, but because the original pointer will be altered, im saving original pointer so that it can be freed later
        char *biasMatrixCols = fakeBiasMatrixCol;
        biasMatrixCols = biasCommaIndicator+1;                                                      // biascommaindicator holds mem add from ',' till end, so i excluded ','
        int intbiasMatrixRows = atoi(biasMatrixRows);                                               // convert strings to ints
        int intbiasMatrixCols = atoi(biasMatrixCols);
        int biasposition = (floatend - (biasShapeIndicatorEnd)) + 1;                                // floatend holds the end of the string mem address, biasshapeindicator holds the ']' mem address
        char *biasMatrix = (char*)malloc( biasposition + 1  );                                             // allocate biasposition number of spaces in mem adress for biasmatrix
        memcpy(biasMatrix, (biasShapeIndicatorEnd+1), ((floatend - biasShapeIndicatorEnd)));        // populate biasmatrix
        biasMatrix[biasposition] = '\0';
        float *float_data = (float *)weightMatrix;                                                  // as the name suggests, this holds the weight matrix
        int wrows = intWeightMatrixRows, wcols = intWeightMatrixCols;                               // Dimensions of the weight matrix, maybe this is not necessary and cna be directly iterated
        // Allocate memory for a 2D array of floats
        float* array = (float*)malloc(finalRows * finalCols * sizeof(float));
        if (array == NULL) {
            return NULL;
        }
        for (int i = 0; i < finalRows; i++) {
            for (int j = 0; j < finalCols; j++) {
                array[i * finalCols + j] = float_data[i * finalCols + j];     //(float)(i * cols + j);
            }
        } // matrix printing for loop ends

        // for debugging purpose        
        // for (int i = 0; i < finalRows; i++) {
        //     for (int j = 0; j < finalCols; j++) {
        //         Serial.printf("%0.5f ",array[i * finalCols + j]);     //(float)(i * cols + j);
        //     }
        //   Serial.printf("\n");
        // }

        free(tempstring);
        free(weightShape);
        free(weightMatrixRows);
        free(fakeWeightMatrixCols);
        free(weightMatrix);
        free(biasMatrix);
        free(biasShape);
        free(biasMatrixRows);
        free(fakeBiasMatrixCol);
        
        ccurrent = eend;
        return array;
    } // if (eend != NULL)
    else 
        return NULL;
    //return array;
}

// get the bias tensor for the layer
float* getBiasTensor(int posOfDollar, char* testing, int lengthOrig, int finalRows, int finalCols){

    //Serial.printf("inside getBiasTensor function\n");
    char *sstart, *eend, *ccurrent;
    int length = lengthOrig - 1;
    int position = 0;
    ccurrent = testing;
    sstart = (char*)memchr(ccurrent+posOfDollar, '$', length - (ccurrent - testing));
    eend = (char*)memchr(sstart+1, '$', length - ((sstart+1) - testing));

    int val = 0;
    while(val==0){
        if (eend != NULL && *(eend+1) == '['){
            val = 1;
            break;
        }
        else{
            char *temporary = (char*)memchr(eend+1, '$', (length - ((eend) - sstart)) );
            eend = temporary;
        } 
    }
    if (eend != NULL){
        position = eend - sstart - 1;
        char *tempstring = (char*)malloc(position + 1);
        memcpy(tempstring, sstart + 1, position);
        char *floatstart, *floatend, *floatmarker;
        int floatlength = (position + 1) - 1;
        char *weightShapeIndicatorEnd = strchr(tempstring, ']');
        char *weightShape = (char*)malloc(weightShapeIndicatorEnd - tempstring);
        
        strncpy(weightShape, tempstring+1, ((weightShapeIndicatorEnd - tempstring) - 1 ) );
        char *weightCommaIndicator = strchr(weightShape, ',');
        char *weightMatrixRows = (char*)malloc( (weightCommaIndicator - weightShape) );
        strncpy(weightMatrixRows, weightShape, (weightCommaIndicator - weightShape));
        char *fakeWeightMatrixCols = (char*)malloc( sizeof(int) );
        char *weightMatrixCols = fakeWeightMatrixCols;                                              // later on i need to free weightMatrixCols malloc, but because the original pointer will be altered, im saving original pointer so that it can be freed later
        weightMatrixCols = weightCommaIndicator+1;
        int intWeightMatrixRows = atoi(weightMatrixRows);
        int intWeightMatrixCols = atoi(weightMatrixCols);
        floatstart = weightShapeIndicatorEnd+1;
        floatmarker = (char*)memchr(tempstring, '^', (floatlength));
        int valid = 0;
        while(valid==0){
            if (floatmarker != NULL && *(floatmarker+1) == '['){                                    // the reason i'm dereferencing floatmaker is because floatmaker only has the pointer to whole mem ad, but to check '[' we need to compare char to char, therefore,  i dereference floatmaker which gives me char at that point
                valid = 1;
                break;
            }
            else{
                char *temp = (char*)memchr(floatmarker+1, '^', (floatlength - (floatmarker-tempstring)) );
                floatmarker = temp;
            }  
        }
        
        floatend = floatstart  + floatlength;
        int floatposition = (floatmarker - floatstart - 1) + 1;
        char *weightMatrix = (char*)malloc(floatposition+1);
        memcpy(weightMatrix, floatstart, ((floatmarker - floatstart)));
        weightMatrix[floatposition] = '\0';
        float *removelater = (float *)weightMatrix;

        char *biasShapeIndicatorEnd = strchr((floatmarker+1), ']');
        char *biasShape = (char*)malloc(biasShapeIndicatorEnd - (floatmarker+1));
        strncpy(biasShape, floatmarker+2, ((biasShapeIndicatorEnd - (floatmarker + 1)) - 1 ));
        char *biasCommaIndicator = strchr(biasShape, ',');
        char *biasMatrixRows = (char*)malloc( (biasCommaIndicator - biasShape) );
        strncpy(biasMatrixRows, biasShape, (biasCommaIndicator - biasShape));
        char *fakeBiasMatrixCol = (char*)malloc(sizeof(int) );                                            // later on i need to free biasMatrixCols malloc, but because the original pointer will be altered, im saving original pointer so that it can be freed later
        char *biasMatrixCols = fakeBiasMatrixCol;
        biasMatrixCols = biasCommaIndicator+1;                                                      // biascommaindicator holds mem add from ',' till end, so i excluded ','
        int intbiasMatrixRows = atoi(biasMatrixRows);                                               // convert strings to ints
        int intbiasMatrixCols = atoi(biasMatrixCols);
        int biasposition = (floatend - (biasShapeIndicatorEnd)) + 1;                                // floatend holds the end of the string mem address, biasshapeindicator holds the ']' mem address
        char *biasMatrix = (char*)malloc( biasposition + 1  );                                             // allocate biasposition number of spaces in mem adress for biasmatrix
        memcpy(biasMatrix, (biasShapeIndicatorEnd+1), ((floatend - biasShapeIndicatorEnd)));        // populate biasmatrix
        biasMatrix[biasposition] = '\0';
        

        float *float_data1 = (float *)biasMatrix;
        float* array = (float*)malloc(finalRows * finalCols * sizeof(float));
        if (array == NULL) {
          return NULL;
        }
        for (int i = 0; i < finalRows; i++) {
            for (int j = 0; j < finalCols; j++) {
                array[i * finalCols + j] = float_data1[i * finalCols + j];     //(float)(i * cols + j);
            }
        }
        // for debugging purpose
        // for (int i = 0; i < finalRows; i++) {
        //     for (int j = 0; j < finalCols; j++) {
        //         Serial.printf("%0.5f ",array[i * finalCols + j]);     //(float)(i * cols + j);
        //     }
        //   Serial.printf("\n");
        // }

        free(tempstring);
        free(weightShape);
        free(weightMatrixRows);
        free(fakeWeightMatrixCols);
        free(weightMatrix);
        free(biasMatrix);
        free(biasShape);
        free(biasMatrixRows);
        free(fakeBiasMatrixCol);
        
        ccurrent = eend;
        return array;
    } // if (eend != NULL)
    else 
        return NULL;
    //return array;
}


dimension* getWeightDimensions(int posOfDollar, char* testing, int lengthOrig){
  //Serial.printf("inside getWeightTensor function\n");
    char *sstart, *eend, *ccurrent;
    int length = lengthOrig - 1;
    int position = 0;
    ccurrent = testing;
    sstart = (char*)memchr(ccurrent+posOfDollar, '$', length - (ccurrent - testing));
    eend = (char*)memchr(sstart+1, '$', length - ((sstart+1) - testing));
    //Serial.printf("debugger --> %c%c%c%c \n", *(sstart), *(sstart+1), *(sstart+2), *(sstart+3));
    //Serial.printf("debugger --> %c%c \n", *(eend), *(eend-1));
    int val = 0;
    while(val==0){
        if (eend != NULL && *(eend+1) == '['){
            val = 1;
            break;
        }
        else{
            char *temporary = (char*)memchr(eend+1, '$', (length - ((eend) - sstart)) );
            eend = temporary;
        } 
    }
  
    if (eend != NULL){
        position = eend - sstart - 1;
        char *tempstring = (char*)malloc(position + 1);
        memcpy(tempstring, sstart + 1, position);
        char *floatstart, *floatend, *floatmarker;
        int floatlength = (position + 1) - 1;
        char *weightShapeIndicatorEnd = strchr(tempstring, ']');
        char *weightShape = (char*)malloc(weightShapeIndicatorEnd - tempstring);
        
        strncpy(weightShape, tempstring+1, ((weightShapeIndicatorEnd - tempstring) - 1 ) );
        char *weightCommaIndicator = strchr(weightShape, ',');
        char *weightMatrixRows = (char*)malloc( (weightCommaIndicator - weightShape) );
        strncpy(weightMatrixRows, weightShape, (weightCommaIndicator - weightShape));
        char *fakeWeightMatrixCols = (char*)malloc( sizeof(int) );
        char *weightMatrixCols = fakeWeightMatrixCols;                                              // later on i need to free weightMatrixCols malloc, but because the original pointer will be altered, im saving original pointer so that it can be freed later
        weightMatrixCols = weightCommaIndicator+1;
        int intWeightMatrixRows = atoi(weightMatrixRows);
        int intWeightMatrixCols = atoi(weightMatrixCols);
        dimension* x = new dimension;                                                   // same as mallocly creating it, but this is the c++ way
        x->rows = intWeightMatrixRows; 
        x->cols = intWeightMatrixCols;
        
        return x;
    } // if (eend != NULL)
    else 
        return NULL;
}


dimension* getBiasDimensions(int posOfDollar, char* testing, int lengthOrig){
  char *sstart, *eend, *ccurrent;
  int length = lengthOrig - 1;
  int position = 0;
  ccurrent = testing;
  sstart = (char*)memchr(ccurrent+posOfDollar, '$', length - (ccurrent - testing));
  eend = (char*)memchr(sstart+1, '$', length - ((sstart+1) - testing));
  int val = 0;
  while(val==0){
      if (eend != NULL && *(eend+1) == '['){
          val = 1;
          break;
      }
      else{
          char *temporary = (char*)memchr(eend+1, '$', (length - ((eend) - sstart)) );
          eend = temporary;
      } 
  }
  if (eend != NULL){
      position = eend - sstart - 1;
      char *tempstring = (char*)malloc(position + 1);
      memcpy(tempstring, sstart + 1, position);
      char *floatstart, *floatend, *floatmarker;
      int floatlength = (position + 1) - 1;
      char *weightShapeIndicatorEnd = strchr(tempstring, ']');
      char *weightShape = (char*)malloc(weightShapeIndicatorEnd - tempstring);
      
      strncpy(weightShape, tempstring+1, ((weightShapeIndicatorEnd - tempstring) - 1 ) );
      char *weightCommaIndicator = strchr(weightShape, ',');
      char *weightMatrixRows = (char*)malloc( (weightCommaIndicator - weightShape) );
      strncpy(weightMatrixRows, weightShape, (weightCommaIndicator - weightShape));
      char *fakeWeightMatrixCols = (char*)malloc( sizeof(int) );
      char *weightMatrixCols = fakeWeightMatrixCols;                                              // later on i need to free weightMatrixCols malloc, but because the original pointer will be altered, im saving original pointer so that it can be freed later
      weightMatrixCols = weightCommaIndicator+1;
      int intWeightMatrixRows = atoi(weightMatrixRows);
      int intWeightMatrixCols = atoi(weightMatrixCols);
      floatstart = weightShapeIndicatorEnd+1;
      floatmarker = (char*)memchr(tempstring, '^', (floatlength));
      int valid = 0;
      while(valid==0){
          if (floatmarker != NULL && *(floatmarker+1) == '['){                                    // the reason i'm dereferencing floatmaker is because floatmaker only has the pointer to whole mem ad, but to check '[' we need to compare char to char, therefore,  i dereference floatmaker which gives me char at that point
              valid = 1;
              break;
          }
          else{
              char *temp = (char*)memchr(floatmarker+1, '^', (floatlength - (floatmarker-tempstring)) );
              floatmarker = temp;
          }  
      }
      
      floatend = floatstart  + floatlength;
      int floatposition = (floatmarker - floatstart - 1) + 1;
      char *weightMatrix = (char*)malloc(floatposition+1);
      memcpy(weightMatrix, floatstart, ((floatmarker - floatstart)));
      weightMatrix[floatposition] = '\0';

      char *biasShapeIndicatorEnd = strchr((floatmarker+1), ']');
      char *biasShape = (char*)malloc(biasShapeIndicatorEnd - (floatmarker+1));
      strncpy(biasShape, floatmarker+2, ((biasShapeIndicatorEnd - (floatmarker + 1)) - 1 ));
      char *biasCommaIndicator = strchr(biasShape, ',');
      char *biasMatrixRows = (char*)malloc( (biasCommaIndicator - biasShape) );
      strncpy(biasMatrixRows, biasShape, (biasCommaIndicator - biasShape));
      char *fakeBiasMatrixCol = (char*)malloc(sizeof(int) );                                    // later on i need to free biasMatrixCols malloc, but because the original pointer will be altered, im saving original pointer so that it can be freed later
      char *biasMatrixCols = fakeBiasMatrixCol;
      biasMatrixCols = biasCommaIndicator+1;                                                    // biascommaindicator holds mem add from ',' till end, so i excluded ','
      int intbiasMatrixRows = atoi(biasMatrixRows);                                             // convert strings to ints
      int intbiasMatrixCols = atoi(biasMatrixCols);
      dimension* x = new dimension;                                                             // same as mallocly creating it, but this is the c++ way
      x->rows = intbiasMatrixRows;
      x->cols = intbiasMatrixCols;
      return x;
    }
    else 
        return NULL;
}



