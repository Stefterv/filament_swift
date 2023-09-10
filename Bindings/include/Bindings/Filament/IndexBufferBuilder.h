//
//  IndexBufferBuilder.h
//
//  Created by Stef Tervelde on 10.08.22.
//
#import <Foundation/Foundation.h>
#import "IndexBuffer.h"
#import "Engine.h"

#ifndef IndexBufferBuilder_h
#define IndexBufferBuilder_h

typedef NS_ENUM(NSInteger, IndexType) {
    IndexTypeUnsignedShort = 12,
    IndexTypeUnsignedInt = 17
};


NS_SWIFT_NAME(IndexBuffer.Builder)
@interface IndexBufferBuilder : NSObject

@property (nonatomic, readonly, nonnull) void* buffer  NS_SWIFT_UNAVAILABLE("Don't access the raw pointers");
- (nonnull id) init: (nonnull void*) buffer NS_SWIFT_UNAVAILABLE("Instances are created internally");
- (nonnull id) init;

NS_ASSUME_NONNULL_BEGIN
/**
 * Size of the index buffer in elements.
 * @param indexCount Number of indices the IndexBuffer can hold.
 * @return A reference to this Builder for chaining calls.
 */
- (instancetype) indexCount: (NSInteger) indexCount;
/**
 * Type of the index buffer, 16-bit or 32-bit.
 * @param indexType Type of indices stored in the IndexBuffer.
 * @return A reference to this Builder for chaining calls.
*/
- (instancetype) bufferType: (IndexType) type;
/**
 * Creates the IndexBuffer object and returns a pointer to it. After creation, the index
 * buffer is uninitialized. Use IndexBuffer::setBuffer() to initialize the IndexBuffer.
 *
 * @param engine Reference to the filament::Engine to associate this IndexBuffer with.
 *
 * @return pointer to the newly created object or nullptr if exceptions are disabled and
 *         an error occurred.
 *
 * @exception utils::PostConditionPanic if a runtime error occurred, such as running out of
 *            memory or other resources.
 * @exception utils::PreConditionPanic if a parameter to a builder function was invalid.
 *
 * @see IndexBuffer::setBuffer
 */
- (IndexBuffer*) build: (Engine*) engine;
NS_ASSUME_NONNULL_END
@end


#endif /* IndexBufferBuilder_h */
