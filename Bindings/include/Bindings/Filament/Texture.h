//
//  Texture.h
//  swift-gltf-viewer
//
//  Created by Stef Tervelde on 30.06.22.
//
#import <Foundation/Foundation.h>

#ifndef Texture_h
#define Texture_h

/**
 * Internal texel formats
 *
 * <p>These formats are used to specify a texture's internal storage format.</p>
 *
 * <h1>Enumerants syntax format</h1>
 *
 * <code>[components][size][type]</code>
 * <br><code>components</code> : List of stored components by this format
 * <br><code>size</code>       : Size in bit of each component
 * <br><code>type</code>       : Type this format is stored as
 *
 * <center>
 * <table border="1">
 *     <tr><th> Name    </th><th> Component                     </th></tr>
 *     <tr><td> R       </td><td> Linear Red                    </td></tr>
 *     <tr><td> RG      </td><td> Linear Red, Green             </td></tr>
 *     <tr><td> RGB     </td><td> Linear Red, Green, Blue       </td></tr>
 *     <tr><td> RGBA    </td><td> Linear Red, Green Blue, Alpha </td></tr>
 *     <tr><td> SRGB    </td><td> sRGB encoded Red, Green, Blue </td></tr>
 *     <tr><td> DEPTH   </td><td> Depth                         </td></tr>
 *     <tr><td> STENCIL </td><td> Stencil                       </td></tr>
 * </table>
 * </center>
 * <br>
 *
 * <center>
 * <table border="1">
 *     <tr><th> Name   </th><th> Type                                                       </th></tr>
 *     <tr><td> (none) </td><td> Unsigned Normalized Integer [0, 1]                         </th></tr>
 *     <tr><td> _SNORM </td><td> Signed Normalized Integer [-1, 1]                          </td></tr>
 *     <tr><td> UI     </td><td> Unsigned Integer [0, 2<sup>size</sup>]                     </td></tr>
 *     <tr><td> I      </td><td> Signed Integer [-2<sup>size-1</sup>, 2<sup>size-1</sup>-1] </td></tr>
 *     <tr><td> F      </td><td> Floating-point                                             </td></tr>
 * </table>
 * </center>
 * <br>
 *
 * <h1>Special color formats</h1>
 *
 * There are a few special color formats that don't follow the convention above:
 *
 * <center>
 * <table border="1">
 *     <tr><th> Name             </th><th> Format </th></tr>
 *     <tr><td> RGB565           </td><td>  5-bits for R and B, 6-bits for G.                            </td></tr>
 *     <tr><td> RGB5_A1          </td><td>  5-bits for R, G and B, 1-bit for A.                          </td></tr>
 *     <tr><td> RGB10_A2         </td><td> 10-bits for R, G and B, 2-bits for A.                         </td></tr>
 *     <tr><td> RGB9_E5          </td><td> <b>Unsigned</b> floating point. 9-bits mantissa for RGB, 5-bits shared exponent                 </td></tr>
 *     <tr><td> R11F_G11F_B10F   </td><td> <b>Unsigned</b> floating point. 6-bits mantissa, for R and G, 5-bits for B. 5-bits exponent.    </td></tr>
 *     <tr><td> SRGB8_A8         </td><td> sRGB 8-bits with linear 8-bits alpha.                        </td></tr>
 *     <tr><td> DEPTH24_STENCIL8 </td><td> 24-bits unsigned normalized integer depth, 8-bits stencil.   </td></tr>
 * </table>
 * </center>
 * <br>
 *
 * <h1>Compressed texture formats</h1>
 *
 * Many compressed texture formats are supported as well, which include (but are not limited to)
 * the following list:
 *
 * <center>
 * <table border="1">
 *     <tr><th> Name            </th><th> Format                            </th></tr>
 *     <tr><td> EAC_R11         </td><td> Compresses R11UI                  </td></tr>
 *     <tr><td> EAC_R11_SIGNED  </td><td> Compresses R11I                   </td></tr>
 *     <tr><td> EAC_RG11        </td><td> Compresses RG11UI                 </td></tr>
 *     <tr><td> EAC_RG11_SIGNED </td><td> Compresses RG11I                  </td></tr>
 *     <tr><td> ETC2_RGB8       </td><td> Compresses RGB8                   </td></tr>
 *     <tr><td> ETC2_SRGB8      </td><td> compresses SRGB8                  </td></tr>
 *     <tr><td> ETC2_EAC_RGBA8  </td><td> Compresses RGBA8                  </td></tr>
 *     <tr><td> ETC2_EAC_SRGBA8 </td><td> Compresses SRGB8_A8               </td></tr>
 *     <tr><td> ETC2_RGB8_A1    </td><td> Compresses RGB8 with 1-bit alpha  </td></tr>
 *     <tr><td> ETC2_SRGB8_A1   </td><td> Compresses sRGB8 with 1-bit alpha </td></tr>
 * </table>
 * </center>
 */
typedef NS_ENUM(NSInteger,InternalFormat) {
    // 8-bits per element
    R8, R8_SNORM, R8UI, R8I, STENCIL8,

    // 16-bits per element
    R16F, R16UI, R16I,
    RG8, RG8_SNORM, RG8UI, RG8I,
    RGB565, RGB9_E5, RGB5_A1,
    RGBA4,
    DEPTH16,

    // 24-bits per element
    RGB8, SRGB8, RGB8_SNORM, RGB8UI, RGB8I,
    DEPTH24,

    // 32-bits per element
    R32F, R32UI, R32I,
    RG16F, RG16UI, RG16I,
    R11F_G11F_B10F,
    RGBA8, SRGB8_A8, RGBA8_SNORM,
    UNUSED, // used to be rgbm
    RGB10_A2, RGBA8UI, RGBA8I,
    DEPTH32F, DEPTH24_STENCIL8, DEPTH32F_STENCIL8,

    // 48-bits per element
    RGB16F, RGB16UI, RGB16I,

    // 64-bits per element
    RG32F, RG32UI, RG32I,
    RGBA16F, RGBA16UI, RGBA16I,

    // 96-bits per element
    RGB32F, RGB32UI, RGB32I,

    // 128-bits per element
    RGBA32F, RGBA32UI, RGBA32I,

    // compressed formats

    // Mandatory in GLES 3.0 and GL 4.3
    EAC_R11, EAC_R11_SIGNED, EAC_RG11, EAC_RG11_SIGNED,
    ETC2_RGB8, ETC2_SRGB8,
    ETC2_RGB8_A1, ETC2_SRGB8_A1,
    ETC2_EAC_RGBA8, ETC2_EAC_SRGBA8,

    // Available everywhere except Android/iOS
    DXT1_RGB, DXT1_RGBA, DXT3_RGBA, DXT5_RGBA,
    DXT1_SRGB, DXT1_SRGBA, DXT3_SRGBA, DXT5_SRGBA,

    // ASTC formats are available with a GLES extension
    RGBA_ASTC_4x4,
    RGBA_ASTC_5x4,
    RGBA_ASTC_5x5,
    RGBA_ASTC_6x5,
    RGBA_ASTC_6x6,
    RGBA_ASTC_8x5,
    RGBA_ASTC_8x6,
    RGBA_ASTC_8x8,
    RGBA_ASTC_10x5,
    RGBA_ASTC_10x6,
    RGBA_ASTC_10x8,
    RGBA_ASTC_10x10,
    RGBA_ASTC_12x10,
    RGBA_ASTC_12x12,
    SRGB8_ALPHA8_ASTC_4x4,
    SRGB8_ALPHA8_ASTC_5x4,
    SRGB8_ALPHA8_ASTC_5x5,
    SRGB8_ALPHA8_ASTC_6x5,
    SRGB8_ALPHA8_ASTC_6x6,
    SRGB8_ALPHA8_ASTC_8x5,
    SRGB8_ALPHA8_ASTC_8x6,
    SRGB8_ALPHA8_ASTC_8x8,
    SRGB8_ALPHA8_ASTC_10x5,
    SRGB8_ALPHA8_ASTC_10x6,
    SRGB8_ALPHA8_ASTC_10x8,
    SRGB8_ALPHA8_ASTC_10x10,
    SRGB8_ALPHA8_ASTC_12x10,
    SRGB8_ALPHA8_ASTC_12x12
};
/**
 * Texture swizzling channels
 */
typedef NS_ENUM(NSInteger, Swizzle) {
    SUBSTITUTE_ZERO,    //!< specified component is substituted with 0
    SUBSTITUTE_ONE,     //!< specified component is substituted with 1
    CHANNEL_0,          //!< specified component taken from channel 0
    CHANNEL_1,          //!< specified component taken from channel 1
    CHANNEL_2,          //!< specified component taken from channel 2
    CHANNEL_3           //!< specified component taken from channel 3
};
/**
 * Pixel color format
 */
typedef NS_ENUM(NSInteger,Format) {
    R,
    R_INTEGER,
    RG,
    RG_INTEGER,
    RGB,
    RGB_INTEGER,
    RGBA,
    RGBA_INTEGER,
    _UNUSED,
    DEPTH_COMPONENT,
    DEPTH_STENCIL,
    STENCIL_INDEX,
    ALPHA
};
/**
 * Type of sampler
 */
typedef NS_ENUM(NSInteger,Sampler) {
    /** 2D sampler */
    SAMPLER_2D_,
    /** 2D array sampler  */
    SAMPLER_2D_ARRAY_,
    /** Cubemap sampler */
    SAMPLER_CUBEMAP_,
    /** External texture sampler */
    SAMPLER_EXTERNAL_,
    /** 3D sampler */
    SAMPLER_3D_,
};

typedef NS_ENUM(NSInteger,TextureUsage) {
    NONE_                = 0x0,
    COLOR_ATTACHMENT    = 0x1,                      //!< Texture can be used as a color attachment
    DEPTH_ATTACHMENT    = 0x2,                      //!< Texture can be used as a depth attachment
    STENCIL_ATTACHMENT  = 0x4,                      //!< Texture can be used as a stencil attachment
    UPLOADABLE          = 0x8,                      //!< Data can be uploaded into this texture (default)
    SAMPLEABLE          = 0x10,                     //!< Texture can be sampled (default)
    SUBPASS_INPUT_       = 0x20,                     //!< Texture can be used as a subpass input
    DEFAULT_             = UPLOADABLE | SAMPLEABLE   //!< Default texture usage
};



NS_SWIFT_NAME(Texture.PixelBufferDescriptor)
@interface PixelBufferDescriptor : NSObject
@property (nonatomic, readonly, nonnull) void* buffer  NS_SWIFT_UNAVAILABLE("Don't access the raw pointers");
- (nonnull id) init: (nonnull void*) buffer NS_SWIFT_UNAVAILABLE("Create a new renderer with engine.createRenderer");
- (nonnull id) init NS_UNAVAILABLE;
@end

@interface Texture : NSObject

@property (nonatomic, readonly, nonnull) void* texture  NS_SWIFT_UNAVAILABLE("Don't access the raw pointers");
- (nonnull id) init: (nonnull void*) texture NS_SWIFT_UNAVAILABLE("Create a new renderer with engine.createRenderer");
- (nonnull id) init NS_UNAVAILABLE;

@end


#endif /* Texture_h */
