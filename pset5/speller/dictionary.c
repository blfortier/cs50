// Implements a dictionary's functionality

#include <stdbool.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "dictionary.h"

// Initialize a global node root
// and node trav, set to NULL
node *root = NULL;
node *trav = NULL;

// To count the number of words
// being entered in dictionary
unsigned int num_words = 0;

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    // To hold the index for current letter
    int alpha_index = 0;

    // To count number of misspelled words
    int misspelled_words = 0;

    // Set trav node pointing to root node
    trav = root;

    // For every char in the word
    for (int i = 0; i < strlen(word); i++)
    {
        // Make sure the char is lowercase
        char letter = tolower(word[i]);

        // If letter is an alpha, set alpha_index
        // to letter - 97 --> will result in
        // a value between 0 and 25, inclusively
        if (isalpha(letter))
             alpha_index = letter - 97;
        // If an apostrophe, set alpha_index to 26
        else if (!isalpha(letter))
            alpha_index = 26;

        // If the pointer to children
        // @ alpha-index is NULL
        if (trav->children[alpha_index] == NULL)
        {
            // Increment misspelled_words
            misspelled_words++;

            // Return false exit loop
            return false;
        }
        else
        {
            // Move pointer to next letter
            trav = trav->children[alpha_index];
        }
    }

   // If the pointer to is_word is
   // true, return true to signify
   // the word is in the dictionary
    if (trav -> is_word)
        return true;

    // Exit function
    return false;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // Open the dictionary file, assign to dict
    FILE *dict = fopen(dictionary, "r");

    // If dict is NULL
    if (dict == NULL)
    {
        // Print error message
        printf("Could not load dictionary\n");

        // Return false upon
        // failed load attempt
        return false;
    }

    // To hold the index for current letter
    int alpha_index;

    // A variable to store each
    // char being read in
    char ch = '\n';

    // malloc the root node
    root = malloc(sizeof(node));

    // Create a new node and
    // assign root to it
    node *leaf = root;

    // Iterate through dictionary to load every word
    while(true)
    {
        // Read in each char
        ch = fgetc(dict);

        // While the end of the word
        // is not being pointed to
        if (ch != 10)
        {
            // If the end of file is reached
            if (feof(dict))
            {
                // Set the pointer to is_word to true
                leaf -> is_word = true;

                // Increment num_words
                num_words++;

                // Close the dict file
                fclose(dict);
                printf("Dictionary loaded!\n");

                // Return true upon successful load
                return true;
            }

            // Ensure each letter is lowercase
            tolower(ch);


            // If ch is an alpha, set alpha_index
            // to ch - 97 --> will result in
            // a value between 0 and 25, inclusively
            if (isalpha(ch))
            {
                alpha_index = ch - 97;
            }
            // If an apostrophe, set alpha_index to 26
            else if (!isalpha(ch))
                alpha_index = 26;

            // Make sure the alpha_index is
            // between 0 and 25, inclusively
            if(alpha_index >= 0 && alpha_index <= 26)
            {
                // If the children node @ alpha_index is empty
                if (leaf -> children[alpha_index] == NULL)
                {
                    // malloc a new children node
                    leaf -> children[alpha_index] = malloc(sizeof(node));
                    //  printf("moving to new node\n");
                    // Point leaf to the newly created node
                    leaf = leaf -> children[alpha_index];
                }
                // If node already exists
                else
                {
                    // Move leaf pointer to next node
                    leaf = leaf ->children[alpha_index];
                }
            }
        }

        // End of word is reached
        else
        {
            //printf("finished word\n");
            // Set pointer to is_word to true
            leaf -> is_word = true;

            // Increment num_words
            num_words++;

            // Set the leaf pointer
            // back to the root node
            leaf = root;
        }
    }

    // If there's an error reading
    // the dictionary
    if (ferror(dict))
    {
        // Close file
        fclose(dict);
        printf("Error reading\n");
       // unload();
        return 1;
    }

    // Return true upon
    // loading of dict
    return true;

}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    // If the dictionary was loaded
  /* if(&load)
   {
      */  // Return number of words
        // in dictionary
        return num_words;
  /* }
   // Return 0 if not loaded yet
    else
        return 0;*/
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    // If root is not NULL
    if (root != NULL)
    {
        // Set trav pointing to the root node
        trav = root;

        // Call the helper function,
        // passing through the trav node
        free_nodes(trav);

        // Return true upon success
        return true;
    }
    // Return false upon failed unload
    else
        return false;

    free(trav);
}

// A void function that accepts a node pointer
// A helper function for unload
void free_nodes(node *travel)
{
    // For every node in children
    for (int i = 0; i < 27; i++)
    {
        // If the pointer to children @ i is not NULL
        // call the free_nodes function recursively
        if (travel->children[i])
            free_nodes(travel->children[i]);
    }

    // Free the travel pointer
    free(travel);
}

