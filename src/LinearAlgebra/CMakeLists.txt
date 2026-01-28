file(GLOB_RECURSE LINEAR_ALGEBRA_SOURCES
        "${CMAKE_CURRENT_SOURCE_DIR}/*.c"
)

#add_library(LinearAlgebra STATIC ${LINEAR_ALGEBRA_SOURCES})
#target_include_directories(LinearAlgebra PUBLIC ${CMAKE_SOURCE_DIR}/include)
#target_link_libraries(LinearAlgebra PUBLIC slib)
