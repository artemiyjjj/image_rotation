#include "file_operations/file_operations.h"

enum open_stat open_file(FILE** file, const char* filename, const char* mode) {
    *file = fopen(filename, mode);
    if (!*file) { return OPEN_ERR; }
    return OPEN_OK;
}

enum close_stat close_file(FILE** file) {
    if (*file == NULL) { return CLOSE_ERR_NO_STREAM; }
    else if (fclose(*file)) { return CLOSE_FAILED; }
    else return CLOSE_OK;
}
