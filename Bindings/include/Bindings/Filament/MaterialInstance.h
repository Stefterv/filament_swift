//
//  MaterialInstance.h

//  Created by Stef Tervelde on 30.06.22.
//
#import <Foundation/Foundation.h>
#import "Texture.h"
#import "TextureSampler.h"

#import <simd/simd.h>

#ifndef MaterialInstance_h
#define MaterialInstance_h

@interface MaterialInstance : NSObject

@property (nonatomic, readonly, nonnull) void* instance  NS_SWIFT_UNAVAILABLE("Don't access the raw pointers");
- (nonnull id) init: (nonnull void*) instance NS_SWIFT_UNAVAILABLE("Instances are created internally");
- (nonnull id) init NS_UNAVAILABLE;

/**
 * Creates a new {@link #MaterialInstance} using another {@link #MaterialInstance} as a template for initialization.
 * The new {@link #MaterialInstance} is an instance of the same {@link Material} of the template instance and
 * must be destroyed just like any other {@link #MaterialInstance}.
 *
 * @param other A {@link #MaterialInstance} to use as a template for initializing a new instance
 * @param name  A name for the new {@link #MaterialInstance} or nullptr to use the template's name
 * @return      A new {@link #MaterialInstance}
 */
NS_ASSUME_NONNULL_BEGIN
+ (instancetype) duplicate: (MaterialInstance*) instance;

- (NSString*) getName;

- (void) setParameterBool: (NSString*) name :(bool) boolean;
- (void) setParameterFloat: (NSString*) name :(float) decimal;
- (void) setParameterInt: (NSString*) name :(int) integer;
- (void) setParameterBool2: (NSString*) name :(bool) boolean1 :(bool) boolean2;
- (void) setParameterFloat2: (NSString*) name :(simd_float2) vector;
- (void) setParameterInt2: (NSString*) name :(simd_int2) vector;
- (void) setParameterBool3: (NSString*) name :(bool) boolean1 :(bool) boolean2 :(bool) boolean3;
- (void) setParameterFloat3: (NSString*) name :(simd_float3) vector;
- (void) setParameterInt3: (NSString*) name :(simd_int3) vector;
- (void) setParameterBool4: (NSString*) name :(bool) boolean1 :(bool) boolean2 :(bool) boolean3 :(bool) boolean4;
- (void) setParameterFloat4: (NSString*) name :(simd_float4) vector;
- (void) setParameterInt4: (NSString*) name :(simd_int4) vector;
- (void) setParameterMat3f: (NSString*) name :(simd_float3x3) vector;
- (void) setParameterMat4f: (NSString*) name :(simd_float4x4) vector;
- (void) setParameterTexture: (NSString*) name :(Texture*) texture :(TextureSampler*) sampler;
#warning Add Color Parameters
/**
 * Set up a custom scissor rectangle; by default this encompasses the View.
 *
 * @param left      left coordinate of the scissor box
 * @param bottom    bottom coordinate of the scissor box
 * @param width     width of the scissor box
 * @param height    height of the scissor box
 */
- (void) setScissor: (int) left :(int) bottom :(int) width :(int) height;
- (void) unsetScissor;
/**
 * Sets a polygon offset that will be applied to all renderables drawn with this material
 * instance.
 *
 *  The value of the offset is scale * dz + r * constant, where dz is the change in depth
 *  relative to the screen area of the triangle, and r is the smallest value that is guaranteed
 *  to produce a resolvable offset for a given implementation. This offset is added before the
 *  depth test.
 *
 *  Warning: using a polygon offset other than zero has a significant negative performance
 *  impact, as most implementations have to disable early depth culling. DO NOT USE unless
 *  absolutely necessary.
 *
 * @param scale scale factor used to create a variable depth offset for each triangle
 * @param constant scale factor used to create a constant depth offset for each triangle
 */
- (void) setPolygonOffset: (double) scale :(double) constant;
/**
 * Overrides the minimum alpha value a fragment must have to not be discarded when the blend
 * mode is MASKED. Defaults to 0.4 if it has not been set in the parent Material. The specified
 * value should be between 0 and 1 and will be clamped if necessary.
 *
 * @see
 * <a href="https://google.github.io/filament/Materials.html#materialdefinitions/materialblock/blendingandtransparency:maskthreshold">
 * Blending and transparency: maskThreshold</a>
 */
- (void) setMaskThreshold: (double) threshold;

/**
 * Sets the screen space variance of the filter kernel used when applying specular
 * anti-aliasing. The default value is set to 0.15. The specified value should be between
 * 0 and 1 and will be clamped if necessary.
 *
 * @see
 * <a href="https://google.github.io/filament/Materials.html#materialdefinitions/materialblock/anti-aliasing:specularantialiasingvariance">
 * Anti-aliasing: specularAntiAliasingVariance</a>
 */
- (void) setSpecularAntiAliasingVariance: (double) variance;

/**
 * Sets the clamping threshold used to suppress estimation errors when applying specular
 * anti-aliasing. The default value is set to 0.2. The specified value should be between 0
 * and 1 and will be clamped if necessary.
 *
 * @see
 * <a href="https://google.github.io/filament/Materials.html#materialdefinitions/materialblock/anti-aliasing:specularantialiasingthreshold">
 * Anti-aliasing: specularAntiAliasingThreshold</a>
 */
- (void) setSpecularAntiAliasingThreshold: (double) threshold;

/**
 * Enables or disables double-sided lighting if the parent Material has double-sided capability,
 * otherwise prints a warning. If double-sided lighting is enabled, backface culling is
 * automatically disabled.
 *
 * @see
 * <a href="https://google.github.io/filament/Materials.html#materialdefinitions/materialblock/rasterization:doublesided">
 * Rasterization: doubleSided</a>
 */
- (void) setDoubleSided: (bool) doubleSided;
/**
 * Overrides the default triangle culling state that was set on the material.
 *
 * @see
 * <a href="https://google.github.io/filament/Materials.html#materialdefinitions/materialblock/rasterization:culling">
 * Rasterization: culling</a>
 */
- (void) setCullingMode: (uint8_t) mode;
/**
 * Overrides the default color-buffer write state that was set on the material.
 *
 * @see
 * <a href="https://google.github.io/filament/Materials.html#materialdefinitions/materialblock/rasterization:colorWrite">
 * Rasterization: colorWrite</a>
 */
- (void) setColorWrite: (bool) enable;
/**
 * Overrides the default depth-buffer write state that was set on the material.
 *
 * @see
 * <a href="https://google.github.io/filament/Materials.html#materialdefinitions/materialblock/rasterization:depthWrite">
 * Rasterization: depthWrite</a>
 */
- (void) setDepthWrite: (bool) enable;
/**
 * Overrides the default depth testing state that was set on the material.
 *
 * @see
 * <a href="https://google.github.io/filament/Materials.html#materialdefinitions/materialblock/rasterization:depthCulling">
 * Rasterization: depthCulling</a>
 */
- (void) setDepthCulling: (bool) enable;


NS_ASSUME_NONNULL_END
@end


#endif /* MaterialInstance_h */
