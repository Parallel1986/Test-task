cmake_minimum_required(VERSION 3.5)

project(Test-task LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories("${PROJECT_SOURCE_DIR}/include_lib")

add_subdirectory("curves_lib")

add_executable(Test-task
	main.cpp
)

target_link_libraries(${PROJECT_NAME}
	PRIVATE Curves_lib::curves
)
