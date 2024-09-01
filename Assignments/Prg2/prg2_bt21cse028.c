#include <stdio.h>
#include <stdlib.h>

void extendedEuclid(int a, int b, int *x, int *y) {
    if (b == 0) {
        *x = 1;
        *y = 0;
        return;
    }
    int x1, y1;
    extendedEuclid(b, a % b, &x1, &y1);
    *x = y1;
    *y = x1 - (a / b) * y1;
}

int main(int argc, char *argv[]) {
    int a = atoi(argv[1]);
    int b = atoi(argv[2]);
    int x, y;
    extendedEuclid(a, b, &x, &y);
    printf("%d %d\n", x, y);
    return 0;
}
