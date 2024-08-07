cmake_minimum_required(VERSION 3.28)
project("glm_vulkan" VERSION 1.0.2)
set(CMAKE_CXX_STANDARD 17)

option(glm_vulkan_DISABLE_EXTRA_WARNINGS "Disable the flags `-Wall`, `-Werror`, and `-Wextra`" OFF)
option(glm_vulkan_ENABLE_TESTS "Build `glm_vulkan` tests" ON)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

include(NoInsourceBuilds)
CheckNoInSourceBuilds()

add_subdirectory(external/glm-1.0.1)
add_subdirectory(external/googletest)

add_library(glm_vulkan SHARED)
target_sources(glm_vulkan
    PRIVATE
        "glm_vulkan/glm_vulkan.cpp"
)
target_include_directories(glm_vulkan PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")
target_link_libraries(glm_vulkan PUBLIC glm)

if (NOT glm_vulkan_DISABLE_EXTRA_WARNINGS)
    target_compile_options(glm_vulkan PRIVATE -Wall -Werror -Wextra)
endif()

if(glm_vulkan_ENABLE_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()
