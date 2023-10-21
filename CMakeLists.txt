cmake_minimum_required(VERSION 3.5)

project(Test-task LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(Test-task
	main.cpp
	include/curves_3d.h
	source/Circle.cpp
	source/Elipse.cpp
	source/Helix.cpp
	source/curves_3d.cpp)

include(GNUInstallDirs)
install(TARGETS Test-task
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
