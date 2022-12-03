#include "image/image.h"

struct image create_image(size_t width, size_t height) {
    struct pixel* pixel_array = malloc(sizeof(struct pixel) * width * height);
    return (struct image) { .width = width, .height = height, .data = pixel_array };
}

void free_image(struct image image) {
    free(image.data);
}

struct pixel get_pixel(const struct image* const image, size_t row, size_t column) {
    return image -> data[image -> width * row + column];
}

void set_pixel(struct image *const image, size_t row, size_t column, struct pixel pixel) {
    image -> data[image -> width * row + column] = pixel;
}

uint8_t get_padding(const struct image *const image) {
    uint8_t padding_size = (image -> width * sizeof(struct pixel)) % 4;
    if (padding_size != 0)
        padding_size = 4 - padding_size;
    return padding_size;
}
