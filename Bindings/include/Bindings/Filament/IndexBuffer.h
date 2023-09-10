//
//  IndexBuffer.h
//
//  Created by Stef Tervelde on 30.06.22.
//
#import <Foundation/Foundation.h>



#ifndef IndexBuffer_h
#define IndexBuffer_h

@class Engine;

@interface IndexBuffer : NSObject

@property (nonatomic, readonly, nonnull) void* buffer  NS_SWIFT_UNAVAILABLE("Don't access the raw pointers");
- (nonnull id) init: (nonnull void*) buffer NS_SWIFT_UNAVAILABLE("Instances are created internally");
- (nonnull id) init NS_UNAVAILABLE;
/**
 * Asynchronously copy-initializes a region of this IndexBuffer from the data provided.
 *
 * @param engine Reference to the filament::Engine to associate this IndexBuffer with.
 * @param buffer A BufferDescriptor representing the data used to initialize the IndexBuffer.
 *               BufferDescriptor points to raw, untyped data that will be interpreted as
 *               either 16-bit or 32-bits indices based on the Type of this IndexBuffer.
 * @param byteOffset Offset in *bytes* into the IndexBuffer
 */
- (void) setBuffer: (nonnull Engine*) engine :(nonnull NSData*) buffer :(uint32_t) byteOffset;
- (void) setBuffer: (nonnull Engine*) engine :(nonnull NSData*) buffer;
/**
 * Returns the size of this IndexBuffer in elements.
 * @return The number of indices the IndexBuffer holds.
 */
- (size_t) getIndexCount;
@end

#endif /* IndexBuffer_h */
