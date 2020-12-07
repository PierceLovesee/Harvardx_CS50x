#include <stdio.h>
#include <cs50.h>

int main(void)
{

    // available variables
    int block;
    int height;
    int row;
    int space;
    int middle;
    int gap;

    //defining how high the pyramid will be
    do
    {
        height = get_int("How high would you like the pyramids?: ");
    }
    while (height < 1 || height > 8);

    //define the distance between the two pyramids
    do
    {
        gap = get_int("How far apart should the pyramids be?: ");
    }
    while (gap < 0 || gap > 4);

    // building the pyramid
    for (row = 0; row < height; row++)
    {
        //measuring out spaces to the left fo the first pyramid
        for (space = 0; space < height - row - 1; space++)
        {
            printf(" ");
        }

        //counting out blocks per row on left pyramid
        for (block = 0; block < row + 1; block++)
        {
            printf("#");
        }

        //spacing out betweent the two pyramids
        for (middle = 0; middle < gap; middle++)
        {
            printf(" ");
        }

        //counting out the blocks per row on the right for second pyramid
        for (block = 0; block < row + 1; block++)
        {
                printf("#");
        }

        printf("\n");
    }
    return space;
}