#include <stdio.h>
#include <string.h>

// Define the maximum size for rows and columns
#define MAX_COLS 5
#define MAX_ROWS 20

void printTable(char table[MAX_ROWS][MAX_COLS], int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%c ", table[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void transpositionCipher(const char* plaintext, char* ciphertext, int cols) {
    int len = strlen(plaintext);
    int rows = (len + cols - 1) / cols; // Calculate number of rows needed

    char table[MAX_ROWS][MAX_COLS];
    
    // Fill the table row by row
    int index = 0;
    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            if (index < len) {
                table[r][c] = plaintext[index++];
            } else {
                table[r][c] = ' '; // Fill empty spaces with space
            }
        }
    }

    // Print the table after filling it
    printf("Table after filling for encryption:\n");
    printTable(table, rows, cols);

    // Generate ciphertext column by column
    index = 0;
    for (int c = 0; c < cols; c++) {
        for (int r = 0; r < rows; r++) {
            ciphertext[index++] = table[r][c];
        }
    }
    ciphertext[index] = '\0'; // Null-terminate the ciphertext string
}

void transpositionDecipher(const char* ciphertext, char* plaintext, int cols) {
    int len = strlen(ciphertext);
    int rows = (len + cols - 1) / cols; // Calculate number of rows needed

    char table[MAX_ROWS][MAX_COLS];
    
    // Fill the table column by column
    int index = 0;
    for (int c = 0; c < cols; c++) {
        for (int r = 0; r < rows; r++) {
            if (index < len) {
                table[r][c] = ciphertext[index++];
            } else {
                table[r][c] = ' '; // Fill empty spaces with space
            }
        }
    }

    // Print the table after filling it
    printf("Table after filling for decryption:\n");
    printTable(table, rows, cols);

    // Generate plaintext row by row
    index = 0;
    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            plaintext[index++] = table[r][c];
        }
    }
    plaintext[index] = '\0'; // Null-terminate the plaintext string
}

int main() {
    const char plaintext[] = "0123456789 abcdefghijklmnopqrstuvwxyz";
    char ciphertext[MAX_ROWS * MAX_COLS + 1]; // Extra space for null terminator
    char decrypted[MAX_ROWS * MAX_COLS + 1]; // Extra space for null terminator

    int cols = MAX_COLS; // Number of columns for the table

    // Perform encryption
    transpositionCipher(plaintext, ciphertext, cols);
    printf("Plaintext:\n%s\n\n", plaintext);
    printf("Ciphertext:\n%s\n\n", ciphertext);

    // Perform decryption
    transpositionDecipher(ciphertext, decrypted, cols);
    printf("Decrypted:\n%s\n", decrypted);

    return 0;
}
