#include <stdio.h>

// Function to perform binary exponentiation with modular arithmetic
long long modular_exponentiation(long long base, long long exp, long long mod) {
    long long result = 1;
    base = base % mod;
    
    printf("Initial Base: %lld, Exponent: %lld, Modulo: %lld\n", base, exp, mod);
    
    while (exp > 0) {
        if (exp % 2 == 1) {  // If exp is odd
            result = (result * base) % mod;
            printf("Result updated: %lld (After multiplying with base)\n", result);
        }
        
        // Square the base
        base = (base * base) % mod;
        printf("Base squared: %lld\n", base);
        
        // Divide the exponent by 2
        exp = exp / 2;
        printf("Exponent halved: %lld\n", exp);
    }
    return result;
}

// Function to compute a^b % m using Fermat's Little Theorem
long long compute_using_fermat(long long a, long long b, long long m) {
    // Apply Fermat's Theorem only when m is prime
    if (m <= 1) {
        printf("Modulo m should be greater than 1 and prime for Fermat's Theorem to apply.\n");
        return -1;
    }

    // Reduce b mod (m-1) if m is prime
    b = b % (m - 1);
    printf("Reduced Exponent using Fermat: b mod (m-1) = %lld\n", b);
    
    // Compute a^b % m
    return modular_exponentiation(a, b, m);
}

int main() {
    long long a, b, m;
    
    // Input values
    printf("Enter base (a): ");
    scanf("%lld", &a);
    printf("Enter exponent (b): ");
    scanf("%lld", &b);
    printf("Enter prime modulo (m): ");
    scanf("%lld", &m);
    
    // Output the result
    long long result = compute_using_fermat(a, b, m);
    printf("Result: %lld^%lld %% %lld = %lld\n", a, b, m, result);

    return 0;
}
