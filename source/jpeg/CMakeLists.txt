cmake_minimum_required(VERSION 3.1)

project(JPEG_Reader)

aux_source_directory(. DIR_SRCS)
add_executable(jpegReader ${DIR_SRCS})