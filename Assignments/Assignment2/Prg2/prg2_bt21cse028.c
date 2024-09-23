#include <stdio.h>
#include <gmp.h>
#include <string.h>

#define K1 8
#define K2 2
#define MOD 37 // Alphabet size (including alphanumeric + space)

// Function to map a character to its numeric equivalent from the table
int char_to_val(char c) {
    if (c >= '0' && c <= '9') {
        return c - '0'; // '0'-'9' -> 0-9
    } else if (c == ' ') {
        return 10; // ' ' -> 10
    } else if (c >= 'a' && c <= 'z') {
        return c - 'a' + 11; // 'a'-'z' -> 11-36
    }
    return -1; // Invalid character
}

// Function to map a numeric value back to its corresponding character
char val_to_char(int val) {
    if (val >= 0 && val <= 9) {
        return '0' + val; // 0-9 -> '0'-'9'
    } else if (val == 10) {
        return ' '; // 10 -> ' '
    } else if (val >= 11 && val <= 36) {
        return 'a' + (val - 11); // 11-36 -> 'A'-'Z'
    }
    return '?'; // Invalid value
}

// Affine Cipher encryption: E(x) = (k1 * x + k2) % mod
void affine_encrypt(char *input, char *output) {
    mpz_t k1, k2, x, encrypted_val, mod;
    
    mpz_init_set_ui(k1, K1);
    mpz_init_set_ui(k2, K2);
    mpz_init(x);
    mpz_init(encrypted_val);
    mpz_init_set_ui(mod, MOD);

    int i = 0;
    while (input[i] != '\0') {
        int char_val = char_to_val(input[i]); // Convert character to numeric value

        if (char_val != -1) { // If it's a valid character
            mpz_set_ui(x, char_val); // Set x = char_val
            mpz_mul(encrypted_val, k1, x); // encrypted_val = k1 * x
            mpz_add(encrypted_val, encrypted_val, k2); // encrypted_val = k1 * x + k2
            mpz_mod(encrypted_val, encrypted_val, mod); // encrypted_val = (k1 * x + k2) % MOD
            
            output[i] = val_to_char(mpz_get_ui(encrypted_val)); // Convert numeric value back to character
        } else {
            output[i] = input[i]; // Non-alphabet characters are unchanged
        }
        i++;
    }
    output[i] = '\0'; // Null-terminate the output string

    // Clear GMP variables
    mpz_clear(k1);
    mpz_clear(k2);
    mpz_clear(x);
    mpz_clear(encrypted_val);
    mpz_clear(mod);
}

// Affine Cipher decryption: D(y) = k1_inv * (y - k2) % mod
void affine_decrypt(char *input, char *output) {
    mpz_t k1_inv, k2, y, decrypted_val, mod, temp;
    
    mpz_init_set_ui(k2, K2);
    mpz_init(y);
    mpz_init(decrypted_val);
    mpz_init(temp);
    mpz_init_set_ui(mod, MOD);

    // Find k1_inv (inverse of k1 mod MOD)
    mpz_init(k1_inv);
    mpz_set_ui(k1_inv, K1);
    if (mpz_invert(k1_inv, k1_inv, mod) == 0) {
        printf("No modular inverse exists for K1!\n");
        return;
    }

    int i = 0;
    while (input[i] != '\0') {
        int char_val = char_to_val(input[i]); // Convert character to numeric value

        if (char_val != -1) { // If it's a valid character
            mpz_set_ui(y, char_val); // Set y = char_val
            mpz_sub(temp, y, k2); // temp = y - k2
            mpz_mul(decrypted_val, k1_inv, temp); // decrypted_val = k1_inv * (y - k2)
            mpz_mod(decrypted_val, decrypted_val, mod); // decrypted_val = (k1_inv * (y - k2)) % MOD
            
            if (mpz_cmp_ui(decrypted_val, 0) < 0) { // Handle negative result by adding MOD
                mpz_add(decrypted_val, decrypted_val, mod);
            }
            
            output[i] = val_to_char(mpz_get_ui(decrypted_val)); // Convert numeric value back to character
        } else {
            output[i] = input[i]; // Non-alphabet characters are unchanged
        }
        i++;
    }
    output[i] = '\0'; // Null-terminate the output string

    // Clear GMP variables
    mpz_clear(k1_inv);
    mpz_clear(k2);
    mpz_clear(y);
    mpz_clear(decrypted_val);
    mpz_clear(temp);
    mpz_clear(mod);
}


int main() {
    char input[1000];  // Buffer for input text
    char encrypted[1000]; // Buffer for encrypted text
    char temp[1000];
    char decrypted[1000]; // Buffer for decrypted text

    // Input plaintext
    printf("Enter plain text: ");
    fgets(input, sizeof(input), stdin);

    // Remove newline character if present
    input[strcspn(input, "\n")] = '\0';

    // Perform Affine Cipher encryption
    affine_encrypt(input, encrypted);
    printf("Encrypted text: %s\n", encrypted);
    

    // Perform Affine Cipher decryption
    affine_decrypt(encrypted, decrypted);
    printf("Decrypted text: %s\n", decrypted);

    return 0;
}
