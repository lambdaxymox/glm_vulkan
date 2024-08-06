cmake_minimum_required(VERSION 3.28)
project("glm_metal" VERSION 1.0.1)
set(CMAKE_CXX_STANDARD 17)

option(GLM_METAL_DISABLE_EXTRA_WARNINGS "Disable the flags `-Wall`, `-Werror`, and `-Wextra`" OFF)
option(GLM_METAL_ENABLE_TESTS "Build `glm_metal` tests" ON)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

include(NoInsourceBuilds)
CheckNoInSourceBuilds()

add_subdirectory(external/glm-1.0.1)
add_subdirectory(external/googletest)

add_library(glm_metal SHARED)
target_sources(glm_metal
    PRIVATE
        "glm_metal/glm_metal.cpp"
)
target_include_directories(glm_metal PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")
target_link_libraries(glm_metal PUBLIC glm)

if (NOT GLM_METAL_DISABLE_EXTRA_WARNINGS)
    target_compile_options(glm_metal PRIVATE -Wall -Werror -Wextra)
endif()

if(GLM_METAL_ENABLE_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()
