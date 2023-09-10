//
//  FilamentInstance.h

//  Created by Stef Tervelde on 30.06.22.
//
#import <Foundation/Foundation.h>
#import "../Filament/Entity.h"

#ifndef FilamentInstance_h
#define FilamentInstance_h

@class FilamentAsset;
@class Animator;

NS_SWIFT_NAME(glTFIO.FilamentInstance)
@interface FilamentInstance : NSObject

@property (nonatomic, readonly, nonnull) void* instance  NS_SWIFT_UNAVAILABLE("Don't access the raw pointers");
- (nonnull id) init: (nonnull void*) instance NS_SWIFT_UNAVAILABLE("Instances are created internally");
- (nonnull id) init NS_UNAVAILABLE;

- (nonnull FilamentAsset*) getAsset;
- (Entity) getRoot;

- (nonnull NSArray<NSNumber*>*) getEntities;
- (nonnull Animator*) getAnimator;
- (void) applyMaterialVariant: (size_t) index;

+ (nonnull NSArray<NSNumber*>*)getEntitiesArray: (nonnull const void*) array :(unsigned long)count;
#warning("TODO Comments")
@end


#endif /* FilamentInstance_h */
