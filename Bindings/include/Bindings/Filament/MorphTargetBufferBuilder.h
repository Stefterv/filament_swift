//
//  MorphTargetBuilder.h

//  Created by Stef Tervelde on 30.06.22.
//
#import <Foundation/Foundation.h>
#import "Engine.h"
#import "MorphTargetBuffer.h"

#ifndef MorphTargetBuilder_h
#define MorphTargetBuilder_h

@interface MorphTargetBufferBuilder : NSObject

@property (nonatomic, readonly, nonnull) void* builder  NS_SWIFT_UNAVAILABLE("Don't access the raw pointers");
- (nonnull id) init: (nonnull void*) builder NS_SWIFT_UNAVAILABLE("Instances are created internally");
- (nonnull id) init NS_UNAVAILABLE;

NS_ASSUME_NONNULL_BEGIN
/**
 * Size of the morph targets in vertex counts.
 * @param vertexCount Number of vertex counts the morph targets can hold.
 * @return A reference to this Builder for chaining calls.
 */
- (instancetype) vertexCount: (size_t) vertexCount;

/**
 * Size of the morph targets in targets.
 * @param count Number of targets the morph targets can hold.
 * @return A reference to this Builder for chaining calls.
 */
- (instancetype) count: (size_t) count;

/**
 * Creates the MorphTargetBuffer object and returns a pointer to it.
 *
 * @param engine Reference to the filament::Engine to associate this MorphTargetBuffer with.
 *
 * @return pointer to the newly created object or nullptr if exceptions are disabled and
 *         an error occurred.
 *
 * @exception utils::PostConditionPanic if a runtime error occurred, such as running out of
 *            memory or other resources.
 * @exception utils::PreConditionPanic if a parameter to a builder function was invalid.
 */
- (MorphTargetBuffer*) build: (Engine*) engine;
NS_ASSUME_NONNULL_END

@end


#endif /* MorphTargetBuilder_h */
