//
//  RenderTarget.h

//  Created by Stef Tervelde on 30.06.22.
//
#import <Foundation/Foundation.h>
#import "Texture.h"

#ifndef RenderTarget_h
#define RenderTarget_h

/**
 * Attachment identifiers
 */
NS_SWIFT_NAME(RenderTarget.AttachmentPoint)
typedef NS_ENUM(NSInteger, AttachmentPoint){
    COLOR0 = 0,          //!< identifies the 1st color attachment
    COLOR1 = 1,          //!< identifies the 2nd color attachment
    COLOR2 = 2,          //!< identifies the 3rd color attachment
    COLOR3 = 3,          //!< identifies the 4th color attachment
    COLOR4 = 4,          //!< identifies the 5th color attachment
    COLOR5 = 5,          //!< identifies the 6th color attachment
    COLOR6 = 6,          //!< identifies the 7th color attachment
    COLOR7 = 7,          //!< identifies the 8th color attachment
    DEPTH  = 8,          //!< identifies the depth attachment
    COLOR  = COLOR0,     //!< identifies the 1st color attachment
};
//! Texture Cubemap Face
typedef NS_ENUM(NSInteger, TextureCubemapFace){
    // don't change the enums values
    POSITIVE_X = 0, //!< +x face
    NEGATIVE_X = 1, //!< -x face
    POSITIVE_Y = 2, //!< +y face
    NEGATIVE_Y = 3, //!< -y face
    POSITIVE_Z = 4, //!< +z face
    NEGATIVE_Z = 5, //!< -z face
};

@interface RenderTarget : NSObject

@property (nonatomic, readonly, nonnull) void* target  NS_SWIFT_UNAVAILABLE("Don't access the raw pointers");
- (nonnull id) init: (nonnull void*) target NS_SWIFT_UNAVAILABLE("Instances are created internally");
- (nonnull id) init NS_UNAVAILABLE;
/**
 * Gets the texture set on the given attachment point
 * @param attachment Attachment point
 * @return A Texture object or nullptr if no texture is set for this attachment point
 */
- (nonnull Texture*) getTexture: (AttachmentPoint) attachment;

/**
 * Returns the mipmap level set on the given attachment point
 * @param attachment Attachment point
 * @return the mipmap level set on the given attachment point
 */
- (uint8_t) getMipLevel: (AttachmentPoint) attachment;

/**
 * Returns the face of a cubemap set on the given attachment point
 * @param attachment Attachment point
 * @return A cubemap face identifier. This is only relevant if the attachment's texture is
 * a cubemap.
 */
- (TextureCubemapFace) getFace: (AttachmentPoint) attachment;

/**
 * Returns the texture-layer set on the given attachment point
 * @param attachment Attachment point
 * @return A texture layer. This is only relevant if the attachment's texture is a 3D texture.
 */
- (uint32_t) getLayer: (AttachmentPoint) attachment;

/**
 * Returns the number of color attachments usable by this instance of Engine. This method is
 * guaranteed to return at least MIN_SUPPORTED_COLOR_ATTACHMENTS_COUNT and at most
 * MAX_SUPPORTED_COLOR_ATTACHMENTS_COUNT.
 * @return Number of color attachments usable in a render target.
 */
- (uint8_t) getSupportedColorAttachmentsCount;
@end


#endif /* RenderTarget_h */
