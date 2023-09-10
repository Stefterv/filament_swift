//
//  RenderableBuilder.h

//  Created by Stef Tervelde on 30.06.22.
//
#import <Foundation/Foundation.h>
#import "RenderableManager.h"
#import "VertexBuffer.h"
#import "IndexBuffer.h"
#import "MaterialInstance.h"
#import "Box.h"
#import "Engine.h"
#import "Entity.h"

#ifndef RenderableBuilder_h
#define RenderableBuilder_h

NS_SWIFT_NAME(RenderableManager.Builder)
@interface RenderableBuilder : NSObject

@property (nonatomic, readonly, nonnull) void* builder  NS_SWIFT_UNAVAILABLE("Don't access the raw pointers");

/**
 * Creates a builder for renderable components.
 *
 * @param count the number of primitives that will be supplied to the builder
 *
 * Note that builders typically do not have a long lifetime since clients should discard
 * them after calling {@link #build}. For a usage example, see {@link RenderableManager}.
 */
- (nonnull id) init: (int) count;
- (nonnull id) init NS_UNAVAILABLE;
NS_ASSUME_NONNULL_BEGIN

/**
 * Specifies the geometry data for a primitive.
 *
 * Filament primitives must have an associated {@link VertexBuffer} and {@link IndexBuffer}.
 * Typically, each primitive is specified with a pair of daisy-chained calls:
 * <code>geometry()</code> and <code>material()</code>.
 *
 * @param index zero-based index of the primitive, must be less than the count passed to Builder constructor
 * @param type specifies the topology of the primitive (e.g., {@link PrimitiveType#TRIANGLES})
 * @param vertices specifies the vertex buffer, which in turn specifies a set of attributes
 * @param indices specifies the index buffer (either u16 or u32)
 * @param offset specifies where in the index buffer to start reading (expressed as a number of indices)
 * @param minIndex specifies the minimum index contained in the index buffer
 * @param maxIndex specifies the maximum index contained in the index buffer
 * @param count number of indices to read (for triangles, this should be a multiple of 3)
 */
- (instancetype) geometry: (int) index :(PrimitiveType) type :(VertexBuffer*) vertices :(IndexBuffer*) indices :(NSInteger) offset :(NSInteger) count :(Engine*) engine;

/**
 * Binds a material instance to the specified primitive.
 *
 * <p>If no material is specified for a given primitive, Filament will fall back to a basic
 * default material.</p>
 *
 * @param index zero-based index of the primitive, must be less than the count passed to Builder constructor
 * @param material the material to bind
 */
- (instancetype) material: (int) index :(MaterialInstance*) material;

/**
 * Sets the drawing order for blended primitives. The drawing order is either global or
 * local (default) to this Renderable. In either case, the Renderable priority takes
 * precedence.
 *
 * @param index the primitive of interest
 * @param blendOrder draw order number (0 by default). Only the lowest 15 bits are used.
 */
- (instancetype) blendOrder: (int) index :(uint16_t) blendOrder;
/**
  * Sets whether the blend order is global or local to this Renderable (by default).
  *
  * @param index the primitive of interest
  * @param enabled true for global, false for local blend ordering.
  */
- (instancetype) globalBlendOrderEnabled: (int) index :(bool) enabled;
/**
 * The axis-aligned bounding box of the renderable.
 *
 * <p>This is an object-space AABB used for frustum culling. For skinning and morphing, this
 * should encompass all possible vertex positions. It is mandatory unless culling is
 * disabled for the renderable.</p>
 */
- (instancetype) boundingBox: (Box) aabb;
/**
 * Sets bits in a visibility mask. By default, this is 0x1.
 *
 * <p>This feature provides a simple mechanism for hiding and showing groups of renderables
 * in a Scene. See {@link View#setVisibleLayers}.</p>
 *
 * <p>For example, to set bit 1 and reset bits 0 and 2 while leaving all other bits
 * unaffected, do: <code>builder.layerMask(7, 2)</code>.</p>
 *
 * @see RenderableManager#setLayerMask
 *
 * @param select the set of bits to affect
 * @param value the replacement values for the affected bits
 */
- (instancetype) layerMask: (uint8_t) select :(uint8_t) value;
/**
 * Provides coarse-grained control over draw order.
 *
 * <p>In general Filament reserves the right to re-order renderables to allow for efficient
 * rendering. However clients can control ordering at a coarse level using <em>priority</em>.</p>
 *
 * <p>For example, this could be used to draw a semitransparent HUD, if a client wishes to
 * avoid using a separate View for the HUD. Note that priority is completely orthogonal to
 * {@link Builder#layerMask}, which merely controls visibility.</p>
 *
 * <p>The priority is clamped to the range [0..7], defaults to 4; 7 is lowest priority
 * (rendered last).</p>
 *
 * @see Builder#blendOrder
 */
- (instancetype) priority: (int) priority;
/**
 * Controls frustum culling, true by default.
 *
 * <p>Do not confuse frustum culling with backface culling. The latter is controlled via
 * the material.</p>
 */
- (instancetype) culling: (bool) enabled;
/**
 * Enables or disables a light channel. Light channel 0 is enabled by default.
 *
 * @param channel Light channel to enable or disable, between 0 and 7.
 * @param enable Whether to enable or disable the light channel.
 */
- (instancetype) lightChannel: (int) channel :(bool) enable;
/**
 * Specifies the number of draw instance of this renderable. The default is 1 instance and
 * the maximum number of instances allowed is 65535. 0 is invalid.
 * All instances are culled using the same bounding box, so care must be taken to make
 * sure all instances render inside the specified bounding box.
 * The material can use getInstanceIndex() in the vertex shader to get the instance index and
 * possibly adjust the position or transform.
 *
 * @param instanceCount the number of instances silently clamped between 1 and 65535.
 */
- (instancetype) instances: (uint16_t) instanceCount;
/**
 * Controls if this renderable casts shadows, false by default.
 *
 * If the View's shadow type is set to {@link View.ShadowType#VSM}, castShadows should only
 * be disabled if either is true:
 * <ul>
 *   <li>{@link RenderableManager#setReceiveShadows} is also disabled</li>
 *   <li>the object is guaranteed to not cast shadows on itself or other objects (for
 *   example, a ground plane)</li>
 * </ul>
 */
- (instancetype) castShadows: (bool) enabled;
/**
 * Controls if this renderable receives shadows, true by default.
 */
- (instancetype) receiveShadows: (bool) enabled;
/**
 * Controls if this renderable uses screen-space contact shadows. This is more
 * expensive but can improve the quality of shadows, especially in large scenes.
 * (off by default).
 */
- (instancetype) screenSpaceContactShadows: (bool) enabled;
/**
 * Allows bones to be swapped out and shared using SkinningBuffer.
 *
 * If skinning buffer mode is enabled, clients must call #setSkinningBuffer() rather than
 * #setBonesAsQuaternions(). This allows sharing of data between renderables.
 *
 * @param enabled If true, enables buffer object mode.  False by default.
 */
- (instancetype) enableSkinningBuffers: (bool) enabled;
// TODO: Skinning & Morphing functions

- (instancetype) build: (Engine*) engine :(Entity) entity;

NS_ASSUME_NONNULL_END
@end


#endif /* RenderableBuilder_h */
