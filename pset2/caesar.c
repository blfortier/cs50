#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Declare the function that will
// be used to create the ciphertext
int alphaIndex(string, int);

int main(int argc, string argv[])
{
    int key;    // holds the integer value of the key
    int alpha;  // holds the ciphertext

    // Make sure an argument was entered on
    // the command line and is greater than zero
    if (argc != 2 || atoi(argv[1]) <= 0)
    {
        // Display a message
        printf("Usage: %s k\n", argv[0]);

        // exit program
        return 1;
    }

    // Convert the given key to an int
    key = atoi(argv[1]);

    // Prompt the user for a plaintext message
    string plaintext = get_string("plaintext: ");

    // Display the ciphertext
    printf("ciphertext: ");

    // Call the function that will encrpyt and
    // display the encrypted plaintext
    alpha = alphaIndex(plaintext, key);

}

// A function that converts the ASCII
// values of the given string to alpha-
// numeric indices. 'A' starts at 0
// It is passed a string and the key
int alphaIndex(string text, int key)
{
    // Loop through the string
    for (int i = 0; i < strlen(text); i++)
    {
        // If the current char in the string is a letter
        // and is also a lowercase
        if (isalpha(text[i]) && islower(text[i]))
        {
            // Print out the ciphered text
            printf("%c", (((text[i] - 97) + key) % 26) + 97);
        }
        // If the current char in the string is a letter
        // and is also uppercase
        else if (isalpha(text[i]) && isupper(text[i]))
        {
            // Print out the ciphered text
            printf("%c", (((text[i] - 65) + key) % 26) + 65);
        }
        // All non alphanumeric characters
        else
        {
            printf("%c", text[i]);
        }
    }

    // Print a new line
    printf("\n");

    // Exit program once complete
    return 0;
}
