file(GLOB_RECURSE sources CONFIGURE_DEPENDS
    src/*.c
    src/*.h
    include/*.h
)

add_executable(image-transformer ${sources} src/file_operations/file_operations.c include/file_operations/file_operations.h include/image/image.h include/image/image_formats/to_bmp.h src/image/image_operations.c include/image/image_operations.h)
target_include_directories(image-transformer PRIVATE src include)
