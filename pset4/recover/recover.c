#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    // Check for CL argument
    if(argc != 2)
    {
        fprintf(stderr, "Usage: ./recover image\n");
        return 1;
    }

    // Store filename
    char *infile = argv[1];

    // Open input file
    FILE* inptr = fopen(infile, "r");

    // Check if file exists
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 2;
    }

    // File to store jpegs in
    FILE* images = NULL;

    // An array to store the bytes being read
    unsigned char buffer[512];

    // An array to store each jpeg's filename
    char picsFile[10];

    // To keep track of number of jpegs found
    int numPics = 0;

    // A boolean to check for a jpeg
    bool findImage = false;

    // Read through memory card until eof
    while (fread(&buffer, 512, 1, inptr) == 1)
    {
        // Check first 3 bytes for start of jpeg
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            // If end of image is reached, close the file
            // If an image isn't already being read in, change
            // findImage to true
            if (findImage == true)
                fclose(images);
            else
                findImage = true;

            // Create filename for each image
            sprintf(picsFile, "%03i.jpg", numPics);

            // Open new file for each jpeg
            images = fopen(picsFile, "w");

            // Increment for every pic found
            numPics++;
        }

         // If currently scanning in jpeg blocks
          if (findImage == true)
            fwrite(&buffer, 512, 1, images);
    }

    // Close all files
    fclose(images);
    fclose(inptr);

    // Program executed successfully
    return 0;
}
