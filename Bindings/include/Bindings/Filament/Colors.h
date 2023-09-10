//
//  Colors.h
//  swift-gltf-viewer
//
//  Created by Stef Tervelde on 10.09.23.
//
#import <Foundation/Foundation.h>

#ifndef Colors_h
#define Colors_h

@interface Colors : NSObject

@property (nonatomic, readonly, nonnull) void* Colors  NS_SWIFT_UNAVAILABLE("Don't access the raw pointers");
- (nonnull id) init: (nonnull void*) Colors NS_SWIFT_UNAVAILABLE("Instances are created internally");
- (nonnull id) init NS_UNAVAILABLE;

@end

#endif /* Colors_h */
