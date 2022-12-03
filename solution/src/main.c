#include "statuse_codes/status_enums.h"
#include "image/image_operations.h"
#include "image/image_formats/from_bmp.h"
#include "image/image_formats/to_bmp.h"

int main( int argc, char** argv ) {
    printf("\n");

    if (argc != 3) {
        fprintf(stderr, "Arguments are not correct\n");
        return 1;
    }
    const char* in_filename = argv[1];
    struct image in_image = {0};
    enum read_stat read_image_stat = read_image(from_bmp, in_filename, &in_image);

    if (read_image_stat != READ_OK) {
        fprintf(stderr, "Can not interact with the source file");
        free_image(in_image);
        return 1;
    }

    const char* out_filename = argv[2];
    struct image out_image = rotate_image(in_image); //in_image;
    free_image(in_image);
    enum write_stat write_image_stat = write_image(to_bmp, out_filename, &out_image);

    if (write_image_stat != WRITE_OK) {
        fprintf(stderr, "Can not interact with the output file.");
        free_image(out_image);
        return 1;
    }

    free_image(out_image);
    return 0;
}
