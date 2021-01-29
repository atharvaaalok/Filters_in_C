#ifndef _BMP
#define _BMP

typedef struct bitmapfileheader_t            // 14 bytes
{
    unsigned char filetype[2];              // bytes for BM to let the programmer know hex equivalent is 42 4d
    unsigned char filesize[4];              // size of the file stored in reverse order that is if size is hex 72 then stored as 72 00 00 00
    unsigned char bitmapcreateapp[4];       // applications that create bitmap files
    unsigned char colordataoffset[4];      // offset at which color data really starts that is after file header and info header in our case 54 bytes later

}__attribute__((__packed__))
BITMAPFILEHEADER;


typedef struct bitmapinfoheader_t                  // 40 bytes
{
    unsigned char headersize[4];                   // size of info header here 40 bytes
    unsigned char imageWidth[4];                   // width of image in pixels --> put in reverse order just like filesize in bitmapfileheader
    unsigned char imageHeight[4];                 // height of image in pixels
    unsigned char color_plane_count[2];           // always 1
    unsigned char bitsperpixel[2];               // B G R format each takes 8 bytes so total 24 bytes for each pixel
    unsigned char compressionmethod[4];
    unsigned char imagesize[4];                  // size of color data in bytes
    unsigned char horizontalresolution[4];        // determines how printer will print the pixels c5 00 00 00   197 pixels per meter
    unsigned char verticalresolution[4];
    unsigned char numberofcolors[4];
    unsigned char numberofimportantcolors[4];

}__attribute__((__packed__))
BITMAPINFOHEADER;


typedef struct bgrtriple_t               // one pixel
{
    unsigned char blue;
    unsigned char green;
    unsigned char red;
}__attribute__((__packed__))
BGRTRIPLE;



#endif