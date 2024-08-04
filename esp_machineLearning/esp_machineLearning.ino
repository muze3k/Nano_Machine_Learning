#include "methods.h"
#include "model.h"
#include "operations.h"

int lengthOfArray = sizeof(testing);
int totalLayers = 4;
int* address;
float testData[] = {0.72779332,  1.12606976, -0.31331522, -0.05345183, -0.02599893};
//float* testDataPointer = testData;
float* weightArray;
float* biasArray;
//float* result;
//float* result1;
float* temp;


struct graph {
    int typeofActivation; // 1 is ReLU
    int weightRows;
    int weightCols;
    int biasRows;
    int biasCols;
};

struct result {  // this use to be float* result
  float* value;
  int rows;
  int cols;
};

graph x[4];
result y = {testData, 1, 5};

void setup() {
  Serial.begin(115200);
  x[0] = {1,5,16,16,1};
  x[1] = {1,16,8,8,1};
  x[2] = {1,8,4,4,1};
  x[3] = {1,4,5,5,1};
  
  address = getMemAddress(testing, totalLayers, sizeof(testing));
  for(int i = 0; i<4; i++){
    // problem is that when i = 3, even the first matMul fails
    Serial.printf("%d iteration\n", i);
    weightArray = getWeightTensor(address[i], testing, lengthOfArray, x[i].weightRows, x[i].weightCols); // i'm gonna have to turn this function into cpp files too, because they are still error prone
    biasArray = getBiasTensor(address[i], testing, lengthOfArray, x[i].biasRows, x[i].biasCols);
    temp = matMul(y.value, y.rows, y.cols, weightArray, x[i].weightRows, x[i].weightCols);
    y.value = temp;
    //y.rows = x[i].weightRows;
    y.cols = x[i].weightCols;
    //result1 = (float*)malloc( (y.rows)*(x[i].weightCols)*sizeof(float) );
    temp = matAdd(y.value, y.rows, y.cols, biasArray, x[i].biasRows, x[i].biasCols); 
    y.value = temp;
    y.cols = x[i].biasRows;
    temp = ReLU(y.value, y.rows, y.cols);
    y.value = temp;
  }
  
  //weightArray = getWeightTensor(address[0], testing, lengthOfArray, x[0].weightRows, x[0].weightCols);
  //biasArray = getBiasTensor(address[0], testing, lengthOfArray, x[0].biasRows, x[0].biasCols);
  //result = matMul(testDataPointer, 1, 5, weightArray, x[0].weightRows, x[0].weightCols);
  //result1 = (float*)malloc(16*sizeof(float));
  
  // adding the bias
  // for (int i = 0; i < 16; i++) {
  //       result1[i] = result[i] + biasArray[i];
  // }
  
  // a very crude ReLu 
  // for (int i = 0; i < 16; i++) {
  //     if(result1[i]<0){
  //         result1[i] = 0.0;
  //     }
  // }
}

void loop() {
  Serial.printf("---- first forward pass ----\n");
  for (int i = 0; i < y.cols; i++) {
    Serial.printf("%0.5f ", y.value[i]);
    //Serial.print(" ");
  }
  Serial.println("_*_");
  delay(2000);
}

