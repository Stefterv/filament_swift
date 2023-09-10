//
//  VertexBufferBuilder.h

//
//  Created by Stef Tervelde on 10.08.22.
//
#import <Foundation/Foundation.h>
#import "VertexBuffer.h"
#import "Engine.h"
#import "VertexAttribute.h"

#ifndef VertexBufferBuilder_h
#define VertexBufferBuilder_h

typedef NS_ENUM(NSInteger, AttributeType) {
    AttributeTypeByte,
    AttributeTypeByte2,
    AttributeTypeByte3,
    AttributeTypeByte4,
    AttributeTypeUbyte,
    AttributeTypeUbyte2,
    AttributeTypeUbyte3,
    AttributeTypeUbyte4,
    AttributeTypeShort,
    AttributeTypeShort2,
    AttributeTypeShort3,
    AttributeTypeShort4,
    AttributeTypeUshort,
    AttributeTypeUshort2,
    AttributeTypeUshort3,
    AttributeTypeUshort4,
    AttributeTypeInt,
    AttributeTypeUint,
    AttributeTypeFloat,
    AttributeTypeFloat2,
    AttributeTypeFloat3,
    AttributeTypeFloat4,
    AttributeTypeHalf,
    AttributeTypeHalf2,
    AttributeTypeHalf3,
    AttributeTypeHalf4,
};


NS_SWIFT_NAME(VertexBuffer.Builder)
@interface VertexBufferBuilder : NSObject

@property (nonatomic, readonly, nonnull) void* buffer  NS_SWIFT_UNAVAILABLE("Don't access the raw pointers");
- (nonnull id) init: (nonnull void*) buffer NS_SWIFT_UNAVAILABLE("Instances are created internally");
- (nonnull id) init;
NS_ASSUME_NONNULL_BEGIN
- (instancetype) bufferCount: (int) bufferCount;
- (instancetype) vertexCount: (NSInteger) vertexCount;
/**
 * Allows buffers to be swapped out and shared using BufferObject.
 *
 * If buffer objects mode is enabled, clients must call setBufferObjectAt rather than
 * setBufferAt. This allows sharing of data between VertexBuffer objects, but it may
 * slightly increase the memory footprint of Filament's internal bookkeeping.
 *
 * @param enabled If true, enables buffer object mode.  False by default.
 */
- (instancetype) enableBufferObjects: (bool) enabled;
- (instancetype) enableBufferObjects;
/**
 * Sets up an attribute for this vertex buffer set.
 *
 * Using \p byteOffset and \p byteStride, attributes can be interleaved in the same buffer.
 *
 * @param attribute The attribute to set up.
 * @param bufferIndex  The index of the buffer containing the data for this attribute. Must
 *                     be between 0 and bufferCount() - 1.
 * @param attributeType The type of the attribute data (e.g. byte, float3, etc...)
 * @param byteOffset Offset in *bytes* into the buffer \p bufferIndex
 * @param byteStride Stride in *bytes* to the next element of this attribute. When set to
 *                   zero the attribute size, as defined by \p attributeType is used.
 *
 * @return A reference to this Builder for chaining calls.
 *
 * @warning VertexAttribute::TANGENTS must be specified as a quaternion and is how normals
 *          are specified.
 *
 * @warning Not all backends support 3-component attributes that are not floats. For help
 *          with conversion, see geometry::Transcoder.
 *
 * @see VertexAttribute
 *
 * This is a no-op if the \p attribute is an invalid enum.
 * This is a no-op if the \p bufferIndex is out of bounds.
 *
 */
- (instancetype) attribute: (VertexAttribute) attribute :(int) bufferIndex :(AttributeType) attributeType;
- (instancetype) attribute: (VertexAttribute) attribute :(int) bufferIndex :(AttributeType) attributeType :(int) byteOffset :(int) byteStride;
/**
 * Sets whether a given attribute should be normalized. By default attributes are not
 * normalized. A normalized attribute is mapped between 0 and 1 in the shader. This applies
 * only to integer types.
 *
 * @param attribute Enum of the attribute to set the normalization flag to.
 * @param normalize true to automatically normalize the given attribute.
 * @return A reference to this Builder for chaining calls.
 *
 * This is a no-op if the \p attribute is an invalid enum.
 */
- (instancetype) normalized: (VertexAttribute) attribute :(bool) normalize;
- (instancetype) normalized: (VertexAttribute) attribute;
/**
 * Creates the VertexBuffer object and returns a pointer to it.
 *
 * @param engine Reference to the filament::Engine to associate this VertexBuffer with.
 *
 * @return pointer to the newly created object or nullptr if exceptions are disabled and
 *         an error occurred.
 *
 * @exception utils::PostConditionPanic if a runtime error occurred, such as running out of
 *            memory or other resources.
 * @exception utils::PreConditionPanic if a parameter to a builder function was invalid.
 */
- (VertexBuffer*) build: (Engine*) engine;

NS_ASSUME_NONNULL_END
@end


#endif /* VertexBufferBuilder_h */
