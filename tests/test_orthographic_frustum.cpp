#include <gtest/gtest.h>
#include <glm/mat4x4.hpp>
#include <glm/vec4.hpp>
#include <glm_vulkan/glm_vulkan.h>


TEST(OrthographicFrustumTests, OrthographicProjectionMatrix) {
    float left = -4.0f;
    float right = 4.0f;
    float bottom = 2.0f;
    float top = -3.0f;
    float near = 1.0f;
    float far = 100.0f;
    auto expected = glm::mat4x4 {
        1.0f / 4.0f,  0.0f,         0.0f,         0.0f,
        0.0f,         2.0f / 5.0f,  0.0f,         0.0f,
        0.0f,         0.0f,         1.0f / 99.0f, 0.0f,
        0.0f,         1.0f / 5.0f, -1.0f / 99.0f, 1.0f
    };
    auto result = glm_vulkan::orthographic_frustum(left, right, bottom, top, near, far);

    EXPECT_EQ(result, expected);
}

TEST(OrthographicFrustumTests, OrthographicProjectionMapsLeftToNegativeOneInClipSpace) {
    float left = -4.0f;
    float right = 4.0f;
    float bottom = 2.0f;
    float top = -3.0f;
    float near = 1.0f;
    float far = 100.0f;
    auto matrix = glm_vulkan::orthographic_frustum(left, right, bottom, top, near, far);
    auto vector = glm::vec4 { left, 0.0f, 2.0f, 1.0f };
    auto projectedVector = matrix * vector;
    float expected = -1.0f;
    float result = projectedVector.x;

    EXPECT_FLOAT_EQ(result, expected);
}

TEST(OrthographicFrustumTests, OrthographicProjectionMapsRightToPositiveOneInClipSpace) {
    float left = -4.0f;
    float right = 4.0f;
    float bottom = 2.0f;
    float top = -3.0f;
    float near = 1.0f;
    float far = 100.0f;
    auto matrix = glm_vulkan::orthographic_frustum(left, right, bottom, top, near, far);
    auto vector = glm::vec4 { right, 0.0f, 2.0f, 1.0f };
    auto projectedVector = matrix * vector;
    float expected = 1.0f;
    float result = projectedVector.x;

    EXPECT_FLOAT_EQ(result, expected);
}

TEST(OrthographicFrustumTests, OrthographicProjectionMapsBottomToPositiveOneInClipSpace) {
    float left = -4.0f;
    float right = 4.0f;
    float bottom = 2.0f;
    float top = -3.0f;
    float near = 1.0f;
    float far = 100.0f;
    auto matrix = glm_vulkan::orthographic_frustum(left, right, bottom, top, near, far);
    auto vector = glm::vec4 { 0.0f, bottom, 2.0f, 1.0f };
    auto projectedVector = matrix * vector;
    float expected = 1.0f;
    float result = projectedVector.y;

    EXPECT_FLOAT_EQ(result, expected);
}

TEST(OrthographicFrustumTests, OrthographicProjectionMapsTopToNegativeOneInClipSpace) {
    float left = -4.0f;
    float right = 4.0f;
    float bottom = 2.0f;
    float top = -3.0f;
    float near = 1.0f;
    float far = 100.0f;
    auto matrix = glm_vulkan::orthographic_frustum(left, right, bottom, top, near, far);
    auto vector = glm::vec4 { 0.0f, top, 2.0f, 1.0f };
    auto projectedVector = matrix * vector;
    float expected = -1.0f;
    float result = projectedVector.y;

    EXPECT_FLOAT_EQ(result, expected);
}

TEST(OrthographicFrustumTests, OrthographicProjectionMapsPositiveNearToZeroInClipSpace) {
    float left = -4.0f;
    float right = 4.0f;
    float bottom = 2.0f;
    float top = -3.0f;
    float near = 1.0f;
    float far = 100.0f;
    auto matrix = glm_vulkan::orthographic_frustum(left, right, bottom, top, near, far);
    auto vector = glm::vec4 { 0.0f, 0.0f, near, 1.0f };
    auto projectedVector = matrix * vector;
    float expected = 0.0f;
    float result = projectedVector.z;

    EXPECT_FLOAT_EQ(result, expected);
}

TEST(OrthographicFrustumTests, OrthographicProjectionMapsPositiveFarToPositiveOneInClipSpace) {
    float left = -4.0f;
    float right = 4.0f;
    float bottom = 2.0f;
    float top = -3.0f;
    float near = 1.0f;
    float far = 100.0f;
    auto matrix = glm_vulkan::orthographic_frustum(left, right, bottom, top, near, far);
    auto vector = glm::vec4 { 0.0f, 0.0f, far, 1.0f };
    auto projectedVector = matrix * vector;
    float expected = 1.0f;
    float result = projectedVector.z;

    EXPECT_FLOAT_EQ(result, expected);
}

TEST(OrthographicFrustumTests, OrthographicProjectionHomogeneousCoordinate) {
    float left = -4.0f;
    float right = 4.0f;
    float bottom = 2.0f;
    float top = -3.0f;
    float near = 1.0f;
    float far = 100.0f;
    auto matrix = glm_vulkan::orthographic_frustum(left, right, bottom, top, near, far);
    auto point = glm::vec4 { 0.0f, 0.0f, 99.0f, 1.0f };
    auto projectedPoint = matrix * point;
    float expected = 1.0f;
    float result = projectedPoint.w;

    EXPECT_FLOAT_EQ(result, expected);
}
