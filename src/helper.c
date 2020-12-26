#include "helper.h"

#include <stdlib.h>
#include <string.h>

char *get_file_extension(const char *file_name) {
  char *dot = strrchr(file_name, '.');
  if (!dot) {
    return "";
  }
  return dot + 1;
}

int last_index_of(char toFind, char *src) {
  int idx = -1;
  int i = 0;
  while (src[i] != '\0') {
    if (src[i] == toFind) {
      idx = i;
    }
    i++;
  }
  return idx;
}

long validate_exif_sig(long byte_count, BYTE img_bytes[byte_count]) {
  if (!(img_bytes[0] == 0xFF && img_bytes[1] == 0xD8)) {
    return 0;
  }

  for (long i = 2; i < byte_count - 1; i++) {
    if (img_bytes[i] == 0xFF) {
      BYTE marker = img_bytes[i + 1];
      if (marker ==
          0xDB)  // 0xFFDB marks the beginning of the quantization table
      {
        return 0;
      }
      if (marker == 0xE1) {
        return i;
      }
      // if another marker that is not the exif marker is present, jump forward
      // by the specified data size of the current marker
      if ((marker & 0xF0) == 0xE0) {
        i += ((img_bytes[i + 2] << 8) | img_bytes[i + 3]) + 1;
        // + 1 because the two bytes that specify the data size are included and
        // + 1 together with i++ results in an increase of 2
      }
    }
  }
  return 0;
}

char *get_pexifed_file_name(char *file_name) {
  char *new_file_name =
      malloc(sizeof(char) * (strlen(file_name) + 7));  // 7 for "pexif_" + '\0'
  // last_index_of needed for absolute paths such as "C:\image.jpg" where
  // adding "pexif_" at the beginning would result in an invalid path
  int last_backslash_idx = last_index_of('\\', file_name);
  int last_slash_idx = last_index_of('/', file_name);
  if (last_backslash_idx == -1 && last_slash_idx == -1) {
    strcpy(new_file_name, "pexif_");
    strcat(new_file_name, file_name);
    return new_file_name;
  }

  int relevant_idx =
      last_backslash_idx != -1 ? last_backslash_idx : last_slash_idx;
  strncpy(new_file_name, file_name, relevant_idx + 1);
  new_file_name[relevant_idx + 1] = '\0';

  strcat(new_file_name, "pexif_");
  strcat(new_file_name, file_name + relevant_idx + 1);
  return new_file_name;
}