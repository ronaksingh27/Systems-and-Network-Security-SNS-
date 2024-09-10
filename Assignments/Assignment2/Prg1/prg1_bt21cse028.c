#include <stdio.h>
#include <gmp.h>
#include <ctype.h>
#include <string.h>

#define SHIFT 8
#define CHAR_SET_SIZE 37

// Function to map a character to its corresponding value based on the provided table
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

// Function to map a value back to its corresponding character based on the provided table
char val_to_char(int val) {
    if (val >= 0 && val <= 9) {
        return '0' + val; // 0-9 -> '0'-'9'
    } else if (val == 10) {
        return ' '; // 10 -> ' '
    } else if (val >= 11 && val <= 36) {
        return 'A' + (val - 11); // 11-36 -> 'A'-'Z'
    }
    return '?'; // Invalid value
}

// Function to perform Caesar Cipher using GMP for number shifts
void caesar_cipher_using_gmp(char *input, char *output) {
    mpz_t pos, shifted_pos;
    
    // Initialize GMP integers
    mpz_init(pos);
    mpz_init(shifted_pos);

    int i = 0;
    while (input[i] != '\0') {
        int char_val = char_to_val(input[i]); // Get character value

        if (char_val != -1) { // If valid character
            mpz_set_ui(pos, char_val); // Set the position in GMP
            mpz_add_ui(shifted_pos, pos, SHIFT); // Add the shift value
            mpz_mod_ui(shifted_pos, shifted_pos, CHAR_SET_SIZE); // Apply modulo 37 for wrapping

            int shifted_val = mpz_get_ui(shifted_pos); // Get shifted value
            output[i] = val_to_char(shifted_val); // Convert back to character
        } else {
            output[i] = input[i]; // For invalid characters, keep them unchanged
        }
        i++;
    }
    output[i] = '\0'; // Null-terminate the output string

    // Clear GMP integers
    mpz_clear(pos);
    mpz_clear(shifted_pos);
}

int main() {
    char input[1000];  // Buffer for input text
    char output[1000]; // Buffer for output text

    // Input plaintext
    printf("Enter plain text: ");
    fgets(input, sizeof(input), stdin);

    // Remove newline character if present
    input[strcspn(input, "\n")] = '\0';

    // Perform Caesar Cipher
    caesar_cipher_using_gmp(input, output);

    // Print the result in uppercase
    printf("%s\n", output);

    return 0;
}
