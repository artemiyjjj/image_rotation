#ifndef IMAGE_TRANSFORMER_IMAGE_OPERATIONS_H
#define IMAGE_TRANSFORMER_IMAGE_OPERATIONS_H
#include "file_operations/file_operations.h"
#include "image/image.h"
#include "statuse_codes/status_enums.h"
#include <stdio.h>

enum read_stat read_image(enum read_stat(from_fun)(FILE *in_file, struct image *const in_image),
                          const char *in_filename, struct image *const in_image);

struct image rotate_image(const struct image image);

enum write_stat write_image(enum write_stat(to_fun)(FILE *out_file, struct image *const out_image),
                            const char *out_filename, struct image *const out_image);

#endif
