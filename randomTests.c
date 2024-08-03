#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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
    printf("size : %d\n,", size);
    while (counter <= size) {        
        printf("%c,", *str);
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

// [4,5] 4 rows 5 cols
float* getTensor(char* string, int position, int rows, int cols, int lengthOrig){
    //char* a = string;
    float *b = (float *)string;
    // Allocate memory for a 2D array of floats
    float* array = (float*)malloc(rows * cols * sizeof(float));
    if (array == NULL) {
        fprintf(stderr, "Memory allocation failed for getTensor function\n");
        exit(1);
    }
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%.5f ", b[i * cols + j]);
            //arr[i][j] = b[i * cols + j];
            array[i * cols + j] = b[i * cols + j];     //(float)(i * cols + j);
        }
        printf("\n");
    } // matrix printing for loop ends
    return array;
}



int main(){
    char testString[] = "$[5,16]\xce\x4d\xcb\x3b\x00\xb9\x25\xbf\x2a\x49^[16,1]\x25\x40\x2d\xbd\x9e\x9b\x84\x3e$[16,8]$[5,16]\xce\x4d\xcb\x3b\x00\xb9\x25\xbf\x2a\x49^[16,1]\x25\x40\x2d\xbd\x9e\x9b\x84\x3e$[16,8]$";
    char tensor[] = "\xf2\x1e\xd9\xbd\x3d\x5b\x66\x3f\x4e\x59\x4a\x3f\x0c\xcc\x46\x3f\x4c\x1b\xc6\x3e\x0d\xe5\x55\xbe\xff\x79\xcf\xbe\xff\xca\x5c\x3e\xa2\x2c\x59\xbc\xd0\x9c\x1a\xbf\x2e\x6d\x3f\x3f\x30\x7f\xd5\xbe\x70\x66\x1f\x3f\xac\x29\x2c\xbf\x6f\x7d\xdb\xbe\xd6\x7c\xfa\x3e\x56\x51\x1f\xbf\x11\x9a\xaa\xbe\xce\xf0\xdd\xbe\x6c\xef\x12\x3e\0";

    int totalLayers = 5; // total number of dollar signs(layers)
    int* address = getMemAddress(testString, totalLayers, sizeof(testString));  // this array now holds the position of all dollar signs
    //printf("print value %d\n", address);
    //printf("print value %c", *(address));
    for (int i = 0; i <= totalLayers; i++) {
        printf("%d\n", address[i]);
    }

    float* array = getTensor(tensor, 1, 4, 5, 82);
    printf("test: %0.5f", array[0 * 5 + 1]);
    free(array);


    return 0;
}

