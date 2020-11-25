#include "helper.h"
#include "pexif.h"
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int save_without_exif(char *file_name, long img_size, long exif_start, BYTE *img_bytes);
void init_basic_jfif(BYTE purged[]);
void save_to_img_file(BYTE purged[], long image_size, char *file_name);
char *get_pexifed_file_name(char *file_name);

int remove_exif_in_cwd()
{
    DIR *dir;
    dir = opendir(".");
    struct dirent *dir_ent;

    if (dir)
    {
        while ((dir_ent = readdir(dir)) != NULL)
        {
            char *file_name = dir_ent->d_name;
            char *extension = get_file_extension(file_name);
            if (strcasecmp(extension, "jpg") == 0 || strcasecmp(extension, "jpeg") == 0)
            {
                remove_exif_from_img(file_name);
            }
        }
        closedir(dir);
    }
    else
    {
        fprintf(stderr, "Couldn't work in the current working directory");
        return 0;
    }
    return 1;
}

int remove_exif_from_img(char *file_name)
{
    FILE *img = fopen(file_name, "rb");
    if (img == NULL)
    {
        fprintf(stderr, "Couldn't open %s", file_name);
        return 0;
    }
    // get the size of the image in bytes
    fseek(img, 0, SEEK_END);
    const long img_size = ftell(img);
    rewind(img);

    // store the image bytes from img in img_bytes
    //BYTE img_bytes[img_size];
    BYTE *img_bytes = malloc(sizeof(BYTE) * img_size);
    fread(img_bytes, 1, img_size, img);
    fclose(img);

    long exif_start = validate_exif_sig(img_size, img_bytes);
    if (exif_start)
    {
        save_without_exif(file_name, img_size, exif_start, img_bytes);
        free(img_bytes);
        return 1;
    }
    free(img_bytes);
    fprintf(stderr, "%s doesn't have a valid exif signature", file_name);
    return 0;
}

int save_without_exif(char *file_name, long img_size, long exif_start, BYTE *img_bytes)
{
    long exif_data_size = ((img_bytes[exif_start + 2] << 8) | img_bytes[exif_start + 3]) + 2; // + 2 to include exif marker 0xFFE1
    long i = exif_start + exif_data_size;

    while (!(img_bytes[i] == 0xFF && img_bytes[i + 1] == 0xDB))
    {
        i += ((img_bytes[i + 2] << 8) | img_bytes[i + 3]) + 2; // skip to next marker
    }

    long new_size = img_size - i + 20; // + 20 because of the 20 jfif bytes
    BYTE *purged = malloc(sizeof(BYTE) * new_size);
    init_basic_jfif(purged);

    long jfif_difference = i - 20;
    for (; i < img_size; i++)
    {
        purged[i - jfif_difference] = img_bytes[i];
    }
    char *new_file_name = get_pexifed_file_name(file_name);
    FILE *new_img = fopen(new_file_name, "wb");
    if (new_img == NULL)
    {
        fprintf(stderr, "Couldn't create %s", new_file_name);
        free(purged);
        free(new_file_name);
        return 0;
    }

    fwrite(purged, 1, new_size, new_img);
    fclose(new_img);
    printf("Pexifed %s\n", file_name);
    free(purged);
    free(new_file_name);
    return 1;
}

void init_basic_jfif(BYTE purged[])
{
    purged[0] = 0xFF, purged[1] = 0xD8;
    purged[2] = 0xFF, purged[3] = 0xE0;
    purged[4] = 0x00, purged[5] = 0x10;
    purged[6] = 0x4A, purged[7] = 0x46, purged[8] = 0x49, purged[9] = 0x46, purged[10] = 0x00;
    purged[11] = 0x01, purged[12] = 0x01;
    purged[13] = 0x00;
    purged[14] = 0x00, purged[15] = 0x01;
    purged[16] = 0x00, purged[17] = 0x01;
    purged[18] = 0x00;
    purged[19] = 0x00;
    // these bytes make up the beginning of a basic jpg in the jfif format
    // for an explanation as to what these specific bytes mean, visit
    // https://www.ccoderun.ca/programming/2017-01-31_jpeg/ or
    // http://web.archive.org/web/20200929185628/https://www.ccoderun.ca/programming/2017-01-31_jpeg/ if necessary
}