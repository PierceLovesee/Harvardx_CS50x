// plovesee
// July 2020
// inlude the following libraries

#include <stdio.h>
#include <cs50.h>
#include <math.h>

// define my variables

long long cc_number;
int cs1;
int cs2;
int cs;
int n;
float digit;



int main(void)
{
    //prompt the user for credit card number

    cc_number = 0

    do
    {
    cc_number = get_long_long("Credit Card Number: ");
    }
    while cc_number <= 0

    //determine the first portion of the check sum, cs1, starting with cs1 = 0

    cs1 = 0;
    digit = 0;
    printf("cs1:\n");
    for(n = 0; n < 8; n++)
    {
        digit = ((cc_number % 10 ^ ((2 * n) + 2 )) / (10 ^ ((2 * n) + 1)));
        cs1 = cs1 + 2 * digit;
        printf("digit %i: %f\n", n, digit);
        //printf("%i\n", cs1);
    }

    //printf("%i\n", cs1);

    //determine the second portion of the check sum, cs2, starting with cs2 = 0

    cs2 = 0;
    printf("cs2:\n");

    for(n = 0; n < 8; n++)
    {
        cs2 = cs2 + ((cc_number % 10 ^ ((2 * n) + 1 )) / (10 ^ (2 * n)));
        printf("%i\n", cs2);
    }

    //printf("%i\n", cs2);

    //determine if the check sum is valid

    cs = (cs1 + cs2) % 10;


    if(cs == 0)
    {
        //AMEX
        if((3 * 10^15) < cc_number && cc_number < (4 * 10^15))
        {
            printf("AMEX\n");
        }
        //MASTER
        else if((5 * 10^16) < cc_number && cc_number < (6 * 10^16))
        {
            printf("MASTERCARD\n");
        }
        //VISA
        else if(((4 * 10^13) < cc_number && cc_number < (5 * 10^13)) || ((4 * 10^16) < cc_number && cc_number < (5 * 10^16)))
        {
            printf("VISA\n");
        }
        //INVALID
        else
        {
            printf("INVALID\n");
        }
    }

    else
    {
        printf("INVALID\n");
    }

    return 0;
}