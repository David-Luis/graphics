# /*
# (c) 2014 +++ Filip Stoklas, aka FipS, http://www.4FipS.com +++
# THIS CODE IS FREE - LICENSED UNDER THE MIT LICENSE
# ARTICLE URL: http://forums.4fips.com/viewtopic.php?f=3&t=1201
# */

cmake_minimum_required(VERSION 2.8)
add_definitions("-std=c++11")
project(hello_triangle)
file(GLOB sources *.cpp)
set(CMAKE_EXECUTABLE_SUFFIX ".html")
add_executable(hello_triangle ${sources})
