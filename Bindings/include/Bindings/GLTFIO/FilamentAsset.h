//
//  FilamentAsset.h

//  Created by Stef Tervelde on 30.06.22.
//
#import <Foundation/Foundation.h>
#import "../Utils/Entity.h"
#import "../Filament/MaterialInstance.h"
#import "../Filament/Box.h"
#import "Animator.h"

#ifndef FilamentAsset_h
#define FilamentAsset_h

NS_SWIFT_NAME(glTFIO.FilamentAsset)
@interface FilamentAsset : NSObject

@property (nonatomic, readonly, nonnull) void* asset  NS_SWIFT_UNAVAILABLE("Don't access the raw pointers");
- (nonnull id) init: (nonnull void*) asset NS_SWIFT_UNAVAILABLE("Create a new renderer with engine.createRenderer");
- (nonnull id) init NS_UNAVAILABLE;

- (Entity) getRoot;
/**
 * Pops a ready renderable off the queue, or returns 0 if no renderables have become ready.
 *
 * NOTE: To determine the progress percentage or completion status, please use
 * ResourceLoader#asyncGetLoadProgress.
 *
 * This helper method allows clients to progressively add renderables to the scene as textures
 * gradually become ready through asynchronous loading.
 *
 * See also ResourceLoader#asyncBeginLoad.
 */
- (Entity) popRenderable;
/**
 * Pops one or more renderables off the queue, or returns the available number.
 *
 * Returns the number of entities written into the given array. If the given array
 * is null, returns the number of available renderables.
 */
- (size_t) popRenderables: (nullable NSMutableArray<NSNumber *>*) entities;
+ (nonnull NSArray<NSNumber*>*) getEntitiesArray: (nonnull const void*) array :(unsigned long)count NS_SWIFT_UNAVAILABLE("Internal method");
/**
 * Gets the list of entities, one for each glTF node.
 *
 * <p>All of these have a transform component. Some of the returned entities may also have a
 * renderable or light component.</p>
 */
- (nonnull NSArray<NSNumber*>*) getEntities;
- (nonnull NSArray<NSNumber*>*) getRenderableEntities;
/**
 * Gets only the entities that have camera components.
 *
 * <p>
 * Note about aspect ratios:<br>
 *
 * gltfio always uses an aspect ratio of 1.0 when setting the projection matrix for perspective
 * cameras. gltfio then sets the camera's scaling matrix with the aspect ratio specified in the
 * glTF file (if present).<br>
 *
 * The camera's scaling matrix allows clients to adjust the aspect ratio independently from the
 * camera's projection.
 * </p>
 *
 * @see com.google.android.filament.Camera#setScaling
 */
- (nonnull NSArray<NSNumber*>*) getCameraEntities;
- (Entity) getFirstEntityByName: (nonnull NSString*) name;
- (nonnull NSArray<NSNumber*>*) getEntitiesByName: (nonnull NSString*) name;
- (nonnull NSArray<NSNumber*>*) getEntitiesByPrefix: (nonnull NSString*) prefix;
- (nonnull NSArray<MaterialInstance*>*) getMaterialInstances;
- (nonnull Box*) getBoundingBox;
- (nonnull NSString*) getName: (Entity) entity;
- (nullable NSString*) getExtras: (Entity) entity;
- (nonnull Animator*) getAnimator;
- (size_t) getSkinCount;
- (nonnull NSArray<NSString*>*) getSkinNames;
- (nonnull NSArray<NSString*>*) getResourceUris;
- (nonnull NSArray<NSString*>*) getMaterialVariantNames;
/**
 * Applies the given material variant to all primitives that it affects.
 *
 * This is efficient because it merely swaps around persistent MaterialInstances. If you change
 * a material parameter while a certain variant is active, the updated value will be remembered
 * after you re-apply that variant.
 *
 * If the asset is instanced, this affects all instances in the same way.
 * To set the variant on an individual instance, use FilamentInstance#applyMaterialVariant.
 *
 * Ignored if variantIndex is out of bounds.
 */
- (void) applyMaterialVariant: (int) variantIndex;

@end


#endif /* FilamentAsset_h */
