#include "pexif.h"
#include "helper.h"
#include <stdio.h>
#include <string.h>

void printUsage();
void handleFileArgs(int argc, char *arg[]);

int main(int argc, char *arg[])
{
    if (argc == 2 && strcmp(arg[1], ".") == 0)
    {
        remove_exif_in_cwd();
    }
    else if (argc > 1)
    {
        handleFileArgs(argc, arg);
    }
    else
    {
        printUsage();
    }
}

void handleFileArgs(int argc, char *arg[])
{
    for (int i = 1; i < argc; i++)
    {
        char *extension = get_file_extension(arg[i]);
        if (strcasecmp(extension, "jpg") == 0 || strcasecmp(extension, "jpeg") == 0)
        {
            remove_exif_from_img(arg[i]);
        }
        else
        {
            fprintf(stderr, "%s doesn't have the jpg or jpeg extension\n", arg[i]);
        }
    }
}

void printUsage()
{
    fprintf(stderr, "Usage:\n(1) pexif .\n(2) pexif (FILEPATH)+\n");
}