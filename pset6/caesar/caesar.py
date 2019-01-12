from cs50 import get_string
from sys import argv


def main():

    # Check for comman line args
    if len(argv) != 2:
       print("Usage: python caesar.py k")

    # Convert the key into an int
    key = int(argv[1])

    # Prompt user for plaintext
    plainTxt = get_string("plaintext: ")

    # Print cyphertext
    print("ciphertext: ", end="")

    # Loop throught plain text
    for c in plainTxt:
        if c.isalpha():
            if c.isupper():
                # If the current character is alpha and upper case
                cypherTxt = ((ord(c) - 65 + key) % 26) + 65
                print(chr(cypherTxt), end ="")
            else:
                # If the current char is an alpha and lower
                cypherTxt = ((ord(c) - 97 + key) % 26) + 97
                print(chr(cypherTxt), end="")
        else:
            # Print all other characters
            print(c, end="")

    # Print a newline after end of cypther text
    print()


if __name__ == "__main__":
    main()