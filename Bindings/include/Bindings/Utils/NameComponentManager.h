//
//  NameComponentManager.h
//  swift-gltf-viewer
//
//  Created by Stef Tervelde on 10.09.23.
//
#import <Foundation/Foundation.h>

#ifndef NameComponentManager_h
#define NameComponentManager_h

@interface NameComponentManager : NSObject

@property (nonatomic, readonly, nonnull) void* manager  NS_SWIFT_UNAVAILABLE("Don't access the raw pointers");
- (nonnull id) init: (nonnull void*) manager NS_SWIFT_UNAVAILABLE("Instances are created internally");
- (nonnull id) init NS_UNAVAILABLE;

@end

#warning("TODO")

#endif /* NameComponentManager_h */
