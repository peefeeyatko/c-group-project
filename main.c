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
#define ZIP_DIR "encrypted_imgs.zip"
#define PASSWORD "database"
#define PASSWORD_MAX_LEN 15

/*******************************************************************************
 * List structs
*******************************************************************************/


/*******************************************************************************
 * Function prototypes 
*******************************************************************************/
void print_menu(void);
int encrypt_image();
int decrypt_image();
int update_password(void);
char* get_password_from_file(void);
char* encrypt_password(const char password[PASSWORD_MAX_LEN + 1]);
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
                    printf("\n"
                        "Success: %s created\n", ZIP_DIR
                    );
                } else {
                    printf("\n"
                        "Error: Something went wrong\n"
                    );
                }
                break;
            case 4:
                if (update_password() == 1) {
                    printf("Success: password updated!\n");
                } else {
                    printf("Error: incorrect password!\n");
                }
                break;
            case 5:
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

/*******************************************************************************
 * This function will compress the ENCRYPTED_DIR and create a single ZIP file.
 * inputs:
 * - none
 * outputs:
 * - 1 for success or 0 for failure
*******************************************************************************/
int compress_to_zip(void)
{
    char cmd[99] = "zip -r ";
    strcat(cmd, ZIP_DIR);
    strcat(cmd, " ");
    strcat(cmd, ENCRYPTED_DIR);
    
    int flag = system(cmd);

    if (flag == 0) {
        return 1;
    }

    return 0;
}

/*******************************************************************************
 * This function will prompt the user to enter a new password and then save it
 * in an encrypted form to a text file named database.
 * inputs:
 * - none
 * outputs:
 * - 1 for success or 0 for failure
*******************************************************************************/
int update_password(void)
{
    char user_input[PASSWORD_MAX_LEN + 1];
    
    printf("Enter old password> ");
    scanf("%s", user_input);

    char* encrypted_user_input = encrypt_password(user_input);
    char* password = get_password_from_file();

    if (strcmp(password, encrypted_user_input) == 0) {
        /* prompt for new password, encrypt it and then save to file */
        char user_input[PASSWORD_MAX_LEN + 1];

        printf("Enter new password> ");
        scanf("%s", user_input);

        char filename[50], ext[10];

        strcpy(filename, PASSWORD);
        strcpy(ext, ".txt");
        strcat(filename, ext);

        FILE* file = fopen(filename, "w+");

        if (file) {
            fprintf(file, encrypt_password(user_input));
            fprintf(file, "\n");
        }

        fclose(file);

        return 1;
    }

    return 0;
}

/*******************************************************************************
 * This function will return the encrypted password from a text file named database
 * inputs:
 * - none
 * outputs:
 * - password as encrypted string
*******************************************************************************/
char* get_password_from_file(void)
{
    char filename[50], ext[10];

    strcpy(filename, PASSWORD);
    strcpy(ext, ".txt");
    strcat(filename, ext);

    FILE* file = fopen(filename, "r");
    char* password;
    password = malloc(sizeof(char) * PASSWORD_MAX_LEN + 1);

    char ch;
    int i = 0;
    for (ch = fgetc(file); ch != '\n'; ch = fgetc(file)) {
        password[i] = ch;
        i++;
    }

    fclose(file);

    return password;
}

/*******************************************************************************
 * This function will convert a plain text string to an encypted string using
 * a ciper algorithm.
 * inputs:
 * - const char password[PASSWORD_MAX_LEN]
 * outputs:
 * - password as encrypted string
*******************************************************************************/
char* encrypt_password(const char password[PASSWORD_MAX_LEN + 1])
{
    char letters[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+-*/.()@&#%$€:;!?,";
    char* password_encrypted;
    password_encrypted = malloc(sizeof(char) * PASSWORD_MAX_LEN + 1);

    int i;

    for (i = 0; i < 15; i++) {
        int a;

        for (a = 0; a < 80; a++) {

            if (password[i] == letters[a]) {
                int q = a + 8;

                if (q > 79) {
                    q -= 80;
                }

                password_encrypted[i] = letters[q];
            }
        }
    }

    return password_encrypted;
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
 * This function will take an encrypted file and then decrypt it.
 * inputs:
 * - encrypted BMP file
 * outputs:
 * - 1 for success or 0 for failure
*******************************************************************************/
int decrypt_image()
{
    return 0;
}
