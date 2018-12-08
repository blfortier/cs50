# Questions

## What's `stdint.h`?

This is a header file that defines integer types, limits of specified width int types, limits of other
int types and macros for integer constant expressions. It's used because depending on the system used,
you can't rely on an int always being 32 bits.

## What's the point of using `uint8_t`, `uint32_t`, `int32_t`, and `uint16_t` in a program?

To keep data types a constant size across systems used to run the program

## How many bytes is a `BYTE`, a `DWORD`, a `LONG`, and a `WORD`, respectively?

BYTE -  1 byte      LONG - 4 bytes
DWORD - 4 bytes     WORD - 2 bytes

## What (in ASCII, decimal, or hexadecimal) must the first two bytes of any BMP file be? Leading bytes used to identify file formats (with high probability) are generally called "magic numbers."

The first 2 bytes of any BMP file are 0x42 ('B') and 0x4D ('M')

## What's the difference between `bfSize` and `biSize`?

bfSize is the size of the BITMAPFILEHEADER and biSize is the size of the BITINFOHEADER

## What does it mean if `biHeight` is negative?

This means that it is a top-down DIB and it's origin is the upper-left corner

## What field in `BITMAPINFOHEADER` specifies the BMP's color depth (i.e., bits per pixel)?

biBitCount

## Why might `fopen` return `NULL` in lines 24 and 32 of `copy.c`?

If the specified input and output file cannot be opened

## Why is the third argument to `fread` always `1` in our code?

The third arg for 'fread' is for the number of elements to read.
This value is always 1 in the code so only one element will be read
at a time

## What value does line 65 of `copy.c` assign to `padding` if `bi.biWidth` is `3`?

It would assign 3

## What does `fseek` do?

'fseek' is used to set the file position indicator for the stream to a new pos.

## What is `SEEK_CUR`?

'SEEK_CUR' moves the file pointer position to the given location

## Whodunit?

It was Professor Plum with the candlestick in the library
