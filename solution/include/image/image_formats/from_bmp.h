#ifndef IMAGE_TRANSFORMER_FROM_BMP_H
#define IMAGE_TRANSFORMER_FROM_BMP_H
#include <stdio.h>
#include "image/image.h"
#include "image/image_formats/headers/bmp_header.h"
#include "statuse_codes/status_enums.h"
enum read_stat from_bmp(FILE*, struct image*);
#endif
