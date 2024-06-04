cmake_minimum_required(VERSION 3.28)
project("glm_metal" VERSION 0.1.0)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -Wextra")

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

include(NoInsourceBuilds)

CheckNoInSourceBuilds()

add_subdirectory(external/glm-1.0.1)

add_library(glm_metal SHARED)
target_sources(glm_metal PRIVATE "glm_metal/glm_metal.cpp")
target_include_directories(glm_metal PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")
target_link_libraries(glm_metal PUBLIC glm)
