# CMake generated Testfile for 
# Source directory: /home/freddie/CLionProjects/Machine-Learning-Freestanding
# Build directory: /home/freddie/CLionProjects/Machine-Learning-Freestanding/cmake-build-release
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test([=[RunMain]=] "/home/freddie/CLionProjects/Machine-Learning-Freestanding/cmake-build-release/main")
set_tests_properties([=[RunMain]=] PROPERTIES  _BACKTRACE_TRIPLES "/home/freddie/CLionProjects/Machine-Learning-Freestanding/CMakeLists.txt;33;add_test;/home/freddie/CLionProjects/Machine-Learning-Freestanding/CMakeLists.txt;0;")
subdirs("src/slib")
subdirs("src/LinearAlgebra")
