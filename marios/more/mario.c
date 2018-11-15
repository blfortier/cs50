#include <stdio.h>
#include <cs50.h>

int main(void)
{

    int height;

    do
    {
        height = get_int("Height of pyramid: ");

    }
    while (height < 0 || height > 23);

    for(int i = 0; i < height; i++)
    {

        // Print the empty spaces to push pyramid to right
        for (int k = 1; k <= height - 1 - i; k++)
        {
            printf(" ");
        }

        // Print hashtags for left pyramid
        for (int j = 1; j < i + 1 + 1; j++)
        {

            printf("#");
        }

        // Print gap between pyramids
        printf("  ");

        // Print hashtags for right pyramid
        for (int j = 1; j < i + 1 + 1; j++)
        {

            printf("#");
        }

        // Start a new line
        printf("\n");

    }

}