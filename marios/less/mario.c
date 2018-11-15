#include <stdio.h>
#include <cs50.h>

int main(void)
{

    int height;

    do
    {
        height = get_int("Height: ");

    }
    while (height < 0 || height > 23);

    for(int i = 0; i < height; i++)
    {

        // Print the empty spaces to push pyramid ot right
        for (int k = 1; k <= height - 1 - i; k++)
        {
            printf(" ");
        }

        // Print hashtags
        for (int j = 0; j < i + 1 + 1; j++)
        {

            printf("#");
        }

        // Start a new line
        printf("\n");
    }

}