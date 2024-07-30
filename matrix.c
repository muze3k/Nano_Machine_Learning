#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>


int matrix1[3][2]={
	{1,2},
	{1,2},
	{1,2}
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
	/* code */
	/*
	int *ptr = *matrix;

	printf("yay hellloooo\n");
	// Print the address of the matrix
    printf("Address of var: %p\n", (void *)&matrix);
    // Print the address stored in pointer ptr
    printf("Address stored in ptr: %p\n", (void *)ptr);
    // Print the address of the pointer itself
    printf("Address of ptr: %p\n", (void *)&ptr);
	*/


    int total = sizeof(matrix1)/sizeof(matrix1[0][0]);
    int matrows = sizeof(matrix1)/sizeof(matrix1[0]);
    int matcols = total/matrows;

	int total1 = sizeof(matrix2)/sizeof(matrix2[0][0]);
    int matrows1 = sizeof(matrix2)/sizeof(matrix2[0]);
    int matcols1 = total1/matrows1;
	

    matMul(*matrix1, matrows, matcols, *matrix2, matrows1, matcols1);
    // -----------------------------------------
    /*
    FILE *file = fopen("matrix_bytes1.bin", "rb");
    if (file == NULL) {
        perror("Failed to open file");
        return EXIT_FAILURE;
    }

    // Define the size of the matrix
    int rows = 1;
    int cols = 16;
    int matrix[rows][cols];

    // Read the bytes from the file into the matrix
    if (fread(matrix, sizeof(int), rows * cols, file) != rows * cols) {
        perror("Failed to read the correct amount of items");
        fclose(file);
        return EXIT_FAILURE;
    }

    // Close the file
    fclose(file);

    // Print the matrix to verify it's correct
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
    printf("%d \n\n", sizeof(float));
	*/


    // --------------------------------------

    
    //char data[] = "\xC\xAD\xFC>q\xA2\xE5>\xA0\x61\x3F\x3D\xC5\x11\x07@\x00\x00\x00\x00\xD4\x60\x05@\x00\x00\x00\x00\x55\x44\x6B\x3F\x00\x00\x00\x00\x00\x00\x00\x00\xA6\x2F\xF5>\x00\x00\x00\x00\xB2\xD6\x03\x3F\x00\x00\x00\x00\xDE\x2A\xE6\x3D\x00\x00\x00\x00";
    //char data[] = "xC\xad\xfc>q\xa2\xe5>\xa0a?=\xc5\x11\x07@\x00\x00\x00\x00\xd4`\x05@\x00\x00\x00\x00UDk?\x00\x00\x00\x00\x00\x00\x00\x00\xa6/\xf5>\x00\x00\x00\x00\xb2\xd6\x03?\x00\x00\x00\x00\xde*\xe6=\x00\x00\x00\x00";
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

    //char str[] = "4$0dense---\xce\x4d\xcb\x3b\x00\xb9\x25\xbf\x2a\x49\x31\xbf\x82\x39\xbf\x3d\x27\x2e\x30\x3e\xae\x1f\x46\x3e\x4d\x59\x80\xbe\x38\x12\x96\xbe\xad\x2b\xe4\x3e\x61\x8b\xf2\xbd\xa3\x42\x29\x3e\x7a\xba\x1f\xbf\x09\x57\x00\x3f\xe7\x5c\xfd\xbe\x85\xe6\x2a\xbf\xc2\xf5\x1c\xbf\x91\x97\xd9\x3e\x45\x1a\x45\xbd\x22\x05\x08\xbf\x28\xd5\xbe\x3e\x6d\x5a\x00\x3f\x92\xf0\x49\xbf\x60\x7e\x82\x3e\xb1\x5d\xa4\xbe\xba\x25\xcd\xbe\x2e\x04\x10\xbf\xeb\xea\xef\xbe\xec\x0e\x0d\xbf\x8a\x54\xd3\x3e\x3d\x81\xac\xbe\x17\x7f\xb3\xbd\x74\x49\xa2\xbe\xd6\xa8\xaa\x3d\xad\x75\xfa\xbd\x7d\x9f\xa5\xbe\x97\xbf\x7c\x3e\x85\x63\xb9\x3e\xda\xac\x3f\x3f\x97\xdb\x37\x3e\x06\x51\xff\x3e\xf3\xf4\x94\xbe\xa4\xbc\xc5\x3e\x69\x2f\xb0\x3e\x1a\xe4\xd0\x3a\x8e\xbd\x5f\xbe\x7c\x9c\x0b\xbf\xdb\x3a\x0b\xbf\x9e\x89\xb0\xbd\xde\x0e\xa2\x3d\xcc\xa7\xac\xbe\x66\xc5\xef\x3e\xca\x5a\x20\x3f\x48\x58\x7e\xbe\xa0\x31\x05\x3f\xbe\xc6\x8d\x3c\x57\xf7\x08\x3f\x53\x60\x05\x3e\x76\x2d\x23\xbf\x48\x09\xb8\x3e\x41\xec\x29\xbf\x48\xf9\xd2\x3d\x6f\x1e\x87\x3e\x81\x3a\x8c\xbe\x7e\xd7\x1b\x3e\x68\x19\x34\x3e\xe6\xde\x84\x3e\x53\xc5\x4b\xbf\x75\x86\x1c\x3f\xf5\x09\x8e\x3d\x87\xd1\x31\x3f\x1a\x99\x43\xbe\x79\x19\x5b\xbe\x27\x7e\xf0\xbe\x62\xe9\x32\xbf\xbc\xe3\xba\xbc\x4f\x5d\x22\xbf\x45\xe4\x04\x3f\x7e\x44\x1d\xbf\x2a\xd5\xe8\x3d\xfa\x58\x15\xbf---\x25\x40\x2d\xbd\x9e\x9b\x84\x3e\x52\xf6\x8e\x3e\x4f\x94\xed\x3d\x36\x94\x17\xbd\x8d\x7f\x88\x3e\x75\xc3\x09\xbe\x69\xd5\x90\xbc\xbb\xf5\x8c\x3e\xfa\x5e\x6a\x3e\x9a\xd1\xdb\x3b\x26\x15\x80\x3e\x00\x00\x00\x00\x67\xe0\x50\x3e\xaa\x98\x8a\x3e\x70\x49\x84\x3e$1dense_1---\x5f\xc9\x27\x3e\xff\x17\xeb\xbe\x2c\xec\x29\xbd\x48\x69\x52\x3e\x12\x04\x36\x3d\xd8\xee\xe7\x3e\x74\xbb\xcb\xbd\xe4\x4d\xd2\x3d\x00\x9d\xe7\x3e\xb6\xdb\x29\xbe\xb3\xfc\x25\x3f\xab\xa1\x7c\x3c\x56\xf9\xd3\x3e\xcc\x75\xab\x3e\x8e\x07\x09\x3f\xf3\xbc\x50\x3e\xbd\x73\x85\xbe\x1b\x70\x18\x3f\xc5\xb8\xa8\x3e\x15\xae\xae\x3e\xcb\x9c\x2f\x3f\x28\x28\xc5\xbe\x12\x20\xfd\x3d\xdc\x9d\x5d\xbe\x98\xc6\x93\xbe\xf8\x64\x21\x3f\xba\xbe\xb2\x3e\x17\xc6\x12\xbd\x93\x35\x9b\x3d\x40\x1a\x30\x3e\xe9\xd3\xda\xbd\x4a\x11\xa8\x3e\x78\x00\xb0\x3e\x70\xad\xb2\xbd\x87\xbe\x85\xbe\x9e\x46\xb1\x3e\x52\x12\x68\xbd\xa0\x59\x5e\xbe\x71\x36\xc8\x3e\x90\x8a\x49\x3e\xee\x33\x87\x3d\x30\x10\xe2\x3e\xd6\x1e\x9f\x3e\xe6\x06\x34\x3f\x80\xee\x63\x3d\xd0\x4d\xd9\xbd\x6b\x3a\x02\x3f\x07\xb1\x82\xbd\x38\x5c\x1a\x3e\x26\xe7\xca\xbd\xd3\xf6\xb8\x3c\xb0\x0c\xa1\xbe\x5d\x29\x91\x3e\x2c\x5a\xe3\xbe\x0b\xeb\xc9\xbe\x5b\x64\x47\x3e\xfe\xff\x71\x3e\xa9\xd3\xaf\x3e\x44\x73\x8b\xbe\xb2\x78\x1b\x3f\x72\x23\xfd\x3e\x30\x5a\x07\xbe\x9c\xe0\xf5\x3e\x28\xff\xc5\x3e\x14\xf1\xbb\x3e\x3d\x44\x39\xbe\x0d\x14\x30\x3f\x8d\xe4\xca\x3e\xc7\x3d\x04\x3f\xc4\x2f\xf2\xbe\x7d\x20\x05\x3f\xbc\xf3\xa6\xbe\x88\x01\x14\x3d\xf0\x01\x96\xbe\xb3\x27\x10\x3f\x3b\x61\x27\x3f\xc5\x9d\x1b\x3e\xc4\xf5\xc8\xbe\xae\xcd\xbd\x3e\x29\xac\x08\xbf\x69\xc7\xbd\xbe\xba\x30\x7d\x3e\x49\x27\x56\xbe\x6c\xec\x92\x3e\x6a\x1a\xa8\x3e\x88\x61\xb8\x3e\x0c\x03\xa8\xbe\xc4\x3c\x89\xbe\xfd\xab\x09\xbb\x7b\x8e\x69\xbd\x7e\x3a\x00\x3f\xa4\x58\xa2\x3e\xfb\xfd\x2d\xbb\x98\xb5\xfe\x3e\xb7\xc4\x4e\xbe\x5d\x63\x84\x3d\xd8\xa0\x5c\xbe\xd0\xd9\xeb\x3e\xfc\x28\xe2\xbe\x18\x6d\x8f\xbe\x8c\x1e\x96\xbe\xf0\x5a\x84\x3e\xa0\xe1\x28\xbe\x38\x85\x5b\xbe\x53\x3f\x8b\xbe\x22\xb6\x08\xbd\x5d\xad\x18\x3e\x56\xf3\xcf\x3e\xee\xf8\xc9\x3e\xa0\xf8\xf4\xbe\x81\x2c\xa3\xbe\x01\x84\xd2\xbe\xe4\xf0\x4d\xbe\x83\x4a\xa2\x3e\xb2\x07\x1a\x3f\x47\xbe\x41\x3e\xc3\xdb\x2b\x3f\x48\xd7\x7c\x3e\x50\x35\xb6\x3e\xbe\xb4\x08\xbe\xa3\x97\xb4\xbe\xe8\x71\x0d\x3f\x65\xe1\xf1\x3e\x85\x85\x9b\x3c\x4f\x16\x9f\x3e\x78\x20\x98\xbe\xf5\x3e\x55\xbe\x6b\x7b\x2f\x3e---\xb5\x62\xa3\xbc\xb5\xe9\x6f\x3e\xf8\x14\x67\x3e\x57\x9c\x69\x3e\xb0\x80\x78\x3e\x00\x00\x00\x00\x3a\x2c\x2f\x3d\x94\xf8\x5e\xbd$2dense_2---\x92\x75\xc7\x3e\x46\xe9\xce\x3e\x7a\xae\x1c\xbf\x4c\xab\x16\x3f\x56\xae\x1a\x3f\x9f\x4b\xbe\x3e\x76\xa6\xbe\x3e\xa9\x25\xf8\x3e\xb6\xbb\x44\x3f\x8b\x30\x1f\xbf\x00\x91\xd8\x3c\xf7\xbf\x06\xbf\x15\x6b\xd4\x3e\xff\xa1\x25\xbf\x5d\x34\xae\xbe\x5d\x6d\x8c\x3d\xaa\x07\x62\x3e\x92\x06\x9b\x3e\xe5\xbd\x17\xbf\xdc\x8b\x0e\xbf\x97\x56\x19\x3f\xc8\x25\x71\x3e\xbf\x18\x18\xbf\x5d\x34\x8c\xbe\x22\x8b\x27\x3e\x2a\x91\xc3\xbe\xb0\x01\x18\xbd\xa3\x92\xdc\x3d\x98\x25\xf5\xbe\x15\x1c\xcb\x3e\x88\x3e\x94\xbe\x6c\x4d\x2a\x3f---\x84\xdb\x52\x3e\x6f\x3c\xa7\xbc\x00\x00\x00\x00\xc9\x72\x85\xbd$3dense_3---\xf2\x1e\xd9\xbd\x3d\x5b\x66\x3f\x4e\x59\x4a\x3f\x0c\xcc\x46\x3f\x4c\x1b\xc6\x3e\x0d\xe5\x55\xbe\xff\x79\xcf\xbe\xff\xca\x5c\x3e\xa2\x2c\x59\xbc\xd0\x9c\x1a\xbf\x2e\x6d\x3f\x3f\x30\x7f\xd5\xbe\x70\x66\x1f\x3f\xac\x29\x2c\xbf\x6f\x7d\xdb\xbe\xd6\x7c\xfa\x3e\x56\x51\x1f\xbf\x11\x9a\xaa\xbe\xce\xf0\xdd\xbe\x6c\xef\x12\x3e---\xf3\x88\x50\x3e\x57\x9f\x2a\x3e\x4c\x3d\x31\x3e\xca\xf4\x31\x3e\x7f\x7f\x41\x3e$";
    //char str[] = "$popototo\xce\x4d\xcb\x3b\x3b$";

    /*  // this section will be removed possibly
    char *start, *end;
    int pos = 0;

    // Get the first occurrence of '$'
    start = strchr(str, '$');
    printf("%s\n", start);
    //printf(start);
    end = strchr(start + 1, '$');
    printf("%s", end);
    pos = end - start - 1;
    char *substring = malloc(pos + 1);
	strncpy(substring, start + 1, pos);
    substring[pos] = '\0';  // Null-terminate the substring

    // Print the extracted substring
    printf("Extracted substring: %s\n", substring);
    free(substring);
	*/


    int len = sizeof(str) - 1;  // Get the total length of the array, minus one for the null terminator
    char *start, *end, *current;
    int pos = 0;

    // Start the search from the beginning of the string
    current = str;

    while (current < str + len) {
        // Find the next '$' starting from 'current'
        start = memchr(current, '$', len - (current - str));

        // If no '$' found, break the loop
        if (start == NULL) break;

        // Find the next '$' after 'start'
        end = memchr(start + 1, '$', len - ((start + 1) - str));

        // Check if there's another '$'
        if (end != NULL) {
            // Calculate position for substring length
            pos = end - start - 1;

            // Allocate memory for the substring
            char *substring = malloc(pos + 1);
            if (substring == NULL) {
                fprintf(stderr, "Memory allocation failed\n");
                return 1;
            }

            // Copy the substring between the two '$' symbols
            memcpy(substring, start + 1, pos);
            substring[pos] = '\0';  // Null-terminate the substring

            // Print the extracted substring
            //printf("Extracted substring: %d\n", substring[10:14]);
            free(substring);

            // Move 'current' to 'end' for the next iteration
            current = end;
        } else {
            break;
        }
    }

    /*
    // Loop until no more '$' is found
    while (start != NULL) {
        // Find the next '$' starting search after the current '$'
        //printf("hello");
        end = strchr(start + 1, '$');

        // Check if there's another '$'
        if (end != NULL) {

            // Calculate position for substring length
            pos = end - start - 1;
            // Allocate memory for the substring
            char *substring = malloc(pos + 1);
            if (substring == NULL) {
                fprintf(stderr, "Memory allocation failed\n");
                return 1;
            }
            // Copy the substring between the two '$' symbols
            strncpy(substring, start + 1, pos);
            substring[pos] = '\0';  // Null-terminate the substring

            // Print the extracted substring
            printf("Extracted substring: %s\n", substring);
            free(substring);

            // Move start to the next '$'
            start = end;
        } else {
            // No more '$' symbols, break the loop
            break;
        }
    }
    */
    

    
	return 0;
}

// issue is i cant find the correct syntax to write binary string



/*

// --- delimiter code

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main() {
    char str[] = "$name---\xce\x4d\xcb\x00\x00---\xce\x4d\xcb$name1---\xce\x4d\xcb---\xce\x4d\xcb$";
    int len = sizeof(str) - 1;  // Get the total length of the array, minus one for the null terminator
    char *start, *end, *current, *part_start, *part_end;
    int pos = 0;

    current = str;

    while (current < str + len) {
        // Find the next '$' starting from 'current'
        start = memchr(current, '$', len - (current - str));
        if (start == NULL) break;
        
        // Find the next '$' after 'start'
        end = memchr(start + 1, '$', len - ((start + 1) - str));
        if (end == NULL) break;
        
        // Process the content between '$' symbols
        current = start + 1;
        while (current < end) {
            // Find the next '---' starting from 'current'
            part_start = memchr(current, '-', end - current);
            if (part_start == NULL || (end - part_start < 3) || memcmp(part_start, "---", 3) != 0) break;

            // Move to the end of '---'
            part_start += 3;
            
            // Find the next '---' after 'part_start'
            part_end = memchr(part_start, '-', end - part_start);
            if (part_end == NULL || (end - part_end < 3) || memcmp(part_end, "---", 3) != 0) {
                part_end = end;  // No more '---', so use 'end' as the stopping point
            }

            // Calculate position for substring length
            pos = part_end - part_start;
            
            // Allocate memory for the substring
            char *substring = malloc(pos + 1);
            if (substring == NULL) {
                fprintf(stderr, "Memory allocation failed\n");
                return 1;
            }

            // Copy the substring between '---'
            memcpy(substring, part_start, pos);
            substring[pos] = '\0';  // Null-terminate the substring

            // Print the extracted substring
            printf("Extracted substring: %s\n", substring);
            free(substring);

            // Move 'current' to 'part_end'
            current = part_end + 3;
        }

        // Move 'current' to 'end' for the next main iteration
        current = end;
    }

    return 0;
}


*/