// include the following libraries

#include <stdio.h>
#include <cs50.h>
#include <math.h>

// defining my variables

float change;
int cents;
int coin_count;


int main(void)
{
    //prompt the user for how much change needs to be given

    do
    {
        change = get_float("How much change needs to be given?\n(expressed in $00.00 format, numbers only): ");
    }
    while (change < 0);

    //convert $ to cents
    cents = round(change * 100);

    //greedy algorithm
    coin_count = 0;
    do
    {
        if(cents >= 25)
        {
           cents = cents - 25;
           coin_count++;
        }
        else if(cents >= 10)
        {
            cents = cents - 10;
            coin_count++;
        }
        else if(cents >= 5)
        {
            cents = cents - 5;
            coin_count++;
        }
        else
        {
            cents--;
            coin_count++;
        }

    }
    while (cents > 0);

printf("The minimum number of coins needed for your change is: %i coins\n", coin_count);
//printf("%i\n", coin_count);


    return 0;
}
