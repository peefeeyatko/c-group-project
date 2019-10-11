/*******************************************************************************
 * 48430 Fundamentals of C Programming - Assignment 3
 * Name(s): MARSHALL SUTTON, CLEMENT MUTEZ, AIDAN LEE, DAVID AZOULAY
 * Student ID: 13583378
 * Date of submission: 11/10/2019
 *
*******************************************************************************/

/*******************************************************************************
 * List header files
*******************************************************************************/
#include "menu.h"
#include "password.h"
#include "encryption.h"
#include "compression.h"

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
                encrypt_image();
                break;
            case 2:
                if (password_prompt() == 1) {
                    decrypt_image();
                } else {
                    printf("Error: incorrect password!\n");
                }
                break;
            case 3:
                if (compress_to_zip() == 1) {
                    printf("\n"
                        "Success: %s created.\n", ZIP_FILE
                    );
                } else {
                    printf("\n"
                        "Error: something went wrong.\n"
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