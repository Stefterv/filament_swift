//
//  FilamentInstance.h

//  Created by Stef Tervelde on 30.06.22.
//
#import <Foundation/Foundation.h>
#import "../Filament/Entity.h"
#import "../Filament/MaterialInstance.h"
#import <simd/simd.h>


#ifndef FilamentInstance_h
#define FilamentInstance_h

@class FilamentAsset;
@class Animator;

NS_SWIFT_NAME(glTFIO.FilamentInstance)
@interface FilamentInstance : NSObject

@property (nonatomic, readonly, nonnull) void* instance  NS_SWIFT_UNAVAILABLE("Don't access the raw pointers");
- (nonnull id) init: (nonnull void*) instance NS_SWIFT_UNAVAILABLE("Instances are created internally");
- (nonnull id) init NS_UNAVAILABLE;

/**
 * Gets the owner of this instance.
 */
- (nonnull FilamentAsset*) getAsset;
/**
 * Gets the list of entities in this instance, one for each glTF node. All of these have a
 * Transform component. Some of the returned entities may also have a Renderable component or
 * Name component.
 */
- (nonnull NSArray<NSNumber*>*) getEntities;
+ (nonnull NSArray<NSNumber*>*) getEntitiesArray: (nonnull const void*) array :(unsigned long)count;
/** Gets the transform root for the instance, which has no matching glTF node. */
- (Entity) getRoot;
/**
 * Applies the given material variant to all primitives in this instance.
 *
 * Ignored if variantIndex is out of bounds.
 */
- (void) applyMaterialVariant: (size_t) index;

/**
 * Returns the number of material variants in the asset.
 */
- (size_t) getMaterialVariantCount;

/**
 * Returns the name of the given material variant, or null if it is out of bounds.
 */
- (nullable NSString*) getMaterialVariantName: (size_t) variantIndex;
/**
 * Returns the animation engine for the instance.
 *
 * Note that an animator can be obtained either from an individual instance, or from the
 * originating FilamentAsset. In the latter case, the animation frame is shared amongst all
 * instances. If individual control is desired, users must obtain the animator from the
 * individual instances.
 *
 * The animator is owned by the asset and should not be manually deleted.
 */
- (nonnull Animator*) getAnimator;
/**
 * Gets the number of skins.
 */
- (size_t) getSkinCount;

/**
 * Gets the skin name at skin index.
 */
- (nonnull NSString*) getSkinNameAt: (size_t) skinIndex;

/**
 * Gets joints at skin index.
 */
- (nonnull NSArray<NSNumber*>*) getJointsAt: (size_t) skinIndex;

/**
 * Attaches the given skin to the given node, which must have an associated mesh with
 * BONE_INDICES and BONE_WEIGHTS attributes.
 *
 * This is a no-op if the given skin index or target is invalid.
 */
- (void) attachSkin: (size_t) skinIndex :(Entity) target;

/**
 * Detaches the given skin from the given node.
 *
 * This is a no-op if the given skin index or target is invalid.
 */
- (void) detachSkin: (size_t) skinIndex :(Entity) target;

/**
 * Gets inverse bind matrices for all joints at the given skin index.
 *
 * See getJointCountAt for determining the number of matrices returned (i.e. the number of joints).
 */
- (nonnull const simd_float4x4*) getInverseBindMatricesAt: (size_t) skinIndex;

/**
 * Resets the AABB on all renderables by manually computing the bounding box.
 *
 * THIS IS ONLY USEFUL FOR MALFORMED ASSETS THAT DO NOT HAVE MIN/MAX SET UP CORRECTLY.
 *
 * Does not affect the return value of getBoundingBox() on the owning asset.
 * Cannot be called after releaseSourceData() on the owning asset.
 * Can only be called after loadResources() or asyncBeginLoad().
 */
- (void) recomputeBoundingBoxes;

/**
 * Gets the axis-aligned bounding box from the supplied min / max values in glTF accessors.
 *
 * If recomputeBoundingBoxes() has been called, then this returns the recomputed AABB.
 */
//- (Aabb) getBoundingBox;

/** Gets all material instances. These are already bound to renderables. */
- (nonnull NSArray<MaterialInstance*>*) getMaterialInstances;

/**
 * Releases ownership of material instances.
 *
 * This makes the client take responsibility for destroying MaterialInstance
 * objects. The getMaterialInstances query becomes invalid after detachment.
 */
- (void) detachMaterialInstances;
@end


#endif /* FilamentInstance_h */
