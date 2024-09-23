#include <stdio.h>
#include <stdlib.h>

int gcd(int a, int b) {
    while (b != 0) {
        int t = b;
        b = a % b;
        a = t;
    }
    return a;
}

void printCommonDivisors(int arr[], int n) {
    int result = arr[0];
    for (int i = 1; i < n; i++)
        result = gcd(result, arr[i]);

    for (int i = 1; i <= result; i++)
        if (result % i == 0)
            printf("%d ", i);
}

int main(int argc, char *argv[]) {
    int n = argc - 1;
    int *arr = malloc(n * sizeof(int));
    for (int i = 0; i < n; i++)
        arr[i] = atoi(argv[i + 1]);

    printCommonDivisors(arr, n);
    free(arr);
    return 0;
}
