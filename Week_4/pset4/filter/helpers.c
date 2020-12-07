#include "helpers.h"
#include "math.h"
#define MAX_COLOR 255

// function prototypes
void average(int i, int height, int j, int width, RGBTRIPLE image_x[height][width]);
void old_timey(int i, int height, int j, int width, RGBTRIPLE image_x[height][width]);
void swap(RGBTRIPLE *a, RGBTRIPLE *b);
RGBTRIPLE blurpixel(int i, int height, int j, int width, RGBTRIPLE any_image[height][width]);

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{

    // 2-dimmensional loop to iterate over the entire image row by row across the height of the array
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // average() function changes Red,  Blue, and Green values in each pixle to the average of the the three
            average(i, height, j, width, image);
        }
    }

    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    // 2-dimmensional array to iterate through the entire image and convert each pixel to sepia
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // old_timey() function converts the subject pixel to sepia
            old_timey(i, height, j, width, image);
        }
    }

    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    int halfwidth;

    if (width % 2 == 0)
    {
        halfwidth = width / 2;
    }
    else
    {
        halfwidth = (width - 1) / 2;
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < halfwidth; j++)
        {
            swap(&image[i][j], &image[i][width - (j + 1)]);
        }
    }

    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // create a new image array for the blured image to be stored in
    RGBTRIPLE  blurimage[height][width];

    // 2-dimmensional loop to blur each pixle of image and copy into blurimage (seperate array to be copied into subject array later)
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            blurimage[i][j] = blurpixel(i, height, j, width, image);
        }
    }

    // 2-dimmensional loop to copy blurimage into image
    for (int j = 0; j < width; j++)
    {
        for (int i = 0; i < height; i++)
        {
            image[i][j] = blurimage[i][j];
        }
    }

    return;
}

// function to calculate the avg value of Red, Green and Blue values in each pixle, set each equal to that
void average(int i, int height, int j, int width, RGBTRIPLE image_x[height][width])
{
    // calculate the average value of the Red, Green and Blue values
    // necissary to cast each component value to float from int for needed precision while computing average
    int avg = round((((float) image_x[i][j].rgbtBlue + (float) image_x[i][j].rgbtRed + (float) image_x[i][j].rgbtGreen) / 3));

    // set each component of the pixel equal to the average value
    image_x[i][j].rgbtBlue = avg;
    image_x[i][j].rgbtRed = avg;
    image_x[i][j].rgbtGreen = avg;

    return;
}

// function to calculate the old timey color of each pixel
void old_timey(int i, int height, int j, int width, RGBTRIPLE image_x[height][width])
{
    int old_red, old_green, old_blue = 0;

    // calculate the old timey color values for each component color; cap at MAX_COLOR
    old_red = round(.393 * (float) image_x[i][j].rgbtRed + .769 * (float) image_x[i][j].rgbtGreen + .189 *
                    (float) image_x[i][j].rgbtBlue);
    if (old_red > MAX_COLOR)
    {
        old_red = MAX_COLOR;
    }

    old_green = round(.349 * (float) image_x[i][j].rgbtRed + .686 * (float) image_x[i][j].rgbtGreen + .168 *
                      (float) image_x[i][j].rgbtBlue);
    if (old_green > MAX_COLOR)
    {
        old_green = MAX_COLOR;
    }

    old_blue = round(.272 * (float) image_x[i][j].rgbtRed + .534 * (float) image_x[i][j].rgbtGreen + .131 *
                     (float) image_x[i][j].rgbtBlue);
    if (old_blue > MAX_COLOR)
    {
        old_blue = MAX_COLOR;
    }

    // set the values of the subject pixel equal to the old timey colors
    image_x[i][j].rgbtRed = old_red;
    image_x[i][j].rgbtGreen = old_green;
    image_x[i][j].rgbtBlue = old_blue;

    return;
}

// swap function for swapping pixels from left to right
void swap(RGBTRIPLE *a, RGBTRIPLE *b)
{
    RGBTRIPLE temp = *a;
    *a = *b;
    *b = temp;
}

//function to return a blurred pixle to be copied into new image (blur)
RGBTRIPLE blurpixel(int i, int height, int j, int width, RGBTRIPLE any_image[height][width])
{
    int pixelcount = 0;
    int redtotal = 0;
    int greentotal = 0;
    int bluetotal = 0;
    RGBTRIPLE blurredpixel;

    for (int deltaj = -1; deltaj < 2; deltaj++)
    {
        for (int deltai = -1; deltai < 2; deltai++)
        {
            int jj = j + deltaj;
            int ii = i + deltai;
            if ((jj) >= 0 && (jj) < width && (ii) >= 0 && (ii) < height)
            {
                pixelcount++;
                redtotal = redtotal + any_image[ii][jj].rgbtRed;
                greentotal = greentotal + any_image[ii][jj].rgbtGreen;
                bluetotal = bluetotal + any_image[ii][jj].rgbtBlue;
            }
        }
    }

    // max to 255 if greater; casting ints to floats for more accuracy
    int avg_red = round((float) redtotal / (float) pixelcount);
    if (avg_red > 255)
    {
        avg_red = 255;
    }

    int avg_green = round((float) greentotal / (float) pixelcount);
    if (avg_green > 255)
    {
        avg_green = 255;
    }

    int avg_blue = round((float) bluetotal / (float) pixelcount);
    if (avg_blue > 255)
    {
        avg_blue = 255;
    }

    // assigning average values for each component color to the pixle to be returned
    blurredpixel.rgbtRed = avg_red;
    blurredpixel.rgbtGreen = avg_green;
    blurredpixel.rgbtBlue = avg_blue;

    return blurredpixel;
}