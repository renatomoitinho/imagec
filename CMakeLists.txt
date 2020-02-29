cmake_minimum_required(VERSION 3.10)
project( exec_opencv )
set(CMAKE_CXX_STANDARD 14)
find_package( OpenCV REQUIRED )
message(STATUS "OpenCV_INCLUDE_DIRS = ${OpenCV_INCLUDE_DIRS}")
message(STATUS "OpenCV_LIBS = ${OpenCV_LIBS}")

find_package(LLVM REQUIRED CONFIG)
message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
message(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")

include_directories( ${OpenCV_INCLUDE_DIRS} )

include_directories(${LLVM_INCLUDE_DIRS})
add_definitions(${LLVM_DEFINITIONS})

add_executable( exec_opencv main.cpp )

llvm_map_components_to_libnames(llvm_libs support core irreader)

target_link_libraries( exec_opencv ${OpenCV_LIBS} )
target_link_libraries( exec_opencv ${llvm_libs})

#cmake_minimum_required(VERSION 3.15)
#project(exec_opencv)
#set(CMAKE_CXX_STANDARD 14)
#add_executable(exec_opencv main.cpp)



#include_directories(${LLVM_INCLUDE_DIRS})
#add_definitions(${LLVM_DEFINITIONS})
#
## Now build our tools
#add_executable(simple-tool tool.cpp)
#
## Find the libraries that correspond to the LLVM components
## that we wish to use
#llvm_map_components_to_libnames(llvm_libs support core irreader)
#
## Link against LLVM libraries
#target_link_libraries(simple-tool ${llvm_libs})