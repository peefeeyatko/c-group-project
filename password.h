#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*******************************************************************************
 * List preprocessing directives
*******************************************************************************/
#define PASSWORD "database"
#define PASSWORD_MAX_LEN 15

/*******************************************************************************
 * Function prototypes 
*******************************************************************************/
int password_prompt(void);
int update_password(void);
char *get_password_from_file(void);
char *encrypt_password(const char password[PASSWORD_MAX_LEN + 1]);