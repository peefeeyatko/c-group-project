#include "password.h"

/*******************************************************************************
 * This function will prompt the user to enter the password
 * inputs:
 * - none
 * outputs:
 * - 1 for success or 0 for failure
*******************************************************************************/
int password_prompt(void)
{
    char user_input[PASSWORD_MAX_LEN + 1];

    printf("Enter password> ");
    scanf("%s", user_input);

    char *encrypted_user_input = encrypt_password(user_input);
    char *password = get_password_from_file();

    if (strcmp(password, encrypted_user_input) == 0) {
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

    char *encrypted_user_input = encrypt_password(user_input);
    char *password = get_password_from_file();

    if (strcmp(password, encrypted_user_input) == 0) {
        /* prompt for new password, encrypt it and then save to file */
        char user_input[PASSWORD_MAX_LEN + 1];

        printf("Enter new password> ");
        scanf("%s", user_input);

        char filename[50], ext[10];

        strcpy(filename, PASSWORD);
        strcpy(ext, ".txt");
        strcat(filename, ext);

        FILE *file = fopen(filename, "w+");

        if (file) {
            fprintf(file, "%s", encrypt_password(user_input));
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
char *get_password_from_file(void)
{
    char filename[50], ext[10];

    strcpy(filename, PASSWORD);
    strcpy(ext, ".txt");
    strcat(filename, ext);

    FILE *file = fopen(filename, "r");
    char *password;
    password = malloc(sizeof(char) * PASSWORD_MAX_LEN + 1);

    char ch;
    int i = 0;
    for (ch = fgetc(file); ch != '\n'; ch = fgetc(file))
    {
        password[i] = ch;
        i++;
    }

    fclose(file);
    return password;
}

/*******************************************************************************
 * This function will convert a plain text string to an encypted string using
 * a cipher algorithm.
 * inputs:
 * - const char password[PASSWORD_MAX_LEN + 1]
 * outputs:
 * - password as encrypted string
*******************************************************************************/
char *encrypt_password(const char password[PASSWORD_MAX_LEN + 1])
{
    char letters[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+-*/.()@&#%$€:;!?,";
    char *password_encrypted;
    password_encrypted = malloc(sizeof(char) * PASSWORD_MAX_LEN + 1);

    int i;

    for (i = 0; i < 15; i++)
    {
        int a;

        for (a = 0; a < 80; a++)
        {

            if (password[i] == letters[a])
            {
                int q = a + 8;

                if (q > 79)
                {
                    q -= 80;
                }

                password_encrypted[i] = letters[q];
            }
        }
    }

    return password_encrypted;
}