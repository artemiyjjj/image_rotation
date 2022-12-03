#ifndef IMAGE_TRANSFORMER_FROM_BMP_H
#define IMAGE_TRANSFORMER_FROM_BMP_H
#include "image/image.h"
#include "image/image_formats/headers/bmp_header.h"
#include "statuse_codes/status_enums.h"
#include <stdio.h>
enum read_stat from_bmp(FILE* in_file, struct image* in_image);
#endif
