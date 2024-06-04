#include "glm_metal.h"


glm::mat4x4 glm_metal::orthographic_frustum_rh(float left, float right, float bottom, float top, float near, float far) {
    float c0r0 = 2.0f / (right - left);
    float c0r1 = 0.0f;
    float c0r2 = 0.0f;
    float c0r3 = 0.0f;

    float c1r0 = 0.0f;
    float c1r1 = 2.0f / (top - bottom);
    float c1r2 = 0.0f;
    float c1r3 = 0.0f;

    float c2r0 =  0.0f;
    float c2r1 =  0.0f;
    float c2r2 = -1.0f / (far - near);
    float c2r3 =  1.0f;

    float c3r0 = -(right + left) / (right - left);
    float c3r1 = -(top + bottom) / (top - bottom);
    float c3r2 = -near / (far - near);
    float c3r3 =  1.0f;

    return glm::mat4x4 {
        c0r0, c0r1, c0r2, c0r3,
        c1r0, c1r1, c1r2, c1r3,
        c2r0, c2r1, c2r2, c2r3,
        c3r0, c3r1, c3r2, c3r3
    };
}

glm::mat4x4 glm_metal::orthographic_frustum_lh(float left, float right, float bottom, float top, float near, float far) {
    float c0r0 = 2.0f / (right - left);
    float c0r1 = 0.0f;
    float c0r2 = 0.0f;
    float c0r3 = 0.0f;

    float c1r0 = 0.0f;
    float c1r1 = 2.0f / (top - bottom);
    float c1r2 = 0.0f;
    float c1r3 = 0.0f;

    float c2r0 = 0.0f;
    float c2r1 = 0.0f;
    float c2r2 = 1.0f / (far - near);
    float c2r3 = 1.0f;

    float c3r0 = -(right + left) / (right - left);
    float c3r1 = -(top + bottom) / (top - bottom);
    float c3r2 = -near / (far - near);
    float c3r3 =  1.0f;

    return glm::mat4x4 {
        c0r0, c0r1, c0r2, c0r3,
        c1r0, c1r1, c1r2, c1r3,
        c2r0, c2r1, c2r2, c2r3,
        c3r0, c3r1, c3r2, c3r3
    };
}

glm::mat4x4 glm_metal::perspective_fov_rh(float fovyRadians, float aspectRatio, float near, float far) {
    float range = (1.0f / glm::tan(fovyRadians * 0.5f)) * near;

    float c0r0 = near / (range * aspectRatio);
    float c0r1 = 0.0f;
    float c0r2 = 0.0f;
    float c0r3 = 0.0f;

    float c1r0 = 0.0f;
    float c1r1 = near / range;
    float c1r2 = 0.0f;
    float c1r3 = 0.0f;

    float c2r0 =  0.0f;
    float c2r1 =  0.0f;
    float c2r2 = -far / (far - near);
    float c2r3 = -1.0f;

    float c3r0 =  0.0f;
    float c3r1 =  0.0f;
    float c3r2 = -(far * near) / (far - near);
    float c3r3 =  0.0f;

    return glm::mat4x4 {
        c0r0, c0r1, c0r2, c0r3,
        c1r0, c1r1, c1r2, c1r3,
        c2r0, c2r1, c2r2, c2r3,
        c3r0, c3r1, c3r2, c3r3
    };
}

glm::mat4x4 glm_metal::perspective_fov_lh(float fovyRadians, float aspectRatio, float near, float far) {
    float range = (1.0f / glm::tan(fovyRadians * 0.5f)) * near;

    float c0r0 = near / (range * aspectRatio);
    float c0r1 = 0.0f;
    float c0r2 = 0.0f;
    float c0r3 = 0.0f;

    float c1r0 = 0.0f;
    float c1r1 = near / range;
    float c1r2 = 0.0f;
    float c1r3 = 0.0f;

    float c2r0 = 0.0f;
    float c2r1 = 0.0f;
    float c2r2 = far / (far - near);
    float c2r3 = 1.0f;

    float c3r0 =  0.0f;
    float c3r1 =  0.0f;
    float c3r2 = -(far * near) / (far - near);
    float c3r3 =  0.0f;

    return glm::mat4x4 {
        c0r0, c0r1, c0r2, c0r3,
        c1r0, c1r1, c1r2, c1r3,
        c2r0, c2r1, c2r2, c2r3,
        c3r0, c3r1, c3r2, c3r3
    };
}

glm::mat4x4 glm_metal::perspective_frustum_rh(float left, float right, float bottom, float top, float near, float far) {
    float c0r0 = (2.0f * near) / (right - left);
    float c0r1 = 0.0f;
    float c0r2 = 0.0f;
    float c0r3 = 0.0f;

    float c1r0 = 0.0f;
    float c1r1 = (2.0f * near) / (top - bottom);
    float c1r2 = 0.0f;
    float c1r3 = 0.0f;

    float c2r0 =  (right + left) / (right - left);
    float c2r1 =  (top + bottom) / (top - bottom);
    float c2r2 = -far / (far - near);
    float c2r3 = -1.0f;

    float c3r0 =  0.0f;
    float c3r1 =  0.0f;
    float c3r2 = -(far * near) / (far - near);
    float c3r3 =  0.0f;
    
    return glm::mat4x4 {
        c0r0, c0r1, c0r2, c0r3,
        c1r0, c1r1, c1r2, c1r3,
        c2r0, c2r1, c2r2, c2r3,
        c3r0, c3r1, c3r2, c3r3
    };
}

glm::mat4x4 glm_metal::perspective_frustum_lh(float left, float right, float bottom, float top, float near, float far) {
    float c0r0 = (2.0f * near) / (right - left);
    float c0r1 = 0.0f;
    float c0r2 = 0.0f;
    float c0r3 = 0.0f;

    float c1r0 = 0.0f;
    float c1r1 = (2.0f * near) / (top - bottom);
    float c1r2 = 0.0f;
    float c1r3 = 0.0f;

    float c2r0 = -(right + left) / (right - left);
    float c2r1 = -(top + bottom) / (top - bottom);
    float c2r2 =  far / (far - near);
    float c2r3 =  1.0f;

    float c3r0 =  0.0f;
    float c3r1 =  0.0f;
    float c3r2 = -(far * near) / (far - near);
    float c3r3 =  0.0f;
    
    return glm::mat4x4 {
        c0r0, c0r1, c0r2, c0r3,
        c1r0, c1r1, c1r2, c1r3,
        c2r0, c2r1, c2r2, c2r3,
        c3r0, c3r1, c3r2, c3r3
    };
}
