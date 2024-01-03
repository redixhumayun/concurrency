cmake_minimum_required(VERSION 3.26)
project(concurrent-queue)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Set OpenMP paths
set(OpenMP_CXX_FLAGS "-Xpreprocessor -fopenmp -I/opt/homebrew/opt/libomp/include")
set(OpenMP_CXX_LIBRARIES "-L/opt/homebrew/opt/libomp/lib -lomp")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_CXX_LIBRARIES}")

# Set the thread sanitizer flag
if (USE_TSAN)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=thread -g -O1")
endif()

# Set the address sanitizer flag
if (USE_ASAN)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address -g -O1")
endif()

include(FetchContent)
include(GoogleTest)

#Add the googletest library
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
FetchContent_MakeAvailable(googletest)

# Add the google benchmark library
FetchContent_Declare(
  googlebenchmark
  GIT_REPOSITORY https://github.com/google/benchmark.git
  GIT_TAG        origin/main
)
FetchContent_MakeAvailable(googlebenchmark)

# Add the include directory for the debug.h file
include_directories(${PROJECT_SOURCE_DIR}/include)

if(CMAKE_BUILD_TYPE MATCHES Debug)
    add_definitions(-DDEBUG)
endif()

add_executable(main main.cpp main-impl.cpp)
add_executable(tests test.cpp main-impl.cpp)
add_executable(queue-benchmarks benchmark.cpp)
add_executable(atomics atomics.cpp)
add_executable(atomics-test atomics-test.cpp)
add_executable(lock-free-queue lock-free-queue.cpp
        lock-free-queue.hpp)

target_link_libraries(main ${OpenMP_CXX_LIBRARIES})
target_link_libraries(tests ${OpenMP_CXX_LIBRARIES} gtest_main benchmark::benchmark)
target_link_libraries(queue-benchmarks benchmark::benchmark)
target_include_directories(tests PRIVATE ${googletest_SOURCE_DIR}/include)

enable_testing()
gtest_discover_tests(tests)
