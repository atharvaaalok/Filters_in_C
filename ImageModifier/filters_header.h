#ifndef _FILTERS
#define _FILTERS

#include "bitmap.h"


// All the function declarations
void reflect(BGRTRIPLE **array, long int width, long int height);
void grayscale(BGRTRIPLE **array, long  int width, long int height);
void multiplier(BGRTRIPLE **array, long int width, long int height);
void blur(BGRTRIPLE **array, long  int width, long int height);
void darken(BGRTRIPLE **array, long  int width, long int height);
void invert(BGRTRIPLE **array, long  int width, long int height);
void whiten(BGRTRIPLE **array, long  int width, long int height);
void halfreflectleft(BGRTRIPLE **array, long int width, long int height);
void halfreflectright(BGRTRIPLE **array, long int width, long int height);
void boundary(BGRTRIPLE **array, long int width, long int height);

#endif