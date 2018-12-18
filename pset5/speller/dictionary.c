// Implements a dictionary's functionality

#include <stdbool.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


#include "dictionary.h"

node *root = NULL;
node *trav = NULL;
unsigned int num_words = 0;


void free_nodes(node *travel);

// Returns true if word is in dictionary else false
bool check(const char *word)
{
     int alpha_index = 0;
    int misspelled_words = 0;
    trav = root;
    //printf("\n\nCHECK\n");
    //printf("checking %s\n", word);


    for (int i = 0; i < strlen(word); i++)
    {
        char letter = tolower(word[i]);
       // printf("checking letter %c\n", letter);

        if (letter >= 97 && letter <= 122)
             alpha_index = letter - 97../
        else if (letter == 39)
            alpha_index = 26;
        //printf("alpha_index is: %i\n", alpha_index);
        //trav = trav -> children[alpha_index];
   // printf("address? %i\n", 0x1087520);
        if (trav->children[alpha_index] == NULL)
        {
            //printf("failed on letter %c found null child\n", letter);
            misspelled_words++;
            return false;
        }
        else
        {
            trav = trav->children[alpha_index];
        }


    }
   // printf("got to end of checked word now checking if the word is valid\n");
    if (trav -> is_word)
        return true;


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

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
   if(&load)
   {
       printf("num words: %u\n", num_words);
        return num_words;
   }
    else
        return 0;




}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    if (root)
    {
        trav = root;
        free_nodes(trav);
        return true;
    }
    else
        return false;

}


void free_nodes(node *travel)
{
    for (int i = 0; i < 27; i++)
    {
        if (travel->children[i])
            free_nodes(travel->children[i]);
    }

    free(travel);
}

