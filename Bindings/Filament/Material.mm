//
//  Material.mm

//  Created by Stef Tervelde on 30.06.22.
//
#import "Bindings/Filament/Material.h"
#import <filament/Material.h>
@implementation Parameter
@end


@implementation Material{
    filament::Material* nativeMaterial;
}

- (id) init:(void *)material{
    self->_material = material;
    self->nativeMaterial = (filament::Material*)material;
    return self;
}

- (MaterialInstance *)createInstance{
    return [[MaterialInstance alloc] init: nativeMaterial->createInstance()];
}
- (MaterialInstance *)createInstance:(NSString *)name{
    return [[MaterialInstance alloc] init: nativeMaterial->createInstance(name.UTF8String)];
}
- (Shading)getShading{
    return (Shading) nativeMaterial->getShading();
}
- (Interpolation)getInterpolation{
    return (Interpolation) nativeMaterial->getInterpolation();
}
- (BlendingMode)getBlendingMode{
    return (BlendingMode) nativeMaterial->getBlendingMode();
}
- (RefractionMode)getRefractionMode{
    return (RefractionMode) nativeMaterial->getRefractionMode();
}
- (RefractionType)getRefractionType{
    return (RefractionType) nativeMaterial->getRefractionType();
}
- (VertexDomain)getVertexDomain{
    return (VertexDomain) nativeMaterial->getVertexDomain();
}
- (CullingMode)getCullingMode{
    return (CullingMode) nativeMaterial->getCullingMode();
}
- (bool)isColorWriteEnabled{
    return nativeMaterial->isColorWriteEnabled();
}
- (bool)isDepthWriteEnabled{
    return nativeMaterial->isDepthWriteEnabled();
}
- (bool)isDepthCullingEnabled{
    return nativeMaterial->isDepthCullingEnabled();
}
- (bool)isDoubleSided{
    return nativeMaterial->isDoubleSided();
}
- (double)getMaskThreshold{
    return nativeMaterial->getMaskThreshold();
}
- (double)getSpecularAntiAliasingVariance{
    return nativeMaterial->getSpecularAntiAliasingVariance();
}
- (double)getSpecularAntiAliasingThreshold{
    return nativeMaterial->getSpecularAntiAliasingThreshold();
}
- (double)getRequiredAttributes{
    auto bitset = nativeMaterial->getRequiredAttributes();
    return bitset.getValue();
}
- (double)getParameterCount{
    return nativeMaterial->getParameterCount();
}
- (NSArray<Parameter *> *)getParameters{
    auto count = nativeMaterial->getParameterCount();
    filament::Material::ParameterInfo params[count];
    auto available = nativeMaterial->getParameters(params, count);
    auto res = [[NSMutableArray<Parameter*> alloc] init];
    for(auto i = 0; i<count; i++){
        auto param = params[i];
        auto _param = [[Parameter alloc] init];
        _param.type = (ParameterType)param.type;
        _param.count = param.count;
        _param.precision = (ParameterPrecision)param.precision;
        _param.name = [[NSString alloc] initWithUTF8String:param.name];
        
        [res addObject: _param];
    }
    return res;
}
- (bool)hasParameter:(NSString *)name{
    return nativeMaterial->hasParameter(name.UTF8String);
}
- (void)setDefaultParameterBool:(NSString *)name :(bool)boolean{
    nativeMaterial->setDefaultParameter(name.UTF8String, boolean);
}
- (void)setDefaultParameterFloat:(NSString *)name :(float)decimal{
    nativeMaterial->setDefaultParameter(name.UTF8String, decimal);
}
- (void)setDefaultParameterInt:(NSString *)name :(int)integer{
    nativeMaterial->setDefaultParameter(name.UTF8String, integer);
}
- (void)setDefaultParameterBool2:(NSString *)name :(bool)boolean1 :(bool)boolean2{
    nativeMaterial->setDefaultParameter(name.UTF8String, filament::math::bool2(boolean1, boolean2));
}
- (void)setDefaultParameterFloat2:(NSString *)name :(simd_float2)vector{
    nativeMaterial->setDefaultParameter(name.UTF8String, filament::math::float2(vector.x, vector.y));
}
- (void)setDefaultParameterInt2:(NSString *)name :(simd_int2)vector{
    nativeMaterial->setDefaultParameter(name.UTF8String, filament::math::int2(vector.x, vector.y));
}
- (void)setDefaultParameterBool3:(NSString *)name :(bool)boolean1 :(bool)boolean2 :(bool)boolean3{
    nativeMaterial->setDefaultParameter(name.UTF8String, filament::math::bool3(boolean1, boolean2, boolean3));
}
- (void)setDefaultParameterFloat3:(NSString *)name :(simd_float3)vector{
    nativeMaterial->setDefaultParameter(name.UTF8String, filament::math::float3(vector.x, vector.y, vector.z));
}
- (void)setDefaultParameterInt3:(NSString *)name :(simd_int3)vector{
    nativeMaterial->setDefaultParameter(name.UTF8String, filament::math::int3(vector.x, vector.y, vector.z));
}
- (void)setDefaultParameterBool4:(NSString *)name :(bool)boolean1 :(bool)boolean2 :(bool)boolean3 :(bool)boolean4{
    nativeMaterial->setDefaultParameter(name.UTF8String, filament::math::bool4(boolean1, boolean2, boolean3, boolean4));
}
- (void)setDefaultParameterFloat4:(NSString *)name :(simd_float4)vector{
    nativeMaterial->setDefaultParameter(name.UTF8String, filament::math::float4(vector.x, vector.y, vector.z, vector.w));
}
- (void)setDefaultParameterInt4:(NSString *)name :(simd_int4)vector{
    nativeMaterial->setDefaultParameter(name.UTF8String, filament::math::int4(vector.x, vector.y, vector.z, vector.w));
}
- (void)setDefaultParameterTexture:(NSString *)name :(Texture *)texture :(TextureSampler *)sampler{
    nativeMaterial->setDefaultParameter(name.UTF8String, (filament::Texture*) texture.texture, *(filament::TextureSampler*) sampler.sampler);
}
- (nonnull MaterialInstance *)getDefaultInstance {
    return [[MaterialInstance alloc] init:nativeMaterial->getDefaultInstance()];
}

- (nonnull NSString *)getName {
    return [[NSString alloc] initWithUTF8String:nativeMaterial->getName()];
}

- (ReflectionMode)getReflectionMode {
    return (ReflectionMode)nativeMaterial->getReflectionMode();
}

- (TransparencyMode)getTransparencyMode {
    return (TransparencyMode)nativeMaterial->getTransparencyMode();
}

- (bool)hasShadowMultiplier {
    return nativeMaterial->hasShadowMultiplier();
}

- (bool)hasSpecularAntiAliasing {
    return nativeMaterial->hasSpecularAntiAliasing();
}

- (bool)isAlphaToCoverageEnabled {
    return nativeMaterial->isAlphaToCoverageEnabled();
}

- (bool)isSampler:(nonnull NSString *)name {
    return nativeMaterial->isSampler(name.UTF8String);
}

- (void)setDefaultParameterRgb:(nonnull NSString *)name :(RgbType)type :(simd_float3)vector {
    nativeMaterial->setDefaultParameter(name.UTF8String, (filament::RgbType)type, filament::math::float3(vector[0],vector[1],vector[2]));
}

- (void)setDefaultParameterRgba:(nonnull NSString *)name :(RgbaType)type :(simd_float4)vector {
    nativeMaterial->setDefaultParameter(name.UTF8String, (filament::RgbaType)type, filament::math::float4(vector[0],vector[1],vector[2],vector[3]));
}

- (MaterialDomain)getMaterialDomain {
    return (MaterialDomain)nativeMaterial->getMaterialDomain();
}

@end
