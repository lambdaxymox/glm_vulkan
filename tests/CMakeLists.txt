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
    test_orthographic_frustum_lh.cpp
)
createTestSuite(
    test_orthographic_frustum_rh
    test_orthographic_frustum_rh.cpp
)
createTestSuite(
    test_perspective_fov_lh
    test_perspective_fov_lh.cpp
)
createTestSuite(
    test_perspective_fov_rh
    test_perspective_fov_rh.cpp
)
createTestSuite(
    test_perspective_frustum_lh
    test_perspective_frustum_lh.cpp
)
createTestSuite(
    test_perspective_frustum_rh
    test_perspective_frustum_rh.cpp
)

include(GoogleTest)
gtest_discover_tests(test_orthographic_frustum_lh)
gtest_discover_tests(test_orthographic_frustum_rh)
gtest_discover_tests(test_perspective_fov_lh)
gtest_discover_tests(test_perspective_fov_rh)
gtest_discover_tests(test_perspective_frustum_lh)
gtest_discover_tests(test_perspective_frustum_rh)
