#ifndef HELPER_H
#define HELPER_H

#include <stdint.h>
typedef uint8_t BYTE;

/**
 * Given a file name in the format *.ext, returns the specific "ext".
 */
char *get_file_extension(const char *file_name);

/**
 * Given a string src, returns the last index of the character toFind in src or
 * -1 if toFind couldn't be found in src.
 */
int last_index_of(char toFind, char *src);

/**
 * Returns the byte position of the beginning of the exif marker 0xFFE1, i.e.
 * the byte position of 0xFF. Returns 0 if the image constituted by the bytes
 * array does not contain an exif marker.
 */
long validate_exif_sig(long byte_count, BYTE img_bytes[]);

/**
 * Given a file name file_name of an image that has been pexifed, returns
 * "pexif_" + file_name. For file names that are absolute paths, "pexif_" is
 * concatenated to the front of the processed file like this: "C:/image.jpg" ->
 * "C:/pexif_image.jpg".
 */
char *get_pexifed_file_name(char *file_name);

#endif