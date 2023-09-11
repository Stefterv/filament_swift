//
//  Material.h
//
//  Created by Stef Tervelde on 30.06.22.
//
#import <Foundation/Foundation.h>
#import "MaterialInstance.h"
#import "Colors.h"

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
NS_SWIFT_NAME(Material.Domain)
typedef NS_ENUM(NSInteger, MaterialDomain){
    Surface         = 0, //!< shaders applied to renderables
    PostProcess    = 1, //!< shaders applied to rendered buffers
    Compute         = 2, //!< compute shader
};
/**
 * How transparent objects are handled
 */
//NS_SWIFT_NAME(Transparency.Mode)
typedef NS_ENUM(NSInteger, TransparencyMode){
    //! the transparent object is drawn honoring the raster state
    DEFAULT,
    /**
     * the transparent object is first drawn in the depth buffer,
     * then in the color buffer, honoring the culling mode, but ignoring the depth test function
     */
    TWO_PASSES_ONE_SIDE,

    /**
     * the transparent object is drawn twice in the color buffer,
     * first with back faces only, then with front faces; the culling
     * mode is ignored. Can be combined with two-sided lighting
     */
    TWO_PASSES_TWO_SIDES
};
/**
 * Reflection mode
 */
//NS_SWIFT_NAME(Reflection.Mode)
typedef NS_ENUM(NSInteger, ReflectionMode){
    Default         = 0, //! reflections sample from the scene's IBL only
    ScreenSpace    = 1, //! reflections sample from screen space, and fallback to the scene's IBL
};

NS_SWIFT_NAME(Material.Parameter)
@interface Parameter : NSObject
@property ParameterType type;
@property (nonnull) NSString* name;
@property ParameterPrecision precision;
@property int count;
@end

@interface Material : NSObject

@property (nonatomic, readonly, nonnull) void* material  NS_SWIFT_UNAVAILABLE("Don't access the raw pointers");
- (nonnull id) init: (nonnull void*) material NS_SWIFT_UNAVAILABLE("Instances are created internally");
- (nonnull id) init NS_UNAVAILABLE;

/**
 * Creates a new instance of this material. Material instances should be freed using
 * Engine::destroy(const MaterialInstance*).
 *
 * @param name Optional name to associate with the given material instance. If this is null,
 * then the instance inherits the material's name.
 *
 * @return A pointer to the new instance.
 */
- (nonnull MaterialInstance*) createInstance;
- (nonnull MaterialInstance*) createInstance: (nonnull NSString*) name;
//! Returns the name of this material
- (nonnull NSString*) getName;
//! Returns the shading model of this material.
- (Shading) getShading;
//! Returns the interpolation mode of this material. This affects how variables are interpolated.
- (Interpolation) getInterpolation;
//! Returns the blending mode of this material.
- (BlendingMode) getBlendingMode;
//! Returns the vertex domain of this material.
- (VertexDomain) getVertexDomain;
//! Returns the material domain of this material.
//! The material domain determines how the material is used.
- (MaterialDomain) getMaterialDomain;
//! Returns the default culling mode of this material.
- (CullingMode) getCullingMode;
//! Returns the transparency mode of this material.
//! This value only makes sense when the blending mode is transparent or fade.
- (TransparencyMode) getTransparencyMode;
//! Indicates whether instances of this material will, by default, write to the color buffer.
- (bool) isColorWriteEnabled;
//! Indicates whether instances of this material will, by default, write to the depth buffer.
- (bool) isDepthWriteEnabled;
//! Indicates whether instances of this material will, by default, use depth testing.
- (bool) isDepthCullingEnabled;
//! Indicates whether this material is double-sided.
- (bool) isDoubleSided;
//! Indicates whether this material uses alpha to coverage.
- (bool) isAlphaToCoverageEnabled;
//! Returns the alpha mask threshold used when the blending mode is set to masked.
- (double) getMaskThreshold;
//! Indicates whether this material uses the shadowing factor as a color multiplier.
//! This values only makes sense when the shading mode is unlit.
- (bool) hasShadowMultiplier;
//! Indicates whether this material has specular anti-aliasing enabled
- (bool) hasSpecularAntiAliasing;
//! Returns the screen-space variance for specular-antialiasing, this value is between 0 and 1.
- (double) getSpecularAntiAliasingVariance;
//! Returns the clamping threshold for specular-antialiasing, this value is between 0 and 1.
- (double) getSpecularAntiAliasingThreshold;
//! Returns the list of vertex attributes required by this material.
- (double) getRequiredAttributes;
//! Returns the refraction mode used by this material.
- (RefractionMode) getRefractionMode;
//! Return the refraction type used by this material.
- (RefractionType) getRefractionType;
//! Returns the reflection mode used by this material.
- (ReflectionMode) getReflectionMode;
NS_ASSUME_NONNULL_BEGIN
/**
 * Gets information about this material's parameters.
 *
 * @param parameters A pointer to a list of ParameterInfo.
 *                   The list must be at least "count" large
 * @param count The number of parameters to retrieve. Must be >= 0 and can be > count.
 *
 * @return The number of parameters written to the parameters pointer.
*/
- (NSArray<Parameter*>*) getParameters;
//! Indicates whether a parameter of the given name exists on this material.
- (bool) hasParameter: (NSString*) name;
//! Indicates whether an existing parameter is a sampler or not.
- (bool) isSampler: (NSString*) name;
/**
 * Sets the value of the given parameter on this material's default instance.
 *
 * @param name The name of the material parameter
 * @param value The value of the material parameter
 *
 * @see getDefaultInstance()
 */
- (void) setDefaultParameterBool: (NSString*) name :(bool) boolean;
/**
 * Sets the value of the given parameter on this material's default instance.
 *
 * @param name The name of the material parameter
 * @param value The value of the material parameter
 *
 * @see getDefaultInstance()
 */
- (void) setDefaultParameterFloat: (NSString*) name :(float) decimal;
/**
 * Sets the value of the given parameter on this material's default instance.
 *
 * @param name The name of the material parameter
 * @param value The value of the material parameter
 *
 * @see getDefaultInstance()
 */
- (void) setDefaultParameterInt: (NSString*) name :(int) integer;
/**
 * Sets the value of the given parameter on this material's default instance.
 *
 * @param name The name of the material parameter
 * @param value The value of the material parameter
 *
 * @see getDefaultInstance()
 */
- (void) setDefaultParameterBool2: (NSString*) name :(bool) boolean1 :(bool) boolean2;
/**
 * Sets the value of the given parameter on this material's default instance.
 *
 * @param name The name of the material parameter
 * @param value The value of the material parameter
 *
 * @see getDefaultInstance()
 */
- (void) setDefaultParameterFloat2: (NSString*) name :(simd_float2) vector;
/**
 * Sets the value of the given parameter on this material's default instance.
 *
 * @param name The name of the material parameter
 * @param value The value of the material parameter
 *
 * @see getDefaultInstance()
 */
- (void) setDefaultParameterInt2: (NSString*) name :(simd_int2) vector;
/**
 * Sets the value of the given parameter on this material's default instance.
 *
 * @param name The name of the material parameter
 * @param value The value of the material parameter
 *
 * @see getDefaultInstance()
 */
- (void) setDefaultParameterBool3: (NSString*) name :(bool) boolean1 :(bool) boolean2 :(bool) boolean3;
/**
 * Sets the value of the given parameter on this material's default instance.
 *
 * @param name The name of the material parameter
 * @param value The value of the material parameter
 *
 * @see getDefaultInstance()
 */
- (void) setDefaultParameterFloat3: (NSString*) name :(simd_float3) vector;
/**
 * Sets the value of the given parameter on this material's default instance.
 *
 * @param name The name of the material parameter
 * @param value The value of the material parameter
 *
 * @see getDefaultInstance()
 */
- (void) setDefaultParameterInt3: (NSString*) name :(simd_int3) vector;
/**
 * Sets the value of the given parameter on this material's default instance.
 *
 * @param name The name of the material parameter
 * @param value The value of the material parameter
 *
 * @see getDefaultInstance()
 */
- (void) setDefaultParameterBool4: (NSString*) name :(bool) boolean1 :(bool) boolean2 :(bool) boolean3 :(bool) boolean4;
/**
 * Sets the value of the given parameter on this material's default instance.
 *
 * @param name The name of the material parameter
 * @param value The value of the material parameter
 *
 * @see getDefaultInstance()
 */
- (void) setDefaultParameterFloat4: (NSString*) name :(simd_float4) vector;
/**
 * Sets the value of the given parameter on this material's default instance.
 *
 * @param name The name of the material parameter
 * @param value The value of the material parameter
 *
 * @see getDefaultInstance()
 */
- (void) setDefaultParameterInt4: (NSString*) name :(simd_int4) vector;
/**
 * Sets a texture and sampler parameters on this material's default instance.
 *
 * @param name The name of the material texture parameter
 * @param texture The texture to set as parameter
 * @param sampler The sampler to be used with this texture
 *
 * @see getDefaultInstance()
 */
- (void) setDefaultParameterTexture: (NSString*) name :(Texture*) texture :(TextureSampler*) sampler;;
/**
 * Sets the color of the given parameter on this material's default instance.
 *
 * @param name The name of the material color parameter
 * @param type Whether the color is specified in the linear or sRGB space
 * @param color The color as a floating point red, green, blue tuple
 *
 * @see getDefaultInstance
 */
- (void) setDefaultParameterRgb: (NSString*) name :(RgbType) type :(simd_float3) vector;
- (void) setDefaultParameterRgba: (NSString*) name :(RgbaType) type :(simd_float4) vector;
//! Returns this material's default instance.
- (MaterialInstance*) getDefaultInstance;
//! Returns this material's default instance.
- (MaterialInstance*) getDefaultInstance;
NS_ASSUME_NONNULL_END

@end


#endif /* Material_h */
