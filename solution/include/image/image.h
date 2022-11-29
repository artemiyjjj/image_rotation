#ifndef IMAGE_TRANSFORMER_IMAGE_H
#define IMAGE_TRANSFORMER_IMAGE_H
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

struct __attribute__((packed)) pixel {
    uint8_t b, g, r;
};

struct image {
    size_t width, height;
    struct pixel* data;
};

struct image create_image(size_t width, size_t height);
void free_image(struct image image);
struct pixel get_pixel(const struct image* image, size_t row, size_t column);
uint8_t get_padding(const struct image* image);
void set_pixel(struct image* image, size_t row, size_t column, struct pixel pixel);
#endif
