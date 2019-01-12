from cs50 import get_int


def main():

    # Prompt user for a height until a
    # number between 1 and 8 is entered
    while True:
        height = get_int("Height between 1 and 8: ")

        if (height > 0 and height <= 8):
            break

    # Call the halfPyramid function
    halfPyramid(height)

# Print a pyramid of hashes, right aligned
# Is passed the desired height as an int


def halfPyramid(height):

    # For as many times as the height
    for i in range(height):

        # Print spaces
        for j in range(1, height - i):
            print(" ", end="")

        # Print hashes
        for k in range(i + 1):
            print("#", end="")

        # Go to next line
        print()


if __name__ == "__main__":
    main()