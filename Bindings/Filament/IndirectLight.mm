//
//  IndirectLight.mm

//  Created by Stef Tervelde on 30.06.22.
//
#import "Bindings/Filament/IndirectLight.h"
#import <filament/IndirectLight.h>
#import <math/mat3.h>
#import "../Math.h"

@implementation IndirectLight{
    filament::IndirectLight* nativeLight;
}

- (id) init:(void *)light{
    self->_light = light;
    self->nativeLight = (filament::IndirectLight*)light;
    return self;
}

- (void)setIntensity:(double)intensity{
    nativeLight->setIntensity(intensity);
}
- (double)getIntensity{
    return nativeLight->getIntensity();
}

- (void)setRotation:(simd_double3x3)rotation{
    nativeLight->setRotation(MAT3F_FROM_SIMD(rotation));
}
- (simd_double3x3)getRotation{
    auto rotation = nativeLight->getRotation();
    return SIMD_DOUBLE3X3_FROM_MAT3X3(rotation);
}
- (Texture *)getReflectionsTexture{
    auto texture = nativeLight->getReflectionsTexture();
    return [[Texture alloc] init:&texture];
}
- (Texture *)getIrradianceTexture{
    auto texture = nativeLight->getIrradianceTexture();
    return [[Texture alloc] init:&texture];
}

+ (simd_double3) getDirectionEstimate:(simd_double3x3)sh{
    auto direction = filament::IndirectLight::getDirectionEstimate(FLOAT3X9_FROM_SIMD(sh));
    return simd_make_double3(direction.x, direction.y, direction.z);
}

+ (simd_double4)getColorEstimate:(simd_double3x3)sh :(simd_double3)direction{
    auto color = filament::IndirectLight::getColorEstimate(FLOAT3X9_FROM_SIMD(sh), FLOAT3_FROM_SIMD(direction));
    return simd_make_double4(color.x, color.y, color.z, color.w);
}



@end
