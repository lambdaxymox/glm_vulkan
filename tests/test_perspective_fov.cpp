#include <gtest/gtest.h>
#include <glm/mat4x4.hpp>
#include <glm/vec4.hpp>
#include <glm_vulkan/glm_vulkan.h>


TEST(PerspectiveFovTests, PerspectiveProjectionMatrix) {
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
    auto result = glm_vulkan::perspective_fov(fovyRadians, aspectRatio, near, far);

    EXPECT_EQ(result, expected);
}

TEST(PerspectiveFovTests, PerspectiveProjectionMapsLeftToNegativeOneInClipSpace) {
    float fovyRadians = glm::pi<float>() / 2.0f;
    float aspectRatio = 4.0f / 3.0f;
    float near = 1.0f;
    float far = 100.0f;
    auto matrix = glm_vulkan::perspective_fov(fovyRadians, aspectRatio, near, far);
    float left = -aspectRatio * near;
    auto vector = glm::vec4 { left, 0.0f, 2.0f, 1.0f };
    auto projectedVector = matrix * vector;
    float expected = -1.0f;
    float result = projectedVector.x;

    EXPECT_FLOAT_EQ(result, expected);
}

TEST(PerspectiveFovTests, PerspectiveProjectionMapsRightToPositiveOneInClipSpace) {
    float fovyRadians = glm::pi<float>() / 2.0f;
    float aspectRatio = 4.0f / 3.0f;
    float near = 1.0f;
    float far = 100.0f;
    auto matrix = glm_vulkan::perspective_fov(fovyRadians, aspectRatio, near, far);
    float right = aspectRatio * near;
    auto vector = glm::vec4 { right, 0.0f, 2.0f, 1.0f };
    auto projectedVector = matrix * vector;
    float expected = 1.0f;
    float result = projectedVector.x;

    EXPECT_FLOAT_EQ(result, expected);
}

TEST(PerspectiveFovTests, PerspectiveProjectionMapsBottomToPositiveOneInClipSpace) {
    float fovyRadians = glm::pi<float>() / 2.0f;
    float aspectRatio = 4.0f / 3.0f;
    float near = 1.0f;
    float far = 100.0f;
    auto matrix = glm_vulkan::perspective_fov(fovyRadians, aspectRatio, near, far);
    float bottom = near;
    auto vector = glm::vec4 { 0.0f, bottom, 2.0f, 1.0f };
    auto projectedVector = matrix * vector;
    float expected = 1.0f;
    float result = projectedVector.y;

    EXPECT_FLOAT_EQ(result, expected);
}

TEST(PerspectiveFovTests, PerspectiveProjectionMapsTopToNegativeOneInClipSpace) {
    float fovyRadians = glm::pi<float>() / 2.0f;
    float aspectRatio = 4.0f / 3.0f;
    float near = 1.0f;
    float far = 100.0f;
    auto matrix = glm_vulkan::perspective_fov(fovyRadians, aspectRatio, near, far);
    float top = -near;
    auto vector = glm::vec4 { 0.0f, top, 2.0f, 1.0f };
    auto projectedVector = matrix * vector;
    float expected = -1.0f;
    float result = projectedVector.y;

    EXPECT_FLOAT_EQ(result, expected);
}

TEST(PerspectiveFovTests, PerspectiveProjectionMapsPositiveNearToZeroInClipSpace) {
    float fovyRadians = glm::pi<float>() / 2.0f;
    float aspectRatio = 4.0f / 3.0f;
    float near = 1.0f;
    float far = 100.0f;
    auto matrix = glm_vulkan::perspective_fov(fovyRadians, aspectRatio, near, far);
    auto vector = glm::vec4 { 0.0f, 0.0f, near, 1.0f };
    auto projectedVector = matrix * vector;
    float expected = 0.0f;
    float result = projectedVector.z;

    EXPECT_FLOAT_EQ(result, expected);
}

TEST(PerspectiveFovTests, PerspectiveProjectionMapsPositiveFarToPositiveOneInClipSpace) {
    float fovyRadians = glm::pi<float>() / 2.0f;
    float aspectRatio = 4.0f / 3.0f;
    float near = 1.0f;
    float far = 100.0f;
    auto matrix = glm_vulkan::perspective_fov(fovyRadians, aspectRatio, near, far);
    auto vector = glm::vec4 { 0.0f, 0.0f, far, 1.0f };
    auto projectedVector = matrix * vector;
    float expected = 100.0f;
    float result = projectedVector.z;

    EXPECT_FLOAT_EQ(result, expected);
}

TEST(PerspectiveFovTests, PerspectiveProjectionPreservesDepthOrdering) {
    float fovyRadians = glm::pi<float>() / 2.0f;
    float aspectRatio = 4.0f / 3.0f;
    float near = 1.0f;
    float far = 100.0f;
    auto matrix = glm_vulkan::perspective_fov(fovyRadians, aspectRatio, near, far);
    auto point1 = matrix * glm::vec4 { 0.0f, 0.0f, 2.0f, 1.0f };
    auto point2 = matrix * glm::vec4 { 0.0f, 0.0f, 99.0f, 1.0f};

    EXPECT_LE(point1.z, point2.z);
}

TEST(PerspectiveFovTests, PerspectiveProjectionHomogeneousCoordinate) {
    float fovyRadians = glm::pi<float>() / 2.0f;
    float aspectRatio = 4.0f / 3.0f;
    float near = 1.0f;
    float far = 100.0f;
    auto matrix = glm_vulkan::perspective_fov(fovyRadians, aspectRatio, near, far);
    auto point = glm::vec4 { 0.0f, 0.0f, 99.0f, 1.0f };
    auto projectedPoint = matrix * point;
    float expected = 99.0f;
    float result = projectedPoint.w;

    EXPECT_FLOAT_EQ(result, expected);
}
