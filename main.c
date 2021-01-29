#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "filters_header.h"


typedef enum image_filter_name_t
{
    Blur, Boundary,Darken, Grayscale, Invert, Multiplier, Reflect, Whiten
}image_filter_name_enum;


void one_image_at_a_time(char image_name[]);
void one_image_filter_at_a_time(char image_name[], image_filter_name_enum image_filter, BITMAPFILEHEADER fileheader, BITMAPINFOHEADER infoheader, int pixelwidth, int pixelheight, int imagewidth, int imageheight, BGRTRIPLE **color_pixel_array);


// array of filter names  ---> order based on order in folder Images_copy
char Image_filter_names[][50] = {
                                    {"Blur"},
                                    {"Boundary"},
                                    {"Darken"},
                                    {"Grayscale"},
                                    {"Halfreflectleft"},
                                    {"Halfreflectright"},
                                    {"Invert"},
                                    {"Multiplier"},
                                    {"Reflect"},
                                    {"Whiten"},
                                };


// function pointer array
void (*fp[])(BGRTRIPLE **, long int, long int) = {blur, boundary, darken, grayscale, halfreflectleft, halfreflectright, invert, multiplier, reflect, whiten};


int Image_filter_count = 10;








int main(void)
{
    char List_of_image_names[100][50];

    FILE *fp_image_names;
    fp_image_names = fopen("ImageList.txt", "r");
    int ch, count = 0;

    while (1)
    {
        ch = fscanf(fp_image_names, "%s", List_of_image_names[count]);
        if (ch == EOF)
        {
            printf("Total Images %d\n", count);
            break;
        }
        count++;
    }


    for (int i = 0; i < count; i++)
    {
        one_image_at_a_time(List_of_image_names[i]);
    }


    return(0);
}







void one_image_at_a_time(char image_name[])
{
    FILE *original;

    // create formatted string for filenames
    char original_image_string[100];

    sprintf(original_image_string, "./Images/%s.bmp", image_name);

    printf("%s : ", image_name);

    original = fopen(original_image_string, "rb");

    if (original == NULL)
    {
        printf("Sorry Unable to open file\n");
        return;
    }

    BITMAPFILEHEADER fileheader;
    BITMAPINFOHEADER infoheader;

    fread(&fileheader, sizeof(BITMAPFILEHEADER), 1, original);
    fread(&infoheader, sizeof(BITMAPINFOHEADER), 1, original);


    unsigned long int filesizebytes = 0 ;
    memcpy(&filesizebytes, fileheader.filesize, sizeof(unsigned int));



    unsigned long int colorbytes = filesizebytes - sizeof(BITMAPFILEHEADER) - sizeof(BITMAPINFOHEADER);
    unsigned long int total_pixels = colorbytes / 3;
    unsigned long int imagewidth = 0, imageheight = 0;

    memcpy(&imagewidth, infoheader.imageWidth, sizeof(unsigned int));
    memcpy(&imageheight, infoheader.imageHeight, sizeof(unsigned int));


    unsigned long int padding = 0;
    unsigned long int pixelwidth = 0, pixelheight = 0;
    unsigned int bitsPerPixel = 0;
    memcpy(&bitsPerPixel, infoheader.bitsperpixel, 2 * sizeof(unsigned char));
    pixelwidth = (floor((bitsPerPixel * imagewidth + 31) / 32) * 4) / 3;
    padding = pixelwidth - imagewidth;
    pixelheight = imageheight;


    BGRTRIPLE **color_pixel_array;
    color_pixel_array = (BGRTRIPLE **)malloc(sizeof(BGRTRIPLE *) * pixelheight);
    for (unsigned int i = 0; i < pixelheight; i++)
    {
        color_pixel_array[i] = (BGRTRIPLE *)malloc(sizeof(BGRTRIPLE) * pixelwidth);
    }


    BGRTRIPLE pixel;


    // read image in upright form
    int bytes_read = 0;
    for (long int i = pixelheight - 1UL; i >= 0; i--)
    {
        for (unsigned long int j = 0; j < pixelwidth; j++)
        {
            bytes_read = fread(&pixel, 3, 1, original);
            color_pixel_array[i][j] = pixel;
        }
    }


    for (int k = 0; k < Image_filter_count; k++)
    {
        one_image_filter_at_a_time(image_name, k, fileheader, infoheader, pixelwidth, pixelheight, imagewidth, imageheight, color_pixel_array);
    }

    printf("\n");


    fclose(original);

    return;
}





void one_image_filter_at_a_time(char image_name[], image_filter_name_enum image_filter, BITMAPFILEHEADER fileheader, BITMAPINFOHEADER infoheader, int pixelwidth, int pixelheight, int imagewidth, int imageheight, BGRTRIPLE **color_pixel_array)
{
    FILE *copy;

    // create formatted string for filenames
    char copy_image_string[100];

    sprintf(copy_image_string, "./Friends_copy/%s/%s_%s.bmp", Image_filter_names[image_filter], image_name, Image_filter_names[image_filter]);

    printf(" %s ", Image_filter_names[image_filter]);

    copy = fopen(copy_image_string, "wb");

    if (copy == NULL)
    {
        printf("Sorry Unable to open file\n");
        return;
    }

    fwrite(&fileheader, sizeof(BITMAPFILEHEADER), 1, copy);
    fwrite(&infoheader, sizeof(BITMAPINFOHEADER), 1, copy);




    BGRTRIPLE pixel;
    BGRTRIPLE **color_pixel_array_copy;
    color_pixel_array_copy = (BGRTRIPLE **)malloc(sizeof(BGRTRIPLE *) * pixelheight);
    for (unsigned int i = 0; i < pixelheight; i++)
    {
        color_pixel_array_copy[i] = (BGRTRIPLE *)malloc(sizeof(BGRTRIPLE) * pixelwidth);
    }

    // create copy
    for (long int i = 0; i < pixelheight; i++)
    {
        for (long int j = 0; j < pixelwidth; j++)
        {
            color_pixel_array_copy[i][j] = color_pixel_array[i][j];
        }
    }


    // call appropriate function
    (*fp[image_filter])(color_pixel_array_copy, imagewidth, imageheight);



    // copy the bytes to file in reverse form
    for (long int i = (pixelheight - 1); i >= 0; i--)
    {
        for (unsigned long int j = 0; j < pixelwidth; j++)
        {
            pixel = color_pixel_array_copy[i][j];
            fwrite(&pixel, 3, 1, copy);
        }
    }


    // free all memory
    for (unsigned int i = 0; i < pixelheight; i++)
    {
        free(color_pixel_array_copy[i]);
    }
    free(color_pixel_array_copy);



    fclose(copy);

    return;
}