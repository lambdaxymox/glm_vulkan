#ifndef GLM_METAL_H
#define GLM_METAL_H

#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/scalar_constants.hpp>


namespace glm_metal {
    /// @brief Construct a new orthographic projection transformation mapping from 
    /// an eye space with a right-handed coordinate system to a clip space with a 
    /// left-handed coordinate coordinate system compatible with Metal's normalized 
    /// device coordinates.
    ///
    /// @details The source eye space coordinate system is a right-handed coordinate 
    /// system with `(x, y, z)` coordinates with the following properties:
    /// @li The camera space `x-axis` faces right.
    /// @li The camera space `y-axis` faces up.
    /// @li The camera space forward direction faces the `negative z-axis`.
    /// @li The camera `z-axis` faces the negative forward direction.
    /// The target clip space coordinate system is a left-handed coordinate
    /// system with `(x, y, z)` coordinates with the following properties:
    /// @li The clip space `x-axis` faces right.
    /// @li The clip space `y-axis` faces up.
    /// @li The clip space `z-axis` faces the camera forward direction.
    /// In particular, we map the eye space `z-axis` to the clip space `z-axis` by
    /// changing the sign of the eye space `z` coordinate. The transformation maps 
    /// the eye space volume `[left, right] x [bottom, top] x [-far, -near]` to 
    /// the normalized device coordinates `[-1, -1] x [-1, 1] x [0, 1]`. The projection
    /// matrix is given by
    /// @code{.unparsed}
    /// [ m[0, 0]  0        0        m[3, 0] ]
    /// [ 0        m[1, 1]  0        m[3, 1] ]
    /// [ 0        0        m[2, 2]  m[3, 2] ]
    /// [ 0        0        0        1       ]
    /// @endcode
    /// where
    /// @code{.unparsed}
    /// m[0, 0] ==  2 / (right - left)
    /// m[3, 0] == -(right + left) / (right - left)
    /// m[1, 1] ==  2 / (top - bottom)
    /// m[3, 1] == -(top + bottom) / (top - bottom)
    /// m[2, 2] == -1 / (far - near)
    /// m[3, 2] == -near / (far - near)
    /// @endcode
    /// where the matrix entries are indexed in column-major order. The input 
    /// parameters satisfy the following pre-conditions to generate a valid 
    /// orthographic projection matrix.
    /// @pre left < right
    /// @pre bottom < top
    /// @pre 0 < near < far
    /// 
    /// @section Parameters
    /// @param left the horizontal position of the left plane in eye space.
    /// The left plane is a plane parallel to the `yz-plane` along the `x-axis`.
    /// @param right the horizontal position of the right plane in eye space.
    /// The right plane is a plane parallel to the `yz-plane` along the `x-axis`. 
    /// @param bottom the vertical position of the bottom plane in eye space.
    /// The bottom plane is a plane parallel to the `zx-plane` along the `y-axis`.
    /// @param top the vertical position of the top plane in eye space.
    /// The top plane is a plane parallel to the `zx-plane` along the `y-axis`.
    /// @param near the distance along the `negative z-axis` of the near plane from the
    /// eye in eye space. The near plane is a plane parallel to the `xy-plane` along
    /// the `negative z-axis`.
    /// @param far the distance along the `negative z-axis` of the far plane from the
    /// eye in eye space. The far plane is a plane parallel to the `xy-plane` along
    /// the `negative z-axis`.
    ///
    /// @return an orthographic projection matrix.
    glm::mat4x4 orthographic_frustum_rh(float left, float right, float bottom, float top, float near, float far);

    /// @brief Construct a new orthographic projection transformation mapping from 
    /// an eye space with a left-handed coordinate system to a clip space with a 
    /// left-handed coordinate coordinate system compatible with Metal's normalized 
    /// device coordinates.
    ///
    /// @details The source eye space coordinate system is a left-handed coordinate 
    /// system with `(x, y, z)` coordinates with the following properties:
    /// @li The camera `x-axis` faces right.
    /// @li The camera `y-axis` faces up.
    /// @li The camera `positive z-axis` faces the forward direction.
    /// The target clip space coordinate system is a left-handed coordinate
    /// system with `(x, y, z)` coordinates with the following properties:
    /// @li The clip space `x-axis` faces right.
    /// @li The clip space `y-axis` faces up.
    /// @li The clip space `z-axis` faces the camera forward direction.
    /// The transformation maps the eye space volume 
    /// `[left, right] x [bottom, top] x [near, far]` to the normalized device coordinates
    /// `[-1, -1] x [-1, 1] x [0, 1]`. The projection matrix is given by
    /// @code{.unparsed}
    /// [ m[0, 0]  0        0        m[3, 0] ]
    /// [ 0        m[1, 1]  0        m[3, 1] ]
    /// [ 0        0        m[2, 2]  m[3, 2] ]
    /// [ 0        0        0        1       ]
    /// @endcode
    /// where
    /// @code{.unparsed}
    /// m[0, 0] ==  2 / (right - left)
    /// m[3, 0] == -(right + left) / (right - left)
    /// m[1, 1] ==  2 / (top - bottom)
    /// m[3, 1] == -(top + bottom) / (top - bottom)
    /// m[2, 2] ==  1 / (far - near)
    /// m[3, 2] == -near / (far - near)
    /// @endcode
    /// where the matrix entries are indexed in column-major order. The input 
    /// parameters satisfy the following pre-conditions to generate a valid 
    /// orthographic projection matrix.
    /// @pre left < right
    /// @pre bottom < top
    /// @pre 0 < near < far
    /// 
    /// @section Parameters
    /// @param left the horizontal position of the left plane in eye space.
    /// The left plane is a plane parallel to the `yz-plane` along the `x-axis`.
    /// @param right the horizontal position of the right plane in eye space.
    /// The right plane is a plane parallel to the `yz-plane` along the `x-axis`. 
    /// @param bottom the vertical position of the bottom plane in eye space.
    /// The bottom plane is a plane parallel to the `zx-plane` along the `y-axis`.
    /// @param top the vertical position of the top plane in eye space.
    /// The top plane is a plane parallel to the `zx-plane` along the `positive y-axis`.
    /// @param near the distance along the `positive z-axis` of the near plane from the
    /// eye in eye space. The near plane is a plane parallel to the `xy-plane` along
    /// the `positive z-axis`.
    /// @param far the distance along the `positive z-axis` of the far plane from the
    /// eye in eye space. The far plane is a plane parallel to the `xy-plane` along
    /// the `positive z-axis`.
    ///
    /// @return an orthographic projection matrix.
    glm::mat4x4 orthographic_frustum_lh(float left, float right, float bottom, float top, float near, float far);

    /// @brief Construct a new perspective field of view projection transformation 
    /// mapping from an eye space with a right-handed coordinate system to a clip space 
    /// with a left-handed coordinate coordinate system compatible with Metal's 
    /// normalized device coordinates.
    ///
    /// @details The source eye space coordinate system is a right-handed coordinate 
    /// system with `(x, y, z)` coordinates with the following properties:
    /// @li The camera space `x-axis` faces right.
    /// @li The camera space `y-axis` faces up.
    /// @li The camera space forward direction faces the `negative z-axis`.
    /// @li The camera `z-axis` faces the negative forward direction.
    /// The target clip space coordinate system is a left-handed coordinate
    /// system with `(x, y, z)` coordinates with the following properties:
    /// @li The clip space `x-axis` faces right.
    /// @li The clip space `y-axis` faces up.
    /// @li The clip space `z-axis` faces the camera forward direction.
    /// In particular, we map the eye space `negative z-axis` to the clip space 
    /// `positive z-axis` by changing the sign of the eye space `z` coordinate. This 
    /// variant of the perspective projection matrix is parametrized using the vertical 
    /// field of view angle `fovyRadians` and the aspect ratio `aspectRatio`. The 
    /// aspect ratio `aspectRatio` is the ratio of the width of the camera viewport to 
    /// the height of the camera viewport. Here
    /// @code{.unparsed} 
    /// tan(fovyRadians) == top / near
    /// aspectRatio == right / top
    /// @endcode
    /// The transformation maps the eye space frustum volume contained in 
    /// `[-right, right] x [-top, top] x [-far, -near]` to the normalized device 
    /// coordinates `[-1, -1] x [-1, 1] x [0, 1]`. The projection matrix is given 
    /// by
    /// @code{.unparsed}
    /// [ m[0, 0]  0         0        0       ]
    /// [ 0        m[1, 1]   0        0       ]
    /// [ 0        0         m[2, 2]  m[3, 2] ]
    /// [ 0        0        -1        0       ]
    /// @endcode
    /// where
    /// @code{.unparsed}
    /// m[0, 0] ==  1 / (aspectRatio * tan(fovy / 2))
    /// m[1, 1] ==  1 / tan(fovy / 2)
    /// m[2, 2] == -far / (far - near)
    /// m[3, 2] == -(far * near) / (far - near)
    /// @endcode
    /// where the matrix entries are indexed in column-major order. The input 
    /// parameters satisfy the following pre-conditions to generate a valid 
    /// perspective projection matrix.
    /// @pre fovyRadians > 0
    /// @pre aspectRatio > 0
    /// @pre 0 < near < far
    /// 
    /// @section Parameters
    /// @param fovyRadians the vertical angle in radians of the symmetric viewing frustum
    /// centered at the eye position in the `xy-plane`.
    /// @param aspectRatio the ratio of the width of the symmmetric viewing frustum to the
    /// height of the symmetric viewing frustum.
    /// @param near the distance along the `negative z-axis` of the near plane from the
    /// eye in eye space. The near plane is a plane parallel to the `xy-plane` along
    /// the `negative z-axis`.
    /// @param far the distance along the `negative z-axis` of the far plane from the
    /// eye in eye space. The far plane is a plane parallel to the `xy-plane` along
    /// the `negative z-axis`.
    ///
    /// @return a symmetric perspective projection matrix.
    glm::mat4x4 perspective_fov_rh(float fovyRadians, float aspectRatio, float near, float far);

    /// @brief Construct a new perspective field of view projection transformation 
    /// mapping from an eye space with a left-handed coordinate system to a clip space 
    /// with a left-handed coordinate coordinate system compatible with Metal's 
    /// normalized device coordinates.
    ///
    /// @details The source eye space coordinate system is a left-handed coordinate 
    /// system with `(x, y, z)` coordinates with the following properties:
    /// @li The camera space `x-axis` faces right.
    /// @li The camera space `y-axis` faces up.
    /// @li The camera space forward direction faces the `positive z-axis`.
    /// The target clip space coordinate system is a left-handed coordinate
    /// system with `(x, y, z)` coordinates with the following properties:
    /// @li The clip space `x-axis` faces right.
    /// @li The clip space `y-axis` faces up.
    /// @li The clip space `z-axis` faces the camera forward direction.
    /// In particular, we map the eye space `positive z-axis` to the clip space 
    /// `positive z-axis` by changing the sign of the eye space `z` coordinate. This 
    /// variant of the perspective projection matrix is parametrized using the vertical 
    /// field of view angle `fovyRadians` and the aspect ratio `aspectRatio`. The 
    /// aspect ratio `aspectRatio` is the ratio of the width of the camera viewport to 
    /// the height of the camera viewport. Here
    /// @code{.unparsed} 
    /// tan(fovyRadians) == top / near
    /// aspectRatio == right / top
    /// @endcode
    /// The transformation maps the eye space frustum volume contained in 
    /// `[-right, right] x [-top, top] x [near, far]` to the normalized device 
    /// coordinates `[-1, -1] x [-1, 1] x [0, 1]`. The projection matrix is given 
    /// by
    /// @code{.unparsed}
    /// [ m[0, 0]  0        0        0       ]
    /// [ 0        m[1, 1]  0        0       ]
    /// [ 0        0        m[2, 2]  m[3, 2] ]
    /// [ 0        0        1        0       ]
    /// @endcode
    /// where
    /// @code{.unparsed}
    /// m[0, 0] ==  1 / (aspectRatio * tan(fovy / 2))
    /// m[1, 1] ==  1 / tan(fovy / 2)
    /// m[2, 2] ==  far / (far - near)
    /// m[3, 2] == -(far * near) / (far - near)
    /// @endcode
    /// where the matrix entries are indexed in column-major order. The input 
    /// parameters satisfy the following pre-conditions to generate a valid 
    /// perspective projection matrix.
    /// @pre fovyRadians > 0
    /// @pre aspectRatio > 0
    /// @pre 0 < near < far
    /// 
    /// @section Parameters
    /// @param fovyRadians the vertical angle in radians of the symmetric viewing frustum
    /// centered at the eye position in the `xy-plane`.
    /// @param aspectRatio the ratio of the width of the symmmetric viewing frustum to the
    /// height of the symmetric viewing frustum.
    /// @param near the distance along the `positive z-axis` of the near plane from the
    /// eye in eye space. The near plane is a plane parallel to the `xy-plane` along
    /// the `positive z-axis`.
    /// @param far the distance along the `positive z-axis` of the far plane from the
    /// eye in eye space. The far plane is a plane parallel to the `xy-plane` along
    /// the `positive z-axis`.
    ///
    /// @return a symmetric perspective projection matrix.
    glm::mat4x4 perspective_fov_lh(float fovyRadians, float aspectRatio, float near, float far);

    /// @brief Construct a new perspective projection transformation mapping from 
    /// an eye space with a right-handed coordinate system to a clip space with a 
    /// left-handed coordinate coordinate system compatible with Metal's normalized 
    /// device coordinates.
    ///
    /// @details The source eye space coordinate system is a right-handed coordinate 
    /// system with `(x, y, z)` coordinates with the following properties:
    /// @li The camera space `x-axis` faces right.
    /// @li The camera space `y-axis` faces up.
    /// @li The camera space forward direction faces the `negative z-axis`.
    /// @li The camera `z-axis` faces the negative forward direction.
    /// The target clip space coordinate system is a left-handed coordinate
    /// system with `(x, y, z)` coordinates with the following properties:
    /// @li The clip space `x-axis` faces right.
    /// @li The clip space `y-axis` faces up.
    /// @li The clip space `z-axis` faces the camera forward direction.
    /// In particular, we map the eye space `z-axis` to the clip space `z-axis` by
    /// changing the sign of the eye space `z` coordinate. The transformation maps 
    /// the eye space frustum volume contained in `[left, right] x [bottom, top] x [-far, -near]` 
    /// to the normalized device coordinates `[-1, -1] x [-1, 1] x [0, 1]`. The projection
    /// matrix is given by
    /// @code{.unparsed}
    /// [ m[0, 0]  0         m[2, 0]  0       ]
    /// [ 0        m[1, 1]   m[2, 1]  0       ]
    /// [ 0        0         m[2, 2]  m[3, 2] ]
    /// [ 0        0        -1        0       ]
    /// @endcode
    /// where
    /// @code{.unparsed}
    /// m[0, 0] ==  2 * near / (right - left)
    /// m[2, 0] ==  (right + left) / (right - left)
    /// m[1, 1] ==  2 * near / (top - bottom)
    /// m[2, 1] ==  (top + bottom) / (top - bottom)
    /// m[2, 2] == -far / (far - near)
    /// m[3, 2] == -(far * near) / (far - near)
    /// @endcode
    /// where the matrix entries are indexed in column-major order. The input 
    /// parameters satisfy the following pre-conditions to generate a valid 
    /// perspective projection matrix.
    /// @pre left < right
    /// @pre bottom < top
    /// @pre 0 < near < far
    /// 
    /// @section Parameters
    /// @param left the horizontal position of the left plane in eye space.
    /// The left plane is a plane parallel to the `yz-plane` along the `x-axis`.
    /// @param right the horizontal position of the right plane in eye space.
    /// The right plane is a plane parallel to the `yz-plane` along the `x-axis`. 
    /// @param bottom the vertical position of the bottom plane in eye space.
    /// The bottom plane is a plane parallel to the `zx-plane` along the `y-axis`.
    /// @param top the vertical position of the top plane in eye space.
    /// The top plane is a plane parallel to the `zx-plane` along the `y-axis`.
    /// @param near the distance along the `negative z-axis` of the near plane from the
    /// eye in eye space. The near plane is a plane parallel to the `xy-plane` along
    /// the `negative z-axis`.
    /// @param far the distance along the `negative z-axis` of the far plane from the
    /// eye in eye space. The far plane is a plane parallel to the `xy-plane` along
    /// the `negative z-axis`.
    ///
    /// @return a perspective projection matrix.
    glm::mat4x4 perspective_frustum_rh(float left, float right, float bottom, float top, float near, float far);

    /// @brief Construct a new perspective projection transformation mapping from 
    /// an eye space with a left-handed coordinate system to a clip space with a 
    /// left-handed coordinate coordinate system compatible with Metal's normalized 
    /// device coordinates.
    ///
    /// @details The source eye space coordinate system is a left-handed coordinate 
    /// system with `(x, y, z)` coordinates with the following properties:
    /// @li The camera `x-axis` faces right.
    /// @li The camera `y-axis` faces up.
    /// @li The camera `positive z-axis` faces the forward direction.
    /// The target clip space coordinate system is a left-handed coordinate
    /// system with `(x, y, z)` coordinates with the following properties:
    /// @li The clip space `x-axis` faces right.
    /// @li The clip space `y-axis` faces up.
    /// @li The clip space `z-axis` faces the camera forward direction.
    /// The transformation maps the eye space volume 
    /// `[left, right] x [bottom, top] x [near, far]` to the normalized device coordinates
    /// `[-1, -1] x [-1, 1] x [0, 1]`. The projection matrix is given by
    /// @code{.unparsed}
    /// [ m[0, 0]  0        m[2, 0]  0       ]
    /// [ 0        m[1, 1]  m[2, 1]  0       ]
    /// [ 0        0        m[2, 2]  m[3, 2] ]
    /// [ 0        0        1        0       ]
    /// @endcode
    /// where
    /// @code{.unparsed}
    /// m[0, 0] ==  2 * near / (right - left)
    /// m[2, 0] == -(right + left) / (right - left)
    /// m[1, 1] ==  2 * near / (top - bottom)
    /// m[2, 1] == -(top + bottom) / (top - bottom)
    /// m[2, 2] ==  far / (far - near)
    /// m[3, 2] == -(far * near) / (far - near)
    /// @endcode
    /// where the matrix entries are indexed in column-major order. The input 
    /// parameters satisfy the following pre-conditions to generate a valid 
    /// perspective projection matrix.
    /// @pre left < right
    /// @pre bottom < top
    /// @pre 0 < near < far
    /// 
    /// @section Parameters
    /// @param left the horizontal position of the left plane in eye space.
    /// The left plane is a plane parallel to the `yz-plane` along the `x-axis`.
    /// @param right the horizontal position of the right plane in eye space.
    /// The right plane is a plane parallel to the `yz-plane` along the `x-axis`. 
    /// @param bottom the vertical position of the bottom plane in eye space.
    /// The bottom plane is a plane parallel to the `zx-plane` along the `y-axis`.
    /// @param top the vertical position of the top plane in eye space.
    /// The top plane is a plane parallel to the `zx-plane` along the `y-axis`.
    /// @param near the distance along the `positive z-axis` of the near plane from the
    /// eye in eye space. The near plane is a plane parallel to the `xy-plane` along
    /// the `positive z-axis`.
    /// @param far the distance along the `positive z-axis` of the far plane from the
    /// eye in eye space. The far plane is a plane parallel to the `xy-plane` along
    /// the `positive z-axis`.
    ///
    /// @return a perspective projection matrix.
    glm::mat4x4 perspective_frustum_lh(float left, float right, float bottom, float top, float near, float far);
}

#endif /* GLM_METAL_H */
