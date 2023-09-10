//
//  EntityManager.h

//  Created by Stef Tervelde on 29.06.22.
//

#import <Foundation/Foundation.h>
#import "Entity.h"

#ifndef EntityManager_h
#define EntityManager_h

@interface EntityManager : NSObject

@property (nonatomic, readonly, nonnull) void* manager NS_SWIFT_UNAVAILABLE("Don't access the raw pointers");
- (nonnull id) init: (nonnull void*) manager NS_SWIFT_UNAVAILABLE("Instances are created internally");
- (nonnull id) init NS_UNAVAILABLE;

- (Entity) create;
- (void) destroy: (Entity) entity;
- (bool) isAlive: (Entity) entity;

+ (nonnull instancetype) get;
@end

#endif /* EntityManager_h */
