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
void nullifier(node *leaf);

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

    printf("num words misspelled: %i\n", misspellings);
    printf("\nNum words in dictionary: %u\n", num_words);

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

    char ch = '\n';
    root = malloc(sizeof(node));

    node *leaf = root;


    // Iterate through dictionary to load every word
    while(true)
    {

        ch = fgetc(dict);

       // printf("checking character: %i\n", ch);



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
            if (isalpha(ch)) // isalpha
                alpha_index = ch - 97;
            else if (!isalpha(ch))
                alpha_index = 26;

           // printf("alpha index for %c is: %i\n", ch, alpha_index);

            if(alpha_index >= 0 && alpha_index <= 26)
            {
                if (leaf -> children[alpha_index] == NULL)
                {
                  //  printf("Creating child node\n");
                    leaf -> children[alpha_index] = malloc(sizeof(node));
                  //  printf("moving to new node\n");
                    leaf = leaf -> children[alpha_index];
                }
                else
                {
                   // printf("moving to existing child node\n");
                    leaf = leaf ->children[alpha_index];
                }
                 //printf("Num words in dictionary: %u\n", num_words);
            }
        }
        else
        {
            //printf("finished word\n");
            leaf -> is_word = true;
            num_words++;
            leaf = root;
        }
       // printf("%c", ch);


    }

     if (ferror(dict))
    {
        fclose(dict);
        printf("Error reading\n");
       // unload();
        return 1;
    }



    //free(leaf);
   // free(root);


    return true;
}


// Returns true if word is in dictionary else false
bool check(const char *word)
{
    int alpha_index = 0;
    int misspelled_words = 0;
    node *pointer = root;
    //printf("\n\nCHECK\n");
    //printf("checking %s\n", word);

    for (int i = 0; i < strlen(word); i++)
    {
        char letter = tolower(word[i]);
       // printf("checking letter %c\n", letter);

        if (isalpha(letter))
             alpha_index = letter - 97;
        else if (!isalpha(letter))
            alpha_index = 26;
        //printf("alpha_index is: %i\n", alpha_index);
        //pointer = pointer -> children[alpha_index];
   // printf("address? %i\n", 0x1087520);
        if (pointer->children[alpha_index] == NULL)
        {
            //printf("failed on letter %c found null child\n", letter);
            misspelled_words++;
            return false;
        }
        else
        {
            pointer = pointer->children[alpha_index];
        }

    }
   // printf("got to end of checked word now checking if the word is valid\n");
    if (pointer -> is_word)
        return true;


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

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{

     return num_words;
    // TODO

    return 0;
}








