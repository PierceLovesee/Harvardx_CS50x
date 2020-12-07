//plovesee; CS50; July 2020

#include <stdio.h>
#include <cs50.h>
#include <math.h>
#include <string.h>
#include <ctype.h>


// declaring functions used as subrutines to main
int count_char(string x);
int count_word(string y);
int count_sent(string z);


int main(void)
{
    // asking for user input for text
    string text = get_string("Text: ");


    // printing the number of letters
    int c = count_char(text);
    //printf("%i letter(s)\n", c);

    // printing the number of words
    int w = count_word(text);
    //printf("%i word(s)\n", w);

    // determine and print the number of sentences
    int s = count_sent(text);
    //printf("%i sentence(s)\n", s);


    // determine L and S for Coleman-Liau index
    float L = 100 * (float) c / (float) w;
    float S = 100 * (float) s / (float) w;

    // determining the Coleman-Liau index
    float index = 0.0588 * L - 0.296 * S - 15.8;

    // decision tree for result based on index
    if(index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if(index >= 1 && index < 16)
    {
        printf("Grade %.0f\n", round(index));
        //printf("%.4f\n", index);
    }
    else
    {
        printf("Grade 16+\n");
    }

    return 0;
}


// function to count individual letters
int count_char(string x)
{
    int count = 0;

    for(int i = 0, n = strlen(x); i < n; i++)
    {
        if(((x[i] <= 90) && (x[i] >= 65)) || ((x[i] <= 122) && (x[i] >= 97)))
        {
            count++;
        }
    }

    return count;
}


// function to count individual words
int count_word(string y)
{
    int count = 1;

    for(int i = 0, n = strlen(y); i < n; i++)
    {
        if(isalnum(y[i]) && (isspace(y[i - 1]) || (isspace(y[i - 2]) && !isalnum(y[i - 1]))))
        {
            count++;
        }
    }

    return count;
}


// function to count the number of sentences in a string
int count_sent(string z)
{
    int count = 0;

    for(int i = 0, n = strlen(z); i < n; i++)
    {
        if(z[i] == 46 || z[i] == 63 || z[i] == 33)
        {
            count++;
        }
    }

    return count;
}