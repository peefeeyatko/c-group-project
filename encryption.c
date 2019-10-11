#include "encryption.h"

int *readFile(char filename[], int size);
int ConvertEndianToInt(const int tab[4]);
int ConvertBitToInt(int tab[8]);
int *ConvertirIntToBit(int value);
void WriteEncryptedFile(char filename[], int *file, int size, int keynumber);
int ReadSize(char filename[]);
int *AddTwoBit(int *bit1, int *bit2);
void WriteDecryptedFile(char filename[], int *file, int size, int keynumber);

/*******************************************************************************
 * function that read the bmp image and put each value on an array 
 * (so we can manipulate the value later)
 * inputs:
 * - file that contain the bmp image, sizoe of bmp image
 * outputs:
 * - array that contain the value of the bmp image
*******************************************************************************/
int *readFile(char filename[], int size)
{
    int *arrayfinal = NULL;           /*to initialize*/
    int i, l;                      /*for the loop*/
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
        fseek(fp, 0, SEEK_SET);
        /*to put the cursor at the beginning of the file*/
        for (l = 0; l < size; l++)
        {
            fread(&arrayfinal[l], 1, 1, fp);
            /*to put each value of the bmp image in the array*/
        }
    }
    fclose(fp);
    return arrayfinal; /*return the array that contain the value of the image*/
}

/*******************************************************************************
 * Gives the size of a bmp image (to create an array of the good size later)
 * inputs:
 * - file that contain the bmp image that we want to know the size
 * outputs:
 * - size of the bmp image
*******************************************************************************/
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

/*******************************************************************************
 * Write the encrypted image file
 * inputs:
 * - new filename, file that contains image, size of file, keynumber 
 * outputs:
 * - new encrypted image file
*******************************************************************************/
void WriteEncryptedFile(char filename[], int *file, int size, int keynumber)
{
    int i;
    int *keybit = ConvertirIntToBit(keynumber); /*creates a keybit to encrypt the document*/
    int array[size];

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
        }

        printf("Success: /%s created!\n", filename);
    }

    fclose(fp);
}

/*******************************************************************************
 * Write the decrypted image file
 * inputs:
 * - new filename, file that contains image, size of file, keynumber 
 * outputs:
 * - new image file
*******************************************************************************/
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

        printf("Success: /%s created!\n", filename);
    }
    
    fclose(fp);
}

/*******************************************************************************
 * Used to do the conversion from endian to int, use to obtain the 
 * size (which is in endian)
 * inputs:
 * - take a tab[4] that contain a endian number
 * outputs:
 * - return the value in int
*******************************************************************************/
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

/*******************************************************************************
 * Used to do the conversion from bit to int
 * inputs:
 * - take a tab[8] that contain a bit number
 * outputs:
 * - the value in int
*******************************************************************************/
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

/*******************************************************************************
 * Used to do the conversion from int to bit
 * inputs:
 * - take a int
 * outputs:
 * - return a tab[8] that contain a bit
*******************************************************************************/
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

/*******************************************************************************
 * This addition is use to encrypt the bmp image 
 * inputs:
 * - take two bit
 * outputs:
 * - return the bit that contain the addition
*******************************************************************************/
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
 * This function will take an image file and then encrypt it and output it 
 * to the encrypted directory.
 * inputs:
 * - none
 * outputs:
 * - encrypted BMP image file
*******************************************************************************/
void encrypt_image(void)
{
    char filename[50];
    printf("Enter the filename (with extension) of an image to encrypt>\n");
    scanf("%s", filename);

    char input_path[99] = IMAGES_DIR;
    strcat(input_path, filename);

    FILE *file = fopen(input_path, "r");

    if (file) {
        int size = ReadSize(input_path);

        char output_path[99] = ENCRYPTED_DIR;
        strcat(output_path, filename);

        int *array = readFile(input_path, size);
        WriteEncryptedFile(output_path, array, size, 200);
    } else {
        printf("Error: Could not open the file /%s\n", input_path);
        printf("Have you created an 'images' folder?\n");
    }

    fclose(file);
}

/*******************************************************************************
 * This function will take an encrypted file and then decrypt it and output 
 * it to the decrypted directory.
 * inputs:
 * - none
 * outputs:
 * - decrypted BMP image file
*******************************************************************************/
void decrypt_image(void)
{
    char filename[50];
    printf("Enter the filename (with extension) of an image to decrypt>\n");
    scanf("%s", filename);

    char input_path[99] = ENCRYPTED_DIR;
    strcat(input_path, filename);

    FILE *file = fopen(input_path, "r");

    if (file) {
        int size2 = ReadSize(input_path);
        int *array2 = readFile(input_path, size2);

        char output_path[99] = DECRYPTED_DIR;
        strcat(output_path, filename);

        WriteDecryptedFile(output_path, array2, size2, 200);
    } else {
        printf("Error: Could not open the file /%s\n", input_path);
        printf("Have you created an 'encrypted' folder?\n");
    }

    fclose(file);
}