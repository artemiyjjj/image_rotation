#ifndef IMAGE_TRANSFORMER_TO_BMP_H
#define IMAGE_TRANSFORMER_TO_BMP_H
#include "image/image.h"
#include "image/image_formats/headers/bmp_header.h"
#include "statuse_codes/status_enums.h"
#include <stdio.h>
enum write_stat to_bmp(FILE*, struct image*);
#endif
