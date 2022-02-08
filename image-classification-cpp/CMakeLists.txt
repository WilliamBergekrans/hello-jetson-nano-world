cmake_minimum_required(VERSION 2.8)

project(HelloNanoWorld)

find_package(jetson-utils)
find_package(jetson-inference)

find_package(CUDA)

link_directories(/usr/lib/aarch64-linux-gnu/tegra)

cuda_add_executable(HelloNanoWorld image-recognition.cpp)

target_link_libraries(HelloNanoWorld jetson-inference)

# To run: 
# Stand in the same folder as this file. 
# run "cmake ."
# Then run "make"
# Example classificaiton run: ./HelloNanoWorld black_bear.jpg