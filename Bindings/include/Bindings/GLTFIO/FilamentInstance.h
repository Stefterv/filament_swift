//
//  FilamentInstance.h
//  swift-gltf-viewer
//
//  Created by Stef Tervelde on 30.06.22.
//
#import <Foundation/Foundation.h>
#import "FilamentAsset.h"

#ifndef FilamentInstance_h
#define FilamentInstance_h

NS_SWIFT_NAME(glTFIO.FilamentInstance)
@interface FilamentInstance : NSObject

@property (nonatomic, readonly, nonnull) void* instance  NS_SWIFT_UNAVAILABLE("Don't access the raw pointers");
- (nonnull id) init: (nonnull void*) instance NS_SWIFT_UNAVAILABLE("Create a new renderer with engine.createRenderer");
- (nonnull id) init NS_UNAVAILABLE;

- (nonnull FilamentAsset*) getAsset;
- (Entity) getRoot;

- (nonnull NSArray<NSNumber*>*) getEntities;
- (nonnull Animator*) getAnimator;
- (void) applyMaterialVariant: (size_t) index;

+ (nonnull NSArray<NSNumber*>*)getEntitiesArray: (nonnull const void*) array :(unsigned long)count;

@end


#endif /* FilamentInstance_h */
