#ifndef IMAGE_TRANSFORMER_FILE_OPERATIONS_H
#define IMAGE_TRANSFORMER_FILE_OPERATIONS_H
#include <stdio.h>
#include "statuse_codes/status_enums.h"

enum open_stat open_file(FILE* file, const char* filename, const char* mode);
enum close_stat close_file(FILE* file);
#endif //IMAGE_TRANSFORMER_FILE_OPERATIONS_H
