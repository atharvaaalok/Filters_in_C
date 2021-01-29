#include <stdio.h>
#include <stdlib.h>
#include "filters_header.h"
#include <math.h>


// All the filter function definitions here

// reflect the image right to left
void reflect(BGRTRIPLE **array, long int width, long int height)
{
    BGRTRIPLE pixel;
    for (long int i = 0; i < height; i++)
    {
        for (long int j = 0; j < (width / 2); j++)
        {
            pixel = array[i][j];
            array[i][j] = array[i][width - j - 1];
            array[i][width - j - 1] = pixel;
        }
    }

    return;
}


// Convert image to grayscale
void grayscale(BGRTRIPLE **array, long  int width, long int height)
{
    float average;
    int assign;
    BGRTRIPLE pixel;
    for (long int i = 0; i < height; i++)
    {
        for (long int j = 0; j < width; j++)
        {
            average = ((float)(array[i][j].blue + array[i][j].green + array[i][j].red)) / 3;
            //image are integers hence need to typecast them before division otherwise result would be integer division
            assign = round(average);                               //assigning assign the value of average that is the grayscale value
            pixel.blue = pixel.green = pixel.red = assign;
            array[i][j] = pixel;
        }
    }
    return;
}


void multiplier(BGRTRIPLE **array, long int width, long int height)
{
    float multiplier = 2;
    BGRTRIPLE pixel;
    for (long int i = 0; i < height; i++)
    {
        for (long int j = 0; j < width; j++)
        {
            pixel = array[i][j];
            pixel.blue *= multiplier;
            pixel.green *= multiplier;
            pixel.red *= multiplier;
            array[i][j] = pixel;
        }
    }

    return;
}

void blur(BGRTRIPLE **array, long  int width, long int height)
{
    BGRTRIPLE **copy_array;
    copy_array = (BGRTRIPLE **)malloc(sizeof(BGRTRIPLE *) * height);
    for (unsigned int i = 0; i < height; i++)
    {
        copy_array[i] = (BGRTRIPLE *)malloc(sizeof(BGRTRIPLE) * width);
    }

    for (long int i = 0; i < height; i++)
    {
        for (long int j = 0; j < width; j++)
        {
            copy_array[i][j] = array[i][j];
        }
    }

    float averageblue, averagegreen, averagered;
    int sumblue, sumgreen, sumred;
    int counter = 0;
    int span = 5;
    BGRTRIPLE pixel;
    for (long int i = span; i < (height - span); i++)
    {
        for (long int j = span; j < (width - span); j++)
        {
            sumblue = sumgreen = sumred = 0;
            counter = 0;
            for (int row = -span; row <= span; row++)
            {
                for (int col = -span; col <= span; col++)
                {
                    counter++;
                    sumblue += copy_array[i + row][j + col].blue;
                    sumgreen += copy_array[i + row][j + col].green;
                    sumred += copy_array[i + row][j + col].red;
                }
            }
            //image are integers hence need to typecast them before division otherwise result would be integer division
            averageblue = ((float)sumblue) / counter;
            averagegreen = ((float)sumgreen) / counter;
            averagered = ((float)sumred) / counter;
            
            pixel.blue = round(averageblue);
            pixel.green = round(averagegreen);
            pixel.red = round(averagered);

            array[i][j] = pixel;
        }
    }
    // printf("%d %d\n", copy_array[height / 2][width / 2].blue, array[height / 2][width / 2].blue);

    return;
}


void darken(BGRTRIPLE **array, long  int width, long int height)
{
    BGRTRIPLE pixel;
    for (long int i = 0; i < height; i++)
    {
        for (long int j = 0; j < width; j++)
        {
            array[i][j].blue = array[i][j].blue / 2;
            array[i][j].green = array[i][j].green / 2;
            array[i][j].red = array[i][j].red / 2;
        }
    }

    return;
}

void invert(BGRTRIPLE **array, long  int width, long int height)
{
    BGRTRIPLE pixel;
    for (long int i = 0; i < height; i++)
    {
        for (long int j = 0; j < width; j++)
        {
            array[i][j].blue = 255 - array[i][j].blue;
            array[i][j].green = 255 - array[i][j].green;
            array[i][j].red = 255 - array[i][j].red;
        }
    }

    return;
}


void whiten(BGRTRIPLE **array, long  int width, long int height)
{
    BGRTRIPLE pixel;
    int value = 50;
    for (long int i = 0; i < height; i++)
    {
        for (long int j = 0; j < width; j++)
        {
            if (array[i][j].blue > (255 - value))
            {
                array[i][j].blue = 255;
            }
            else
            {
                array[i][j].blue = array[i][j].blue + value;
            }

            if (array[i][j].green > (255 - value))
            {
                array[i][j].green = 255;
            }
            else
            {
                array[i][j].green = array[i][j].green + value;
            }

            if (array[i][j].red > (255 - value))
            {
                array[i][j].red = 255;
            }
            else
            {
                array[i][j].red = array[i][j].red + value;
            }
        }
    }

    return;
}


void halfreflectleft(BGRTRIPLE **array, long int width, long int height)
{
    BGRTRIPLE pixel;
    for (long int i = 0; i < height; i++)
    {
        for (long int j = 0; j < (width / 2); j++)
        {
            array[i][width - j] = array[i][j];
        }
    }

    return;
}

void halfreflectright(BGRTRIPLE **array, long int width, long int height)
{
    BGRTRIPLE pixel;
    for (long int i = 0; i < height; i++)
    {
        for (long int j = 0; j < (width / 2); j++)
        {
            array[i][j] = array[i][width - j];
        }
    }

    return;
}


void boundary(BGRTRIPLE **array, long int width, long int height)
{
    BGRTRIPLE **copyar;
    copyar = (BGRTRIPLE **)malloc(sizeof(BGRTRIPLE *) * height);
    for (unsigned int i = 0; i < height; i++)
    {
        copyar[i] = (BGRTRIPLE *)malloc(sizeof(BGRTRIPLE) * width);
    }

    for (long int i = 0; i < height; i++)
    {
        for (long int j = 0; j < width; j++)
        {
            copyar[i][j] = array[i][j];
        }
    }

    int bluex = 0, greenx = 0, redx = 0;
    int bluey = 0, greeny = 0, redy = 0;
    int blueroot = 0, greenroot = 0, redroot = 0;
    for (long int i = 1; i < (height - 1); i++)
    {
        for (long int j = 1; j < (width - 1); j++)
        {
            // Gx
            bluex = greenx = redx = 0;
            bluex = (copyar[i-1][j-1].blue)*(-1) + (copyar[i-1][j].blue)*(0)+ (copyar[i-1][j+1].blue)*(1)+ (copyar[i][j-1].blue)*(-2)+ (copyar[i][j].blue)*(0)+ (copyar[i][j+1].blue)*(2)+ (copyar[i+1][j-1].blue)*(-1)+ (copyar[i+1][j].blue)*(0)+ (copyar[i+1][j+1].blue)*(1);
            greenx = (copyar[i-1][j-1].green)*(-1) + (copyar[i-1][j].green)*(0)+ (copyar[i-1][j+1].green)*(1)+ (copyar[i][j-1].green)*(-2)+ (copyar[i][j].green)*(0)+ (copyar[i][j+1].green)*(2)+ (copyar[i+1][j-1].green)*(-1)+ (copyar[i+1][j].green)*(0)+ (copyar[i+1][j+1].green)*(1);
            redx = (copyar[i-1][j-1].red)*(-1) + (copyar[i-1][j].red)*(0)+ (copyar[i-1][j+1].red)*(1)+ (copyar[i][j-1].red)*(-2)+ (copyar[i][j].red)*(0)+ (copyar[i][j+1].red)*(2)+ (copyar[i+1][j-1].red)*(-1)+ (copyar[i+1][j].red)*(0)+ (copyar[i+1][j+1].red)*(1);

            // Gy
            bluey = greeny = redy = 0;
            bluey = (copyar[i-1][j-1].blue)*(-1) + (copyar[i-1][j].blue)*(-2)+ (copyar[i-1][j+1].blue)*(-1)+ (copyar[i][j-1].blue)*(0)+ (copyar[i][j].blue)*(0)+ (copyar[i][j+1].blue)*(0)+ (copyar[i+1][j-1].blue)*(1)+ (copyar[i+1][j].blue)*(2)+ (copyar[i+1][j+1].blue)*(1);
            greeny = (copyar[i-1][j-1].green)*(-1) + (copyar[i-1][j].green)*(-2)+ (copyar[i-1][j+1].green)*(-1)+ (copyar[i][j-1].green)*(0)+ (copyar[i][j].green)*(0)+ (copyar[i][j+1].green)*(0)+ (copyar[i+1][j-1].green)*(1)+ (copyar[i+1][j].green)*(2)+ (copyar[i+1][j+1].green)*(1);
            redy = (copyar[i-1][j-1].red)*(-1) + (copyar[i-1][j].red)*(-2)+ (copyar[i-1][j+1].red)*(-1)+ (copyar[i][j-1].red)*(0)+ (copyar[i][j].red)*(0)+ (copyar[i][j+1].red)*(0)+ (copyar[i+1][j-1].red)*(1)+ (copyar[i+1][j].red)*(2)+ (copyar[i+1][j+1].red)*(1);

            // Gx^2 + Gy^2
            blueroot = round( pow( ( pow(bluex, 2) + pow(bluey,2) ), 0.5 ) );
            greenroot = round( pow( ( pow(greenx, 2) + pow(greeny,2) ), 0.5 ) );
            redroot = round( pow( ( pow(redx, 2) + pow(redy,2) ), 0.5 ) );

            array[i][j].blue = (blueroot > 255) ? 255 : blueroot ;
            array[i][j].green = (greenroot > 255) ? 255 : greenroot ;
            array[i][j].red = (redroot > 255) ? 255 : redroot ;
        }
    }


    return;
}

