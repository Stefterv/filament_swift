//
//  MaterialInstance.mm

//  Created by Stef Tervelde on 30.06.22.
//
#import "Bindings/Filament/MaterialInstance.h"
#import <filament/MaterialInstance.h>
#import <filament/Texture.h>
#import <filament/TextureSampler.h>
#import "../Math.h"

@implementation MaterialInstance{
    filament::MaterialInstance* nativeInstance;
}

- (id) init:(void *)instance{
    self->_instance = instance;
    self->nativeInstance = (filament::MaterialInstance*)instance;
    return self;
}

+ (instancetype)duplicate:(MaterialInstance *)instance{
    auto duplicate = filament::MaterialInstance::duplicate( (filament::MaterialInstance*)  instance.instance);
    return [[MaterialInstance alloc] init: duplicate];
}
- (NSString *)getName{
    return [[NSString alloc] initWithUTF8String: nativeInstance->getName()];
}
- (void)setParameterBool:(NSString *)name :(bool)boolean{
    nativeInstance->setParameter(name.UTF8String, boolean);
}
- (void)setParameterFloat:(NSString *)name :(float)decimal{
    nativeInstance->setParameter(name.UTF8String, decimal);
}
- (void)setParameterInt:(NSString *)name :(int)integer{
    nativeInstance->setParameter(name.UTF8String, integer);
}
- (void)setParameterBool2:(NSString *)name :(bool)boolean1 :(bool)boolean2{
    nativeInstance->setParameter(name.UTF8String, filament::math::bool2(boolean1, boolean2));
}
- (void)setParameterFloat2:(NSString *)name :(simd_float2)vector{
    nativeInstance->setParameter(name.UTF8String, filament::math::float2(vector.x, vector.y));
}
- (void)setParameterInt2:(NSString *)name :(simd_int2)vector{
    nativeInstance->setParameter(name.UTF8String, filament::math::int2(vector.x, vector.y));
}
- (void)setParameterBool3:(NSString *)name :(bool)boolean1 :(bool)boolean2 :(bool)boolean3{
    nativeInstance->setParameter(name.UTF8String, filament::math::bool3(boolean1, boolean2, boolean3));
}
- (void)setParameterFloat3:(NSString *)name :(simd_float3)vector{
    nativeInstance->setParameter(name.UTF8String, filament::math::float3(vector.x, vector.y, vector.z));
}
- (void)setParameterInt3:(NSString *)name :(simd_int3)vector{
    nativeInstance->setParameter(name.UTF8String, filament::math::int3(vector.x, vector.y, vector.z));
}
- (void)setParameterBool4:(NSString *)name :(bool)boolean1 :(bool)boolean2 :(bool)boolean3 :(bool)boolean4{
    nativeInstance->setParameter(name.UTF8String, filament::math::bool4(boolean1, boolean2, boolean3, boolean4));
}
- (void)setParameterFloat4:(NSString *)name :(simd_float4)vector{
    nativeInstance->setParameter(name.UTF8String, filament::math::float4(vector.x, vector.y, vector.z, vector.w));
}
- (void)setParameterInt4:(NSString *)name :(simd_int4)vector{
    nativeInstance->setParameter(name.UTF8String, filament::math::int4(vector.x, vector.y, vector.z, vector.w));
}
- (void)setParameterMat3f:(NSString *)name :(simd_float3x3)vector{
    nativeInstance->setParameter(name.UTF8String, MAT3F_FROM_SIMD(vector));
}
- (void)setParameterMat4f:(NSString *)name :(simd_float4x4)vector{
    nativeInstance->setParameter(name.UTF8String, MAT4F_FROM_SIMD(vector));
}
- (void)setParameterTexture:(NSString *)name :(Texture *)texture :(TextureSampler *)sampler{
    nativeInstance->setParameter(name.UTF8String, (filament::Texture*) texture.texture, *(filament::TextureSampler*) sampler.sampler);
}
- (void)setScissor:(int)left :(int)bottom :(int)width :(int)height{
    nativeInstance->setScissor(left, bottom, width, height);
}
- (void)unsetScissor{
    nativeInstance->unsetScissor();
}
- (void)setPolygonOffset:(double)scale :(double)constant{
    nativeInstance->setPolygonOffset(scale, constant);
}
- (void)setMaskThreshold:(double)threshold{
    nativeInstance->setMaskThreshold(threshold);
}
- (void)setSpecularAntiAliasingVariance:(double)variance{
    nativeInstance->setSpecularAntiAliasingVariance(variance);
}
- (void)setSpecularAntiAliasingThreshold:(double)threshold{
    nativeInstance->setSpecularAntiAliasingThreshold(threshold);
}
- (void)setDoubleSided:(bool)doubleSided{
    nativeInstance->setDoubleSided(doubleSided);
}
- (void)setCullingMode:(uint8_t)mode{
    nativeInstance->setCullingMode((filament::backend::CullingMode) mode);
}
- (void)setColorWrite:(bool)enable{
    nativeInstance->setColorWrite(enable);
}
- (void)setDepthWrite:(bool)enable{
    nativeInstance->setDepthWrite(enable);
}
- (void)setDepthCulling:(bool)enable{
    nativeInstance->setDepthCulling(enable);
}

@end
