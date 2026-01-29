cmake_minimum_required(VERSION 3.20)
project(Machine-Learning-Freestanding C ASM)

# C standard
set(CMAKE_C_STANDARD 11)

# Add library subdirectories
add_subdirectory(src/slib)
#add_subdirectory(src/LinearAlgebra)
#add_subdirectory(src/NeuralNetwork)

# Main executable
add_executable(main src/main.c)
target_include_directories(main PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(main PRIVATE slib) #LinearAlgebra NeuralNetwork)

# Freestanding flags
target_compile_options(main PRIVATE
        -ffreestanding
        -fno-builtin
        -no-pie
)
target_link_options(main PRIVATE
        -nostdlib
        -static
        -no-pie
        -Wl,--strip-all
)

# Testing
enable_testing()
add_test(NAME RunMain COMMAND main)
