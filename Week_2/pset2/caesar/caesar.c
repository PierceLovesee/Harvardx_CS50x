// plovesee; CS50; Caesar; 7-26-2020

// include the following libraries
#include <stdio.h>
#include <ctype.h>
#include <math.h>
#include <cs50.h>
#include <stdlib.h>
#include <string.h>

// function used within main to validate key
bool validate_key(int x, string y);


// main function of the program
int main (int argc, string argv[])
{

    // validating the key
    if (validate_key(argc, argv[1]) == false)
    {
        return 1;
    }

    // convert key from string to integer
    int k = atoi(argv[1]);

    // collect user input for the plain text
    string plain = get_string("plaintext:  ");


    // convert plain text to ciphertext
    int l = strlen(plain);
    char cipher[l];

    for (int i = 0; i < l; i++)
    {
        // condition for converting capital letters
        if ( plain[i] > 64 && plain[i] < 91)
        {
            cipher[i] = 65 + (((plain[i] - 65) + k) % 26);
        }

        // condition for converting non-capital letters
        else if ( plain[i] > 96 && plain[i] < 123 )
        {
           cipher[i] = 97 + (((plain[i] - 97) + k) % 26);
        }

        // condition for non alphabetic characters
        else
        {
            cipher[i] = plain[i];
        }
    }


    // print out ciphertext
    printf("ciphertext:  ");
    for (int i = 0; i < l; i++)
    {
        printf("%c", cipher[i]);
    }
    printf("\n");

    // vale returned if no errors
    return 0;
}


// function to validate the key (k)
bool validate_key(int x, string y)
{
    if (x == 2)
    {
         for (int i = 0; i < strlen(y); i++)
            {
                if ( y[i] < 48 || y[i] > 57 )
                {
                    // error message if key contains anything besides #s
                    printf("key must only contain numbers\n");
                    return false;
                }
            }
        return true;
    }

    else if (x < 2)
    {
        // error message for no key
        printf("User input must include key ( i.e. ./caesar KEY)\n");

        return false;
    }

    else if (x > 2)
    {
        // error message for more than one key
        printf("User input must include only 1 key ( i.e. ./caesar KEY)\n");

        return false;
    }

    return false;
}