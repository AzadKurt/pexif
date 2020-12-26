#ifndef PEXIF_H
#define PEXIF_H

/**
 * Removes the exif data from the image with the given file name.
 * The given file name is allowed to be an absolute path.
 */
int remove_exif_from_img(char *file_name);

/**
 * Removes the exif data from all jpg/jpeg images in the current working
 * directory.
 */
int remove_exif_in_cwd();

#endif