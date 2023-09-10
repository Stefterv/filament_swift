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
    ShadingUnlit,

    /**
     * Default, standard lighting
     *
     * @see
     * <a href="https://google.github.io/filament/Materials.html#materialmodels/litmodel">
     * Lit model</a>
     */
    ShadingLit,

    /**
     * Subsurface lighting model
     *
     * @see
     * <a href="https://google.github.io/filament/Materials.html#materialmodels/subsurfacemodel">
     * Subsurface model</a>
     */
    ShadingSubsurface,

    /**
     * Cloth lighting model
     *
     * @see
     * <a href="https://google.github.io/filament/Materials.html#materialmodels/clothmodel">
     * Cloth model</a>
     */
    ShadingCloth,

    /**
     * Legacy lighting model
     *
     * @see
     * <a href="https://google.github.io/filament/Materials.html#materialmodels/specularglossiness">
     * Specular glossiness</a>
     */
    ShadingSPECULAR_GLOSSINESS
};
NS_SWIFT_NAME(Material.Interpolation)
typedef NS_ENUM(NSInteger, Interpolation) {
    /** Default, smooth interpolation */
    InterpolationSmooth,

    /** Flat interpolation */
    InterpolationFlat
};
NS_SWIFT_NAME(Material.BlendingMode)
typedef NS_ENUM(NSInteger, BlendingMode) {
    /** Material is opaque. */
    BlendingModeOpaque,

    /**
     * Material is transparent and color is alpha-pre-multiplied.
     * Affects diffuse lighting only.
     */
    BlendingModeTransparent,

    /** Material is additive (e.g.: hologram). */
    BlendingModeAdd,

    /** Material is masked (i.e. alpha tested). */
    BlendingModeMasked,

    /**
     * Material is transparent and color is alpha-pre-multiplied.
     * Affects specular lighting.
     */
    BlendingModeFade,

    /** Material darkens what's behind it. */
    BlendingModeMultiply,

    /** Material brightens what's behind it. */
    BlendingModeScreen,
};
NS_SWIFT_NAME(Material.RefractionMode)
typedef NS_ENUM(NSInteger, RefractionMode) {
    RefractionModeNone,
    RefractionModeCubemap,
    RefractionModeScreen_Space
};
NS_SWIFT_NAME(Material.RefractionType)
typedef NS_ENUM(NSInteger, RefractionType) {
    RefractionTypeSolid,
    RefractionTypeThin
};
NS_SWIFT_NAME(Material.VertexDomain)
typedef NS_ENUM(NSInteger, VertexDomain) {
    /** Vertices are in object space, default. */
    VertexDomainObject,

    /** Vertices are in world space. */
    VertexDomainWorld,

    /** Vertices are in view space. */
    VertexDomainView,

    /** Vertices are in normalized device space. */
    VertexDomainDevice
};
NS_SWIFT_NAME(Material.CullingMode)
typedef NS_ENUM(NSInteger, CullingMode) {
    /** No culling. Front and back faces are visible. */
    CullingModeNone,

    /** Front face culling. Only back faces are visible. */
    CullingModeFront,

    /** Back face culling. Only front faces are visible. */
    CullingModeBack,

    /** Front and back culling. Geometry is not visible. */
    CullingModeFront_And_Back
};

NS_SWIFT_NAME(Parameter.Type)
typedef NS_ENUM(NSInteger, ParameterType) {
    ParameterTypeBool,
    ParameterTypeBool2,
    ParameterTypeBool3,
    ParameterTypeBool4,
    ParameterTypeFloat,
    ParameterTypeFloat2,
    ParameterTypeFloat3,
    ParameterTypeFloat4,
    ParameterTypeInt,
    ParameterTypeInt2,
    ParameterTypeInt3,
    ParameterTypeInt4,
    ParameterTypeUint,
    ParameterTypeUint2,
    ParameterTypeUint3,
    ParameterTypeUint4,
    ParameterTypeMat3,
    ParameterTypeMat4,
    ParameterTypeSampler2D,
    ParameterTypeSampler2DArray,
    ParameterTypeSamplerCubemap,
    ParameterTypeSamplerExternal,
    ParameterTypeSampler3D,
    ParameterTypeSubpassInput
};
NS_SWIFT_NAME(Parameter.Precision)
typedef NS_ENUM(NSInteger, ParameterPrecision) {
    ParameterPrecisionLow,
    ParameterPrecisionMedium,
    ParameterPrecisionHigh,
    ParameterPrecisionDefault
};

#warning Replace with Struct
NS_SWIFT_NAME(Material.Parameter)
@interface Parameter : NSObject
@property ParameterType type;
@property NSString*_Nonnull name;
@property ParameterPrecision precision;
@property int count;
@end

@interface Material : NSObject

@property (nonatomic, readonly, nonnull) void* material  NS_SWIFT_UNAVAILABLE("Don't access the raw pointers");
- (nonnull id) init: (nonnull void*) material NS_SWIFT_UNAVAILABLE("Instances are created internally");
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
- (NSArray<Parameter*>*) getParameters;
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
- (void) setDefaultParameterTexture: (NSString*) name :(Texture*) texture :(TextureSampler*) sampler;;
NS_ASSUME_NONNULL_END
#warning("TODO Comments")

@end


#endif /* Material_h */
