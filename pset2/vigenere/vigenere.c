#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Declare the function that will
// be used to create the ciphertext
int encodeText(string, string);

int main(int argc, string argv[])
{
    string key;     // holds the key given as a string
    int encoded;    // holds the ciphertext
    int keyLength;  // holds the length of the key

    // Assign the given code to the variable key
    key = argv[1];

    // Make sure only one argument (the key) was entered on
    // the command line, and consists of all letters
    if (argc != 2)
    {
        // Display an error message
        printf("Please enter one key to encode with");

        // exit program
        return 1;
    }
    else
    {
        // Loop through the characters in the key
        // to ensure only alpha characters are present
        for (int i = 0; i < strlen(key); i++)
        {

            // Display an error mesage if nonalpha chars are found
            if (!isalpha(key[i]))
            {
                printf("The key should only consist of letters...\n");

                // exit program
                return 1;
            }
        }
    }

    // Change the key to all uppercase letters
    // This is helpful with mixed case keywords
    for (int i = 0; i < key[i]; i++)
    {
        key[i] = toupper(key[i]);
    }

    // Prompt the user for a plaintext message
    string plaintext = get_string("plaintext: ");

    // Display the ciphertext
    printf("ciphertext: ");

    // Call the function that will encrpyt
    // and display the ciphertext
    encoded = encodeText(plaintext, key);
}

// A function that takes a plaintext message and
// uses the Vigenere cipher to encode it using a
//  key. ciphertexxt = (plaintext + keyCharacter) % 26
// It is passed two strings, the message and the key
int encodeText(string message, string code)
{
    // to store the length of the keyword
    int codeLength = strlen(code);

    // to keep track of which character in the
    // keyword is currently being used
    int keyIndex = 0;

    // Loop through the string
    for (int i = 0; i < strlen(message); i++)
    {
        // To cycle back to beginning of keyword
        char keyLetter = code[(keyIndex % codeLength)];

        // If the current char in the string is a letter
        // and is also a lowercase
        if (isalpha(message[i]) && islower(message[i]))
        {
            // Print out the ciphered text
            printf("%c", ((message[i] - 97 + (keyLetter - 65)) % 26) + 97);

            // Increase keyIndex
            keyIndex++;
        }
        // If the current char in the string is a letter
        // and is also uppercase
        else if (isalpha(message[i]) && isupper(message[i]))
        {
            // Print out the ciphered text
            printf("%c", ((message[i] - 65 + (keyLetter - 65)) % 26) + 65);

            // Increase keyIndex
            keyIndex++;
        }
        // All non alphanumeric characters
        else
        {
            printf("%c", message[i]);
        }

    }

    // Print a new line
    printf("\n");

    // Exit program once complete
    return 0;
}
