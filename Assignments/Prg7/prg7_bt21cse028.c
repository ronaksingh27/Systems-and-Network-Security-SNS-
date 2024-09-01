#include <stdio.h>
#include <stdlib.h>

// Function to calculate gcd of two numbers
int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

// Extended Euclidean Algorithm to find x and y such that ax + my = gcd(a, m)
int extended_gcd(int a, int m, int *x, int *y) {
    if (m == 0) {
        *x = 1;
        *y = 0;
        return a;
    }
    int x1, y1;
    int gcd = extended_gcd(m, a % m, &x1, &y1);
    *x = y1;
    *y = x1 - (a / m) * y1;
    return gcd;
}

void solve_linear_congruence(int a, int b, int m) {
    int g = gcd(a, m);

    // Check if gcd(a, m) divides b
    if (b % g != 0) {
        printf("No\n");
        return;
    }

    // Find one particular solution using Extended Euclidean Algorithm
    int x0, y;
    extended_gcd(a, m, &x0, &y);

    // Normalize the solution to ensure that it solves the equation ax ≡ b (mod m)
    x0 = (x0 * (b / g)) % m;

    if (x0 < 0) {
        x0 += m;
    }

    // Number of solutions is gcd(a, m)
    printf("Yes\n");
    printf("Number of solutions: %d\n", g);

    // Generate all solutions in range [0, m-1]
    int i;
    for (i = 0; i < g; ++i) {
        int solution = (x0 + i * (m / g)) % m;
        printf("%d ", solution);
    }
    printf("\n");
}

int main() {
    int a, b, m;
    printf("Enter values for a, b and m: ");
    scanf("%d%d%d", &a, &b, &m);

    solve_linear_congruence(a, b, m);

    return 0;
}
