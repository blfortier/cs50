#include <stdio.h>
#include <cs50.h>


int main(void)
{
    int minutes;

        // prompt user for input
        printf("Minutes: ");
        minutes = get_int();

        if(minutes > 0){
            // display the number of water bottles equivalent to user input
            printf("Bottles: %i\n", minutes * 12);
        }

}
