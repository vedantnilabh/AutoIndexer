cmake_minimum_required(VERSION 3.14)
project(22su_PA02)

set(CMAKE_CXX_STANDARD 17)

# The configure_file statements below ensure that files are copied into the data
# folder that will be created in the build folder.
configure_file(data/test_book.txt data/test_book.txt NEWLINE_STYLE UNIX)
configure_file(data/terms.txt data/terms.txt NEWLINE_STYLE UNIX)

add_executable(22su_PA02 main.cpp DSVector.h DSString.h DSString.cpp)

add_executable(22su_PA02_tests DSVector.h catch.hpp catch_setup.cpp sample_tests.cpp catch_setup.h DSString.h DSString.cpp AutoIndexer.h AutoIndexer.cpp)