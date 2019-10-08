#include "compression.h"

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
    strcat(cmd, ZIP_FILE);
    strcat(cmd, " ");
    strcat(cmd, ENCRYPTED_DIR);

    int flag = system(cmd);

    if (flag == 0)
    {
        return 1;
    }

    return 0;
}