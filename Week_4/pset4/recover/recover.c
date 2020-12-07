/* plovesee
*  Recover; August 2020
*/

#include <stdio.h>
#include <stdlib.h>
#include <cs50.h>
#include <stdint.h>

// define BYTE type
typedef uint8_t BYTE;

// function prototypes
bool start_jpeg(BYTE buffer[]);

int main(int argc, char *argv[])
{

    // checking user input at command line
    if (argc < 2)
    {
        printf("Usage: ./recover image\n");
        return 1;
    }

    if (argc > 2)
    {
        printf("Only one file allowed\n");
        return 2;
    }


    // defining the buffer array and initializing to 0
    BYTE buffer[512] = {0};

    // opening the .raw file and storing in the file array; input from the command line
    FILE *file = fopen(argv[1], "r");
    // error checking for if file is not able to be read
    if (file == NULL)
    {
        printf("Unable to read file\n");
        return 1;
    }

    int filenumber = 0;
    FILE *recovered_file = NULL;
    int name_size = 8;
    char filename[name_size];
    // need found_first_image to make sure that the first file definately starts with an actual jpeg header; not just something that did not satisfy start_jpeg()
    bool found_first_image = false;


    // loop for runing through file, determining if start of jpeg, making and appending to individual jpeg files
    while (fread(buffer, 512, 1, file))
    {
        // branch for when a pack comes up that starts with a jpeg header
        if (start_jpeg(buffer) == true)
        {
            // condition if this is the first jpeg file
            if (filenumber == 0)
            {
                sprintf(filename, "%03i.jpg", filenumber);
                recovered_file = fopen(filename, "w");
                filenumber++;
                if (recovered_file == NULL)
                {
                    return 1;
                }
                fwrite(buffer, 512, 1, recovered_file);
                found_first_image = true;
            }
            // condition if this is not the first jpeg file and a jpeg header is encountered
            else
            {
                fclose(recovered_file);
                sprintf(filename, "%03i.jpg", filenumber);
                recovered_file = fopen(filename, "w");
                filenumber++;
                if (recovered_file == NULL)
                {
                    return 1;
                }
                fwrite(buffer, 512, 1, recovered_file);
            }

        }
        // branch if the first image has already been found && the next jpeg header has not been encountered yet
        else if (found_first_image)
        {
            fwrite(buffer, 512, 1, recovered_file);
        }

    }

    // closing out the files
    fclose(recovered_file);
    fclose(file);

    return 0;
}


// function to determine if the current block being looked at is the start of a jpeg or not
bool start_jpeg(BYTE buffer[])
{
    if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
    {
        return true;

    }
    else
    {
        return false;

    }
}