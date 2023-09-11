//
//  SkinningBuffer.h

//  Created by Stef Tervelde on 30.06.22.
//
#import <Foundation/Foundation.h>
#import <simd/simd.h>

#ifndef SkinningBuffer_h
#define SkinningBuffer_h

@class Engine;

@interface SkinningBuffer : NSObject

@property (nonatomic, readonly, nonnull) void* buffer  NS_SWIFT_UNAVAILABLE("Don't access the raw pointers");
- (nonnull id) init: (nonnull void*) buffer NS_SWIFT_UNAVAILABLE("Instances are created internally");
- (nonnull id) init NS_UNAVAILABLE;
/**
 * Updates the bone transforms in the range [offset, offset + count).
 * @param engine Reference to the filament::Engine to associate this SkinningBuffer with.
 * @param transforms pointer to at least count Bone
 * @param count number of Bone elements in transforms
 * @param offset offset in elements (not bytes) in the SkinningBuffer (not in transforms)
 * @see RenderableManager::setSkinningBuffer
 */
- (void) setBones: (nonnull Engine*) engine :(nonnull simd_float4 const*) transforms :(size_t) count :(size_t) offset;

/**
 * Updates the bone transforms in the range [offset, offset + count).
 * @param engine Reference to the filament::Engine to associate this SkinningBuffer with.
 * @param transforms pointer to at least count mat4f
 * @param count number of mat4f elements in transforms
 * @param offset offset in elements (not bytes) in the SkinningBuffer (not in transforms)
 * @see RenderableManager::setSkinningBuffer
 */
//- (void) setBones: (nonnull Engine*) engine :(math::mat4f const*) transforms :(size_t) count :(size_t) offset;

/**
 * Returns the size of this SkinningBuffer in elements.
 * @return The number of bones the SkinningBuffer holds.
 */
- (size_t) getBoneCount;
@end


#endif /* SkinningBuffer_h */
