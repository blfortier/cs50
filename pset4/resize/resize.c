// Copies a BMP file

#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        fprintf(stderr, "Usage: ./resize n infile outfile\n");
        return 1;
    }

    // remember size to resize by, store as int
    int resize = atoi(argv[1]);

    // Make sure argv[1] is a positive number <= 100
    if (resize < 0 || resize > 100)
    {
        fprintf(stderr, "Please enter a number to resize bmp file by. Must be between 0 and 100\n");
        return 1;
    }

    // remember filenames
    char *infile = argv[2];
    char *outfile = argv[3];

    // open input file
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 2;
    }

    // open output file
    FILE *outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf, bfNew;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // Assign the new header variable the original header's info
    bfNew = bf;

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi, biNew;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    // Assign the new header variable the original header's info
    biNew = bi;

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 ||
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }

    // Resize the image's height and width
    biNew.biWidth *= resize;
    biNew.biHeight *= resize;

    // determine padding for scanlines, original
    int paddingOld = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    // determine padding for resized image
    int paddingNew = (4 - (biNew.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    // Calculate the resized image's image size
    biNew.biSizeImage = ((sizeof(RGBTRIPLE) * biNew.biWidth) + paddingNew) * abs(biNew.biHeight);

    // Calculate the resized image's file size
    bfNew.bfSize = biNew.biSizeImage + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);

    // write outfile's BITMAPFILEHEADER, updated with new header
    fwrite(&bfNew, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER, updated with new header
    fwrite(&biNew, sizeof(BITMAPINFOHEADER), 1, outptr);

    // iterate over infile's scanlines
    for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++)
    {
        // Read the scanlines for as many times as resize
        for (int j = 0; j < resize; j++)
        {
            // iterate over pixels in scanline
            for (int k = 0; k < bi.biWidth; k++)
            {
                // temporary storage
                RGBTRIPLE triple;

                // read RGB triple from infile
                fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

                // Write the triple to the file 'resize' times, horizontal resizing
                for (int p = 0; p < resize; p++)
                   fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
            }

            // Add padding to outfile
            for (int l = 0; l < paddingNew; l++)
                    fputc(0x00, outptr);

            // Bring the cursor to the beginning of the scanline, vertical resizing
            if (j < resize - 1)
                fseek(inptr, -bi.biWidth * sizeof(RGBTRIPLE), SEEK_CUR);
        }

         // skip over padding, if any
        fseek(inptr, paddingOld, SEEK_CUR);
    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // success
    return 0;
}
