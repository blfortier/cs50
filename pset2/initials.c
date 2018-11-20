#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

int main(void)
{

    // Get user's name
    string name = get_string();

    // Print first initial of user's name
    printf("%c", toupper(name[0]));

    // Loop through the string name
    for (int i = 0; i < strlen(name); i++)
    {
        // Once a space is reached, print next character
        if (name[i] == ' ')
        {
            printf("%c", toupper(name[i + 1]));
        }
    }

    // Print a new line
    printf("\n");

}