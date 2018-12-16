#include <ctype.h>
#include <stdio.h>
#include <sys/resource.h>
#include <sys/time.h>
#include <stdlib.h>
#include <string.h>

#include "dictionary.h"

// Undefine any definitions
#undef calculate
#undef getrusage

// Default dictionary
#define DICTIONARY "dictionaries/large"

// Prototype
double calculate(const struct rusage *b, const struct rusage *a);

int main (int argc, char *argv[])
{


    // Check for correct number of args
    if (argc != 2 && argc != 3)
    {
        printf("Usage: speller [dictionary] text\n");
        return 1;
    }

    // Structures for timing data
    //struct rusage before, after;

    // Benchmarks
   // double time_check = 0.0, time_size = 0.0, time_unload = 0.0;
    //double time_load = 0.0,
   // double time_check = 0.0;

    // Determine dictionary to use
    char *dictionary = (argc == 3) ? argv[1] : DICTIONARY;

  //  getrusage(RUSAGE_SELF, &before);
    bool loaded = load(dictionary);
  //  getrusage(RUSAGE_SELF, &after);

     // Exit if dictionary not loaded
    if (!loaded)
    {
        printf("Could not load %s.\n", dictionary);
        return 1;
    }
    else if(loaded)
        printf("Yes! Loaded!!\n");


     // Try to open text
    char *text = (argc == 3) ? argv[2] : argv[1];
    FILE *file = fopen(text, "r");
    if (file == NULL)
    {
        printf("Could not open %s.\n", text);
        //unload();
        return 1;
    }

    // Prepare to report misspellings
    printf("\nMISSPELLED WORDS\n\n");

    // Prepare to spell-check
    int index = 0, misspellings = 0, words = 0;
    char word[LENGTH + 1];

    // Spell-check each word in text
    for (int c = fgetc(file); c != EOF; c = fgetc(file))
    {
        // Allow only alphabetical characters and apostrophes
        if (isalpha(c) || (c == '\'' && index > 0))
        {
            // Append character to word
            word[index] = c;
            index++;

            // Ignore alphabetical strings too long to be words
            if (index > LENGTH)
            {
                // Consume remainder of alphabetical string
                while ((c = fgetc(file)) != EOF && isalpha(c));

                // Prepare for new word
                index = 0;
            }
        }

        // Ignore words with numbers (like MS Word can)
        else if (isdigit(c))
        {
            // Consume remainder of alphanumeric string
            while ((c = fgetc(file)) != EOF && isalnum(c));

            // Prepare for new word
            index = 0;
        }

        // We must have found a whole word
        else if (index > 0)
        {
            // Terminate current word
            word[index] = '\0';

            // Update counter
            words++;

            // Check word's spelling
        //    getrusage(RUSAGE_SELF, &before);
            bool misspelled = !check(word);
       //     getrusage(RUSAGE_SELF, &after);

            // Update benchmark
          //  time_check += calculate(&before, &after);

            // Print word if misspelled
            if (misspelled)
            {
                printf("%s\n", word);
                misspellings++;
            }

            // Prepare for next word
            index = 0;
        }
    }

    printf("num words mispelled: %i\n", misspellings);





}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    FILE *dict = fopen(dictionary, "r");

    if (dict == NULL)
    {
        printf("Could not load dictionary\n");
        return false;
    }

    int alpha_index;
    //char letter;
    long long num_words = 0;
    char ch = '\n';

    root = malloc(sizeof(node));
    node *leaf = NULL;

    // Iterate through dictionary to load every word
    while(true)
    {
        leaf = root;

        ch = fgetc(dict);
       // printf("%c", ch);


        // While the end of the word
        // is not being pointed to
        if (ch != 10)
        {

            if (feof(dict))
            {
                leaf -> is_word = true;
                num_words++;
                fclose(dict);
                printf("Dictionary loaded!\n");
                return true;
            }

            tolower(ch);
            if (ch >= 97 && ch <= 122)
                alpha_index = ch - 97;
            else if (ch == 39)
                alpha_index = 26;

            if(alpha_index >= 0 && alpha_index <= 26)
            {
                if (leaf -> children[alpha_index] == NULL)
                {
                    leaf -> children[alpha_index] = malloc(sizeof(node));

                }
                else
                    leaf = leaf -> children[alpha_index];
            }
        }

        leaf -> is_word = true;
        num_words++;
    }
     if (ferror(dict))
    {
        fclose(dict);
        printf("Error reading\n");
       // unload();
        return 1;
    }


    free(leaf);
   // free(root);

    //printf("Dictionary: \n%c", ch);

    return true;
}


// Returns true if word is in dictionary else false
bool check(const char *word)
{
    int alpha_index = 0;
    int misspelled_words = 0;
    node *pointer = root;


     for (int i = 0; i <= strlen(word); i++)
    {
        int letter = tolower(word[i]);
       // int nextLetter = (word[i + 1]);
        if (letter >= 97 && letter <= 122)
             alpha_index = letter - 97;
        else if (letter == 39)
            alpha_index = 26;

       // pointer = children[alpha_index];

        if ((pointer -> children[alpha_index]) == NULL)
        {
            misspelled_words++;
            return false;
        }


        pointer = pointer -> children[alpha_index];

        if (letter == '\n')
        {
            if ((pointer -> is_word) == true)
                return true;
        }


    }


    return false;
}


// Returns number of seconds between b and a
double calculate(const struct rusage *b, const struct rusage *a)
{
    if (b == NULL || a == NULL)
    {
        return 0.0;
    }
    else
    {
        return ((((a->ru_utime.tv_sec * 1000000 + a->ru_utime.tv_usec) -
                  (b->ru_utime.tv_sec * 1000000 + b->ru_utime.tv_usec)) +
                 ((a->ru_stime.tv_sec * 1000000 + a->ru_stime.tv_usec) -
                  (b->ru_stime.tv_sec * 1000000 + b->ru_stime.tv_usec)))
                / 1000000.0);
    }
}










