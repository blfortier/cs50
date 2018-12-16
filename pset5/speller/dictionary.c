// Implements a dictionary's functionality

#include <stdbool.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


#include "dictionary.h"

// Returns true if word is in dictionary else false
bool check(const char *word)
{
     int alpha_index = 0;
    int mispelled_words = 0;
    node *pointer = root;


     for (int i = 0; i <= strlen(word); i++)
    {
        int letter = tolower(word[i]);

        if (letter >= 97 && letter <= 122)
             alpha_index = letter - 97;
        else if (letter == 39)
            alpha_index = 26;

        pointer = pointer -> children[alpha_index];

        if ((pointer -> children[i]) == NULL)
        {
            mispelled_words++;
            return false;
        }
        else
            pointer = pointer -> children[i + 1];

        if (letter == EOF)
        {
            if ((pointer -> is_word) == true)
                return true;
        }


    }


    return false;

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

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return 0;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    // TODO
    return false;
}


