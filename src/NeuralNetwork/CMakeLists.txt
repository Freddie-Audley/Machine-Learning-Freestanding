file(GLOB_RECURSE NEURAL_NETWORK_SOURCES
        "${CMAKE_CURRENT_SOURCE_DIR}/*/*.c"
)

#add_library(NeuralNetwork STATIC ${NEURAL_NETWORK_SOURCES})
#target_include_directories(NeuralNetwork PUBLIC ${CMAKE_SOURCE_DIR}/include)
#target_link_libraries(NeuralNetwork PUBLIC slib LinearAlgebra)

#target_compile_options(slib PRIVATE
#        -ffreestanding
#        -fno-builtin
#        -fno-stack-protector
#        -no-pie
#)
#
#target_link_options(slib PRIVATE
#        -nostdlib
#        -static
#        -no-pie
#)
