//
//  Camera.h
//
//  Created by Stef Tervelde on 29.06.22.
//
#import <Foundation/Foundation.h>
#import <simd/simd.h>

#ifndef Camera_h
#define Camera_h

/**
 * Camera represents the eye through which the scene is viewed.
 * <p>
 * A Camera has a position and orientation and controls the projection and exposure parameters.
 *
 * <h1><u>Creation and destruction</u></h1>
 *
 * In Filament, Camera is a component that must be associated with an entity. To do so,
 * use {@link Engine#createCamera(int)}. A Camera component is destroyed using
 * {@link Engine#destroyCameraComponent(int Entity)} ()}.
 *
 * <pre>
 *  Camera myCamera = engine.createCamera(myCameraEntity);
 *  myCamera.setProjection(45, 16.0/9.0, 0.1, 1.0);
 *  myCamera.lookAt(0, 1.60, 1,
 *                  0, 0, 0,
 *                  0, 1, 0);
 *  engine.destroyCameraComponent(myCameraEntity);
 * </pre>
 *
 *
 * <h1><u>Coordinate system</u></h1>
 *
 * The camera coordinate system defines the <b>view space</b>. The camera points towards its -z axis
 * and is oriented such that its top side is in the direction of +y, and its right side in the
 * direction of +x.
 * <p>
 * Since the <b>near</b> and <b>far</b> planes are defined by the distance from the camera,
 * their respective coordinates are -distance<sub>near</sub> and -distance<sub>far</sub>.
 *
 * <h1><u>Clipping planes</u></h1>
 *
 * The camera defines six <b>clipping planes</b> which together create a <b>clipping volume</b>. The
 * geometry outside this volume is clipped.
 * <p>
 * The clipping volume can either be a box or a frustum depending on which projection is used,
 * respectively {@link Projection#ORTHO ORTHO} or {@link Projection#PERSPECTIVE PERSPECTIVE}.
 * The six planes are specified either directly or indirectly using  {@link #setProjection} or
 * {@link #setLensProjection}.
 * <p>
 * The six planes are:
 * <ul>
 * <li> left    </li>
 * <li> right   </li>
 * <li> bottom  </li>
 * <li> top     </li>
 * <li> near    </li>
 * <li> far     </li>
 * </ul>
 * <p>
 *
 * To increase the depth-buffer precision, the <b>far</b> clipping plane is always assumed to be at
 * infinity for rendering. That is, it is not used to clip geometry during rendering.
 * However, it is used during the culling phase (objects entirely behind the <b>far</b>
 * plane are culled).
 *
 * <h1><u>Choosing the <b>near</b> plane distance</u></h1>
 *
 * The <b>near</b> plane distance greatly affects the depth-buffer resolution.
 * <p>
 *
 * Example: Precision at 1m, 10m, 100m and 1Km for various near distances assuming a 32-bit float
 * depth-buffer
 *
 * <center>
 * <table border="1">
 *     <tr>
 *         <th> near (m) </th><th> 1 m </th><th> 10 m </th><th> 100 m</th><th> 1 Km </th>
 *     </tr>
 *     <tr>
 *         <td>0.001</td><td>7.2e-5</td><td>0.0043</td><td>0.4624</td><td>48.58</td>
 *     </tr>
 *     <tr>
 *         <td>0.01</td><td>6.9e-6</td><td>0.0001</td><td>0.0430</td><td>4.62</td>
 *     </tr>
 *     <tr>
 *         <td>0.1</td><td>3.6e-7</td><td>7.0e-5</td><td>0.0072</td><td>0.43</td>
 *     </tr>
 *     <tr>
 *         <td>1.0</td><td>0</td><td>3.8e-6</td><td>0.0007</td><td>0.07</td>
 *     </tr>
 * </table>
 * </center>
 * <p>
 *
 * As can be seen in the table above, the depth-buffer precision drops rapidly with the
 * distance to the camera.
 * <p>
 * Make sure to pick the highest <b>near</b> plane distance possible.
 *
 *
 * <h1><u>Exposure</u></h1>
 *
 * The Camera is also used to set the scene's exposure, just like with a real camera. The lights
 * intensity and the Camera exposure interact to produce the final scene's brightness.
 *
 * @see View
 */

@interface Camera : NSObject

typedef NS_ENUM(NSInteger, Projection) {
    ProjectionPerspective = 0,
    ProjectionOrtho = 1
};
typedef NS_ENUM(NSInteger, Fov) {
    ProjectionVertical = 0,
    ProjectionHorizontal = 1
};

@property (nonatomic, readonly, nonnull) void* camera NS_SWIFT_UNAVAILABLE("Don't access the raw pointers");
- (nonnull id) init: (nonnull void*) camera NS_SWIFT_UNAVAILABLE("Instances are created internally");
- (nonnull id) init NS_UNAVAILABLE;

/**
 * Sets the projection matrix from a frustum defined by six planes.
 *
 * @param projection    type of projection to use
 *
 * @param left          distance in world units from the camera to the left plane,
 *                      at the near plane. Precondition: <code>left</code> != <code>right</code>
 *
 * @param right         distance in world units from the camera to the right plane,
 *                      at the near plane. Precondition: <code>left</code> != <code>right</code>
 *
 * @param bottom        distance in world units from the camera to the bottom plane,
 *                      at the near plane. Precondition: <code>bottom</code> != <code>top</code>
 *
 * @param top           distance in world units from the camera to the top plane,
 *                      at the near plane. Precondition: <code>bottom</code> != <code>top</code>
 *
 * @param near          distance in world units from the camera to the near plane.
 *                      The near plane's position in view space is z = -<code>near</code>.
 *                      Precondition:
 *                      <code>near</code> > 0 for {@link Projection#PERSPECTIVE} or
 *                      <code>near</code> != <code>far</code> for {@link Projection#ORTHO}.
 *
 * @param far           distance in world units from the camera to the far plane.
 *                      The far plane's position in view space is z = -<code>far</code>.
 *                      Precondition:
 *                      <code>far</code> > <code>near</code>
 *                              for {@link Projection#PERSPECTIVE} or
 *                      <code>far</code> != <code>near</code>
 *                              for {@link Projection#ORTHO}.
 *
 * <p>
 * These parameters are silently modified to meet the preconditions above.
 *
 * @see Projection
 */
- (void) setProjection: (Projection) projection :(double) left :(double) right :(double) bottom :(double) top :(double) near :(double) far;
/**
 * Sets the projection matrix from the field-of-view.
 *
 * @param fovInDegrees  full field-of-view in degrees.
 *                      0 < <code>fovInDegrees</code> < 180
 *
 * @param aspect        aspect ratio width/height. <code>aspect</code> > 0
 *
 * @param near          distance in world units from the camera to the near plane.
 *                      The near plane's position in view space is z = -<code>near</code>.
 *                      Precondition:
 *                      <code>near</code> > 0 for {@link Projection#PERSPECTIVE} or
 *                      <code>near</code> != <code>far</code> for {@link Projection#ORTHO}.
 *
 * @param far           distance in world units from the camera to the far plane.
 *                      The far plane's position in view space is z = -<code>far</code>.
 *                      Precondition:
 *                      <code>far</code> > <code>near</code>
 *                              for {@link Projection#PERSPECTIVE} or
 *                      <code>far</code> != <code>near</code>
 *                              for {@link Projection#ORTHO}.
 *
 * @param direction    direction of the field-of-view parameter.
 * <p>
 * These parameters are silently modified to meet the preconditions above.
 *
 * @see Fov
 */
- (void) setProjection: (double) fovInDegrees :(double) aspect :(double) near :(double) far :(Fov) direction;
/**
 * Sets the projection matrix from the focal length.
 *
 * @param focalLength   lens's focal length in millimeters. <code>focalLength</code> > 0
 *
 * @param aspect        aspect ratio width/height. <code>aspect</code> > 0
 *
 * @param near          distance in world units from the camera to the near plane.
 *                      The near plane's position in view space is z = -<code>near</code>.
 *                      Precondition:
 *                      <code>near</code> > 0 for {@link Projection#PERSPECTIVE} or
 *                      <code>near</code> != <code>far</code> for {@link Projection#ORTHO}.
 *
 * @param far           distance in world units from the camera to the far plane.
 *                      The far plane's position in view space is z = -<code>far</code>.
 *                      Precondition:
 *                      <code>far</code> > <code>near</code>
 *                              for {@link Projection#PERSPECTIVE} or
 *                      <code>far</code> != <code>near</code>
 *                              for {@link Projection#ORTHO}.
 *
 */
- (void) setLensProjection: (double) focalLength :(double) aspect :(double) near :(double) far;

/**
 * Sets a custom projection matrix.
 *
 * <p>The projection matrix must define an NDC system that must match the OpenGL convention,
 * that is all 3 axis are mapped to [-1, 1].</p>
 *
 * @param inProjection  custom projection matrix for rendering and culling
 *
 * @param near          distance in world units from the camera to the near plane.
 *                      The near plane's position in view space is z = -<code>near</code>.
 *                      Precondition:
 *                      <code>near</code> > 0 for {@link Projection#PERSPECTIVE} or
 *                      <code>near</code> != <code>far</code> for {@link Projection#ORTHO}.
 *
 * @param far           distance in world units from the camera to the far plane.
 *                      The far plane's position in view space is z = -<code>far</code>.
 *                      Precondition:
 *                      <code>far</code> > <code>near</code>
 *                              for {@link Projection#PERSPECTIVE} or
 *                      <code>far</code> != <code>near</code>
 *                              for {@link Projection#ORTHO}.
 */
- (void) setCustomProjection: (simd_double4x4) inProjection :(double) near :(double) far;
/**
* Sets a custom projection matrix.
*
* <p>The projection matrices must define an NDC system that must match the OpenGL convention,
* that is all 3 axis are mapped to [-1, 1].</p>
*
* @param inProjection              custom projection matrix for rendering.
*
* @param inProjectionForCulling    custom projection matrix for culling.
*
* @param near          distance in world units from the camera to the near plane.
*                      The near plane's position in view space is z = -<code>near</code>.
*                      Precondition:
*                      <code>near</code> > 0 for {@link Projection#PERSPECTIVE} or
*                      <code>near</code> != <code>far</code> for {@link Projection#ORTHO}.
*
* @param far           distance in world units from the camera to the far plane.
*                      The far plane's position in view space is z = -<code>far</code>.
*                      Precondition:
*                      <code>far</code> > <code>near</code>
*                              for {@link Projection#PERSPECTIVE} or
*                      <code>far</code> != <code>near</code>
*                              for {@link Projection#ORTHO}.
*/
- (void) setCustomProjection: (simd_double4x4) inProjection :(simd_double4x4) inProjectionForCulling :(double) near :(double) far;
/**
 * Sets an additional matrix that scales the projection matrix.
 *
 * <p>This is useful to adjust the aspect ratio of the camera independent from its projection.
 * First, pass an aspect of 1.0 to setProjection. Then set the scaling with the desired aspect
 * ratio:<br>
 *
 * <code>
 *     double aspect = width / height;
 *
 *     // with Fov.HORIZONTAL passed to setProjection:
 *     camera.setScaling(1.0, aspect);
 *
 *     // with Fov.VERTICAL passed to setProjection:
 *     camera.setScaling(1.0 / aspect, 1.0);
 * </code>
 *
 * By default, this is an identity matrix.
 * </p>
 *
 * @param xscaling  horizontal scaling to be applied after the projection matrix.
 * @param yscaling  vertical scaling to be applied after the projection matrix.
 *
 * @see Camera#setProjection
 * @see Camera#setLensProjection
 * @see Camera#setCustomProjection
 */
- (void) setScaling: (double) xscaling :(double) yscaling;
/**
 * Sets an additional matrix that shifts (translates) the projection matrix.
 * <p>
 * The shift parameters are specified in NDC coordinates, that is, if the translation must
 * be specified in pixels, the xshift and yshift parameters be scaled by 1.0 / viewport.width
 * and 1.0 / viewport.height respectively.
 * </p>
 *
 * @param xshift    horizontal shift in NDC coordinates applied after the projection
 * @param yshift    vertical shift in NDC coordinates applied after the projection
 *
 * @see Camera#setProjection
 * @see Camera#setLensProjection
 * @see Camera#setCustomProjection
 */
- (void) setShift: (double) xshift :(double) yshift;

/**
 * Sets the camera's view matrix.
 * <p>
 * Helper method to set the camera's entity transform component.
 * Remember that the Camera "looks" towards its -z axis.
 * <p>
 * This has the same effect as calling:
 *
 * <pre>
 *  engine.getTransformManager().setTransform(
 *          engine.getTransformManager().getInstance(camera->getEntity()), viewMatrix);
 * </pre>
 *
 * @param viewMatrix The camera position and orientation provided as a <b>rigid transform</b> matrix.
 */
// - (void) setModelMatrix: (nonnull float[]) viewMatrix;
/**
 * Sets the camera's view matrix.
 * <p>
 * Helper method to set the camera's entity transform component.
 * Remember that the Camera "looks" towards its -z axis.
 * <p>
 *
 * @param viewMatrix The camera position and orientation provided as a <b>rigid transform</b> matrix.
 */
- (void) setModelMatrix: (simd_double4x4) viewMatrix;

/**
 * Sets the camera's view matrix.
 *
 * @param eyeX      x-axis position of the camera in world space
 * @param eyeY      y-axis position of the camera in world space
 * @param eyeZ      z-axis position of the camera in world space
 * @param centerX   x-axis position of the point in world space the camera is looking at
 * @param centerY   y-axis position of the point in world space the camera is looking at
 * @param centerZ   z-axis position of the point in world space the camera is looking at
 * @param upX       x-axis coordinate of a unit vector denoting the camera's "up" direction
 * @param upY       y-axis coordinate of a unit vector denoting the camera's "up" direction
 * @param upZ       z-axis coordinate of a unit vector denoting the camera's "up" direction
 */
- (void) lookAt: (simd_double3) eye :(simd_double3) center :(simd_double3) up;

- (double) getNear;

- (double) getCullingFar;


/**
 * Retrieves the camera's projection matrix. The projection matrix used for rendering always has
 * its far plane set to infinity. This is why it may differ from the matrix set through
 * setProjection() or setLensProjection().
 *
 * @return A simd_double4x4 containing the camera's projection.
 */
- (simd_double4x4) getProjectionMatrix;

/**
 * Retrieves the camera's culling matrix. The culling matrix is the same as the projection
 * matrix, except the far plane is finite.
 *
 * @return A simd_double4x4 containing the camera's projection.
 */
- (simd_double4x4) getCullingProjectionMatrix;

/**
 * Retrieves the camera's model matrix. The model matrix encodes the camera position and
 * orientation, or pose.
 * @return A  simd_double4x4 containing the camera's pose
 */

- (simd_double4x4) getModelMatrix;

/**
 * Retrieves the camera's view matrix. The view matrix is the inverse of the model matrix.
 *
 * @return A  simd_double4x4 containing the camera's view
 */

- (simd_double4x4) getViewMatrix;


- (simd_double3) getPosition;

- (simd_double3) getLeftVector;

- (simd_double3) getUpVector;

- (simd_double3) getForwardVector;
/**
 * Sets this camera's exposure (default is f/16, 1/125s, 100 ISO)
 *
 * The exposure ultimately controls the scene's brightness, just like with a real camera.
 * The default values provide adequate exposure for a camera placed outdoors on a sunny day
 * with the sun at the zenith.
 *
 * With the default parameters, the scene must contain at least one Light of intensity
 * similar to the sun (e.g.: a 100,000 lux directional light) and/or an indirect light
 * of appropriate intensity (30,000).
 *
 * @param aperture      Aperture in f-stops, clamped between 0.5 and 64.
 *                      A lower aperture value increases the exposure, leading to
 *                      a brighter scene. Realistic values are between 0.95 and 32.
 *
 * @param shutterSpeed  Shutter speed in seconds, clamped between 1/25,000 and 60.
 *                      A lower shutter speed increases the exposure. Realistic values are
 *                      between 1/8000 and 30.
 *
 * @param sensitivity   Sensitivity in ISO, clamped between 10 and 204,800.
 *                      A higher sensitivity increases the exposure. Realistic values are
 *                      between 50 and 25600.
 *
 * @see LightManager
 * @see #setExposure(float)
 */

- (void) setExposure: (double) aperture :(double) shutterSpeed :(double) sensitivity;

- (double) getAperture;

- (double) getShutterSpeed;

- (double) getFocalLength;


/**
 * Set the camera focus distance in world units
 * @param distance Distance from the camera to the focus plane in world units. Must be
 *                 positive and larger than the camera's near clipping plane.
 */
- (void) setFocusDistance: (double) distance;

- (double) getFocusDistance;

/**
 * Helper to compute the effective focal length taking into account the focus distance
 *
 * @param focalLength       focal length in any unit (e.g. [m] or [mm])
 * @param focusDistance     focus distance in same unit as focalLength
 * @return                  the effective focal length in same unit as focalLength
 */
+ (double) computeEffectiveFocalLength: (double) focalLength :(double)focusDistance;

/**
 * Helper to compute the effective field-of-view taking into account the focus distance
 *
 * @param fovInDegrees      full field of view in degrees
 * @param focusDistance     focus distance in meters [m]
 * @return                  effective full field of view in degrees
 */
+ (double) computeEffectiveFov: (double) fovInDegrees :(double) focusDistance;



@end

#endif /* Camera_h */
