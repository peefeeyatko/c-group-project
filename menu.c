#include "menu.h"

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
        "1. run encryption\n"
        "2. run decryption\n"
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
    printf("\n"
        "1. Add .bmp image files to the 'images' folder and then choose run encryption.\n"
        "   The encrypted images will then be output to the 'encrypted_images' folder.\n\n"
        "2. Enter the password in order to run decryption which will then\n"
        "   scan the 'encrypted_images' folder and decrypt each image and output\n"
        "   to a specified location.\n\n"
        "3. Compress to ZIP will create a zip file of the 'encrypted_images' folder\n"
        "   and it's contents.\n\n"
        "4. Update password allows a user to change password after entering the\n"
        "   old password and saves the new password in an encrypted form to\n"
        "   database.txt\n");
}