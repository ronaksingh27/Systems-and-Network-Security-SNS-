#include <stdio.h>
#include <string.h>

#define PT_SIZE 37  // Total elements in the PT row: 0-9, space, a-z

// The custom PT and Val arrays from your table
char PT[] = "0123456789 abcdefghijklmnopqrstuvwxyz";
char Val[] = "ronaksipghtqublvjwmxyzcde 0123456789";

void print_table(char* rotor )
{
    for(int i =0 ;i < PT_SIZE ; i++ )
    {
        printf("%c ",PT[i] );
    }printf("\n");
    for(int i =0 ;i < PT_SIZE ; i++ )
    {
        printf("%c ",rotor[i] );
    }printf("\n");
}

// Function to find the index of a character in the PT array
int find_index(char ch) {
    for (int i = 0; i < PT_SIZE; i++) {
        if (PT[i] == ch) {
            return i;
        }
    }
    return -1;  // Character not found
}

// Function to rotate the rotor (i.e., rotate the Val array)
void rotate_rotor(char* rotor) {
    char temp = rotor[0];
    // Shift all elements to the left
    for (int i = 0; i < PT_SIZE - 1; i++) {
        rotor[i] = rotor[i + 1];
    }
    rotor[PT_SIZE - 1] = temp;  // Put the first element at the end
}

// Function to encrypt a message using the custom rotor cipher
void encrypt_message(const char* message, char* encrypted_message, char* rotor) {
    int index;
    for (int i = 0; message[i] != '\0'; i++) {
        
        printf("message : %c\n",message[i]);
        
        // Find the index of the message character in the PT array
        index = find_index(message[i]);
        printf("index : %d\n",index);
        
        if (index != -1) {
            // Encrypt the character using the current rotor mapping
            encrypted_message[i] = rotor[index];
            
            printf("rotor : %c\n",rotor[index]);
        } else {
            // If character not found, copy as is
            encrypted_message[i] = message[i];
        }

        // Rotate the rotor after each character
        rotate_rotor(rotor);
        print_table(rotor);
    }
    encrypted_message[strlen(message)] = '\0';  // Null-terminate the string
}

int main() {
    const char* message = "hello world";
    char encrypted_message[100];

    // Initialize the rotor with the Val array (which will rotate)
    char rotor[PT_SIZE];
    strcpy(rotor, Val);  // Copy the initial Val array

    print_table(rotor);

    // Encrypt the message
    encrypt_message(message, encrypted_message, rotor);

    // Output the encrypted message
    printf("Original: %s\n", message);
    printf("Encrypted: %s\n", encrypted_message);

    return 0;
}
