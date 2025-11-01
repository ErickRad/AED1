#include <stdio.h>
#include <stdlib.h>

#define arraySize 5

int *twoSum(int *array, int arrayLength, int targetSum, int *resultSize){
    for (int first = 0; first < arrayLength; first++){
        for (int second = first + 1; second < arrayLength; second++){
            if (array[first] + array[second] == targetSum){
                int *result = (int *)malloc(sizeof(int) * 2);
                result[0] = first;
                result[1] = second;
                *resultSize = 2;
                return result;
            }
        }
    }
    
    *resultSize = 0;
    return NULL;
}

int main(){
    int resultSize;
    int targetSum = 12;
    int array[arraySize] = {3, 8, 2, 7, 5};

    int *result = twoSum(array, arraySize, targetSum, &resultSize);

    if (result != NULL){
        printf("[%d, %d]\n", result[0], result[1]);
        free(result);
    }

    return 0;
}
