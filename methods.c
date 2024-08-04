#include <stdio.h>
#include <string.h>
#include <stdlib.h>


void parseModel(char *testing, int lengthOrig){
    //printf("inside the parseModel method in methods.c, %c\n", testing[1223]);
    char *sstart, *eend, *ccurrent;
    //int length = sizeof(testing) - 1;  // --> this is the problem, the length here is 7 for some reason
    int length = lengthOrig - 1;
    //printf("this is length %d\n", length);
    //printf("\nthis is string length : %d", length);
    int position = 0;
    ccurrent = testing;                                                                                 // ccurent now has the memory address of entire string
    //printf("this is ccurrent : %c\n", ccurrent[0]);
    // this is comparing ccurent with (testing which is char* plus length which is int)??
    //printf("this is mem address ccurrent : %d", ccurrent);
    //printf("this is mem address testing : %d", testing);
    while (ccurrent < testing + length){
        //printf("inside while loop\n");
        sstart = memchr(ccurrent, '$', length - (ccurrent - testing));                                  // syntax : memchr(string, searchElement, look for these many memory addresses). Therefore, sstart now has the memory address of first '$'
        //printf("this is sstart : %s\n", sstart);
        
        // this is the error, if x24 appear in the string, it thinks $ has occured
        eend = memchr(sstart+1, '$', length - ((sstart+1) - testing));                                  // start searching from first '$' up until the end, but now the total number of memory blocks to look for is decreased, hence used (sstart+1)
        int val = 0;
        //printf("\nfloatmarker ---> %c", *floatmarker);
        while(val==0){
            // here lies the problem, for some reason we are stuck in this while loop
            //printf("inside valid\n");
            if (eend != NULL && *(eend+1) == '['){                                    // the reason i'm dereferencing floatmaker is because floatmaker only has the pointer to whole mem ad, but to check '[' we need to compare char to char, therefore,  i dereference floatmaker which gives me char at that point
                val = 1;
                //printf("validated\n");
                break;
            }
            else{
                char *temporary = memchr(eend+1, '$', (length - ((eend) - sstart)) );
                eend = temporary;
                //printf("elsefied\n");
            } 
        }


        //printf("this is eend : %s", eend);
        if (eend != NULL){
            //printf("inside eendNULL\n");
            position = eend - sstart - 1;                                                               // position used for malloc variable declaration. new char[] would have this many elements
            char *tempstring = malloc(position + 1);
            memcpy(tempstring, sstart + 1, position);                                                   // new mallocly created tempstring is filled with elements found between two '$'
            //tempstring[position] = '\0';                                                              // Null-terminate the substring
            
            char *floatstart, *floatend, *floatmarker;
            //int floatlength = sizeof(tempstring) - 1;
            int floatlength = (position + 1) - 1;

            // get the values in [] which is the shape of matrix
            char *weightShapeIndicatorEnd = strchr(tempstring, ']');
            //printf("weightshapeindicator : %s\n", weightShapeIndicatorEnd);
            char *weightShape = malloc(weightShapeIndicatorEnd - tempstring);
            strncpy(weightShape, tempstring+1, ((weightShapeIndicatorEnd - tempstring) - 1 ) );
            //printf("weightshape : %s\n", weightShape);
            char *weightCommaIndicator = strchr(weightShape, ',');
            //printf("weightcommaindicator : %s\n", weightCommaIndicator);

            char *weightMatrixRows = malloc( (weightCommaIndicator - weightShape) );
            strncpy(weightMatrixRows, weightShape, (weightCommaIndicator - weightShape));
            //weightMatrixRows[ ((weightCommaIndicator - weightShape) + 1) ] = '\0';
            char *fakeWeightMatrixCols = malloc( sizeof(int) );
            char *weightMatrixCols = fakeWeightMatrixCols;                                              // later on i need to free weightMatrixCols malloc, but because the original pointer will be altered, im saving original pointer so that it can be freed later
            weightMatrixCols = weightCommaIndicator+1;
            int intWeightMatrixRows = atoi(weightMatrixRows);
            int intWeightMatrixCols = atoi(weightMatrixCols);
            
            printf("this is weight matrix rows : %s\n", weightMatrixRows);
            printf("this is weight matrix cols : %s\n", weightMatrixCols);


            //floatstart = tempstring;
            floatstart = weightShapeIndicatorEnd+1;
            //printf("floatstart : %c\n", *(floatstart));
            //printf("tempstring : %c\n", *(tempstring));
            //printf("\nthis is floatstart/tempstring : %s", floatstart);
            floatmarker = memchr(tempstring, '^', (floatlength));                                       // floatmarker would get the memory address of '^'
            // if (floatmarker == NULL) {
            //     // Handle the error: '^' character not found in the string
            //     fprintf(stderr, "Error: '^' character not found in the string.\n");
            //     // Continue with the rest of the program or perform an alternative action
            // } 
            
            // testing the state machine logic  - basically i will check if the next character from '^' is '[' or not, if yes then its correct parsing
            int valid = 0;
            //printf("\nfloatmarker ---> %c", *floatmarker);
            while(valid==0){
                // here lies the problem, for some reason we are stuck in this while loop
                //printf("inside valid\n");
                if (floatmarker != NULL && *(floatmarker+1) == '['){                                    // the reason i'm dereferencing floatmaker is because floatmaker only has the pointer to whole mem ad, but to check '[' we need to compare char to char, therefore,  i dereference floatmaker which gives me char at that point
                    valid = 1;
                    //printf("validated\n");
                    break;
                }
                else{
                    char *temp = memchr(floatmarker+1, '^', (floatlength - (floatmarker-tempstring)) );
                    floatmarker = temp;
                    //printf("elsefied\n");
                } 
                //printf("random tests\n"); 
            }
            //printf("outside valid\n");

            // state machine testing logic ends
            //printf("floatmarker : %s\n", floatmarker);
            //printf("floatmarker : %d\n", floatmarker);
            floatend = floatstart  + floatlength;                                                       // floatend has the memory address of last index
            //printf("floatend : %d\n", floatend);
            int floatposition = (floatmarker - floatstart - 1) + 1;                                     // floatposition decided how much memory to allocate for weight matrix
            //printf("floatposition : %d\n", floatposition);
            char *weightMatrix = malloc(floatposition+1);
            memcpy(weightMatrix, floatstart, ((floatmarker - floatstart)));
            weightMatrix[floatposition] = '\0';
            //printf("weightmatrix : %d\n", weightMatrix);
            float *removelater = (float *)weightMatrix;
            printf("this is true value of weight Matrix : %0.5f\n", removelater[0]);


            
            char *biasShapeIndicatorEnd = strchr((floatmarker+1), ']');                                 //floatmarker is where the second '^' is, therefore '[' would be floatmarker+1
            //printf("biasshapeindicatorend : %s\n", biasShapeIndicatorEnd);
            char *biasShape = malloc(biasShapeIndicatorEnd - (floatmarker+1));
            strncpy(biasShape, floatmarker+2, ((biasShapeIndicatorEnd - (floatmarker + 1)) - 1 ));      // populate biasShape
            //printf("biasShape : %s\n", biasShape);
            char *biasCommaIndicator = strchr(biasShape, ',');
            //printf("this is bias shape : %s\n", biasShape);
            char *biasMatrixRows = malloc( (biasCommaIndicator - biasShape) );
            strncpy(biasMatrixRows, biasShape, (biasCommaIndicator - biasShape));
            char *fakeBiasMatrixCol = malloc (sizeof(int) );                                            // later on i need to free biasMatrixCols malloc, but because the original pointer will be altered, im saving original pointer so that it can be freed later
            char *biasMatrixCols = fakeBiasMatrixCol;
            biasMatrixCols = biasCommaIndicator+1;                                                      // biascommaindicator holds mem add from ',' till end, so i excluded ','
            int intbiasMatrixRows = atoi(biasMatrixRows);                                               // convert strings to ints
            int intbiasMatrixCols = atoi(biasMatrixCols);

            //printf("this is bias matrix rows : %s\n", biasMatrixRows);
            //printf("this is bias matrix cols : %s\n", biasMatrixCols);

            int biasposition = (floatend - (biasShapeIndicatorEnd)) + 1;                                // floatend holds the end of the string mem address, biasshapeindicator holds the ']' mem address
            char *biasMatrix = malloc( biasposition + 1  );                                             // allocate biasposition number of spaces in mem adress for biasmatrix
            memcpy(biasMatrix, (biasShapeIndicatorEnd+1), ((floatend - biasShapeIndicatorEnd)));        // populate biasmatrix
            biasMatrix[biasposition] = '\0';                                                            // good practice i guess


            float *float_data = (float *)weightMatrix;                                                  // as the name suggests, this holds the weight matrix
            int wrows = intWeightMatrixRows, wcols = intWeightMatrixCols;                               // Dimensions of the weight matrix, maybe this is not necessary and cna be directly iterated
            printf("weight Matrix:\n");
            for (int i = 0; i < wrows; i++) {
                for (int j = 0; j < wcols; j++) {
                    printf("%.5f ", float_data[i * wcols + j]);
                }
                printf("\n");
            } // matrix printing for loop ends



            float *float_data1 = (float *)biasMatrix;
            //free(putin);
            //printf("%d", *float_data);
            // Print the matrix
            int crows = intbiasMatrixRows, ccols = intbiasMatrixCols;                                   // Dimensions of the matrix
            printf("bias Matrix:\n");
            for (int i = 0; i < crows; i++) {
                for (int j = 0; j < ccols; j++) {
                    printf("%.5f ", float_data1[i * ccols + j]);
                }
                printf("\n");
            } // matrix printing for loop

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
        } // if (eend != NULL)
    else break;   // this break is very important otherwise the while statement just keeps looping

    } // while
}

float* getWeightTensor(int posOfDollar, char* testing, int lengthOrig, int finalRows, int finalCols){
    char *sstart, *eend, *ccurrent;
    int length = lengthOrig - 1;
    int position = 0;
    ccurrent = testing;                                                                                 // ccurent now has the memory address of entire string
    //printf("this is ccurrent : %c\n", ccurrent[0]);
    // this is comparing ccurent with (testing which is char* plus length which is int)??
    printf("this is mem address ccurrent : %d", ccurrent);
    printf("this is mem address testing : %d", testing);
    //printf("inside while loop\n");
    sstart = memchr(ccurrent+posOfDollar, '$', length - (ccurrent - testing));                                  // syntax : memchr(string, searchElement, look for these many memory addresses). Therefore, sstart now has the memory address of first '$'
    //printf("this is sstart : %s\n", sstart);
    
    eend = memchr(sstart+1, '$', length - ((sstart+1) - testing));                                  // start searching from first '$' up until the end, but now the total number of memory blocks to look for is decreased, hence used (sstart+1)
    //printf("this is eend : %s", eend);
    int val = 0;
    //printf("\nfloatmarker ---> %c", *floatmarker);
    while(val==0){
        // here lies the problem, for some reason we are stuck in this while loop
        //printf("inside valid\n");
        if (eend != NULL && *(eend+1) == '['){                                    // the reason i'm dereferencing floatmaker is because floatmaker only has the pointer to whole mem ad, but to check '[' we need to compare char to char, therefore,  i dereference floatmaker which gives me char at that point
            val = 1;
            //printf("validated\n");
            break;
        }
        else{
            char *temporary = memchr(eend+1, '$', (length - ((eend) - sstart)) );
            eend = temporary;
            //printf("elsefied\n");
        } 
    }
    if (eend != NULL){
        //printf("inside eendNULL\n");
        position = eend - sstart - 1;                                                               // position used for malloc variable declaration. new char[] would have this many elements
        char *tempstring = malloc(position + 1);
        memcpy(tempstring, sstart + 1, position);                                                   // new mallocly created tempstring is filled with elements found between two '$'
        //tempstring[position] = '\0';                                                              // Null-terminate the substring
        
        char *floatstart, *floatend, *floatmarker;
        //int floatlength = sizeof(tempstring) - 1;
        int floatlength = (position + 1) - 1;

        // get the values in [] which is the shape of matrix
        char *weightShapeIndicatorEnd = strchr(tempstring, ']');
        //printf("weightshapeindicator : %s\n", weightShapeIndicatorEnd);
        char *weightShape = malloc(weightShapeIndicatorEnd - tempstring);
        strncpy(weightShape, tempstring+1, ((weightShapeIndicatorEnd - tempstring) - 1 ) );
        //printf("weightshape : %s\n", weightShape);
        char *weightCommaIndicator = strchr(weightShape, ',');
        //printf("weightcommaindicator : %s\n", weightCommaIndicator);

        char *weightMatrixRows = malloc( (weightCommaIndicator - weightShape) );
        strncpy(weightMatrixRows, weightShape, (weightCommaIndicator - weightShape));
        //weightMatrixRows[ ((weightCommaIndicator - weightShape) + 1) ] = '\0';
        char *fakeWeightMatrixCols = malloc( sizeof(int) );
        char *weightMatrixCols = fakeWeightMatrixCols;                                              // later on i need to free weightMatrixCols malloc, but because the original pointer will be altered, im saving original pointer so that it can be freed later
        weightMatrixCols = weightCommaIndicator+1;
        int intWeightMatrixRows = atoi(weightMatrixRows);
        int intWeightMatrixCols = atoi(weightMatrixCols);
        
        printf("this is weight matrix rows : %s\n", weightMatrixRows);
        printf("this is weight matrix cols : %s\n", weightMatrixCols);


        //floatstart = tempstring;
        floatstart = weightShapeIndicatorEnd+1;
        //printf("floatstart : %s\n", floatstart);
        //printf("tempstring : %s\n", tempstring);
        //printf("\nthis is floatstart/tempstring : %s", floatstart);
        floatmarker = memchr(tempstring, '^', (floatlength));                                       // floatmarker would get the memory address of '^'

        // testing the state machine logic  - basically i will check if the next character from '^' is '[' or not, if yes then its correct parsing
        int valid = 0;
        while(valid==0){
            if (floatmarker != NULL && *(floatmarker+1) == '['){                                    // the reason i'm dereferencing floatmaker is because floatmaker only has the pointer to whole mem ad, but to check '[' we need to compare char to char, therefore,  i dereference floatmaker which gives me char at that point
                valid = 1;
                break;
            }
            else{
                char *temp = memchr(floatmarker+1, '^', (floatlength - (floatmarker-tempstring)) );
                floatmarker = temp;
            }  
        }

        // state machine testing logic ends
        //printf("floatmarker : %s\n", floatmarker);
        //printf("floatmarker : %d\n", floatmarker);
        floatend = floatstart  + floatlength;                                                       // floatend has the memory address of last index
        //printf("floatend : %d\n", floatend);
        int floatposition = (floatmarker - floatstart - 1) + 1;                                     // floatposition decided how much memory to allocate for weight matrix
        //printf("floatposition : %d\n", floatposition);
        char *weightMatrix = malloc(floatposition+1);
        memcpy(weightMatrix, floatstart, ((floatmarker - floatstart)));
        weightMatrix[floatposition] = '\0';
        //printf("weightmatrix : %d\n", weightMatrix);
        float *removelater = (float *)weightMatrix;
        printf("this is true value of weight Matrix : %0.5f\n", removelater[0]);


        
        char *biasShapeIndicatorEnd = strchr((floatmarker+1), ']');                                 //floatmarker is where the second '^' is, therefore '[' would be floatmarker+1
        //printf("biasshapeindicatorend : %s\n", biasShapeIndicatorEnd);
        char *biasShape = malloc(biasShapeIndicatorEnd - (floatmarker+1));
        strncpy(biasShape, floatmarker+2, ((biasShapeIndicatorEnd - (floatmarker + 1)) - 1 ));      // populate biasShape
        //printf("biasShape : %s\n", biasShape);
        char *biasCommaIndicator = strchr(biasShape, ',');
        //printf("this is bias shape : %s\n", biasShape);
        char *biasMatrixRows = malloc( (biasCommaIndicator - biasShape) );
        strncpy(biasMatrixRows, biasShape, (biasCommaIndicator - biasShape));
        char *fakeBiasMatrixCol = malloc (sizeof(int) );                                            // later on i need to free biasMatrixCols malloc, but because the original pointer will be altered, im saving original pointer so that it can be freed later
        char *biasMatrixCols = fakeBiasMatrixCol;
        biasMatrixCols = biasCommaIndicator+1;                                                      // biascommaindicator holds mem add from ',' till end, so i excluded ','
        int intbiasMatrixRows = atoi(biasMatrixRows);                                               // convert strings to ints
        int intbiasMatrixCols = atoi(biasMatrixCols);

        //printf("this is bias matrix rows : %s\n", biasMatrixRows);
        //printf("this is bias matrix cols : %s\n", biasMatrixCols);

        int biasposition = (floatend - (biasShapeIndicatorEnd)) + 1;                                // floatend holds the end of the string mem address, biasshapeindicator holds the ']' mem address
        char *biasMatrix = malloc( biasposition + 1  );                                             // allocate biasposition number of spaces in mem adress for biasmatrix
        memcpy(biasMatrix, (biasShapeIndicatorEnd+1), ((floatend - biasShapeIndicatorEnd)));        // populate biasmatrix
        biasMatrix[biasposition] = '\0';                                                            // good practice i guess


        float *float_data = (float *)weightMatrix;                                                  // as the name suggests, this holds the weight matrix
        int wrows = intWeightMatrixRows, wcols = intWeightMatrixCols;                               // Dimensions of the weight matrix, maybe this is not necessary and cna be directly iterated
        printf("weight Matrix:\n");
        for (int i = 0; i < wrows; i++) {
            for (int j = 0; j < wcols; j++) {
                printf("%.5f ", float_data[i * wcols + j]);
            }
            printf("\n");
        } // matrix printing for loop ends

        // ---->
        //float *b = (float *)string;
        // Allocate memory for a 2D array of floats
        float* array = (float*)malloc(finalRows * finalCols * sizeof(float));
        if (array == NULL) {
            fprintf(stderr, "Memory allocation failed for getTensor function\n");
            exit(1);
        }
        for (int i = 0; i < finalRows; i++) {
            for (int j = 0; j < finalCols; j++) {
                //printf("%.5f ", float_data[i * finalCols + j]);
                //arr[i][j] = b[i * cols + j];
                array[i * finalCols + j] = float_data[i * finalCols + j];     //(float)(i * cols + j);
            }
            //printf("\n");
        } // matrix printing for loop ends
        //return array;
        
        // ---->


        float *float_data1 = (float *)biasMatrix;
        //free(putin);
        //printf("%d", *float_data);
        // Print the matrix
        int crows = intbiasMatrixRows, ccols = intbiasMatrixCols;                                   // Dimensions of the matrix
        printf("bias Matrix:\n");
        for (int i = 0; i < crows; i++) {
            for (int j = 0; j < ccols; j++) {
                printf("%.5f ", float_data1[i * ccols + j]);
            }
            printf("\n");
        } // matrix printing for loop

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
        printf("broken\n");   // this break is very important otherwise the while statement just keeps looping
        return NULL;
}


float* getBiasTensor(int posOfDollar, char* testing, int lengthOrig, int finalRows, int finalCols){
    char *sstart, *eend, *ccurrent;
    int length = lengthOrig - 1;
    int position = 0;
    ccurrent = testing;                                                                                 // ccurent now has the memory address of entire string
    //printf("this is ccurrent : %c\n", ccurrent[0]);
    // this is comparing ccurent with (testing which is char* plus length which is int)??
    printf("this is mem address ccurrent : %d", ccurrent);
    printf("this is mem address testing : %d", testing);
    //printf("inside while loop\n");
    sstart = memchr(ccurrent+posOfDollar, '$', length - (ccurrent - testing));                                  // syntax : memchr(string, searchElement, look for these many memory addresses). Therefore, sstart now has the memory address of first '$'
    //printf("this is sstart : %s\n", sstart);
    
    eend = memchr(sstart+1, '$', length - ((sstart+1) - testing));                                  // start searching from first '$' up until the end, but now the total number of memory blocks to look for is decreased, hence used (sstart+1)
    //printf("this is eend : %s", eend);
    int val = 0;
    //printf("\nfloatmarker ---> %c", *floatmarker);
    while(val==0){
        // here lies the problem, for some reason we are stuck in this while loop
        //printf("inside valid\n");
        if (eend != NULL && *(eend+1) == '['){                                    // the reason i'm dereferencing floatmaker is because floatmaker only has the pointer to whole mem ad, but to check '[' we need to compare char to char, therefore,  i dereference floatmaker which gives me char at that point
            val = 1;
            //printf("validated\n");
            break;
        }
        else{
            char *temporary = memchr(eend+1, '$', (length - ((eend) - sstart)) );
            eend = temporary;
            //printf("elsefied\n");
        } 
    }
    if (eend != NULL){
        //printf("inside eendNULL\n");
        position = eend - sstart - 1;                                                               // position used for malloc variable declaration. new char[] would have this many elements
        char *tempstring = malloc(position + 1);
        memcpy(tempstring, sstart + 1, position);                                                   // new mallocly created tempstring is filled with elements found between two '$'
        //tempstring[position] = '\0';                                                              // Null-terminate the substring
        
        char *floatstart, *floatend, *floatmarker;
        //int floatlength = sizeof(tempstring) - 1;
        int floatlength = (position + 1) - 1;

        // get the values in [] which is the shape of matrix
        char *weightShapeIndicatorEnd = strchr(tempstring, ']');
        //printf("weightshapeindicator : %s\n", weightShapeIndicatorEnd);
        char *weightShape = malloc(weightShapeIndicatorEnd - tempstring);
        strncpy(weightShape, tempstring+1, ((weightShapeIndicatorEnd - tempstring) - 1 ) );
        //printf("weightshape : %s\n", weightShape);
        char *weightCommaIndicator = strchr(weightShape, ',');
        //printf("weightcommaindicator : %s\n", weightCommaIndicator);

        char *weightMatrixRows = malloc( (weightCommaIndicator - weightShape) );
        strncpy(weightMatrixRows, weightShape, (weightCommaIndicator - weightShape));
        //weightMatrixRows[ ((weightCommaIndicator - weightShape) + 1) ] = '\0';
        char *fakeWeightMatrixCols = malloc( sizeof(int) );
        char *weightMatrixCols = fakeWeightMatrixCols;                                              // later on i need to free weightMatrixCols malloc, but because the original pointer will be altered, im saving original pointer so that it can be freed later
        weightMatrixCols = weightCommaIndicator+1;
        int intWeightMatrixRows = atoi(weightMatrixRows);
        int intWeightMatrixCols = atoi(weightMatrixCols);
        
        printf("this is weight matrix rows : %s\n", weightMatrixRows);
        printf("this is weight matrix cols : %s\n", weightMatrixCols);


        //floatstart = tempstring;
        floatstart = weightShapeIndicatorEnd+1;
        //printf("floatstart : %s\n", floatstart);
        //printf("tempstring : %s\n", tempstring);
        //printf("\nthis is floatstart/tempstring : %s", floatstart);
        floatmarker = memchr(tempstring, '^', (floatlength));                                       // floatmarker would get the memory address of '^'

        // testing the state machine logic  - basically i will check if the next character from '^' is '[' or not, if yes then its correct parsing
        int valid = 0;
        while(valid==0){
            if (floatmarker != NULL && *(floatmarker+1) == '['){                                    // the reason i'm dereferencing floatmaker is because floatmaker only has the pointer to whole mem ad, but to check '[' we need to compare char to char, therefore,  i dereference floatmaker which gives me char at that point
                valid = 1;
                break;
            }
            else{
                char *temp = memchr(floatmarker+1, '^', (floatlength - (floatmarker-tempstring)) );
                floatmarker = temp;
            }  
        }

        // state machine testing logic ends
        //printf("floatmarker : %s\n", floatmarker);
        //printf("floatmarker : %d\n", floatmarker);
        floatend = floatstart  + floatlength;                                                       // floatend has the memory address of last index
        //printf("floatend : %d\n", floatend);
        int floatposition = (floatmarker - floatstart - 1) + 1;                                     // floatposition decided how much memory to allocate for weight matrix
        //printf("floatposition : %d\n", floatposition);
        char *weightMatrix = malloc(floatposition+1);
        memcpy(weightMatrix, floatstart, ((floatmarker - floatstart)));
        weightMatrix[floatposition] = '\0';
        //printf("weightmatrix : %d\n", weightMatrix);
        float *removelater = (float *)weightMatrix;
        printf("this is true value of weight Matrix : %0.5f\n", removelater[0]);


        
        char *biasShapeIndicatorEnd = strchr((floatmarker+1), ']');                                 //floatmarker is where the second '^' is, therefore '[' would be floatmarker+1
        //printf("biasshapeindicatorend : %s\n", biasShapeIndicatorEnd);
        char *biasShape = malloc(biasShapeIndicatorEnd - (floatmarker+1));
        strncpy(biasShape, floatmarker+2, ((biasShapeIndicatorEnd - (floatmarker + 1)) - 1 ));      // populate biasShape
        //printf("biasShape : %s\n", biasShape);
        char *biasCommaIndicator = strchr(biasShape, ',');
        //printf("this is bias shape : %s\n", biasShape);
        char *biasMatrixRows = malloc( (biasCommaIndicator - biasShape) );
        strncpy(biasMatrixRows, biasShape, (biasCommaIndicator - biasShape));
        char *fakeBiasMatrixCol = malloc (sizeof(int) );                                            // later on i need to free biasMatrixCols malloc, but because the original pointer will be altered, im saving original pointer so that it can be freed later
        char *biasMatrixCols = fakeBiasMatrixCol;
        biasMatrixCols = biasCommaIndicator+1;                                                      // biascommaindicator holds mem add from ',' till end, so i excluded ','
        int intbiasMatrixRows = atoi(biasMatrixRows);                                               // convert strings to ints
        int intbiasMatrixCols = atoi(biasMatrixCols);

        //printf("this is bias matrix rows : %s\n", biasMatrixRows);
        //printf("this is bias matrix cols : %s\n", biasMatrixCols);

        int biasposition = (floatend - (biasShapeIndicatorEnd)) + 1;                                // floatend holds the end of the string mem address, biasshapeindicator holds the ']' mem address
        char *biasMatrix = malloc( biasposition + 1  );                                             // allocate biasposition number of spaces in mem adress for biasmatrix
        memcpy(biasMatrix, (biasShapeIndicatorEnd+1), ((floatend - biasShapeIndicatorEnd)));        // populate biasmatrix
        biasMatrix[biasposition] = '\0';                                                            // good practice i guess


        float *float_data = (float *)weightMatrix;                                                  // as the name suggests, this holds the weight matrix
        int wrows = intWeightMatrixRows, wcols = intWeightMatrixCols;                               // Dimensions of the weight matrix, maybe this is not necessary and cna be directly iterated
        printf("weight Matrix:\n");
        for (int i = 0; i < wrows; i++) {
            for (int j = 0; j < wcols; j++) {
                printf("%.5f ", float_data[i * wcols + j]);
            }
            printf("\n");
        } // matrix printing for loop ends

        // ---->
        //float *b = (float *)string;
        // Allocate memory for a 2D array of floats
        // float* array = (float*)malloc(finalRows * finalCols * sizeof(float));
        // if (array == NULL) {
        //     fprintf(stderr, "Memory allocation failed for getTensor function\n");
        //     exit(1);
        // }
        // for (int i = 0; i < finalRows; i++) {
        //     for (int j = 0; j < finalCols; j++) {
        //         //printf("%.5f ", float_data[i * finalCols + j]);
        //         //arr[i][j] = b[i * cols + j];
        //         array[i * finalCols + j] = float_data[i * finalCols + j];     //(float)(i * cols + j);
        //     }
        //     //printf("\n");
        // } // matrix printing for loop ends
        //return array;
        
        // ---->


        float *float_data1 = (float *)biasMatrix;
        //free(putin);
        //printf("%d", *float_data);
        // Print the matrix
        int crows = intbiasMatrixRows, ccols = intbiasMatrixCols;                                   // Dimensions of the matrix
        printf("bias Matrix:\n");
        for (int i = 0; i < crows; i++) {
            for (int j = 0; j < ccols; j++) {
                //printf("%.5f ", float_data1[i * ccols + j]);
            }
            //printf("\n");
        } // matrix printing for loop

        float* array = (float*)malloc(finalRows * finalCols * sizeof(float));
        if (array == NULL) {
            fprintf(stderr, "Memory allocation failed for getTensor function\n");
            exit(1);
        }
        for (int i = 0; i < finalRows; i++) {
            for (int j = 0; j < finalCols; j++) {
                //printf("%.5f ", float_data[i * finalCols + j]);
                //arr[i][j] = b[i * cols + j];
                array[i * finalCols + j] = float_data1[i * finalCols + j];     //(float)(i * cols + j);
            }
            //printf("\n");
        }
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
        printf("broken\n");   // this break is very important otherwise the while statement just keeps looping
        return NULL;
}

float* matMul(float* matrixA, int matrixArows, int matrixAcols, float* matrixB, int matrixBrows, int matrixBcols){
    
    //printf("--> in methods function: %0.5f\n", matrixB[0 * matrixBcols + 1]);
    //printf("\nperforming matMul\n");
    printf("\n\ninside matMUL MatrixA:\n");
    for (int i = 0; i < matrixArows; i++) {
        for (int j = 0; j < matrixAcols; j++) {
            printf("%.5f ", matrixA[i * matrixAcols + j]);
        }
        printf("\n");
    }

    printf("\n\ninside matMUL MatrixB:\n");
    for (int i = 0; i < matrixBrows; i++) {
        for (int j = 0; j < matrixBcols; j++) {
            printf("%.5f ", matrixB[i * matrixBcols + j]);
        }
        printf("\n");
    }

    if (matrixAcols != matrixBrows) {
    printf("Matrix multiplication not possible\n\n");
    return NULL;
    }

    printf("\n\n--------matrix multiplication in detail-----------\n");
    //float resultantMatrix[matrixArows][matrixBcols]; // Adjust size based on your matrices
    float* resultantMatrix = (float*)malloc(matrixArows * matrixBcols * sizeof(float));
    if (resultantMatrix == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }


	for (int i = 0; i < matrixArows; i++) {
		for (int j = 0; j < matrixBcols; j++) {
		  //resultantMatrix[i][j] = 0; // Initialize elements to zero
          printf("i:%d, j:%d\n", i, j);
		  for (int k = 0; k < matrixAcols; k++) {
		    //resultantMatrix[i][j] += matrixA[i][k] * matrixB[k][j];
            //printf("val:%0.5f   ", (*(matrixB + k * matrixBcols + j)));
            //printf("resultantMatrix:%0.5f\n", resultantMatrix[i][j]);
		  	//resultantMatrix[i][j] += (*(matrixA + i * matrixAcols + k)) * (*(matrixB + k * matrixBcols + j));
            resultantMatrix[i *matrixBcols +j] += (*(matrixA + i * matrixAcols + k)) * (*(matrixB + k * matrixBcols + j));
		  }
		}
	}
    //printf("--> in methods function: %0.5f\n", resultantMatrix[0 * matrixBcols + 0]);


    for (int i = 0; i < matrixArows; i++) {
        for (int j = 0; j < matrixBcols; j++) {
            printf("%.5f ", resultantMatrix[i * matrixBcols + j]);
        }
        printf("\n");
    }
    
    return resultantMatrix;
}


// returns the positions of dollar signs in the long string
int* getMemAddress(char* str, int n, int size){
    //int dollarSign[n];  // so that we can access dollar sign just by passing the number where it resides in string
    int* dollarSign = malloc(n * sizeof(int));   // so that we can access dollar sign just by passing the number where it resides in string
    if (dollarSign == NULL) {
        fprintf(stderr, "Memory allocation failed while creating array in getMemAddress\n");
        exit(1);
    }
    int count = 0;  // increases when dollar encountered
    int counter = 0; // increases every iteration
    //int size = sizeof(str);
    //printf("size : %d\n,", size);
    while (counter <= size) {        
        //printf("%c,", *str);
        if (*str == '$') {
            count++;
            dollarSign[count] = counter;  // populate array with $ position in string
            if (count == n) {
                //return str;  // Return the pointer to the nth "$"
            }
        }
        str++;
        counter++;
    }
    //printf("not found\n");
    return dollarSign;  // If the nth "$" is not found, return NULL
}

