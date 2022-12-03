#include "image/image_formats/from_bmp.h"
static enum read_stat read_header( FILE* in_file, struct bmp_header* in_header );
static enum read_stat read_all_pixels( FILE* in_file, struct image* in_image );

enum read_stat from_bmp( FILE *const in_file, struct image *const in_image ) {
    struct bmp_header in_header = { 0 };
    enum read_stat header_read_stat = read_header( in_file, &in_header );
    if ( header_read_stat != READ_OK ) { return header_read_stat; }
    *in_image = create_image( in_header.biWidth, in_header.biHeight );
    enum read_stat pixels_read_stat = read_all_pixels( in_file, in_image );
    if ( pixels_read_stat != READ_OK ) { free_image( *in_image ); }
    return pixels_read_stat;
}

static enum read_stat read_header( FILE *const in_file, struct bmp_header *const in_header ) {
    size_t result = fread( in_header, sizeof( struct bmp_header ), 1, in_file );
    return result != 1 ? READ_ERR_HEADER_INVALID : READ_OK;
}

static enum read_stat read_all_pixels( FILE *const in_file, struct image *const in_image ) {
    struct pixel *pixel_array = in_image -> data;
    const size_t width = in_image -> width;
    const size_t height = in_image -> height;
    const uint8_t padding_size = get_padding(in_image );
    for ( size_t i = 0; i < height; i++ ) {
        size_t pixel_size = fread( pixel_array + (i * width), sizeof( struct pixel ), width, in_file );
        if ( pixel_size != width ) { return READ_ERR_PIXELS_INVALID_RESOLUTION; }
        int seek = fseek(in_file, padding_size, SEEK_CUR );
        if ( seek ) { return READ_ERR_PIXELS_INVALID_VALUES; }
    }
    return READ_OK;
}


