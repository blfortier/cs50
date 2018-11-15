#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(void)
{

    float change;
    int count = 0;
    int cents;
    int quarters;
    int dimes;
    int nickels;
    int pennies;


    // Prompt user for amount of change owed
    // If given a negative number, repeatedly
    // ask until valid input is given
    do
    {
        change = get_float("Change owed: ");
    }
    while (change < 0);

    // Convert change given to cents
    cents = round(change * 100);
    // printf("%i\n", cents);

    while (cents >= 25)
    {
        quarters = cents / 25;
        printf("Quarters used: %i\n", quarters);
        count += quarters;
        cents -= (quarters * 25);
    }

    while (cents >= 10)
    {
        dimes = cents / 10;
        printf("Dimes used: %i\n", dimes);
        count += dimes;
        cents -= (dimes * 10);
    }

    while (cents >= 5)
    {
        nickels = cents / 5;
        printf("Nickels used: %i\n", nickels);
        count += nickels;
        cents -= (nickels * 5);
    }

    while (cents >= 1)
    {
        pennies = cents / 1;
        printf("Pennies used: %i\n", pennies);
        count += pennies;
        cents -= (pennies * 1);
    }

    printf("%i\n", count);
}

