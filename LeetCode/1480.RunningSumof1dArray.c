#include <stdio.h>
#include <stdlib.h>

#define arraySize 5

int *runningSum(int *array, int arrayLength, int *returnSize){
    int *result = (int *)malloc(sizeof(int) * arrayLength);

    result[0] = array[0];

    for (int i = 1; i < arrayLength; i++){
        result[i] = result[i - 1] + array[i];
    }

    *returnSize = arrayLength;
    return result;
}

int main(){
    int array[arraySize] = {1, 2, 3, 4, 5};
    int returnSize;
    int arrayLength = arraySize;

    int *result = runningSum(array, arrayLength, &returnSize);

    printf("[");
    for (int i = 0; i < arrayLength; i++){
        printf("%d ", result[i]);
    }
    printf("]\n");

    free(result);

    return 0;
}
