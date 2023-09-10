//
//  BufferObjectBuilder.h
//  swift-gltf-viewer
//
//  Created by Stef Tervelde on 10.09.23.
//
#import <Foundation/Foundation.h>
#import "Engine.h"
#import "BufferObject.h"

#ifndef BufferObjectBuilder_h
#define BufferObjectBuilder_h

typedef NS_ENUM(NSInteger, BindingType) {
    Vertex = 0
};

@interface BufferObjectBuilder : NSObject

@property (nonatomic, readonly, nonnull) void* Builder  NS_SWIFT_UNAVAILABLE("Don't access the raw pointers");
- (nonnull id) init: (nonnull void*) Builder NS_SWIFT_UNAVAILABLE("Instances are created internally");
- (nonnull id) init NS_UNAVAILABLE;

NS_ASSUME_NONNULL_BEGIN
/**
 * Size of the buffer in bytes.
 * @param byteCount Maximum number of bytes the BufferObject can hold.
 * @return A reference to this Builder for chaining calls.
 */
- (instancetype) size: (uint32_t) byteCount;

/**
 * The binding type for this buffer object. (defaults to VERTEX)
 * @param BindingType Distinguishes between SSBO, VBO, etc. For now this must be VERTEX.
 * @return A reference to this Builder for chaining calls.
 */
- (instancetype) bindingType: (BindingType) bindingType;

/**
 * Creates the BufferObject and returns a pointer to it. After creation, the buffer
 * object is uninitialized. Use BufferObject::setBuffer() to initialize it.
 *
 * @param engine Reference to the filament::Engine to associate this BufferObject with.
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
- (BufferObject*) build :(nonnull Engine*) engine;
NS_ASSUME_NONNULL_END

@end


#endif /* BufferObjectBuilder_h */
