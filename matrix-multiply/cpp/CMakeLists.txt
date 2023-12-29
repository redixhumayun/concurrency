cmake_minimum_required(VERSION 3.26)
project(matrix-multiply)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Set OpenMP paths
set(OpenMP_CXX_FLAGS "-Xpreprocessor -fopenmp -I/opt/homebrew/opt/libomp/include")
set(OpenMP_CXX_LIBRARIES "-L/opt/homebrew/opt/libomp/lib -lomp")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_CXX_LIBRARIES}")

#Add the googletest library
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
FetchContent_MakeAvailable(googletest)

# Add the include directory for the debug.h file
include_directories(${PROJECT_SOURCE_DIR}/include)

if(CMAKE_BUILD_TYPE MATCHES Debug)
    add_definitions(-DDEBUG)
endif()

add_executable(main main.cpp main-impl.cpp)
add_executable(tests test.cpp main-impl.cpp)

target_link_libraries(main ${OpenMP_CXX_LIBRARIES})
target_link_libraries(tests ${OpenMP_CXX_LIBRARIES} gtest_main)
target_include_directories(tests PRIVATE ${googletest_SOURCE_DIR}/include)
