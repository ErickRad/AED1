#include <stdio.h>
#include <stdbool.h>

bool lemonadeChange(int* bills, int billsSize) {
    int five = 0;
    int ten  = 0;

    for (int i = 0; i < billsSize; i++) {
        int bill = bills[i];

        if (bill == 5) {
            five++;
            continue;
        }

        if (bill == 10) {
            if (five < 1) {
                return false;
            }

            five--;
            ten++;
            continue;
        }

        if (bill == 20) {
            if (ten >= 1 && five >= 1) {
                ten--;
                five--;
                continue;
            }

            if (five >= 3) {
                five -= 3;
                continue;
            }

            return false;
        }
    }

    return true;
}

int main(void) {
    int tests[][10] = {
        {5,5,5,10,20},
        {5,5,10},
        {5,5,10,10,20},
        {5,5,5,5,20,20,20},
        {5,10,5,10,20}
    };

    int sizes[] = {5, 3, 5, 7, 5};
    const int numTests = sizeof(sizes) / sizeof(int);

    for (int t = 0; t < numTests; t++) {
        printf("Test #%d: ", t + 1);

        bool ok = lemonadeChange(tests[t], sizes[t]);

        if (ok) {
            printf("SUCCESS\n");
        } else {
            printf("FAIL\n");
        }
    }
}
