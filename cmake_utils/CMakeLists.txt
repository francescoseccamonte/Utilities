# A minimal example of a CMakeLists.txt file

cmake_minimum_required(VERSION 3.10)   			# CMake version check
project(project_name)               			# Create project "simple_example"
set(CMAKE_CXX_STANDARD 11)            			# Enable c++11 standard
# set (CMAKE_CXX_FLAGS "-pthread")				# compile options

set(SOURCE_FILES src/main.cpp)            		# Add main.cpp file of project root directory as source file
add_executable(project_exec ${SOURCE_FILES})    # Add executable target with source files listed in SOURCE_FILES variable
