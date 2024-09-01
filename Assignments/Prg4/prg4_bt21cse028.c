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

void printRRSM(int m) {
    int phi_m = 0;  // To count the number of elements in RRSM
    for (int i = 1; i < m; i++) {
        if (gcd(i, m) == 1) {  // If i is coprime with m
            printf("%d ", i);
            phi_m++;
        }
    }
    printf("\nφ(%d) = %d\n", m, phi_m);  // Print the value of φ(m)
}

int main(int argc, char *argv[]) {
    int m = atoi(argv[1]);
    printRRSM(m);
    return 0;
}
