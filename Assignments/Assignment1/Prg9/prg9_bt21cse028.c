#include <stdio.h>
#include <stdlib.h>

int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int order(int a, int m) {
    if (gcd(a, m) != 1)
        return -1;
    int result = 1;
    int x = a % m;
    while (x != 1) {
        x = x * a % m;
        result++;
    }
    return result;
}

int main(int argc, char *argv[]) {
    int a = atoi(argv[1]);
    int m = atoi(argv[2]);
    int result = order(a, m);
    if (result == -1)
        printf("a and m must be coprime\n");
    else
        printf("%d\n", result);
    return 0;
}
