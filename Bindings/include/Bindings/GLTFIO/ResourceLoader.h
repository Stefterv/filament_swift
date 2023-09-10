//
//  ResourceLoader.h

//  Created by Stef Tervelde on 30.06.22.
//
#import <Foundation/Foundation.h>
#import "../Filament/Engine.h"
#import "TextureProvider.h"
#import "FilamentAsset.h"

#ifndef ResourceLoader_h
#define ResourceLoader_h

NS_SWIFT_NAME(glTFIO.ResourceConfiguration)
@interface ResourceConfiguration : NSObject
@property (nonnull) Engine* engine;
@property (nonnull) NSString* path;
@property (nonnull) bool* normalizeSkinningWeights;
@end


NS_SWIFT_NAME(glTFIO.ResourceLoader)
@interface ResourceLoader : NSObject

@property (nonatomic, readonly, nonnull) void* loader  NS_SWIFT_UNAVAILABLE("Don't access the raw pointers");
- (nonnull id) init: (nonnull ResourceConfiguration *) config;
- (nonnull id) init NS_UNAVAILABLE;

/**
 * Feeds the binary content of an external resource into the loader's URI cache.
 *
 * On some platforms, `ResourceLoader` does not know how to download external resources on its
 * own (external resources might come from a filesystem, a database, or the internet) so this
 * method allows clients to download external resources and push them to the loader.
 *
 * Every resource should be passed in before calling #loadResources or #asyncBeginLoad. See
 * also FilamentAsset#getResourceUris.
 *
 * When loading GLB files (as opposed to JSON-based glTF files), clients typically do not
 * need to call this method.
 */
- (void) addResourceData: (nonnull NSString*) uri :(nonnull NSData*) buffer;


- (void) addTextureProvider: (nonnull NSString*) mimeType :(nonnull TextureProvider*) provider;
- (bool) hasResourceData: (nonnull NSString*) uri;
/**
 * Frees memory by evicting the URI cache that was populated via addResourceData.
 *
 * This can be called only after a model is fully loaded or after loading has been cancelled.
 */
- (void) evictResourceData;
/**
 * Iterates through all external buffers and images and creates corresponding Filament objects
 * (vertex buffers, textures, etc), which become owned by the asset.
 *
 * NOTE: this is a synchronous API, please see [asyncBeginLoad] as an alternative.
 *
 * @param asset the Filament asset that contains URI-based resources
 * @return self (for daisy chaining)
 */
- (nonnull instancetype) loadResources: (nonnull FilamentAsset*) asset;
/**
 * Starts an asynchronous resource load.
 *
 * Returns false if the loading process was unable to start.
 *
 * This is an alternative to #loadResources and requires periodic calls to #asyncUpdateLoad.
 * On multi-threaded systems this creates threads for texture decoding.
 */
- (bool) asyncBeginLoad: (nonnull FilamentAsset*) asset;

- (double) asyncGetLoadProgress;
/**
 * Updates an asynchronous load by performing any pending work that must take place
 * on the main thread.
 *
 * Clients must periodically call this until #asyncGetLoadProgress returns 100%.
 * After progress reaches 100%, calling this is harmless; it just does nothing.
 */
- (void) asyncUpdateLoad;
/**
 * Cancels pending decoder jobs and frees all CPU-side texel data.
 *
 * Calling this is only necessary if the asyncBeginLoad API was used
 * and cancellation is required before progress reaches 100%.
 */
- (void) asyncCancelLoad;


@end


#endif /* ResourceLoader_h */
