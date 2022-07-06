//
//  EntityManager.h
//  swift-gltf-viewer
//
//  Created by Stef Tervelde on 29.06.22.
//

#import <Foundation/Foundation.h>
#import "Entity.h"

#ifndef EntityManager_h
#define EntityManager_h

NS_SWIFT_NAME(Utils.EntityManager)
@interface EntityManager : NSObject

@property (nonatomic, readonly, nonnull) void* manager NS_SWIFT_UNAVAILABLE("Don't access the raw pointers");
- (nonnull id) init: (nonnull void*) manager NS_SWIFT_UNAVAILABLE("Create a new renderer with engine.createRenderer");
- (nonnull id) init NS_UNAVAILABLE;

- (Entity) create;
- (void) destroy: (Entity) entity;
- (bool) isAlive: (Entity) entity;

+ (nonnull instancetype) get;
@end

#endif /* EntityManager_h */
