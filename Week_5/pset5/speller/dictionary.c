// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <strings.h>
#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// *** Likely will want to change N to something larger than 1
// Number of buckets in hash table
const unsigned int N = 10000;

// Hash table
node *table[N];





// Returns true if word is in dictionary else false
bool check(const char *word)
{

    int hashKey = hash(word);


    if (table[hashKey] == NULL)
    {
        return false;
    }
    else
    {
        struct node *p;
        p = table[hashKey];

        while (p != NULL)
        {
            if (strcasecmp(word, p->word) == 0)
            {
                return true;
            }
            p = p->next;
        }
    }

return false;
}





// Hashes word to a number
// hash function borrowed from Jacob Sober: https://www.youtube.com/watch?v=2Ti5yvumFTU
// only changes made to the hash function he showed in his youtube video was to make
// the hash function not case sensitive (i.e. Foo, foo, foO, etc., will all be hashed to
// the same key)
unsigned int hash(const char *word)
{
    int length = strlen(word);
    unsigned int hashKey = 0;
    for (int i = 0; i < length; i++)
    {
        hashKey += tolower(word[i]);
        hashKey = (hashKey * tolower(word[i])) % N;
    }
    return hashKey;
}





// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    FILE *dicPtr = fopen(dictionary, "r");
    if (dicPtr == NULL)
    {
        return false;
    }

    char buffer[LENGTH + 1];

    while (fscanf(dicPtr, "%s", buffer) != EOF)
    {
        struct node *temp = (struct node*)malloc(sizeof(struct node));
        if (temp == NULL)
        {
            return false;
        }
        temp->next = NULL;

        strcpy(temp->word, buffer);

        int hashKey = hash(temp->word);

        if (table[hashKey] == NULL)
        {
            table[hashKey] = temp;
        }
        else
        {
            temp-> next = table[hashKey];
            table[hashKey] = temp;
        }
    }
    fclose(dicPtr);
    return true;
}




// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    int words = 0;

    for (int i = 0; i < N; i++)
    {
        struct node *p;
        p = table[i];
        while (p != NULL)
        {
            p = p->next;
            words++;
        }
    }
    return words;
}





// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    for (int i = 0; i < N; i++)
    {
        struct node *temp2;
        temp2 = table[i];
        struct node *temp1;
        temp1 = table[i];

        while (temp2 != NULL)
        {
            temp1 = temp2;
            temp2 = temp2->next;
            free(temp1);
        }
    }
    return true;
}



