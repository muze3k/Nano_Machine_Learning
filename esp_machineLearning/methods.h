#ifndef METHODS_H
#define METHODS_H

#ifdef __cplusplus
extern "C" {
#endif

int* getMemAddress(char* str, int n, int size);
float* getWeightTensor(int posOfDollar, char* testing, int lengthOrig, int finalRows, int finalCols);
float* getBiasTensor(int posOfDollar, char* testing, int lengthOrig, int finalRows, int finalCols);

#ifdef __cplusplus
}
#endif

#endif // METHODS_H

