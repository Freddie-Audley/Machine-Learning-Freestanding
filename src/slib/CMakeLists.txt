file(GLOB_RECURSE SLIB_SOURCES
        "${CMAKE_CURRENT_SOURCE_DIR}/*/*.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/*/*.s"
)

add_library(slib STATIC ${SLIB_SOURCES})
target_include_directories(slib PUBLIC ${CMAKE_SOURCE_DIR}/include)

target_compile_options(slib PRIVATE
    -ffreestanding
    -fno-builtin
    -fno-stack-protector
    -no-pie
)

target_link_options(slib PRIVATE
    -nostdlib
    -static
    -no-pie
)
