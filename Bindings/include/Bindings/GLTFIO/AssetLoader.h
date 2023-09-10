//
//  AssetLoader.h

//  Created by Stef Tervelde on 30.06.22.
//
#import <Foundation/Foundation.h>
#import "../Filament/Engine.h"
#import "../Utils/NameComponentManager.h"
#import "MaterialProvider.h"
#import "FilamentAsset.h"
#import "FilamentInstance.h"

#ifndef AssetLoader_h
#define AssetLoader_h

/**
 * Consumes a blob of glTF 2.0 content (either JSON or GLB) and produces a {@link FilamentAsset}
 * object, which is a bundle of Filament entities, material instances, textures, vertex buffers,
 * and index buffers.
 *
 * <p>AssetLoader does not fetch external buffer data or create textures on its own. Clients can use
 * the provided {@link ResourceLoader} class for this, which obtains the URI list from the asset.</p>
 *
 * @see Animator
 * @see FilamentAsset
 * @see ResourceLoader
 */

NS_SWIFT_NAME(AssetLoader.Configuration)
@interface AssetConfiguration : NSObject
@property (nonnull) Engine* engine;
@property (nonnull) MaterialProvider* materials;
@property (nullable) EntityManager* entities;
@property (nullable) NameComponentManager* names;

@end

NS_SWIFT_NAME(glTFIO.AssetLoader)
@interface AssetLoader : NSObject

@property (nonatomic, readonly, nonnull) void* loader  NS_SWIFT_UNAVAILABLE("Don't access the raw pointers");
- (nonnull id) init: (nonnull void*) loader NS_SWIFT_UNAVAILABLE("Instances are created internally");
- (nonnull id) init NS_UNAVAILABLE;

+ (nonnull instancetype) create: (nonnull AssetConfiguration*) config;

- (nullable FilamentAsset*) createAssetFromJson: (nonnull NSData*) bytes;
- (nullable FilamentAsset*) createAssetFromBinary: (nonnull NSData*) bytes;
/**
 * Consumes the contents of a glTF 2.0 file and produces a primary asset with one or more
 * instances. The primary asset has ownership over the instances.
 *
 * The returned instances share their textures, material instances, and vertex buffers with the
 * primary asset. However each instance has its own unique set of entities, transform
 * components, and renderable components. Instances are freed when the primary asset is freed.
 *
 * Light components are not instanced, they belong only to the primary asset.
 *
 * Clients must use ResourceLoader to load resources on the primary asset.
 *
 * The entity accessor and renderable stack API in the primary asset can be used to control the
 * union of all instances. The individual FilamentInstance objects can be used to access each
 * instance's partition of entities.  Similarly, the Animator in the primary asset controls all
 * instances. To animate instances individually, use FilamentInstance::getAnimator().
 *
 * @param bytes the contents of a glTF 2.0 file (JSON or GLB)
 * @param numBytes the number of bytes in "bytes"
 * @param instances destination pointer, to be populated by the requested number of instances
 * @param numInstances requested number of instances
 * @return the primary asset that has ownership over all instances
 */
- (nullable FilamentAsset*) createInstancedAsset: (nonnull NSArray*) bytes :(nonnull NSMutableArray<FilamentInstance*>*) instances;
/**
 * Adds a new instance to an instanced asset.
 *
 * Use this with caution. It is more efficient to pre-allocate a max number of instances, and
 * gradually add them to the scene as needed. Instances can also be "recycled" by removing and
 * re-adding them to the scene.
 *
 * NOTE: destroyInstance() does not exist because gltfio favors flat arrays for storage of
 * entity lists and instance lists, which would be slow to shift. We also wish to discourage
 * create/destroy churn, as noted above.
 *
 * This cannot be called after FilamentAsset::releaseSourceData().
 * This cannot be called on a non-instanced asset.
 * See also AssetLoader::createInstancedAsset().
 */
- (nullable FilamentInstance*) createInstance: (nonnull FilamentAsset*) primary;
/**
 * Destroys the given asset and all of its associated Filament objects.
 *
 * This destroys entities, components, material instances, vertex buffers, index buffers,
 * and textures. This does not necessarily immediately free all source data, since
 * texture decoding or GPU uploading might be underway.
 */
- (void) destroyAsset: (nonnull FilamentAsset*) asset;


@end


#endif /* AssetLoader_h */
