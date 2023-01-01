#include "image/image_formats/to_bmp.h"

#define BMP_RESERVED 0
#define BMP_USED_COLOR 0
#define BMP_IMPORTANT_COLOR 0
#define BMP_PLANES 1
#define BMP_PIXELS_PER_METER 0
#define BMP_COMPRESSION 0
#define BMP_BIT_COLOR_DEPTH 24
#define BMP_INFO_SIZE 40
#define BMP_TYPE 19778

static enum write_stat write_header(FILE *const out_file, struct bmp_header *out_header);

static enum write_stat write_all_pixels(FILE *const out_file, struct image *out_image);

static struct bmp_header create_bmp_header(struct image *const out_image);

enum write_stat to_bmp(FILE *const out_file, struct image *const out_image) {
    struct bmp_header out_header = create_bmp_header(out_image);
    enum write_stat header_write_stat = write_header(out_file, &out_header);
    if (header_write_stat != WRITE_OK) { return header_write_stat; }
    enum write_stat pixels_write_stat = write_all_pixels(out_file, out_image);
    return pixels_write_stat;
}

static struct bmp_header create_bmp_header(struct image *out_image) {
    size_t image_width = out_image->width;
    size_t image_height = out_image->height;
    uint32_t bmp_header_size = sizeof(struct bmp_header);
    uint32_t bmp_pixel_array_size = (sizeof(struct pixel) * image_width + get_padding(out_image)) * image_height;
    struct bmp_header bmp_header = {
            .bfType = BMP_TYPE,
            .bfReserved = BMP_RESERVED,
            .bfileSize = bmp_header_size + bmp_pixel_array_size,
            .bOffBits = bmp_header_size,
            .biSizeImage = bmp_pixel_array_size,
            .biSize = BMP_INFO_SIZE,
            .biWidth = image_width,
            .biHeight = image_height,
            .biPlanes = BMP_PLANES,
            .biBitCount = BMP_BIT_COLOR_DEPTH,
            .biCompression = BMP_COMPRESSION,
            .biXPelsPerMeter = BMP_PIXELS_PER_METER,
            .biYPelsPerMeter = BMP_PIXELS_PER_METER,
            .biClrUsed = BMP_USED_COLOR,
            .biClrImportant = BMP_IMPORTANT_COLOR
    };
    return bmp_header;
}

static enum write_stat write_header(FILE *const out_file,
                                    struct bmp_header *const header) {
    size_t result = fwrite(header, sizeof(struct bmp_header), 1, out_file);
    if (result != 1) {
        return WRITE_ERR_INVALID_HEADER;
    }
    return WRITE_OK;
}

static enum write_stat write_all_pixels(FILE *const out_file,
                                        struct image *const out_image) {
    size_t image_width = out_image->width;
    size_t image_height = out_image->height;
    struct pixel *pixel_array = out_image->data;
    uint8_t padding = get_padding(out_image);
    uint64_t padding_unit = 0;

    for (size_t i = 0; i < image_height; i++) {
        size_t pixel_size =
                fwrite(pixel_array + image_width * i, sizeof(struct pixel), image_width, out_file);
        if (pixel_size != image_width) {
            return WRITE_ERR_PIXELS;
        }
        size_t padding_size = fwrite(&padding_unit, 1, padding, out_file);
        if (padding_size != padding) {
            return WRITE_ERR_PIXELS;
        }
    }
    return WRITE_OK;
}

