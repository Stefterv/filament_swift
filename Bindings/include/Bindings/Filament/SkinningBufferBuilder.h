//
//  SkinningBufferBuilder.h

//  Created by Stef Tervelde on 30.06.22.
//
#import <Foundation/Foundation.h>
#import "SkinningBuffer.h"

#ifndef SkinningBufferBuilder_h
#define SkinningBufferBuilder_h

@class Engine;

@interface SkinningBufferBuilder : NSObject

@property (nonatomic, readonly, nonnull) void* builder  NS_SWIFT_UNAVAILABLE("Don't access the raw pointers");
- (nonnull id) init: (nonnull void*) builder NS_SWIFT_UNAVAILABLE("Instances are created internally");
- (nonnull id) init NS_UNAVAILABLE;

NS_ASSUME_NONNULL_BEGIN
/**
 * Size of the skinning buffer in bones.
 *
 * Due to limitation in the GLSL, the SkinningBuffer must always by a multiple of
 * 256, this adjustment is done automatically, but can cause
 * some memory overhead. This memory overhead can be mitigated by using the same
 * SkinningBuffer to store the bone information for multiple RenderPrimitives.
 *
 * @param boneCount Number of bones the skinning buffer can hold.
 * @return A reference to this Builder for chaining calls.
 */
- (instancetype) boneCount: (uint32_t) boneCount;

/**
 * The new buffer is created with identity bones
 * @param initialize true to initializing the buffer, false to not.
 * @return A reference to this Builder for chaining calls.
 */
- (instancetype) initialize: (bool) initialize;

/**
 * Creates the SkinningBuffer object and returns a pointer to it.
 *
 * @param engine Reference to the filament::Engine to associate this SkinningBuffer with.
 *
 * @return pointer to the newly created object or nullptr if exceptions are disabled and
 *         an error occurred.
 *
 * @exception utils::PostConditionPanic if a runtime error occurred, such as running out of
 *            memory or other resources.
 * @exception utils::PreConditionPanic if a parameter to a builder function was invalid.
 *
 * @see SkinningBuffer::setBones
 */
- (SkinningBuffer*) build: (Engine*) engine;
NS_ASSUME_NONNULL_END
@end


#endif /* SkinningBufferBuilder_h */
