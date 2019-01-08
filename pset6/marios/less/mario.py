from cs50 import get_int

def main():

    while True:
        height = get_int("Height between 0 and 23: ")

        if (height >= 0 or height <= 23):
            break;

    halfPyramid(height)


def halfPyramid(height):
    for i in range(height):
        for j in range(height - 1 - i, height + 1):
            print(" ", end = "")
        print(" ")
        for k in range(1, i + 2):
            print("#", end = "")
    print("\n")

if __name__ == "__main__":
    main()