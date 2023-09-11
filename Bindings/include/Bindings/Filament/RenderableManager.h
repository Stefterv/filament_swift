//
//  RenderableManager.h

//  Created by Stef Tervelde on 30.06.22.
//
#import <Foundation/Foundation.h>
#import "Box.h"
#import "MaterialInstance.h"
#import "VertexBuffer.h"
#import "IndexBuffer.h"
#import "Entity.h"
#import "SkinningBuffer.h"
#import "MorphTargetBuffer.h"

#ifndef RenderableManager_h
#define RenderableManager_h

typedef NS_ENUM(NSInteger, PrimitiveType) {
    PrimitiveTypePoints = 0,
    PrimitiveTypeLines = 1,
    PrimitiveTypeLineStrip = 3,
    PrimitiveTypeTriangles = 4,
    PrimitiveTypeTriangleStrip = 5
};

/**
 * Factory and manager for \em renderables, which are entities that can be drawn.
 *
 * Renderables are bundles of \em primitives, each of which has its own geometry and material. All
 * primitives in a particular renderable share a set of rendering attributes, such as whether they
 * cast shadows or use vertex skinning.
 *
 * Usage example:
 *
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * auto renderable = utils::EntityManager::get().create();
 *
 * RenderableManager::Builder(1)
 *         .boundingBox({{ -1, -1, -1 }, { 1, 1, 1 }})
 *         .material(0, matInstance)
 *         .geometry(0, RenderableManager::PrimitiveType::TRIANGLES, vertBuffer, indBuffer, 0, 3)
 *         .receiveShadows(false)
 *         .build(engine, renderable);
 *
 * scene->addEntity(renderable);
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *
 * To modify the state of an existing renderable, clients should first use RenderableManager
 * to get a temporary handle called an \em instance. The instance can then be used to get or set
 * the renderable's state. Please note that instances are ephemeral; clients should store entities,
 * not instances.
 *
 * - For details about constructing renderables, see RenderableManager::Builder.
 * - To associate a 4x4 transform with an entity, see TransformManager.
 * - To associate a human-readable label with an entity, see utils::NameComponentManager.
 */

@interface RenderableManager : NSObject

@property (nonatomic, readonly, nonnull) void* manager  NS_SWIFT_UNAVAILABLE("Don't access the raw pointers");
- (nonnull id) init: (nonnull void*) manager NS_SWIFT_UNAVAILABLE("Instances are created internally");
- (nonnull id) init NS_UNAVAILABLE;
/**
 * Checks if the given entity already has a renderable component.
 */
- (bool) hasComponent: (Entity) e;

/**
 * Gets a temporary handle that can be used to access the renderable state.
 *
 * @return Non-zero handle if the entity has a renderable component, 0 otherwise.
 */
- (EntityInstance) getInstance: (Entity) e;
/**
 * Destroys the renderable component in the given entity.
 */
- (void) destroy: (Entity) e;
/**
 * Changes the bounding box used for frustum culling.
 *
 * @see Builder#boundingBox
 * @see RenderableManager#getAxisAlignedBoundingBox
 */
- (void) setAxisAlignedBoundingBox: (EntityInstance) instance :(Box) aabb;
/**
 * Changes the visibility bits.
 *
 * @see Builder#layerMask
 * @see View#setVisibleLayers
 */
- (void) setLayerMask: (EntityInstance) instance :(uint8_t) select :(uint8_t) value;
/**
 * Changes the coarse-level draw ordering.
 *
 * \see Builder::priority().
 */
- (void) setPriority: (EntityInstance) instance :(int) priority;
/**
 * Changes the channel a renderable is associated to.
 *
 * \see Builder::channel().
 */
- (void) setChannel: (EntityInstance) instance :(uint8_t) channel;
/**
 * Changes whether or not frustum culling is on.
 *
 * \see Builder::culling()
 */
- (void) setCulling: (EntityInstance) instance :(bool) enabled;
/**
 * Changes whether or not the large-scale fog is applied to this renderable
 * @see Builder::fog()
 */
- (void) setFogEnabled: (EntityInstance) instance :(bool) enable;

/**
 * Returns whether large-scale fog is enabled for this renderable.
 * @return True if fog is enabled for this renderable.
 * @see Builder::fog()
 */
- (bool) getFogEnabled: (EntityInstance) instance;
/**
 * Enables or disables a light channel.
 * Light channel 0 is enabled by default.
 *
 * @param i        Instance of the component obtained from getInstance().
 * @param channel  Light channel to set
 * @param enable   true to enable, false to disable
 *
 * @see Builder#lightChannel
 */
- (void) setLightChannel: (EntityInstance) instance :(uint8_t) channel :(bool) value;
/**
 * Returns whether a light channel is enabled on a specified renderable.
 * @param i        Instance of the component obtained from getInstance().
 * @param channel  Light channel to query
 * @return         true if the light channel is enabled, false otherwise
 */
- (bool) getLightChannel: (EntityInstance) instance :(uint8_t) channel;
/**
 * Changes whether or not the renderable casts shadows.
 *
 * \see Builder::castShadows()
 */
- (void) setCastShadows: (EntityInstance) instance :(bool) enabled;
/**
 * Changes whether or not the renderable can receive shadows.
 *
 * \see Builder::receiveShadows()
 */
- (void) setReceiveShadows: (EntityInstance) instance :(bool) enabled;
/**
 * Changes whether or not the renderable can use screen-space contact shadows.
 *
 * \see Builder::screenSpaceContactShadows()
 */
- (void) setScreenSpaceContactShadows: (EntityInstance) instance :(bool) enabled;
/**
 * Checks if the renderable can cast shadows.
 *
 * \see Builder::castShadows().
 */
- (bool) isShadowCaster: (EntityInstance) instance;
/**
 * Checks if the renderable can receive shadows.
 *
 * \see Builder::receiveShadows().
 */
- (bool) isShadowReceiver: (EntityInstance) instance;
/**
 * Updates the bone transforms in the range [offset, offset + boneCount).
 * The bones must be pre-allocated using Builder::skinning().
 */
- (void) setBones: (EntityInstance) instance :(nonnull const simd_float4*) transforms :(size_t) boneCount :(size_t) offset;
/**
 * Associates a region of a SkinningBuffer to a renderable instance
 *
 * Note: due to hardware limitations offset + 256 must be smaller or equal to
 *       skinningBuffer->getBoneCount()
 *
 * @param instance          Instance of the component obtained from getInstance().
 * @param skinningBuffer    skinning buffer to associate to the instance
 * @param count             Size of the region in bones, must be smaller or equal to 256.
 * @param offset            Start offset of the region in bones
*/
- (void) setSkinningBuffer: (EntityInstance) instance :(nonnull SkinningBuffer*) skinningBuffer :(size_t) count :(size_t) offset;
/**
 * Updates the vertex morphing weights on a renderable, all zeroes by default.
 *
 * The renderable must be built with morphing enabled, see Builder::morphing(). In legacy
 * morphing mode, only the first 4 weights are considered.
 *
 * @param instance Instance of the component obtained from getInstance().
 * @param weights Pointer to morph target weights to be update.
 * @param count Number of morph target weights.
 * @param offset Index of the first morph target weight to set at instance.
 */
- (void) setMorphWeights: (EntityInstance) instance :(nonnull float const*) weights :(size_t) count :(size_t) offset;

/**
 * Associates a MorphTargetBuffer to the given primitive.
 */
- (void) setMorphTargetBufferAt: (EntityInstance) instance :(uint8_t) level :(size_t) primitiveIndex :(nonnull MorphTargetBuffer*) morphTargetBuffer :(size_t) offset :(size_t) count;

/**
 * Utility method to change a MorphTargetBuffer to the given primitive
 */
- (void) setMorphTargetBufferAt: (EntityInstance) instance :(uint8_t) level :(size_t) primitiveIndex :(nonnull MorphTargetBuffer*) morphTargetBuffer;

/**
 * Get a MorphTargetBuffer to the given primitive or null if it doesn't exist.
 */
- (nullable MorphTargetBuffer*) getMorphTargetBufferAt: (EntityInstance) instance :(uint8_t) level :(size_t) primitiveIndex;

/**
 * Gets the number of morphing in the given entity.
 */
- (size_t) getMorphTargetCount: (EntityInstance) instance;
/**
 * Gets the bounding box used for frustum culling.
 *
 * \see Builder::boundingBox()
 * \see RenderableManager::setAxisAlignedBoundingBox()
 */
- (Box) getAxisAlignedBoundingBox: (EntityInstance) instance;
/**
 * Get the visibility bits.
 *
 * \see Builder::layerMask()
 * \see View::setVisibleLayers().
 * \see RenderableManager::getLayerMask()
 */
- (uint8_t) getLayerMask: (EntityInstance) instance;
/**
 * Gets the immutable number of primitives in the given renderable.
 */
- (size_t) getPrimitiveCount: (EntityInstance) instance;
/**
 * Changes the material instance binding for the given primitive.
 *
 * The MaterialInstance's material must have a feature level equal or lower to the engine's
 * selected feature level.
 *
 * @exception utils::PreConditionPanic if the engine doesn't support the material's
 *                                     feature level.
 *
 * @see Builder::material()
 * @see Engine::setActiveFeatureLevel
 */
- (void) setMaterialInstanceAt: (EntityInstance) instance :(int) primitiveIndex :(nonnull MaterialInstance*) materialInstance;
/**
 * Retrieves the material instance that is bound to the given primitive.
 */
- (nonnull MaterialInstance*) getMaterialInstanceAt: (EntityInstance) instance :(int) primitiveIndex;
/**
 * Changes the geometry for the given primitive.
 *
 * \see Builder::geometry()
 */
- (void) setGeometryAt: (EntityInstance) instance :(int) primitiveIndex :(PrimitiveType) type :(nonnull VertexBuffer*) vertices :(nonnull IndexBuffer*) indices :(int) offset :(int) count;
/**
* Changes the drawing order for blended primitives. The drawing order is either global or
* local (default) to this Renderable. In either case, the Renderable priority takes precedence.
*
* @see Builder#blendOrder
*
* @param instance the renderable of interest
* @param primitiveIndex the primitive of interest
* @param blendOrder draw order number (0 by default). Only the lowest 15 bits are used.
*/
- (void) setBlendOrderAt: (EntityInstance) instance :(int) primitiveIndex :(int) blendOrder;
/**
 * Changes whether the blend order is global or local to this Renderable (by default).
 *
 * @see Builder#globalBlendOrderEnabled
 *
 * @param instance the renderable of interest
 * @param primitiveIndex the primitive of interest
 * @param enabled true for global, false for local blend ordering.
 */
- (void) setGlobalBlendOrderEnabledAt: (EntityInstance) instance :(int) primitiveIndex :(int) blendOrder;
/**
 * Retrieves the set of enabled attribute slots in the given primitive's VertexBuffer.
 */
- (u_int32_t) getEnabledAttributesAt: (EntityInstance) instance :(size_t) primitiveIndex;
@end


#endif /* RenderableManager_h */
