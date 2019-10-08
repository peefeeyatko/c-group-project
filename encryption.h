#include <math.h>
#include <stdio.h>
#include <string.h>

/*******************************************************************************
 * List preprocessing directives
*******************************************************************************/
#define IMAGES_DIR "./images/"

/*******************************************************************************
 * Function prototypes 
*******************************************************************************/
int encrypt_image();
int decrypt_image();
void readFile(const char filename[99]);
int convertEndianToInt(const int tab[4]);