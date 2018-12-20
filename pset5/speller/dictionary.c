// Implements a dictionary's functionality                                                                                          // Ways to improve processing time
                                                                                                                                    // Check for prefixes when loading the dictionary
#include <stdbool.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "dictionary.h"

// To count the number of words
// being entered in dictionary
unsigned int words_total = 0;

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    // To hold the index for current letter
    int position = 0;

    // To count number of misspelled words
    int misspelled_words = 0;

    // Set trav node pointing to root node
    // These nodes were declared globally
    trav = root;

    // For every char in the word
    for (int i = 0; i < strlen(word); i++)
    {
        // Get the position for each letter
        position = alpha_index(word[i]);

        // If the pointer to children
        // @ position is NULL
        if (trav -> children[position] == NULL)
        {
            // Increment misspelled_words
            misspelled_words++;

            // Return false exit loop
            return false;
        }
        else
        {
            // Move pointer to next letter
            trav = trav -> children[position];
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
    int position = 0;

    // A variable to store each
    // char being read in
    char ch;

    // Create a root node with a pointer
    root = null_node(trav);
    trav = root;

    // Iterate through dictionary to load every word
    while(true)
    {
        // Read in each char
        ch = fgetc(dict);

        // Get position of char
        position = alpha_index(ch);

        // While the end of the word
        // is not being pointed to
        if (ch != '\n')
        {
            // If the end of file is reached
            if (feof(dict))
            {
                // Set the pointer to is_word to true
                trav -> is_word = true;

                // Close the dict file
                fclose(dict);

                // Return true upon successful load
                return true;
            }

            // Make sure the position is
            // between 0 and 26, inclusively
            if(position >= 0 && position <= 26)
            {
                // If the children node @ alpha_index is empty
                if (trav -> children[position] == NULL)
                {
                    // malloc a new children node
                    trav -> children[position] = null_node(trav -> children[position]);
                     //printf("moving to new node\n");
                    // Point leaf to the newly created node
                    //trav = trav -> children[position];
                }
                // If node already exists

                    // Move trav pointer to next node
                    trav = trav -> children[position];
            }
        }

        // End of word is reached
        else
        {
            // printf("finished word\n");
            // Set pointer to is_word to true
            trav -> is_word = true;

            // Increment num_words
            words_total++;

            // Set the trav pointer
            // back to the root node
            trav = root;
        }
    }

    // If there's an error reading
    // the dictionary
    if (ferror(dict))
    {
        // Close file
        fclose(dict);
        printf("Error reading\n");
        return false;
    }

    // Close file
    fclose(dict);

    // Return true upon
    // loading of dict
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    // If the dictionary was loaded,
    // return number of words
    if (&load)
        return words_total;
    else
        return 0;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    // Call the free_nodes function
    // to free all malloc'd node
    free_nodes(root);
    return true;
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
// in the children node. Accepts a
// char and returns an int
int alpha_index(char ch)
{
    // Return the index based on char
    if (ch >= 'a' && ch <= 'z')
         return ch - 'a';
    else if(ch >= 'A' && ch <= 'Z')
         return ch - 'A';
    else
        return 26;
}

// A function that creates and initializes to
// NULL the 27 pointers in the node children
// Accepts and returns a node pointer
node *null_node(node *node_ptr)
{
    node_ptr = malloc(sizeof(node));
    // If the pointer is NULL, return NULL
    if (node_ptr == NULL)
        return NULL;

    // For every node in children, set to NULL
    for (int i = 0; i < 27; i++)
        node_ptr -> children[i] = NULL;

    // Set is_word to false
    node_ptr -> is_word = false;

    // Return the node that was just created
    return node_ptr;
}
