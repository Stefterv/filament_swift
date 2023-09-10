//
//  BufferObjectBuilder.h
//  swift-gltf-viewer
//
//  Created by Stef Tervelde on 10.09.23.
//
#import <Foundation/Foundation.h>

#ifndef BufferObjectBuilder_h
#define BufferObjectBuilder_h

@interface BufferObjectBuilder : NSObject

@property (nonatomic, readonly, nonnull) void* Builder  NS_SWIFT_UNAVAILABLE("Don't access the raw pointers");
- (nonnull id) init: (nonnull void*) Builder NS_SWIFT_UNAVAILABLE("Instances are created internally");
- (nonnull id) init NS_UNAVAILABLE;

#warning("TODO")


@end


#endif /* BufferObjectBuilder_h */
