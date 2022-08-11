//
//  RenderableManager.h

//  Created by Stef Tervelde on 30.06.22.
//
#import <Foundation/Foundation.h>
#import "Box.h"
#import "MaterialInstance.h"
#import "VertexBuffer.h"
#import "IndexBuffer.h"
#import "../Utils/Entity.h"

#ifndef RenderableManager_h
#define RenderableManager_h

@interface RenderableManager : NSObject

@property (nonatomic, readonly, nonnull) void* manager  NS_SWIFT_UNAVAILABLE("Don't access the raw pointers");
- (nonnull id) init: (nonnull void*) manager NS_SWIFT_UNAVAILABLE("Create a new renderer with engine.createRenderer");
- (nonnull id) init NS_UNAVAILABLE;
typedef NS_ENUM(NSInteger, PrimitiveType) {
    PrimitiveTypePoints = 0,
    PrimitiveTypeLines = 1,
    PrimitiveTypeLineStrip = 3,
    PrimitiveTypeTriangles = 4,
    PrimitiveTypeTriangleStrip = 5
};
// TODO: Skinning & Morphing functions
/**
 * Changes the bounding box used for frustum culling.
 *
 * @see Builder#boundingBox
 * @see RenderableManager#getAxisAlignedBoundingBox
 */
- (void) setAxisAlignedBoundingBox: (EntityInstance) instance :(nonnull Box*) aabb;
/**
 * Changes the visibility bits.
 *
 * @see Builder#layerMask
 * @see View#setVisibleLayers
 */
- (void) setLayerMask: (EntityInstance) instance :(uint8_t) select :(uint8_t) value;
- (void) setPriority: (EntityInstance) instance :(int) priority;
- (void) setCulling: (EntityInstance) instance :(bool) enabled;
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

- (void) setCastShadows: (EntityInstance) instance :(bool) enabled;
- (void) setReceiveShadows: (EntityInstance) instance :(bool) enabled;
- (void) setScreenSpaceContactShadows: (EntityInstance) instance :(bool) enabled;
- (bool) isShadowCaster: (EntityInstance) instance;
- (bool) isShadowReceiver: (EntityInstance) instance;
- (nonnull Box*) getAxisAlignedBoundingBox: (EntityInstance) instance;
- (size_t) getPrimitiveCount: (EntityInstance) instance;
- (void) setMaterialInstanceAt: (EntityInstance) instance :(int) primitiveIndex :(nonnull MaterialInstance*) materialInstance;
- (nonnull MaterialInstance*) getMaterialInstanceAt: (EntityInstance) instance :(int) primitiveIndex;
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
@end


#endif /* RenderableManager_h */
