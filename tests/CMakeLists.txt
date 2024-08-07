enable_testing()

function(createTestSuite testSuiteName fileList)
    add_executable(${testSuiteName} "${fileList}")
    target_link_libraries(
        ${testSuiteName}
        glm_vulkan
        glm
        GTest::gtest_main
    )
endfunction()

createTestSuite(
    test_orthographic_frustum
    test_orthographic_frustum.cpp
)
createTestSuite(
    test_perspective_fov
    test_perspective_fov.cpp
)
createTestSuite(
    test_perspective_frustum
    test_perspective_frustum.cpp
)

include(GoogleTest)
gtest_discover_tests(test_orthographic_frustum)
gtest_discover_tests(test_perspective_fov)
gtest_discover_tests(test_perspective_frustum)
