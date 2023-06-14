/*
 *  This program receives a file name, reverses the file and outputs a new file.
 *  Author: ZeAi Sun
 *  Date: Jan 20, 2023
 *  Update: Apr 14, 2023
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>

/* This function checks if the number of input filenames is 2. */
int check_num_args(int argc, char *argv[])
{
    if (argc == 3) // argc - 1 = number of input arguments, which should be 2.
    {
        return 0;
    }
    else
    {
        perror("Error: invalid number of arguments");
        exit(-1);
    }
}

/* This function checks if the start file is a regular file. */
/* reference: https://stackoverflow.com/questions/40163270/what-is-s-isreg-and-what-does-it-do. */
int check_src_file_is_regular(char *f_name)
{
    if (access(f_name, R_OK) == -1)  // check if the file is readable.
    {
        perror("Error: source is unreadable");
        exit(-1);
    }
    else
    {
        struct stat f_info;  // create a new struct stat structure to store the info of the file.

        if ( (lstat(f_name, &f_info)) != -1)     // ensure that the stat is created successfully.
        {
            if (S_ISLNK(f_info.st_mode))
            {
                perror("Error: source is a link");
                exit(-1);
            }
            else if (S_ISDIR(f_info.st_mode))
            {
                perror("Error: source is a directory");
                exit(-1);
            }
            else if (S_ISREG(f_info.st_mode))
            {
                return 0;
            }
            else
            {
                perror("Error: not a valid regular file");
                exit(-1);
            }
        }
    }
}

/* This function copies the content of the start file into the end file reversely. */
int copy_src_to_dest(char *src, char *dest)
{
    if (access(dest, W_OK) == -1)  // check if the destination is writable.
    {
        perror("Error: destination is unwritable");
        return(-1);
    }
    else                           // check if the destination is a directory.
    {
        struct stat d_info;
        if ((lstat(dest, &d_info)) != -1)
        {
            if (S_ISDIR(d_info.st_mode))
            {
                perror("Error: destination is a directory");
                return(-1);
            }
        }
    }

    FILE *f1 = fopen(src, "r");  // open the start file.
    FILE *f2 = fopen(dest, "w"); // create a new end file using the given name.

    int f1c = 0; // create f1 charatcer counter.
    int f2c = 0; // create f2 character counter.

    while (!feof(f1)) // use a while loop to count the number of characters in f1.
    {
        fgetc(f1);
        f1c += 1;
    }

    fseek(f1, -1, SEEK_END); // move the pointer to the end of f1.
    while (f1c != f2c + 1)   // read from f1 and write into f2 until all charaters are written.
    {
        int c = fgetc(f1);       // get a char from the start file.
        fseek(f1, -2, SEEK_CUR); // move the pointer back 2 charatcers.
        fputc(c, f2);            // put the char into the end file.
        f2c += 1;                // increment the f2 character counter.
    }

    fclose(f1); // close both files.
    fclose(f2);

    return 0;
}

int main(int argc, char *argv[])
{
    /* These functions exit(-1) if there is a problem. */
    check_num_args(argc, argv);
    check_src_file_is_regular(argv[1]);
    copy_src_to_dest(argv[1], argv[2]);
    return 0; /* no error */
}
