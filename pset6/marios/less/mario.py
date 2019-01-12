from cs50 import get_int

def main():

    while True:
        height = get_int("Height between 1 and 8: ")

        if (height >= 0 and height <= 8):
            break;

   # halfPyramid(height)


#def halfPyramid(height):

    for i in range(0, height):

        for j in range(1, height - i):
            print(" ", end = "")
            print("#" * i, end = "")

       # for k in range(i + 1):
       #     print("#", end = "")

        print()


if __name__ == "__main__":
    main()