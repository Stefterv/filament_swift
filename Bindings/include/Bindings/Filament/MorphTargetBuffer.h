//
//  MorphTarget.h

//  Created by Stef Tervelde on 30.06.22.
//
#import <Foundation/Foundation.h>
#import <simd/simd.h>
#import "Engine.h"

#ifndef MorphTarget_h
#define MorphTarget_h

@interface MorphTargetBuffer : NSObject

@property (nonatomic, readonly, nonnull) void* buffer  NS_SWIFT_UNAVAILABLE("Don't access the raw pointers");
- (nonnull id) init: (nonnull void*) buffer NS_SWIFT_UNAVAILABLE("Instances are created internally");
- (nonnull id) init NS_UNAVAILABLE;

/**
 * Updates positions for the given morph target.
 *
 * This is equivalent to the float4 method, but uses 1.0 for the 4th component.
 *
 * Both positions and tangents must be provided.
 *
 * @param engine Reference to the filament::Engine associated with this MorphTargetBuffer.
 * @param targetIndex the index of morph target to be updated.
 * @param positions pointer to at least "count" positions
 * @param count number of float3 vectors in positions
 * @param offset offset into the target buffer, expressed as a number of float4 vectors
 * @see setTangentsAt
 */
- (void) setPositionsAt: (nonnull Engine*) engine :(size_t) targetIndex :(nonnull simd_float3 const*) positions :(size_t) count :(size_t) offset;

/**
 * Updates positions for the given morph target.
 *
 * Both positions and tangents must be provided.
 *
 * @param engine Reference to the filament::Engine associated with this MorphTargetBuffer.
 * @param targetIndex the index of morph target to be updated.
 * @param positions pointer to at least "count" positions
 * @param count number of float4 vectors in positions
 * @param offset offset into the target buffer, expressed as a number of float4 vectors
 * @see setTangentsAt
 */
#warning  Get simd_float4 array from swift
//- (void) setPositionsAt: (nonnull Engine*) engine :(size_t) targetIndex :(simd_float4 const*) positions :(size_t) count :(size_t) offset;

/**
 * Updates tangents for the given morph target.
 *
 * These quaternions must be represented as signed shorts, where real numbers in the [-1,+1]
 * range multiplied by 32767.
 *
 * @param engine Reference to the filament::Engine associated with this MorphTargetBuffer.
 * @param targetIndex the index of morph target to be updated.
 * @param tangents pointer to at least "count" tangents
 * @param count number of short4 quaternions in tangents
 * @param offset offset into the target buffer, expressed as a number of short4 vectors
 * @see setPositionsAt
 */
- (void) setTangentsAt: (nonnull Engine*) engine :(size_t) targetIndex :(nonnull simd_short4 const*) tangents :(size_t) count :(size_t) offset;

/**
 * Returns the vertex count of this MorphTargetBuffer.
 * @return The number of vertices the MorphTargetBuffer holds.
 */
- (size_t) getVertexCount;

/**
 * Returns the target count of this MorphTargetBuffer.
 * @return The number of targets the MorphTargetBuffer holds.
 */
- (size_t) getCount;
@end

#endif /* MorphTarget_h */
