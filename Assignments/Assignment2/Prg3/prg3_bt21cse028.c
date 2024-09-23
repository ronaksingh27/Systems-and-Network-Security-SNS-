#include <stdio.h>
#include <gmp.h>
#include <string.h>
#include <ctype.h>

#define PT_SPACE 37  // Number of alphanumeric characters and space (0-9, a-z, space)

// Function to get the index in the table based on character
int char_to_index(char c) {
    if (c >= '0' && c <= '9')
        return c - '0';
    else if (c >= 'a' && c <= 'z')
        return c - 'a' + 11; // 'a' starts at index 11
    else if (c == ' ')
        return 10; // space is at index 10
    return -1;
}

// Function to get the character based on index in the table
char index_to_char(int index) {
    if (index >= 0 && index <= 9)
        return '0' + index;
    else if (index == 10)
        return ' ';
    else if (index >= 11 && index <= 36)
        return 'a' + (index - 11);
    return '?';
}

// Function to encrypt the plaintext using Autokey Cipher
void autokey_encrypt(const char *plaintext, char *ciphertext, int initial_key) {
    int pt_len = strlen(plaintext);
    int key = initial_key;  // Start with the initial key

    for (int i = 0; i < pt_len; i++) {
        int pt_index = char_to_index(plaintext[i]);
        int cipher_index = (pt_index + key) % PT_SPACE;

        // Store the cipher character
        ciphertext[i] = index_to_char(cipher_index);

        // Update the key to use the plaintext character's index for the next round
        key = pt_index;
    }

    ciphertext[pt_len] = '\0';  // Null-terminate the cipher text
}

// Function to decrypt the ciphertext using Autokey Cipher
void autokey_decrypt(const char *ciphertext, char *plaintext, int initial_key) {
    int ct_len = strlen(ciphertext);
    int key = initial_key;  // Start with the initial key

    for (int i = 0; i < ct_len; i++) {
        int ct_index = char_to_index(ciphertext[i]);
        int pt_index = (ct_index - key + PT_SPACE) % PT_SPACE;

        // Store the plaintext character
        plaintext[i] = index_to_char(pt_index);

        // Update the key to use the plaintext character's index for the next round
        key = pt_index;
    }

    plaintext[ct_len] = '\0';  // Null-terminate the plain text
}

int main() {
    // Input message
    char plaintext[256];
    char ciphertext[256];
    char decryptedtext[256];
    int initial_key = 8;  // Hard-coded initial key

    // Initialize GMP variables
    mpz_t gmp_key;
    mpz_init(gmp_key);
    mpz_set_ui(gmp_key, initial_key);  // Set the initial key value in GMP

    // Input plaintext from the user
    printf("Enter plaintext: ");
    fgets(plaintext, sizeof(plaintext), stdin);
    plaintext[strcspn(plaintext, "\n")] = 0;  // Remove trailing newline

    // Convert input to lowercase for uniformity
    for (int i = 0; plaintext[i]; i++) {
        plaintext[i] = tolower(plaintext[i]);
    }

    // Encrypt the plaintext
    autokey_encrypt(plaintext, ciphertext, mpz_get_ui(gmp_key));

    // Convert cipher to uppercase for the output
    char text[256];
    for (int i = 0; ciphertext[i]; i++) {
        text[i] = toupper(ciphertext[i]);
    }

    printf("Ciphertext: %s\n", text);

    // Decrypt the ciphertext
    autokey_decrypt(ciphertext, decryptedtext, mpz_get_ui(gmp_key));

    // Output decrypted text
    printf("Decrypted Text: %s\n", decryptedtext);

    // Clear GMP variables
    mpz_clear(gmp_key);

    return 0;
}
