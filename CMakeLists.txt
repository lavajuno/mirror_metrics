cmake_minimum_required(VERSION 3.22)
project(mirror_metrics_engine VERSION 0.0.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)

include(FetchContent)

FetchContent_Declare(prometheus-cpp
    GIT_REPOSITORY https://github.com/jupp0r/prometheus-cpp
    GIT_TAG v1.2.4
)
FetchContent_MakeAvailable(prometheus-cpp)

# External libraries from source
add_subdirectory(lib/mirror-logging)

# Include header files
include_directories(${CMAKE_SOURCE_DIR}/src)

# Internal libraries from source
add_library(event
    src/event/Event.cpp
    src/event/TimeStamp.cpp
)

# Libraries to be linked internally
target_link_libraries(event
    mirror-logging
)

# Libraries to be linked to executable
link_libraries(
    mirror-logging
    event
    prometheus-cpp::pull
)
add_executable(mirror_metrics_engine src/main.cpp)
