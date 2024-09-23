#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <gmp.h>

// Function to print the key matrix for matrix Multilication
void printKeyMatrix(mpz_t keyMatrix[5][5]) {
    printf("Key Matrix:\n");
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            gmp_printf("%Zd ", keyMatrix[i][j]);
        }
        printf("\n");
    }
}

// Function to generate the key matrix from the key string
void getKeyMatrix(char *key, mpz_t keyMatrix[5][5]) {
    int k = 0;
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            mpz_init_set_ui(keyMatrix[i][j], (key[k]) % 65);
            k++;
        }
    }
}

// Function to encrypt the message
void encrypt(mpz_t cipherMatrix[5][1], mpz_t keyMatrix[5][5], mpz_t messageVector[5][1]) {
    mpz_t sum;
    mpz_init(sum);

    for (int i = 0; i < 5; i++) {
        mpz_set_ui(cipherMatrix[i][0], 0); // Initialize cipherMatrix[i][0] to 0

        for (int x = 0; x < 5; x++) {
            mpz_mul(sum, keyMatrix[i][x], messageVector[x][0]);
            mpz_add(cipherMatrix[i][0], cipherMatrix[i][0], sum);
        }

        mpz_mod_ui(cipherMatrix[i][0], cipherMatrix[i][0], 26);
    }

    mpz_clear(sum);
}

// Function to implement Hill Cipher
void HillCipher(char *message, char *key) {
    mpz_t keyMatrix[5][5];
    mpz_t messageVector[5][1];
    mpz_t cipherMatrix[5][1];

    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            mpz_init(keyMatrix[i][j]);
        }
        mpz_init(messageVector[i][0]);
        mpz_init(cipherMatrix[i][0]);
    }

    getKeyMatrix(key, keyMatrix);
    printKeyMatrix(keyMatrix);

    // Generate vector for the message
    for (int i = 0; i < 5; i++)
        mpz_set_ui(messageVector[i][0], (message[i]) % 65);

    // Encrypt the message
    encrypt(cipherMatrix, keyMatrix, messageVector);

    // Generate and print the ciphertext
    printf("Ciphertext: ");
    for (int i = 0; i < 5; i++) {
        char c = mpz_get_ui(cipherMatrix[i][0]) + 65;
        printf("%c", c);
    }
    printf("\n");

    // Clear GMP variables
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            mpz_clear(keyMatrix[i][j]);
        }
        mpz_clear(messageVector[i][0]);
        mpz_clear(cipherMatrix[i][0]);
    }
}

// Helper function to convert a string to uppercase
void toUpperCase(char* str) {
    for (int i = 0; str[i] != '\0'; i++) {
        str[i] = toupper(str[i]);
    }
}

// Driver function
int main() {
    char message[] = "ACTEG";  // Ensure message length matches matrix size
    char key[] = "ronaksipghtqublvjwmxyzcde";  // Ensure key length matches matrix size^2

    toUpperCase(message);
    toUpperCase(key);

    HillCipher(message, key);

    return 0;
}
