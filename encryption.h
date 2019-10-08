#include <stdio.h>
#include <math.h>

/*******************************************************************************
 * Function prototypes 
*******************************************************************************/
void readFile(const char filename[99]);
int convertEndianToInt(const int tab[4]);

/*******************************************************************************
 * Read the file and put each number of the file in one cell of an array
 * inputs:
 * - char filename[]
 * outputs:
 * - none
*******************************************************************************/
void readFile(const char filename[99])
{
    int array[6];     /* array that will takes the first 6 value of the file */
    int arraysize[4]; /* array that will contain the size of the file in Endian */
    int j, k, l, m, size;
    FILE *fp = fopen(filename, "rb"); /* to open the file in read mode */
    
    if (fp == NULL) {
        printf("failure");
    } else {
        for (j = 0; j < 6; j++) {
            fread(&array[j], 1, 1, fp);
        }

        for (k = 0; k < 4; k++) {
            arraysize[k] = array[k + 2];
            /* the size of the file is situated between array[1] and array[5] */
        }

        size = convertEndianToInt(arraysize);
        /* we use the conversion because the size in the Header is in Endian */
        int arrayfinal[size];
        /* to create a array of the size of the file */
        /* printf("size ; %d", size); that line was to make sure we obtain the good size of the file */
        fseek(fp, 0, SEEK_SET);
        /* to put the cursor at the beginning of the file */
        for (l = 0; l < size; l++) {
            fread(&arrayfinal[l], 1, 1, fp);
        }

        printf("HEADER\n"); /* not necessary, but it is to print the arrayfinal of the file */

        for (m = 0; m < 14; m++) {
            printf("%d ", arrayfinal[m]);
        }

        printf("\n");
        printf("HEADER INFOS\n");

        for (m = 14; m < 54; m++) {
            printf("%d ", arrayfinal[m]);
        }

        printf("\n");
        printf("IMAGE\n");

        for (m = 54; m < size; m++) {
            printf("%d ", arrayfinal[m]);
        }

        printf("\n");
    }
    fclose(fp);
}

/*******************************************************************************
 * Use to do the conversion from endian to int
 * inputs:
 * - tab[4] that contain a endian number
 * outputs:
 * - the value in int
*******************************************************************************/
int convertEndianToInt(const int tab[4])
{
    int value = 0;
    int power = 1;
    int i;

    for (i = 0; i < 4; i++) {
        value += (tab[i] * power);
        power *= 256;
    }

    return value;
}