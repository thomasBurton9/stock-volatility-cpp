cmake_minimum_required(VERSION 3.20)

# 1. Project name 
project(stock-volatility-cpp VERSION 1.0 LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# 3. Executable
add_executable(${PROJECT_NAME} 
    src/main.cpp
    src/volatility.cpp
)

target_include_directories(${PROJECT_NAME} PRIVATE include)
