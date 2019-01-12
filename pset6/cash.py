from cs50 import get_float

def main():

    # Prompt the user for the amount
    # of change owed until a positive
    # number is entered
    while True:
        change = get_float("Change owed: ")
        if (change >= 0):
            break

    # Call the function that will
    # print the amount of coins that
    # will be given to the user
    changeReturned(change)

# A function that will convert the
# amount of change entered into cents
# and will calculate the number of
# coins needed to make change
def changeReturned(change):

    # Convert change into cents
    cents = round(change * 100)

    # Set the counter to 0
    count = 0;

    # Calculate how many quarters can be used
    if cents >= 25:
        quarters = cents // 25;

        # Keep track of amount of coins
        count += quarters

        # Keep track of amount of change
        cents %= 25

    # Calculate how many dimes can be used
    if cents >= 10:
        dimes = cents // 10

        # Keep track of amount of coins and change
        count += dimes

        # Keep track of amount of change
        cents %= 10

    # Calculate how many nickels can be used
    if cents >= 5:
        nickels = cents // 5

        # Keep track of amount of coins and change
        count += nickels

        # Keep track of amount of change
        cents %= 5

    # Calculate how many pennies can be used
    if cents >= 1:
        pennies = cents // 1

        # Keep track of amount of coins and change
        count += pennies

        # Keep track of amount of change
        cents %= 1

    # Print total coins used
    print(count)


if __name__ == "__main__":
    main()