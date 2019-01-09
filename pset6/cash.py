from cs50 import get_float

def main():

    while True:
        change = get_float("Change owed: ")
        if (change >= 0):
            break


    changeReturned(change)

def changeReturned(change):

    cents = round(change * 100)
    count = 0;

    if cents >= 25:
        quarters = cents // 25;
        print("quarters used: {}".format(quarters))
        count += quarters
        print("count: {}".format(count))
        cents -= (quarters * 25)
        print("cents remaining: {}".format(cents))

    if cents >= 10:
        dimes = cents // 10
        print("Dimes used: {}".format(dimes))
        count += dimes
        print("count: {}".format(count))
        cents -= (dimes * 10)
        print("cents remaining: {}".format(cents))


    if cents >= 5:
        nickels = cents // 5
        print("Nickels used: {}".format(nickels))
        count += nickels
        print("count: {}".format(count))
        cents -= (nickels * 5)
        print("cents remaining: {}".format(cents))

    if cents >= 1:
        pennies = cents // 1
        print("Pennies used: {}".format(pennies))
        count += pennies
        print("count: {}".format(count))
        cents -= (pennies * 1)
        print("cents remaining: {}".format(cents))


    print("Total coins given: {}".format(count))


if __name__ == "__main__":
    main()