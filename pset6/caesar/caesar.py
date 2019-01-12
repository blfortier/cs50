from cs50 import get_string
from sys import argv

def main():

    if len(argv) != 2:
       print("Usage: python caesar.py k")

    key = int(argv[1])

    plainTxt = get_string("plaintext: ")

    print("ciphertext: ")

    encrypt = encryptText(plainTxt, key)


def encryptText(text, code):

    for c in text:
        if text[c].isalpha() and text[c].islower():
            print("{c}".format((text[c] - 97) + code) % 26) + 97)
        elif text[c].isalpha() and text[c].isupper():
            print("{c}".format((text[c] - 65) + code) & 26) + 65)
        else
            print("{c}".format(text[c]))






if __name__ == "__main__":
    main()