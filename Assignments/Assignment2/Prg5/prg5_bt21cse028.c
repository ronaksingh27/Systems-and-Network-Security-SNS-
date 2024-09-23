#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <gmp.h>

// Function to generate the key in a cyclic manner
// until its length is equal to the original text
void generateKey(const char* str, const char* key, char* generatedKey) {
    int strLen = strlen(str);
    int keyLen = strlen(key);
    int i, j;

    for (i = 0, j = 0; i < strLen; i++, j++) {
        if (j == keyLen) {
            j = 0; // restart the key if it ends
        }
        generatedKey[i] = key[j]; // assign key character
    }
    generatedKey[i] = '\0'; // null terminate the generated key
}

// Function to generate the ciphertext using the key and GMP
void cipherText(const char* str, const char* key, char* cipherText) {
    int strLen = strlen(str);

    mpz_t gmp_str_char, gmp_key_char, gmp_mod_result;
    mpz_inits(gmp_str_char, gmp_key_char, gmp_mod_result, NULL);

    for (int i = 0; i < strLen; i++) {
        // converting characters to GMP numbers (ASCII minus 'A')
        mpz_set_ui(gmp_str_char, str[i] - 'A');
        mpz_set_ui(gmp_key_char, key[i] - 'A');

        // (str[i] + key[i]) % 26
        mpz_add(gmp_mod_result, gmp_str_char, gmp_key_char);
        mpz_mod_ui(gmp_mod_result, gmp_mod_result, 26);

        // convert back to ASCII
        cipherText[i] = mpz_get_ui(gmp_mod_result) + 'A';
    }
    cipherText[strLen] = '\0'; // null terminate

    mpz_clears(gmp_str_char, gmp_key_char, gmp_mod_result, NULL);
}

// Function to decrypt the ciphertext back to the original text using GMP
void originalText(const char* cipher_text, const char* key, char* orig_text) {
    int textLen = strlen(cipher_text);

    mpz_t gmp_cipher_char, gmp_key_char, gmp_mod_result;
    mpz_inits(gmp_cipher_char, gmp_key_char, gmp_mod_result, NULL);

    for (int i = 0; i < textLen; i++) {
        // converting characters to GMP numbers (ASCII minus 'A')
        mpz_set_ui(gmp_cipher_char, cipher_text[i] - 'A');
        mpz_set_ui(gmp_key_char, key[i] - 'A');

        // (cipher_text[i] - key[i] + 26) % 26
        mpz_sub(gmp_mod_result, gmp_cipher_char, gmp_key_char);
        mpz_add_ui(gmp_mod_result, gmp_mod_result, 26); // ensure non-negative
        mpz_mod_ui(gmp_mod_result, gmp_mod_result, 26);

        // convert back to ASCII
        orig_text[i] = mpz_get_ui(gmp_mod_result) + 'A';
    }
    orig_text[textLen] = '\0'; // null terminate

    mpz_clears(gmp_cipher_char, gmp_key_char, gmp_mod_result, NULL);
}

// Helper function to convert a string to uppercase
void toUpperCase(char* str) {
    for (int i = 0; str[i] != '\0'; i++) {
        str[i] = toupper(str[i]);
    }
}

int main() {
    char str[] = "systemandnetworksecurity";
    char keyword[] = "ronaksipghtqublvjwmxyzcde";

    // Convert to uppercase if needed
    toUpperCase(str);
    toUpperCase(keyword);

    // Create buffers for key, ciphertext, and decrypted text
    char key[strlen(str) + 1]; // +1 for null terminator
    char cipher_text[strlen(str) + 1];
    char decrypted_text[strlen(str) + 1];

    // Generate the key
    generateKey(str, keyword, key);

    // Generate ciphertext using GMP
    cipherText(str, key, cipher_text);
    printf("Ciphertext: %s\n", cipher_text);

    // Decrypt the ciphertext using GMP
    originalText(cipher_text, key, decrypted_text);
    printf("Original/Decrypted Text: %s\n", decrypted_text);

    return 0;
}
