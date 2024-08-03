void parseModel(char *testing, int lengthOrig);
int* getMemAddress(char* str, int n, int size);
float* getWeightTensor(int posOfDollar, char* testing, int lengthOrig, int finalRows, int finalCols);
float* getBiasTensor(int posOfDollar, char* testing, int lengthOrig, int finalRows, int finalCols);
float* matMul(float* matrixA, int matrixArows, int matrixAcols, float* matrixB, int matrixBrows, int matrixBcols);