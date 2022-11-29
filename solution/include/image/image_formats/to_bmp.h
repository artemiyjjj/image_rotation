#ifndef IMAGE_TRANSFORMER_TO_BMP_H
#define IMAGE_TRANSFORMER_TO_BMP_H
#include <stdio.h>
#include "statuse_codes/status_enums.h"
#include "image/image_formats/headers/bmp_header.h"
#include "image/image.h"
enum write_stat to_bmp(FILE*, struct image*);
#endif
