// Helper functions for music
#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

// Used as a base value to
// determine frequency levels
#define A4_HZ 440.0

#include "helpers.h"

// Converts a fraction formatted as X/Y to eighths
int duration(string fraction)
{
    // The first char of the string
    // is stored as an int in num
    // This represents the numerator
    int num = atoi(&fraction[0]);

    // The third char of the string
    // is stored as an int in den
    // This represents the denominator
    int den = atoi(&fraction[2]);

    // Determine the number of 1/8 beats
    // Take den and figure out how you
    // can mulitply it to get 8, then
    // mulitiply num by that number
    // ex) the beat given was "1/2"
    // num = 1 and den = 2
    // den * 4 = 8 so --> num * 4 = 4
    // There are 4 1/8 beats
    switch (den)
    {
        case 8:
            return (num * 1);
            break;
        case 4:
            return (num * 2);
            break;
        case 2:
            return (num * 4);
            break;
        case 1:
            return (num * 8);
            break;
        default:
            return 1;
    }
}

// Calculates frequency (in Hz) of a note
int frequency(string note)
{
    // Variables to hold the note (letter) and
    // the accidental (accid) (if applicable)
    char letter, accid;

    // A variable to hold the ocatave (1 - 8)
    int octave;

    // A variable to hold the frequency in hz
    double hz;

    // If the given string (note) has a length
    // of 2, assign the first char to letter
    // and the second char to octave
    if (strlen(note) == 2)
    {
        letter = note[0];

        // Store the octave
        // as an int
        octave = atoi(&note[1]);
    }

    // If the given string (note) has a length
    // of 3, assign the first char to letter, the
    // second char to accid, and the third char
    // to octave
    if (strlen(note) == 3)
    {
        letter = note[0];
        accid = note[1];

        // Store the octave
        // as an int
        octave = atoi(&note[2]);
    }

    // Determmine the hertz in the 4th octave of
    // the given note (letter) using A4_HZ (440 hz)
    // as a starting point. Depending on how far from
    // the A key letter is, multiply or divide A4_HZ
    // by 2 ^ (x / 12)  x -- semitones away from note A4
    switch (letter)
    {
        case 'C':
            hz = (A4_HZ / pow(2.0, (9.0 / 12.0)));
            break;
        case 'D':
            hz = (A4_HZ / pow(2.0, (7.0 / 12.0)));
            break;
        case 'E':
            hz = (A4_HZ / pow(2.0, (5.0 / 12.0)));
            break;
        case 'F':
            hz = (A4_HZ / pow(2.0, (4.0 / 12.0)));
            break;
        case 'G':
            hz = (A4_HZ / pow(2.0, (2.0 / 12.0)));
            break;
        case 'A':
            hz = A4_HZ;
            break;
        case 'B':
            hz = (A4_HZ * pow(2.0, (2.0 / 12.0)));
            break;
        default:
            break;
    }

    // If the octave is greater than 4
    if (octave > 4)
    {
        // Multiply the freq. (hz) by 2
        // for every octave shifted up
        for (int i = 0; i < octave - 4; i++)
        {
            hz *= 2.0;
        }
    }

    // If the octave is less than 4
    else if (octave < 4)
    {
        // Divide the freq. (hz) by 2
        // for every octave shifted down
        for (int i = 0; i < 4 - octave; i++)
        {
            hz /= 2.0;
        }
    }

    // If the note is sharp multiply
    // freq. (hz) by 2 ^ (1 / 12)
    if (accid == '#')
        hz *= pow(2.0, (1.0 / 12.0));
    // If the note is flat divide
    // freq. (hz) by 2 ^ (1 / 12)
    else if (accid == 'b')
        hz /= pow(2.0, (1.0 / 12.0));

    // Round and return hz
    return round(hz);
}

// Determines whether a string represents a rest
bool is_rest(string s)
{
    // If the string is empty, it is a rest
    // return true
    if (strlen(s) == 0)
        return true;
    // no rest
    else
        return false;
}
