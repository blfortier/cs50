// Implements a dictionary's functionality

#include <stdbool.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "dictionary.h"

typedef struct node
{
    bool is_word;
    struct node *children[27];
}
node;

// Declare a helper function for unload
void free_nodes(node *travel);


// Initialize a global node root
// and node trav, set to NULL
node *root = NULL;

// To count the number of words
// being entered in dictionary
unsigned int num_words = 0;

int alpha_index(char);

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    // To hold the index for current letter
    int position = 0;

    char letter = '\n';

    // To count number of misspelled words
    int misspelled_words = 0;

    // Set trav node pointing to root node
    node *trav = root;

    // For every char in the word
    for (int i = 0; i < strlen(word); i++)
    {
        position = alpha_index(letter);

        // If the pointer to children
        // @ alpha-index is NULL
        if (trav->children[position] == NULL)
        {
            // Increment misspelled_words
            misspelled_words++;

            // Return false exit loop
            return false;
        }
        else
        {
            // Move pointer to next letter
            trav = trav->children[position];
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
        unload();
        // Return false upon
        // failed load attempt
        return false;
    }

    // To hold the index for current letter
    int position = 0;

    // A variable to store each
    // char being read in
    char ch;

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
                //num_words++;

                // Close the dict file
                fclose(dict);


                // Return true upon successful load
                return true;
            }

            position = alpha_index(ch);


            // Make sure the alpha_index is
            // between 0 and 26, inclusively
            if(position >= 0 && position <= 26)
            {
                // If the children node @ alpha_index is empty
                if (leaf -> children[position] == NULL)
                {
                    // malloc a new children node
                    leaf -> children[position] = malloc(sizeof(node));
                    //  printf("moving to new node\n");
                    // Point leaf to the newly created node
                    leaf = leaf -> children[position];
                }
                // If node already exists
                else
                {
                    // Move leaf pointer to next node
                    leaf = leaf ->children[position];
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
        unload();
        return false;
    }

    fclose(dict);
    unload();
    // Return true upon
    // loading of dict
    return true;

}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    // If the dictionary was loaded return number of words
    if (&load)
        return num_words;
    else
        return 0;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    node *traverse = NULL;

    // If root is not NULL
    while (root != NULL)
    {
        // Set trav pointing to the root node
        traverse = root;

        // Call the helper function,
        // passing through the trav node
        free_nodes(traverse);

        // Return true upon success
        return true;
    }

    // Return false upon failed unload
     return false;

    free(traverse);
}

// A void function that accepts a node pointer
// A helper function for unload
void free_nodes(node *travel)
{
    // For every node pointer in children
    for (int i = 0; i < 27; i++)
    {
        // If the pointer to children @ i is not NULL,
        // call the free_nodes function recursively
        if (travel -> children[i])
            free_nodes(travel -> children[i]);
    }

    // Free the travel pointer
    free(travel);
}

// Find the position for the letter
// in the children node
int alpha_index(char ch)
{
    // If an apostrophe
    if (ch == '\'')
        return 26;
    else if (ch >= 'a' && ch <= 'z')
        return ch - 'a';
    else
        return ch - 'A';
}

