//
//  Camera.mm
//  
//
//  Created by Stef Tervelde on 29.06.22.
//

#import "Bindings/Filament/Camera.h"
#import <filament/Camera.h>
#import <math/mat2.h>
#import "../Math.h"

@implementation Camera{
    filament::Camera* nativeCamera;
}

- (id) init:(void *)camera{
    self->_camera = camera;
    self->nativeCamera = (filament::Camera*) camera;
    return self;
}

- (void)setProjection:(Projection)projection :(double)left :(double)right :(double)bottom :(double)top :(double)near :(double)far{
    nativeCamera->setProjection((filament::Camera::Projection) projection, left, right, bottom, top, near, far);
}

- (void)setProjection:(double)fovInDegrees :(double)aspect :(double)near :(double)far :(Fov)direction{
    nativeCamera->setProjection(fovInDegrees, aspect, near, far, (filament::Camera::Fov) direction);
}

- (void)setLensProjection:(double)focalLength :(double)aspect :(double)near :(double)far{
    nativeCamera->setLensProjection(focalLength, aspect, near, far);
}

- (void)setCustomProjection:(simd_double4x4)inProjection :(double)near :(double)far{
    nativeCamera->setCustomProjection(MAT4_FROM_SIMD(inProjection), near, far);
}

- (void)setCustomProjection:(simd_double4x4)inProjection :(simd_double4x4)inProjectionForCulling :(double)near :(double)far{
    nativeCamera->setCustomProjection(MAT4_FROM_SIMD(inProjection), MAT4_FROM_SIMD(inProjectionForCulling), near, far);
}

- (void)setScaling:(double)xscaling :(double)yscaling{
    nativeCamera->setScaling(filament::math::double2(xscaling, yscaling));
}

- (void)setShift:(double)xshift :(double)yshift{
    nativeCamera->setShift(filament::math::double2(xshift, yshift));
}

- (void)setModelMatrix:(simd_double4x4)viewMatrix{
    nativeCamera->setModelMatrix(MAT4_FROM_SIMD(viewMatrix));
}

- (void)lookAt:(simd_double3)eye :(simd_double3)center :(simd_double3)up{
    nativeCamera->lookAt(FLOAT3_FROM_SIMD(eye), FLOAT3_FROM_SIMD(center), FLOAT3_FROM_SIMD(up));
}

- (double)getNear{
    return nativeCamera->getNear();
}

- (double)getCullingFar{
    return nativeCamera->getCullingFar();
}

- (simd_double4x4)getProjectionMatrix{
    auto matrix = nativeCamera->getProjectionMatrix();
    return SIMD_DOUBLE4X4_FROM_MAT4(matrix);
}

- (simd_double4x4)getCullingProjectionMatrix{
    auto matrix = nativeCamera->getCullingProjectionMatrix();
    return SIMD_DOUBLE4X4_FROM_MAT4(matrix);
}

- (simd_double4x4)getModelMatrix{
    auto matrix = nativeCamera->getModelMatrix();
    return SIMD_DOUBLE4X4_FROM_MAT4(matrix);
}
- (simd_double4x4)getViewMatrix{
    auto matrix = nativeCamera->getViewMatrix();
    return SIMD_DOUBLE4X4_FROM_MAT4(matrix);
}

- (simd_double3)getPosition{
    auto position = nativeCamera->getPosition();
    return SIMD_DOUBLE3_FROM_FLOAT3(position);
}

- (simd_double3)getLeftVector{
    auto vector = nativeCamera->getLeftVector();
    return SIMD_DOUBLE3_FROM_FLOAT3(vector);
}
- (simd_double3)getUpVector{
    auto vector = nativeCamera->getUpVector();
    return SIMD_DOUBLE3_FROM_FLOAT3(vector);
}
- (simd_double3)getForwardVector{
    auto vector = nativeCamera->getForwardVector();
    return SIMD_DOUBLE3_FROM_FLOAT3(vector);
}
- (void)setExposure:(double)aperture :(double)shutterSpeed :(double)sensitivity{
    nativeCamera->setExposure(aperture, shutterSpeed, sensitivity);
}

- (double)getAperture{
    return nativeCamera->getAperture();
}
- (double)getShutterSpeed{
    return nativeCamera->getShutterSpeed();
}
- (double)getFocalLength{
    return nativeCamera->getFocalLength();
}
- (double)getFocusDistance{
    return nativeCamera->getFocusDistance();
}
- (void)setFocusDistance:(double)distance{
    nativeCamera->setFocusDistance(distance);
}
+ (double)computeEffectiveFov:(double)fovInDegrees :(double)focusDistance{
    return filament::Camera::computeEffectiveFov(fovInDegrees, focusDistance);
}
+ (double)computeEffectiveFocalLength:(double)focalLength :(double)focusDistance{
    return filament::Camera::computeEffectiveFocalLength(focalLength, focusDistance);
}

@end
