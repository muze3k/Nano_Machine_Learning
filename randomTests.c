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



int main(){
    char testString[] = "$[5,16]\xce\x4d\xcb\x3b\x00\xb9\x25\xbf\x2a\x49^[16,1]\x25\x40\x2d\xbd\x9e\x9b\x84\x3e$[16,8]$[5,16]\xce\x4d\xcb\x3b\x00\xb9\x25\xbf\x2a\x49^[16,1]\x25\x40\x2d\xbd\x9e\x9b\x84\x3e$[16,8]$";
    int totalLayers = 5; // total number of dollar signs(layers)
    int* address = getMemAddress(testString, totalLayers, sizeof(testString));  // this array now holds the position of all dollar signs
    //printf("print value %d\n", address);
    //printf("print value %c", *(address));
    for (int i = 0; i <= totalLayers; i++) {
        printf("%d\n", address[i]);
    }
    return 0;
}
