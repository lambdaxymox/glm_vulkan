#include <gtest/gtest.h>
#include <glm/mat4x4.hpp>
#include <glm/vec4.hpp>
#include <glm_metal/glm_metal.h>


TEST(PerspectiveFovLhTests, PerspectiveProjectionMatrix) {
    float fovyRadians = glm::pi<float>() / 2.0f;
    float aspectRatio = 4.0f / 3.0f;
    float near = 1.0f;
    float far = 100.0f;
    auto expected = glm::mat4x4 {
        3.0f / 4.0f, 0.0f,  0.0f,           0.0f,
        0.0f,        1.0f,  0.0f,           0.0f,
        0.0f,        0.0f,  100.0f / 99.0f, 1.0f,
        0.0f,        0.0f, -100.0f / 99.0f, 0.0f
    };
    auto result = glm_metal::perspective_fov_lh(fovyRadians, aspectRatio, near, far);

    EXPECT_EQ(result, expected);
}

TEST(PerspectiveFovLhTests, PerspectiveProjectionMapsLeftToNegativeOneInNDC) {
    float fovyRadians = glm::pi<float>() / 2.0f;
    float aspectRatio = 4.0f / 3.0f;
    float near = 1.0f;
    float far = 100.0f;
    auto matrix = glm_metal::perspective_fov_lh(fovyRadians, aspectRatio, near, far);
    float left = -aspectRatio * near;
    auto vector = glm::vec4 { left, 0.0f, 2.0f, 1.0f };
    auto projectedVector = matrix * vector;
    float expected = -1.0f;
    float result = projectedVector.x;

    EXPECT_FLOAT_EQ(result, expected);
}

TEST(PerspectiveFovLhTests, PerspectiveProjectionMapsRightToPositiveOneInNDC) {
    float fovyRadians = glm::pi<float>() / 2.0f;
    float aspectRatio = 4.0f / 3.0f;
    float near = 1.0f;
    float far = 100.0f;
    auto matrix = glm_metal::perspective_fov_lh(fovyRadians, aspectRatio, near, far);
    float right = aspectRatio * near;
    auto vector = glm::vec4 { right, 0.0f, 2.0f, 1.0f };
    auto projectedVector = matrix * vector;
    float expected = 1.0f;
    float result = projectedVector.x;

    EXPECT_FLOAT_EQ(result, expected);
}

TEST(PerspectiveFovLhTests, PerspectiveProjectionMapsBottomToNegativeOneInNDC) {
    float fovyRadians = glm::pi<float>() / 2.0f;
    float aspectRatio = 4.0f / 3.0f;
    float near = 1.0f;
    float far = 100.0f;
    auto matrix = glm_metal::perspective_fov_lh(fovyRadians, aspectRatio, near, far);
    float bottom = -near;
    auto vector = glm::vec4 { 0.0f, bottom, 2.0f, 1.0f };
    auto projectedVector = matrix * vector;
    float expected = -1.0f;
    float result = projectedVector.y;

    EXPECT_FLOAT_EQ(result, expected);
}

TEST(PerspectiveFovLhTests, PerspectiveProjectionMapsTopToPositiveOneInNDC) {
    float fovyRadians = glm::pi<float>() / 2.0f;
    float aspectRatio = 4.0f / 3.0f;
    float near = 1.0f;
    float far = 100.0f;
    auto matrix = glm_metal::perspective_fov_lh(fovyRadians, aspectRatio, near, far);
    float top = near;
    auto vector = glm::vec4 { 0.0f, top, 2.0f, 1.0f };
    auto projectedVector = matrix * vector;
    float expected = 1.0f;
    float result = projectedVector.y;

    EXPECT_FLOAT_EQ(result, expected);
}

TEST(PerspectiveFovLhTests, PerspectiveProjectionMapsPositiveNearToZeroInNDC) {
    float fovyRadians = glm::pi<float>() / 2.0f;
    float aspectRatio = 4.0f / 3.0f;
    float near = 1.0f;
    float far = 100.0f;
    auto matrix = glm_metal::perspective_fov_lh(fovyRadians, aspectRatio, near, far);
    auto vector = glm::vec4 { 0.0f, 0.0f, near, 1.0f };
    auto projectedVector = matrix * vector;
    float expected = 0.0f;
    float result = projectedVector.z;

    EXPECT_FLOAT_EQ(result, expected);
}

TEST(PerspectiveFovLhTests, PerspectiveProjectionMapsPositiveFarToPositiveOneInNDC) {
    float fovyRadians = glm::pi<float>() / 2.0f;
    float aspectRatio = 4.0f / 3.0f;
    float near = 1.0f;
    float far = 100.0f;
    auto matrix = glm_metal::perspective_fov_lh(fovyRadians, aspectRatio, near, far);
    auto vector = glm::vec4 { 0.0f, 0.0f, far, 1.0f };
    auto projectedVector = matrix * vector;
    float expected = 100.0f;
    float result = projectedVector.z;

    EXPECT_FLOAT_EQ(result, expected);
}

TEST(PerspectiveFovLhTests, PerspectiveProjectionPreservesDepthOrdering) {
    float fovyRadians = glm::pi<float>() / 2.0f;
    float aspectRatio = 4.0f / 3.0f;
    float near = 1.0f;
    float far = 100.0f;
    auto matrix = glm_metal::perspective_fov_lh(fovyRadians, aspectRatio, near, far);
    auto point1 = matrix * glm::vec4 { 0.0f, 0.0f, 2.0f, 1.0f };
    auto point2 = matrix * glm::vec4 { 0.0f, 0.0f, 99.0f, 1.0f};

    EXPECT_LE(point1.z, point2.z);
}

TEST(PerspectiveFovLhTests, PerspectiveProjectionHomogeneousCoordinate) {
    float fovyRadians = glm::pi<float>() / 2.0f;
    float aspectRatio = 4.0f / 3.0f;
    float near = 1.0f;
    float far = 100.0f;
    auto matrix = glm_metal::perspective_fov_lh(fovyRadians, aspectRatio, near, far);
    auto point = glm::vec4 { 0.0f, 0.0f, 99.0f, 1.0f };
    auto projectedPoint = matrix * point;
    float expected = 99.0f;
    float result = projectedPoint.w;

    EXPECT_FLOAT_EQ(result, expected);
}
