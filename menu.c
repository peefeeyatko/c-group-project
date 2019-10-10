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
        "   Encrypted images are saved to the 'encrypted' folder.\n\n"
        "2. Enter the password in order to run decryption which will then prompt the\n"
        "   user for a filename of an image inside the 'encrypted' folder.\n"
        "   Decrypted images are saved to the 'decrypted' folder.\n\n"
        "3. Compress to ZIP will create a zip file of the 'encrypted' folder\n"
        "   and it's contents.\n\n"
        "4. Update password allows a user to change password after entering the\n"
        "   old password and saves the new password in an encrypted form to\n"
        "   database.txt (the default password is \"password\")\n");
}