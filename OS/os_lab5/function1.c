#include <stdio.h>
#include <stdlib.h>
#include "lib.h"


// Вариант 27
int main() {
    printf("1 row length - count 'Pi' number\n");
    printf("2 x - count 'e' number\n");
    int variant;
    while (scanf("%d", &variant) > 0) {
        if (variant == 1) {
            int row_length;
            scanf("%d", &row_length);
            printf("Result of counting 'Pi': %.10lf\n", Pi(row_length));
        } else if (variant == 2) {
            int x;
            scanf("%d", &x);
            printf("Result of counting 'e': %.10lf\n", E(x));
        } else {
            printf("Entered invalid command!\n");
        }
    }
}