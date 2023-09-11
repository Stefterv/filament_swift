//
//  FilamentAsset.h

//  Created by Stef Tervelde on 30.06.22.
//
#import <Foundation/Foundation.h>
#import "../Filament/Entity.h"
#import "../Filament/Box.h"

#ifndef FilamentAsset_h
#define FilamentAsset_h

@class FilamentInstance;
@class Animator;
@class Engine;
@class Scene;
@class SceneMask;

NS_SWIFT_NAME(glTFIO.FilamentAsset)
@interface FilamentAsset : NSObject

@property (nonatomic, readonly, nonnull) void* asset  NS_SWIFT_UNAVAILABLE("Don't access the raw pointers");
- (nonnull id) init: (nonnull void*) asset NS_SWIFT_UNAVAILABLE("Object is created internally");
- (nonnull id) init NS_UNAVAILABLE;
+ (nonnull NSArray<NSNumber*>*) getEntitiesArray: (nonnull const void*) array :(unsigned long)count NS_SWIFT_UNAVAILABLE("Internal method");
/**
 * Gets the list of entities, one for each glTF node.
 *
 * <p>All of these have a transform component. Some of the returned entities may also have a
 * renderable or light component.</p>
 */
- (nonnull NSArray<NSNumber*>*) getEntities;
/**
 * Gets the list of entities in the scene representing lights. All of these have a Light component.
 */
- (nonnull NSArray<NSNumber*>*) getLightEntities;
/**
 * Gets the list of entities in the asset that have renderable components.
 */
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
/**
* Gets the transform root for the asset, which has no matching glTF node.
*
* This node exists for convenience, allowing users to transform the entire asset. For instanced
* assets, this is a "super root" where each of its children is a root in a particular instance.
* This allows users to transform all instances en masse if they wish to do so.
*/
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
/** Gets resource URIs for all externally-referenced buffers. */
- (nonnull NSArray<NSString*>*) getResourceUris;
/**
 * Gets the bounding box computed from the supplied min / max values in glTF accessors.
 *
 * This does not return a bounding box over all FilamentInstance, it's just a straightforward
 * AAAB that can be determined at load time from the asset data.
 */
- (nonnull Aabb*) getBoundingBox;

/** Gets the NameComponentManager label for the given entity, if it exists. */
- (nonnull NSString*) getName: (Entity) entity;

/** Returns the first entity with the given name, or 0 if none exist. */
- (Entity) getFirstEntityByName: (nonnull NSString*) name;
/**
 * Gets a list of entities with the given name.
 *
 * @param name Null-terminated string to match.
 * @param maxCount Maximum number of entities to retrieve.
 *
 * @return array containing the entities
 */
- (nonnull NSArray<NSNumber*>*) getEntitiesByName: (nonnull NSString*) name :(size_t) maxCount;
/**
 * Gets a list of entities whose names start with the given prefix.
 *
 * @param prefix Null-terminated prefix string to match.
 * @param maxCount Maximum number of entities to retrieve.
 *
 * @return array containing the entities
 */
- (nonnull NSArray<NSNumber*>*) getEntitiesByPrefix: (nonnull NSString*) prefix :(size_t) maxCount;
/** Gets the glTF extras string for a specific node, or for the asset, if it exists. */
- (nullable NSString*) getExtras: (Entity) entity;
/**
* Gets the morph target name at the given index in the given entity.
*/
- (nonnull NSString*) getMorphTargetNameAt: (Entity) entity :(size_t) targetIndex;

/**
* Returns the number of morph targets in the given entity.
*/
- (size_t) getMorphTargetCountAt: (Entity) entity;

/**
* Lazily creates a single LINES renderable that draws the transformed bounding-box hierarchy
* for diagnostic purposes. The wireframe is owned by the asset so clients should not delete it.
*/
- (Entity) getWireframe;

/**
* Returns the Filament engine associated with the AssetLoader that created this asset.
*/
- (nonnull Engine*) getEngine;

/**
* Reclaims CPU-side memory for URI strings, binding lists, and raw animation data.
*
* This should only be called after ResourceLoader::loadResources().
* If this is an instanced asset, this prevents creation of new instances.
*/
- (void) releaseSourceData;

/**
* Returns a weak reference to the underlying cgltf hierarchy. This becomes invalid after
* calling releaseSourceData().
*/
- (nullable const void*) getSourceAsset;

/**
* Returns the number of scenes in the asset.
*/
- (size_t) getSceneCount;

/**
* Returns the name of the given scene.
*
* Returns null if the given scene does not have a name or is out of bounds.
*/
- (nonnull NSString*) getSceneName: (size_t) sceneIndex;

/**
* Adds entities to a Filament scene only if they belong to at least one of the given glTF
* scenes.
*
* This is just a helper that provides an alternative to directly calling scene->addEntities()
* and provides filtering functionality.
*/
- (void) addEntitiesToScene: (nonnull Scene*) targetScene :(nonnull NSArray<NSNumber*>*) entities :(uint32_t) sceneFilter;

/**
* Releases ownership of entities and their Filament components.
*
* This makes the client take responsibility for destroying Filament
* components (e.g. Renderable, TransformManager component) as well as
* the underlying entities.
*/
- (void) detachFilamentComponents;

- (bool) areFilamentComponentsDetached;

/**
* Convenience function to get the first instance, or null if it doesn't exist.
*/
- (nonnull FilamentInstance*) getInstance;
@end


#endif /* FilamentAsset_h */
