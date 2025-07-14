cmake_minimum_required(VERSION 3.10)

# Set the project name
project(DualModelReactor)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Specify the directories for the source files
include_directories(include)

# Add the source files
add_executable(DualModelReactor src/DualModelReactor.cpp)

# Link libraries (if needed)
# target_link_libraries(DualModelReactor <your_libraries>)
