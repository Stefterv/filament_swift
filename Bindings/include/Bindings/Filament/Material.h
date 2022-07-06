//
//  Material.h
//
//  Created by Stef Tervelde on 30.06.22.
//
#import <Foundation/Foundation.h>
#import "MaterialInstance.h"

#ifndef Material_h
#define Material_h



NS_SWIFT_NAME(Material.Shading)
typedef NS_ENUM(NSInteger, Shading) {
    /**
     * No lighting applied, emissive possible
     *
     * @see
     * <a href="https://google.github.io/filament/Materials.html#materialmodels/unlitmodel">
     * Unlit model</a>
     */
    UNLIT,

    /**
     * Default, standard lighting
     *
     * @see
     * <a href="https://google.github.io/filament/Materials.html#materialmodels/litmodel">
     * Lit model</a>
     */
    LIT,

    /**
     * Subsurface lighting model
     *
     * @see
     * <a href="https://google.github.io/filament/Materials.html#materialmodels/subsurfacemodel">
     * Subsurface model</a>
     */
    SUBSURFACE,

    /**
     * Cloth lighting model
     *
     * @see
     * <a href="https://google.github.io/filament/Materials.html#materialmodels/clothmodel">
     * Cloth model</a>
     */
    CLOTH,

    /**
     * Legacy lighting model
     *
     * @see
     * <a href="https://google.github.io/filament/Materials.html#materialmodels/specularglossiness">
     * Specular glossiness</a>
     */
    SPECULAR_GLOSSINESS
};
NS_SWIFT_NAME(Material.Interpolation)
typedef NS_ENUM(NSInteger, Interpolation) {
    /** Default, smooth interpolation */
    SMOOTH,

    /** Flat interpolation */
    FLAT
};
NS_SWIFT_NAME(Material.BlendingMode)
typedef NS_ENUM(NSInteger, BlendingMode) {
    /** Material is opaque. */
    OPAQUE,

    /**
     * Material is transparent and color is alpha-pre-multiplied.
     * Affects diffuse lighting only.
     */
    TRANSPARENT,

    /** Material is additive (e.g.: hologram). */
    ADD,

    /** Material is masked (i.e. alpha tested). */
    MASKED,

    /**
     * Material is transparent and color is alpha-pre-multiplied.
     * Affects specular lighting.
     */
    FADE,

    /** Material darkens what's behind it. */
    MULTIPLY,

    /** Material brightens what's behind it. */
    SCREEN,
};
NS_SWIFT_NAME(Material.RefractionMode)
typedef NS_ENUM(NSInteger, RefractionMode) {
    NONE,
    CUBEMAP,
    SCREEN_SPACE
};
NS_SWIFT_NAME(Material.RefractionType)
typedef NS_ENUM(NSInteger, RefractionType) {
    SOLID,
    THIN
};
NS_SWIFT_NAME(Material.VertexDomain)
typedef NS_ENUM(NSInteger, VertexDomain) {
    /** Vertices are in object space, default. */
    OBJECT,

    /** Vertices are in world space. */
    WORLD,

    /** Vertices are in view space. */
    VIEW,

    /** Vertices are in normalized device space. */
    DEVICE
};
NS_SWIFT_NAME(Material.CullingMode)
typedef NS_ENUM(NSInteger, CullingMode) {
    /** No culling. Front and back faces are visible. */
    None,

    /** Front face culling. Only back faces are visible. */
    FRONT,

    /** Back face culling. Only front faces are visible. */
    BACK,

    /** Front and back culling. Geometry is not visible. */
    FRONT_AND_BACK
};

NS_SWIFT_NAME(Parameter.Type)
typedef NS_ENUM(NSInteger, ParameterType) {
    Bool,
    BOOL2,
    BOOL3,
    BOOL4,
    FLOAT,
    FLOAT2,
    FLOAT3,
    FLOAT4,
    INT,
    INT2,
    INT3,
    INT4,
    UINT,
    UINT2,
    UINT3,
    UINT4,
    MAT3,
    MAT4,
    SAMPLER_2D,
    SAMPLER_2D_ARRAY,
    SAMPLER_CUBEMAP,
    SAMPLER_EXTERNAL,
    SAMPLER_3D,
    SUBPASS_INPUT
};
NS_SWIFT_NAME(Parameter.Precision)
typedef NS_ENUM(NSInteger, ParameterPrecision) {
    LOW,
    MEDIUM,
    HIGH,
    DEFAULT
};

NS_SWIFT_NAME(Material.Parameter)
@interface Parameter : NSObject
@property ParameterType type;
@property NSString*_Nonnull name;
@property ParameterPrecision precision;
@property int count;
@end

@interface Material : NSObject

@property (nonatomic, readonly, nonnull) void* material  NS_SWIFT_UNAVAILABLE("Don't access the raw pointers");
- (nonnull id) init: (nonnull void*) material NS_SWIFT_UNAVAILABLE("Create a new renderer with engine.createRenderer");
- (nonnull id) init NS_UNAVAILABLE;

- (nonnull MaterialInstance*) createInstance;
- (nonnull MaterialInstance*) createInstance: (nonnull NSString*) name;

- (Shading) getShading;
- (Interpolation) getInterpolation;
- (BlendingMode) getBlendingMode;
- (RefractionMode) getRefractionMode;
- (RefractionType) getRefractionType;
- (VertexDomain) getVertexDomain;
- (CullingMode) getCullingMode;
- (bool) isColorWriteEnabled;
- (bool) isDepthWriteEnabled;
- (bool) isDepthCullingEnabled;
- (bool) isDoubleSided;
- (double) getMaskThreshold;
- (double) getSpecularAntiAliasingVariance;
- (double) getSpecularAntiAliasingThreshold;
- (double) getRequiredAttributes;
- (double) getParameterCount;
NS_ASSUME_NONNULL_BEGIN
- (NSArray<Parameter*>*) getParamters;
- (bool) hasParameter: (NSString*) name;
- (void) setDefaultParameterBool: (NSString*) name :(bool) boolean;
- (void) setDefaultParameterFloat: (NSString*) name :(float) decimal;
- (void) setDefaultParameterInt: (NSString*) name :(int) integer;
- (void) setDefaultParameterBool2: (NSString*) name :(bool) boolean1 :(bool) boolean2;
- (void) setDefaultParameterFloat2: (NSString*) name :(simd_float2) vector;
- (void) setDefaultParameterInt2: (NSString*) name :(simd_int2) vector;
- (void) setDefaultParameterBool3: (NSString*) name :(bool) boolean1 :(bool) boolean2 :(bool) boolean3;
- (void) setDefaultParameterFloat3: (NSString*) name :(simd_float3) vector;
- (void) setDefaultParameterInt3: (NSString*) name :(simd_int3) vector;
- (void) setDefaultParameterBool4: (NSString*) name :(bool) boolean1 :(bool) boolean2 :(bool) boolean3 :(bool) boolean4;
- (void) setDefaultParameterFloat4: (NSString*) name :(simd_float4) vector;
- (void) setDefaultParameterInt4: (NSString*) name :(simd_int4) vector;
- (void) setDefaultParameterTexture: (NSString*) name :(Texture*) texture;
NS_ASSUME_NONNULL_END


@end


#endif /* Material_h */
