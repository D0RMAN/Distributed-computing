project(EigenValues)
cmake_minimum_required(VERSION 2.8)

set(CMAKE_BUILD_TYPE Release)
set(SRC_LIST
	Matrix.cpp
	f.cpp
)


add_library(${PROJECT_NAME} SHARED ${SRC_LIST})