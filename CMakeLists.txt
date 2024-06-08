cmake_minimum_required(VERSION 3.28)
project("glm_metal" VERSION 0.1.0)

option(GLM_METAL_DISABLE_EXTRA_WARNINGS "Disable the flags `-Wall`, `-Werror`, and `-Wextra`" OFF)
set(CMAKE_CXX_STANDARD 17)

if (NOT GLM_METAL_DISABLE_EXTRA_WARNINGS)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -Wextra")
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
endif()

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

include(NoInsourceBuilds)

CheckNoInSourceBuilds()

add_subdirectory(external/glm-1.0.1)
add_subdirectory(external/googletest)

add_library(glm_metal SHARED)
target_sources(glm_metal PRIVATE "glm_metal/glm_metal.cpp")
target_include_directories(glm_metal PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")
target_link_libraries(glm_metal PUBLIC glm)

enable_testing()

add_executable(
    test_projection
    tests/test_perspective_frustum_rh.cpp
    tests/test_perspective_frustum_lh.cpp
)
target_link_libraries(
    test_projection
    glm_metal
    glm
    GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(test_projection)
