cmake_minimum_required(VERSION 3.28)
project("glm_metal" VERSION 1.0.1)
set(CMAKE_CXX_STANDARD 17)

option(GLM_METAL_DISABLE_EXTRA_WARNINGS "Disable the flags `-Wall`, `-Werror`, and `-Wextra`" OFF)

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

function(createTestSuite testSuiteName fileList)
    add_executable(${testSuiteName} "${fileList}")
    target_link_libraries(
        ${testSuiteName}
        glm_metal
        glm
        GTest::gtest_main
    )
endfunction()

createTestSuite(
    test_orthographic_frustum_lh
    tests/test_orthographic_frustum_lh.cpp
)
createTestSuite(
    test_orthographic_frustum_rh
    tests/test_orthographic_frustum_rh.cpp
)
createTestSuite(
    test_perspective_fov_lh
    tests/test_perspective_fov_lh.cpp
)
createTestSuite(
    test_perspective_fov_rh
    tests/test_perspective_fov_rh.cpp
)
createTestSuite(
    test_perspective_frustum_lh
    tests/test_perspective_frustum_lh.cpp
)
createTestSuite(
    test_perspective_frustum_rh
    tests/test_perspective_frustum_rh.cpp
)

include(GoogleTest)
gtest_discover_tests(test_orthographic_frustum_lh)
gtest_discover_tests(test_orthographic_frustum_rh)
gtest_discover_tests(test_perspective_fov_lh)
gtest_discover_tests(test_perspective_fov_rh)
gtest_discover_tests(test_perspective_frustum_lh)
gtest_discover_tests(test_perspective_frustum_rh)
