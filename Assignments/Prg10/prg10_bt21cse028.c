#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

bool is_primitive_root(int g, int p) {
    int phi = p - 1;
    for (int i = 1; i < phi; i++) {
        if (gcd(i, phi) == 1) {
            int res = 1;
            for (int j = 0; j < i; j++)
                res = (res * g) % p;
            if (res == 1)
                return false;
        }
    }
    return true;
}

void find_primitive_roots(int p) {
    for (int g = 2; g < p; g++) {
        if (is_primitive_root(g, p)) {
            printf("%d ", g);
        }
    }
    printf("\n");
}

int main(int argc, char *argv[]) {
    int p = atoi(argv[1]);
    find_primitive_roots(p);
    return 0;
}
