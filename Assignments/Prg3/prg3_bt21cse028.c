#include <stdio.h>
#include <stdlib.h>

void primeFactors(int n) {
    for (int i = 2; i * i <= n; i++) {
        while (n % i == 0) {
            printf("%d ", i);
            n /= i;
        }
    }
    if (n > 1)
        printf("%d ", n);
}

int main(int argc, char *argv[]) {
    int n = atoi(argv[1]);
    primeFactors(n);
    return 0;
}
