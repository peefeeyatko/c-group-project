#include "encryption.h"

int *readFile(char filename[], int size);
int ConvertEndianToInt(const int tab[4]);
int ConvertBitToInt(int tab[8]);
int *ConvertirIntToBit(int value);
void WriteEncryptedFile(char filename[], int *file, int size, int keynumber);
int ReadSize(char filename[]);
int *AddTwoBit(int *bit1, int *bit2);
void WriteDecryptedFile(char filename[], int *file, int size, int keynumber);

/*function that read the bmp image and put each value on an array (so we can manipulate the value later)
 input: -file that contain the bmp image that we want to encrypt or manipulate
        - size of the bmp image
 output: array that contain the value of the bmp image*/
int *readFile(char filename[], int size)
{
    int *arrayfinal = NULL;           /*to initialize*/
    int i, l, m;                      /*for the loop*/
    FILE *fp = fopen(filename, "rb"); /*to open the file in read mode*/
    if (fp == NULL)
    {
        printf("failure");
    }
    else
    {
        arrayfinal = malloc(size * sizeof(int)); /*to create the array of the size of the bmp image*/
        for (i = 0; i < size; i++)               /*to initialize each value*/
        {
            arrayfinal[i] = 0;
        }
        /*printf("size ; %d", size); that line was to make sure we obtain the good size of the file*/
        fseek(fp, 0, SEEK_SET);
        /*to put the cursor at the beginning of the file*/
        for (l = 0; l < size; l++)
        {
            fread(&arrayfinal[l], 1, 1, fp);
            /*to put each value of the bmp image in the array*/
        }
        /*under this is just to print the image but it is not useful for the program*/
        printf("HEADER\n");
        for (m = 0; m < 14; m++)
        {
            printf("%d ", arrayfinal[m]);
        }
        printf("\n");
        printf("HEADER INFOS\n");
        for (m = 14; m < 54; m++)
        {
            printf("%d ", arrayfinal[m]);
        }
        printf("\n");
        printf("IMAGE\n");
        for (m = 54; m < size; m++)
        {
            printf("%d ", arrayfinal[m]);
        }
        printf("the size is : %d\n", size);
        printf("\n");
    }
    fclose(fp);
    return arrayfinal; /*return the array that contain the value of the image*/
}

/*function that gives the size of a bmp image (to create an array of the good size later)
 input: file that contain the bmp image that we want to know the size
 output: size of the bmp image*/
int ReadSize(char filename[])
{
    int array[6];           /*array that will takes the first 6 value of the file*/
    int arraysize[4];       /*array thath will contain the size of the file in Endian*/
    int i, j, k;            /*for the loop*/
    int size = 0;           /*to initialize*/
    for (i = 0; i < 6; i++) /*to initialize*/
    {
        array[i] = 0;
    }
    for (i = 0; i < 4; i++) /*to initialize*/
    {
        arraysize[i] = 0;
    }
    FILE *fp = fopen(filename, "rb"); /*to open the file in read mode*/
    if (fp == NULL)
    {
        printf("failure");
    }
    else
    {
        for (j = 0; j < 6; j++) /*take the first 6 value*/
        {
            fread(&array[j], 1, 1, fp);
        }
        for (k = 0; k < 4; k++)
        {
            arraysize[k] = array[k + 2];
            /*the size of the file is situated between array[2] and array[5]*/
        }
        size = ConvertEndianToInt(arraysize); /*convert the size from endian to int*/
    }
    fclose(fp);
    return size; /*return the size of the file in int*/
}

/*void that creates a encrypted bmp image from a array
 input: -name of new bmp image created
        -file that contain the bmp image that the user want to encrypt
        -size of the file (so size of the array)
        -keynumber is the number that we use to encrypt the file (between 0 and 255)
 output: no output*/
void WriteEncryptedFile(char filename[], int *file, int size, int keynumber)
{
    int i;
    int *keybit = ConvertirIntToBit(keynumber); /*creates a keybit to encrypt the document*/
    int array[size];
    for (i = 0; i < 8; i++)
    {
        printf("%d value of key bit is : %d\n", i, keybit[i]);
    }
    printf("\n");
    FILE *fp = fopen(filename, "wb"); /*to open the file in write mode*/
    if (fp == NULL)
    {
        printf("failure");
    }
    else
    {
        for (i = 0; i < 54; i++) /* copy the header info of the original image (to conserve the bmp format)*/
        {
            array[i] = file[i];
            fwrite(&file[i], 1, 1, fp);
        }
        for (i = 54; i < size; i++) /*to encrypt the image (but keep the bmp format)*/
        {
            int *tempbit = ConvertirIntToBit(file[i]);
            int *tempbit2 = AddTwoBit(tempbit, keybit); /*temporary bit that contain the value of file[i]+keynumber (in bit)*/
            int value = ConvertBitToInt(tempbit2);      /*value that contain the addition*/
            array[i] = value;
            fwrite(&array[i], 1, 1, fp); /*write the value in the file*/
                                         /*so this loop take the value file[i], convert it in bit, add it to the keybit, and out the result in the file*/
            free(tempbit);
            free(tempbit2);
            /*tempbit = NULL;
		    tempbit2 = NULL;*/
        }
    }
    fclose(fp);
}

void WriteDecryptedFile(char filename[], int *file, int size, int keynumber)
{
    int i;
    int array[size];
    int *keybit = ConvertirIntToBit(keynumber); /*creates a keybit to encrypt the document*/
    FILE *fp = fopen(filename, "wb");           /*to open the file in write mode*/
    if (fp == NULL)
    {
        printf("failure");
    }
    else
    {
        for (i = 0; i < 54; i++) /* copy the header info of the original image (to conserve the bmp format)*/
        {
            array[i] = file[i];
            fwrite(&file[i], 1, 1, fp);
        }
        for (i = 54; i < size; i++) /*to decrypt the image (but keep the bmp format)*/
        {
            int *tempbit = ConvertirIntToBit(file[i]);
            int *tempbit2 = AddTwoBit(tempbit, keybit); /*temporary bit that contain the value of file[i]+keynumber (in bit)*/
            int value = ConvertBitToInt(tempbit2);      /*value that contain the addition*/
            array[i] = value;
            fwrite(&array[i], 1, 1, fp); /*write the value in the file*/
                                         /*so this loop take the value file[i], convert it in bit, add it to the keybit, and out the result in the file*/
            free(tempbit);
            free(tempbit2);
        }
    }
    fclose(fp);
}

/*use to do the conversion from endian to int, use to obtain the size (which is in endian)
 input: take a tab[4] that contain a endian number
 output: return the value in int*/
int ConvertEndianToInt(const int array[4])
{
    int value = 0;          /*value that will contain the convertion*/
    int power = 1;          /*the power*/
    int i;                  /*for the loop*/
    for (i = 0; i < 4; i++) /*loop that goes through the endian array*/
    {
        value += (array[i] * power); /*formula to convert the int*/
        power *= 256;
    }
    return value; /*return the int that contain the endian number convert in int*/
}

/*use to do the conversion from bit to int
 input: take a tab[8] that contain a bit umber
 output: return the value in int*/
int ConvertBitToInt(int *tab)
{
    int value = 0;
    int power = 0;
    int i;
    for (i = 7; i >= 0; i--)
    {
        if (tab[i] == 1)
        {
            value += pow(2, power);
        }
        power++;
    }
    return value; /*return the int that contain the bit convert in int*/
}

/*use to do the conversion from int to bit
 input: take a int
 output: return a tab[8] that contain a bit*/
int *ConvertirIntToBit(int value)
{
    int *array = malloc(8 * sizeof(int));
    int i, j;
    for (i = 0; i < 8; i++)
    {
        array[i] = 0;
    }
    for (j = 7; j >= 0; j--)
    {
        array[j] = value % 2;
        value /= 2;
    }
    return array; /*return the array that contain the value convert in bit*/
}

/*use to do the addition of two bit, the addition follows this rules:
 1+1 = 0;
 0+0 = 0;
 1+0 = 1;
 0+1 = 1;
 this addition is use to encrypt the bmp image
 input: take two bit
 output: return the bit that contain the addition*/
int *AddTwoBit(int *bit1, int *bit2)
{
    int *value = malloc(8 * sizeof(int)); /*create the array that will contain the addition*/
    int i, j, temp;                       /*i, j for the loop, temp is a temporary variable*/
    for (i = 0; i < 8; i++)               /*to initialize the array value*/
    {
        value[i] = 0;
    }
    for (j = 0; j < 8; j++)
    {
        temp = bit1[j] + bit2[j];   /*temporary variable contain the addition of the two bit*/
        if (temp == 0 || temp == 1) /*case where we add 1+0 or 0+1, or 0+0*/
        /*if the result is 0 then value = 0, if the result is 1 then the value = 1*/
        {
            value[j] = temp;
        }
        if (temp == 2) /*if the result is 2, it means it is 1+1*/
        /*so value = 0*/
        {
            value[j] = 0;
        }
    }
    return value; /*return the bit that contain the addition*/
}

/*******************************************************************************
 * This function will take an image file and then encrypt the file.
 * inputs:
 * - BMP file
 * outputs:
 * - 1 for success or 0 for failure
*******************************************************************************/
void encrypt_image()
{
    char filename[99] = IMAGES_DIR;
    strcat(filename, "coco.bmp");

    int size = ReadSize(filename);

    char path[99] = ENCRYPTED_DIR;
    strcat(path, "coco.bmp");

    int *array = readFile(filename, size);
    WriteEncryptedFile(path, array, size, 200);
}

/*******************************************************************************
 * This function will take an encrypted file and then decrypt it.
 * inputs:
 * - encrypted BMP file
 * outputs:
 * - 1 for success or 0 for failure
*******************************************************************************/
void decrypt_image()
{
    char path[99] = ENCRYPTED_DIR;
    char filename[99] = "coco.bmp";
    strcat(path, filename);

    int size2 = ReadSize(path);
    int *array2 = readFile(path, size2);

    char destination[99] = DECRYPTED_DIR;
    strcat(destination, filename);

    printf("%s\n", destination);

    WriteDecryptedFile(destination, array2, size2, 200);
}