//
//  VertexBuffer.h
//
//  Created by Stef Tervelde on 30.06.22.
//
#import <Foundation/Foundation.h>

#ifndef VertexBuffer_h
#define VertexBuffer_h

@class Engine;

@interface VertexBuffer : NSObject

@property (nonatomic, readonly, nonnull) void* buffer  NS_SWIFT_UNAVAILABLE("Don't access the raw pointers");
- (nonnull id) init: (nonnull void*) buffer NS_SWIFT_UNAVAILABLE("Instances are created internally");
- (nonnull id) init NS_UNAVAILABLE;
- (size_t) getVertexCount;
/**
 * Asynchronously copy-initializes the specified buffer from the given buffer data.
 *
 * Do not use this if you called enableBufferObjects() on the Builder.
 *
 * @param engine Reference to the filament::Engine to associate this VertexBuffer with.
 * @param bufferIndex Index of the buffer to initialize. Must be between 0
 *                    and Builder::bufferCount() - 1.
 * @param buffer A BufferDescriptor representing the data used to initialize the buffer at
 *               index \p bufferIndex. BufferDescriptor points to raw, untyped data that will
 *               be copied as-is into the buffer.
 * @param byteOffset Offset in *bytes* into the buffer at index \p bufferIndex of this vertex
 *                   buffer set.
 */
- (void) setBufferAt: (nonnull Engine*) engine :(int) bufferIndex :(nonnull NSData*) data :(int) byteOffset;
- (void) setBufferAt: (nonnull Engine*) engine :(int) bufferIndex :(nonnull NSData*) data;

@end


#endif /* VertexBuffer_h */
