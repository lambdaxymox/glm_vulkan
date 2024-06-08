#include <gtest/gtest.h>
#include <glm/mat4x4.hpp>
#include <glm/vec4.hpp>
#include <glm_metal/glm_metal.h>


TEST(PerspectiveFrustumLhTests, PerspectiveProjectionMatrix) {
    float left = -4.0f;
    float right = 4.0f;
    float bottom = -2.0f;
    float top = 3.0f;
    float near = 1.0f;
    float far = 100.0f;
    auto expected = glm::mat4x4 {
        1.0f / 4.0f,  0.0f,         0.0f,           0.0f,
        0.0f,         2.0f / 5.0f,  0.0f,           0.0f,
        0.0f,        -1.0f / 5.0f,  100.0f / 99.0f, 1.0f,
        0.0f,         0.0f,        -100.0f / 99.0f, 0.0f
    };
    auto result = glm_metal::perspective_frustum_lh(left, right, bottom, top, near, far);

    EXPECT_EQ(result, expected);
}

TEST(PerspectiveFrustumLhTests, PerspectiveProjectionMapsLeftToNegativeOneInNDC) {
    float left = -4.0f;
    float right = 4.0f;
    float bottom = -2.0f;
    float top = 3.0f;
    float near = 1.0f;
    float far = 100.0f;
    auto matrix = glm_metal::perspective_frustum_lh(left, right, bottom, top, near, far);
    auto vector = glm::vec4 { left, 0.0f, 2.0f, 1.0f };
    auto projectedVector = matrix * vector;
    float expected = -1.0f;
    float result = projectedVector.x;

    EXPECT_FLOAT_EQ(result, expected);
}

TEST(PerspectiveFrustumLhTests, PerspectiveProjectionMapsRightToPositiveOneInNDC) {
    float left = -4.0f;
    float right = 4.0f;
    float bottom = -2.0f;
    float top = 3.0f;
    float near = 1.0f;
    float far = 100.0f;
    auto matrix = glm_metal::perspective_frustum_lh(left, right, bottom, top, near, far);
    auto vector = glm::vec4 { right, 0.0f, 2.0f, 1.0f };
    auto projectedVector = matrix * vector;
    float expected = 1.0f;
    float result = projectedVector.x;

    EXPECT_FLOAT_EQ(result, expected);
}

TEST(PerspectiveFrustumLhTests, PerspectiveProjectionMapsBottomToNegativeOneInNDC) {
    float left = -4.0f;
    float right = 4.0f;
    float bottom = -2.0f;
    float top = 3.0f;
    float near = 1.0f;
    float far = 100.0f;
    auto matrix = glm_metal::perspective_frustum_lh(left, right, bottom, top, near, far);
    auto vector = glm::vec4 { 0.0f, bottom, 2.0f, 1.0f };
    auto projectedVector = matrix * vector;
    float expected = -1.0f;
    float result = projectedVector.y;

    EXPECT_FLOAT_EQ(result, expected);
}

TEST(PerspectiveFrustumLhTests, PerspectiveProjectionMapsTopToPositiveOneInNDC) {
    float left = -4.0f;
    float right = 4.0f;
    float bottom = -2.0f;
    float top = 3.0f;
    float near = 1.0f;
    float far = 100.0f;
    auto matrix = glm_metal::perspective_frustum_lh(left, right, bottom, top, near, far);
    auto vector = glm::vec4 { 0.0f, top, 2.0f, 1.0f };
    auto projectedVector = matrix * vector;
    float expected = 1.0f;
    float result = projectedVector.y;

    EXPECT_FLOAT_EQ(result, expected);
}

TEST(PerspectiveFrustumLhTests, PerspectiveProjectionMapsPositiveNearToZeroInNDC) {
    float left = -4.0f;
    float right = 4.0f;
    float bottom = -2.0f;
    float top = 3.0f;
    float near = 1.0f;
    float far = 100.0f;
    auto matrix = glm_metal::perspective_frustum_lh(left, right, bottom, top, near, far);
    auto vector = glm::vec4 { 0.0f, 0.0f, near, 1.0f };
    auto projectedVector = matrix * vector;
    float expected = 0.0f;
    float result = projectedVector.z;

    EXPECT_FLOAT_EQ(result, expected);
}

TEST(PerspectiveFrustumLhTests, PerspectiveProjectionMapsPositiveFarToPositiveOneInNDC) {
    float left = -4.0f;
    float right = 4.0f;
    float bottom = -2.0f;
    float top = 3.0f;
    float near = 1.0f;
    float far = 100.0f;
    auto matrix = glm_metal::perspective_frustum_lh(left, right, bottom, top, near, far);
    auto vector = glm::vec4 { 0.0f, 0.0f, far, 1.0f };
    auto projectedVector = matrix * vector;
    float expected = 100.0f;
    float result = projectedVector.z;

    EXPECT_FLOAT_EQ(result, expected);
}

TEST(PerspectiveFrustumLhTests, PerspectiveProjectionPreservesDepthOrdering) {
    float left = -4.0f;
    float right = 4.0f;
    float bottom = -2.0f;
    float top = 3.0f;
    float near = 1.0f;
    float far = 100.0f;
    auto matrix = glm_metal::perspective_frustum_lh(left, right, bottom, top, near, far);
    auto point1 = matrix * glm::vec4 { 0.0f, 0.0f, 2.0f, 1.0f };
    auto point2 = matrix * glm::vec4 { 0.0f, 0.0f, 99.0f, 1.0f};

    EXPECT_LE(point1.z, point2.z);
}

TEST(PerspectiveFrustumLhTests, PerspectiveProjectionHomogeneousCoordinate) {
    float left = -4.0f;
    float right = 4.0f;
    float bottom = -2.0f;
    float top = 3.0f;
    float near = 1.0f;
    float far = 100.0f;
    auto matrix = glm_metal::perspective_frustum_lh(left, right, bottom, top, near, far);
    auto point = glm::vec4 { 0.0f, 0.0f, 99.0f, 1.0f };
    auto projectedPoint = matrix * point;
    float expected = 99.0f;
    float result = projectedPoint.w;

    EXPECT_FLOAT_EQ(result, expected);
}
