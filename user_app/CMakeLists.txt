project(UserApp)
cmake_minimum_required(VERSION 2.8)

set(SRC_LIST
	main.cpp
)

add_executable(${PROJECT_NAME} ${SRC_LIST})
target_link_libraries(${PROJECT_NAME} dl)