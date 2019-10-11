#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*******************************************************************************
 * List preprocessing directives
*******************************************************************************/
#define IMAGES_DIR "images/"
#define ENCRYPTED_DIR "encrypted/"
#define DECRYPTED_DIR "decrypted/"

/*******************************************************************************
 * Function prototypes 
*******************************************************************************/
void encrypt_image(void);
void decrypt_image(void);

int *readFile(char filename[], int size);
int convertEndianToInt(const int tab[4]);
int *AddTwoBit(int *bit1, int *bit2);
int *ConvertirIntToBit(int value);
int ConvertBitToInt(int *tab);
void WriteDecryptedFile(char filename[], int *file, int size, int keynumber);
void WriteEncryptedFile(char filename[], int *file, int size, int keynumber);
int ReadSize(char filename[]);