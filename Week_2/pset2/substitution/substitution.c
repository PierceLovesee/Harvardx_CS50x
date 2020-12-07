// plovesee; CS50; Caesar; 7-26-2020

// libraries included in this program
#include <stdio.h>
#include <ctype.h>
#include <math.h>
#include <cs50.h>
#include <stdlib.h>

// functions used within main
bool validate_key(int x, string y);

// main function of the program
int main (int argc, string argv[])
{

    bool vk = validate_key(argc, argv);
    if (vk = false)
    {
        return 1;
    }




    return 0;
}


// function to validate the key (k)
bool validate_key(int x, string y);
{

if (x == 2)
{
        for (int i = 0; i < strlen(y); i++)
        {
            if (!isdigit(y[i]))
            {
                return false;
            }

            return true
        }
}
else if (x < 2)
{
    printf("./caesar")
}
    if (x == 2 &&
}