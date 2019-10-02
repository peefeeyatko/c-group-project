/*******************************************************************************
 * 48430 Fundamentals of C Programming - Assignment 3
 * Name(s): MARSHALL SUTTON, CLEMENT MUTEZ, AIDAN LEE, AMMAR CHOWDHURY, DAVID AZOULAY
 * Student ID: 13583378
 * Date of submission:
 * A brief statement on what you could achieve (less than 50 words):
 * 
 * 
 * A brief statement on what you could NOT achieve (less than 50 words):
 * 
 * 
*******************************************************************************/

/*******************************************************************************
 * List header files
*******************************************************************************/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*******************************************************************************
 * List preprocessing directives
*******************************************************************************/
#define ENCRYPTED_DIR "./encrypted_images"
#define IMAGES_DIR "./images"
#define PASSWORD "database"

/*******************************************************************************
 * List structs
*******************************************************************************/


/*******************************************************************************
 * Function prototypes 
*******************************************************************************/
void print_menu(void);
int encrypt_image();
int decrypt_image();
int compress_to_zip(void);
void help_menu(void);

/*******************************************************************************
 * Main
*******************************************************************************/
int main(void)
{
    printf("Welcome...\n");
    print_menu();

    int user_input;
    scanf("%d", &user_input);

    while (user_input != 6) {

        switch (user_input) {
            case 1:
                break;
            case 2:
                break;
            case 3:
                if (compress_to_zip() == 1) {
                    printf("\nSuccess: encrypted_imgs.zip created\n");
                } else {
                    printf("\nError: Something went wrong\n");
                }
                break;
            case 4:
                break;
            case 5:
                help_menu();
                break;
            default:
                help_menu();
                break;
        }
        
        print_menu();
        scanf("%d", &user_input);
    }

    return 0;
}

/*******************************************************************************
 * This function prints the initial menu with all the options
 * this program.
 * inputs:
 * - none
 * outputs:
 * - none
*******************************************************************************/
void print_menu(void)
{
    printf("\n"
           "1. encrypt image(s)\n"
           "2. decrypt images(s)\n"
           "3. compress to ZIP\n"
           "4. update password\n"
           "5. view help\n"
           "6. exit the program\n"
           "Enter choice (number between 1-6)>\n");
}

/*******************************************************************************
 * This function prints the help menu with all instructions on how to use
 * this program.
 * inputs:
 * - none
 * outputs:
 * - none
*******************************************************************************/
void help_menu(void)
{
    printf("Help\n");
}

/*******************************************************************************
 * This function will compress the ENCYPTED_DIR and create a single ZIP file.
 * inputs:
 * - none
 * outputs:
 * - 1 for success or 0 for failure
*******************************************************************************/
int compress_to_zip(void)
{
    char cmd[99] = "zip -r encrypted_imgs.zip ";
    strcat(cmd, ENCRYPTED_DIR);
    
    int flag = system(cmd);

    if (flag == 0) {
        return 1;
    }

    return 0;
}

/*******************************************************************************
 * This function will take an image file and then encrypt the file.
 * inputs:
 * - BMP file
 * outputs:
 * - 1 for success or 0 for failure
*******************************************************************************/
int encrypt_image()
{
    return 0;
}

/*******************************************************************************
 * This function will take an encrypted file and then decrypt.
 * inputs:
 * - encrypted file
 * outputs:
 * - 1 for success or 0 for failure
*******************************************************************************/
int decrypt_image()
{
    return 0;
}
