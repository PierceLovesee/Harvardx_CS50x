#include <stdio.h>
#include <cs50.h>

int main(void)
{

    // available variables
    int block;
    int height;
    int row;
    int space;

    //defining how high the pyramid will be
    do
    {
        height = get_int("How high would you like the pyramid?: ");
    }
    while (height < 1 || height > 8);

    // building the pyramid
    for (row = 0; row < height; row++)
    {
        for (space = 0; space < height - row - 1; space++)
        {
            printf(" ");
        }
        for (block = 0; block < row + 1; block++)
        {
            printf("#");
        }

        printf("\n");
    }
    return space;
}