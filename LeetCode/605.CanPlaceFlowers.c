#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool canPlaceFlowers(int *garden, int gardenSize, int flowersToPlant){
    if (flowersToPlant == 0) return true;
    int planted = 0;

    if (gardenSize >= 1 && garden[0] == 0) {
        if (gardenSize == 1 || garden[1] == 0) {
            garden[0] = 1;
            planted++;
            if (planted >= flowersToPlant) return true;
        }
    }

    for (int i = 1; i < gardenSize - 1; i++){
        if (garden[i - 1] == 0 && garden[i] == 0 && garden[i + 1] == 0) {
            garden[i] = 1;
            planted++;
            if (planted >= flowersToPlant) return true;
        }
    }

    if (gardenSize >= 2 && garden[gardenSize - 1] == 0 && garden[gardenSize - 2] == 0) {
        planted++;
    }

    return planted >= flowersToPlant;
}

int main(){
    int garden[] = {0, 1, 0, 1, 0, 1, 0};
    int gardenSize = 7;
    int flowersToPlant = 3;

    bool result = canPlaceFlowers(garden, gardenSize, flowersToPlant);

    printf("%d", result);

    return 0;
}


