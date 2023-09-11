//
//  RenderTargetBuilder.h

//  Created by Stef Tervelde on 05.07.22.
//
#import <Foundation/Foundation.h>
#import "RenderTarget.h"
#import "Engine.h"

#ifndef RenderTargetBuilder_h
#define RenderTargetBuilder_h

NS_SWIFT_NAME(RenderTarget.Builder)
@interface RenderTargetBuilder : NSObject

@property (nonatomic, readonly, nonnull) void* builder  NS_SWIFT_UNAVAILABLE("Don't access the raw pointers");
- (nonnull id) init: (nonnull void*) builder NS_SWIFT_UNAVAILABLE("Instances are created internally");
- (nonnull id) init NS_UNAVAILABLE;

NS_ASSUME_NONNULL_BEGIN
/**
 * Sets a texture to a given attachment point.
 *
 * When using a DEPTH attachment, it is important to always disable post-processing
 * in the View. Failing to do so will cause the DEPTH attachment to be ignored in most
 * cases.
 *
 * When the intention is to keep the content of the DEPTH attachment after rendering,
 * Usage::SAMPLEABLE must be set on the DEPTH attachment, otherwise the content of the
 * DEPTH buffer may be discarded.
 *
 * @param attachment The attachment point of the texture.
 * @param texture The associated texture object.
 * @return A reference to this Builder for chaining calls.
 */
- (instancetype) texture: (AttachmentPoint) attachment :(Texture*) texture;

/**
 * Sets the mipmap level for a given attachment point.
 *
 * @param attachment The attachment point of the texture.
 * @param level The associated mipmap level, 0 by default.
 * @return A reference to this Builder for chaining calls.
 */
- (instancetype) mipLevel: (AttachmentPoint) attachment :(uint8_t) level;

/**
 * Sets the cubemap face for a given attachment point.
 *
 * @param attachment The attachment point.
 * @param face The associated cubemap face.
 * @return A reference to this Builder for chaining calls.
 */
- (instancetype) face: (AttachmentPoint) attachment :(TextureCubemapFace) face;

/**
 * Sets the layer for a given attachment point (for 3D textures).
 *
 * @param attachment The attachment point.
 * @param layer The associated cubemap layer.
 * @return A reference to this Builder for chaining calls.
 */
- (instancetype) layer: (AttachmentPoint) attachment :(uint32_t) layer;

/**
 * Creates the RenderTarget object and returns a pointer to it.
 *
 * @return pointer to the newly created object or nullptr if exceptions are disabled and
 *         an error occurred.
 */
- (RenderTarget*) build: (Engine*) engine;
NS_ASSUME_NONNULL_END
@end


#endif /* RenderTargetBuilder_h */
