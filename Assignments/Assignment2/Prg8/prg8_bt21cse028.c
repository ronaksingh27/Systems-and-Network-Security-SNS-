#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Function to print the Rail Fence table
void printRailFenceTable(char **rail, int numRails, int len) {
    printf("Rail Fence Table:\n");
    for (int i = 0; i < numRails; i++) {
        for (int j = 0; j < len; j++) {
            if (rail[i][j] == '\n') {
                printf(" ");
            } else {
                printf("%c", rail[i][j]);
            }
        }
        printf("\n");
    }
}

// Function to encrypt the plaintext using Rail Fence Cipher
void railFenceEncrypt(char *plaintext, char *ciphertext, int numRails) {
    int len = strlen(plaintext);
    int k = 0; // ciphertext index

    // Create 2D array for storing cipher pattern dynamically
    char **rail = (char **)malloc(numRails * sizeof(char *));
    for (int i = 0; i < numRails; i++) {
        rail[i] = (char *)malloc(len * sizeof(char));
        memset(rail[i], '\n', len * sizeof(char)); // marks as empty
    }

    // To find the direction (up or down in zigzag)
    int row = 0, direction = 1; // Initially going down
    
    // Arrange the plaintext into the zigzag pattern
    for (int i = 0; i < len; i++) {
        rail[row][i] = plaintext[i];
        if (row == 0) {
            direction = 1; // start moving down
        } else if (row == numRails - 1) {
            direction = -1; // start moving up
        }
        row += direction;
    }

    // Print the Rail Fence Table
    printRailFenceTable(rail, numRails, len);

    // Read the zigzag text row-wise to form ciphertext
    for (int i = 0; i < numRails; i++) {
        for (int j = 0; j < len; j++) {
            if (rail[i][j] != '\n') {
                ciphertext[k++] = rail[i][j];
            }
        }
    }
    ciphertext[k] = '\0'; // null-terminate the string

    // Free the allocated memory
    for (int i = 0; i < numRails; i++) {
        free(rail[i]);
    }
    free(rail);
}

// Function to decrypt the ciphertext using Rail Fence Cipher
void railFenceDecrypt(char *ciphertext, char *decrypted, int numRails) {
    int len = strlen(ciphertext);
    int k = 0; // ciphertext index

    // Create 2D array for storing cipher pattern dynamically
    char **rail = (char **)malloc(numRails * sizeof(char *));
    for (int i = 0; i < numRails; i++) {
        rail[i] = (char *)malloc(len * sizeof(char));
        memset(rail[i], '\n', len * sizeof(char)); // marks as empty
    }

    // To find the direction (up or down in zigzag)
    int row = 0, direction = 1; // Initially going down
    
    // Arrange in the zigzag pattern with placeholders
    for (int i = 0; i < len; i++) {
        rail[row][i] = '*';
        if (row == 0) {
            direction = 1; // start moving down
        } else if (row == numRails - 1) {
            direction = -1; // start moving up
        }
        row += direction;
    }

    // Fill the zigzag pattern row-wise from ciphertext
    for (int i = 0; i < numRails; i++) {
        for (int j = 0; j < len; j++) {
            if (rail[i][j] == '*') {
                rail[i][j] = ciphertext[k++];
            }
        }
    }

    // Print the Rail Fence Table
    printRailFenceTable(rail, numRails, len);

    // Read the zigzag text column-wise to get original text
    row = 0;
    direction = 1;
    for (int i = 0; i < len; i++) {
        decrypted[i] = rail[row][i];
        if (row == 0) {
            direction = 1; // start moving down
        } else if (row == numRails - 1) {
            direction = -1; // start moving up
        }
        row += direction;
    }
    decrypted[len] = '\0'; // null-terminate the string

    // Free the allocated memory
    for (int i = 0; i < numRails; i++) {
        free(rail[i]);
    }
    free(rail);
}

int main() {
    char plaintext[100], ciphertext[100], decrypted[100];
    int numRails;

    printf("Enter the plaintext: ");
    fgets(plaintext, sizeof(plaintext), stdin);
    plaintext[strcspn(plaintext, "\n")] = 0; // Remove newline character
    
    printf("Enter number of rails: ");
    scanf("%d", &numRails);

    // Encrypt the plaintext
    railFenceEncrypt(plaintext, ciphertext, numRails);
    printf("Encrypted Text: %s\n", ciphertext);

    // Decrypt the ciphertext
    railFenceDecrypt(ciphertext, decrypted, numRails);
    printf("Decrypted Text: %s\n", decrypted);

    return 0;
}
