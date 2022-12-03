#include "image/image_operations.h"

enum read_stat read_image(enum read_stat(from_fun)(FILE *in_file, struct image *const in_image),
                          const char *in_filename, struct image *const in_image) {
    FILE* in_file = NULL;
    enum open_stat file_open_stat = open_file(&in_file, in_filename, "rb");
    if (file_open_stat != OPEN_OK) { return READ_ERR_OPEN_FAILED; }
    enum read_stat image_read_stat = from_fun(in_file, in_image);
    if (image_read_stat != READ_OK) {
        close_file(&in_file);
        return image_read_stat;
    }
    enum close_stat file_close_stat = close_file(&in_file);
    return file_close_stat != CLOSE_OK ? READ_ERR_CLOSE_FAILED : READ_OK;
}

struct image rotate_image(const struct image in_image) {
    size_t in_width = in_image.width;
    size_t in_height = in_image.height;
    size_t out_width = in_height;
    size_t out_height = in_width;
    struct image out_image = create_image(out_width, out_height);
    if (out_image.data != NULL) {
        for (size_t i = 0; i < in_height; i++) {
            for (size_t j = 0; j < in_width; j++) {
                struct pixel pixel = get_pixel(&in_image, i, j);
                set_pixel(&out_image, j, in_height - i - 1, pixel);
            }
        }
        return out_image;
    }
    else { return (struct image) {0}; }
}

enum write_stat write_image(enum write_stat(to_fun)(FILE *out_file, struct image *const out_image),
                            const char *out_filename, struct image *const out_image) {
    FILE* out_file = NULL;
    enum open_stat file_open_stat = open_file(&out_file, out_filename, "wb");
    if (file_open_stat == OPEN_ERR) { return WRITE_ERR_OPEN; }
    enum write_stat image_write_stat = to_fun(out_file, out_image);
    if (image_write_stat != WRITE_OK) {
        close_file(&out_file);
        return image_write_stat; }
    enum close_stat file_close_stat = close_file(&out_file);
    return file_close_stat != CLOSE_OK ? WRITE_ERR_CLOSE : WRITE_OK;
}
