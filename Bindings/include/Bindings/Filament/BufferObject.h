//
//  BufferObject.h
//  swift-gltf-viewer
//
//  Created by Stef Tervelde on 10.09.23.
//
#import <Foundation/Foundation.h>
#import "Engine.h"

#ifndef BufferObject_h
#define BufferObject_h

@interface BufferObject : NSObject

@property (nonatomic, readonly, nonnull) void* BufferObject  NS_SWIFT_UNAVAILABLE("Don't access the raw pointers");
- (nonnull id) init: (nonnull void*) BufferObject NS_SWIFT_UNAVAILABLE("Instances are created internally");
- (nonnull id) init NS_UNAVAILABLE;

/**
 * Asynchronously copy-initializes a region of this BufferObject from the data provided.
 *
 * @param engine Reference to the filament::Engine associated with this BufferObject.
 * @param buffer A BufferDescriptor representing the data used to initialize the BufferObject.
 * @param byteOffset Offset in bytes into the BufferObject
 */
- (void) setBuffer: (nonnull Engine*) engine :(nonnull NSData*) buffer :(uint32_t) byteOffset;

/**
 * Returns the size of this BufferObject in elements.
 * @return The maximum capacity of the BufferObject.
 */
- (size_t) getByteCount;

@end


#endif /* BufferObject_h */
