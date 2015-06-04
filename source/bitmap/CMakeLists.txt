cmake_minimum_required(VERSION 3.1)

project (BitmapReader)

aux_source_directory(. DIR_SRCS)
add_executable(bitmapReader ${DIR_SRCS})