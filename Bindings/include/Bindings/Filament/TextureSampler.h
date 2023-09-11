//
//  TextureSampler.h

//  Created by Stef Tervelde on 30.06.22.
//
#import <Foundation/Foundation.h>

#ifndef TextureSampler_h
#define TextureSampler_h


//! Sampler Wrap mode
NS_SWIFT_NAME(TextureSampler.WrapMode)
typedef NS_ENUM(NSInteger, SamplerWrapMode){
    CLAMP_TO_EDGE,      //!< clamp-to-edge. The edge of the texture extends to infinity.
    REPEAT,             //!< repeat. The texture infinitely repeats in the wrap direction.
    MIRRORED_REPEAT,    //!< mirrored-repeat. The texture infinitely repeats and mirrors in the wrap direction.
};

//! Sampler minification filter
NS_SWIFT_NAME(TextureSampler.MinFilter)
typedef NS_ENUM(NSInteger, SamplerMinFilter){
    // don't change the enums values
    NEAREST = 0,                //!< No filtering. Nearest neighbor is used.
    LINEAR = 1,                 //!< Box filtering. Weighted average of 4 neighbors is used.
    NEAREST_MIPMAP_NEAREST = 2, //!< Mip-mapping is activated. But no filtering occurs.
    LINEAR_MIPMAP_NEAREST = 3,  //!< Box filtering within a mip-map level.
    NEAREST_MIPMAP_LINEAR = 4,  //!< Mip-map levels are interpolated, but no other filtering occurs.
    LINEAR_MIPMAP_LINEAR = 5    //!< Both interpolated Mip-mapping and linear filtering are used.
};

//! Sampler magnification filter
NS_SWIFT_NAME(TextureSampler.MagFilter)
typedef NS_ENUM(NSInteger, SamplerMagFilter){
    // don't change the enums values
    NearestFilter = 0,                //!< No filtering. Nearest neighbor is used.
    LinearFilter = 1,                 //!< Box filtering. Weighted average of 4 neighbors is used.
};

//! Sampler compare mode
NS_SWIFT_NAME(TextureSampler.CompareMode)
typedef NS_ENUM(NSInteger, SamplerCompareMode){
    // don't change the enums values
    NoneCompare = 0,
    CompareToTexture = 1
};

//! comparison function for the depth / stencil sampler
NS_SWIFT_NAME(TextureSampler.CompareFunc)
typedef NS_ENUM(NSInteger, SamplerCompareFunc){
    // don't change the enums values
    LE = 0,     //!< Less or equal
    GE,         //!< Greater or equal
    L,          //!< Strictly less than
    G,          //!< Strictly greater than
    E,          //!< Equal
    NE,         //!< Not equal
    A,          //!< Always. Depth / stencil testing is deactivated.
    N           //!< Never. The depth / stencil test always fails.
};

@interface TextureSampler : NSObject

@property SamplerMagFilter filterMag;         //!< magnification filter (NEAREST)
@property SamplerMinFilter filterMin;         //!< minification filter  (NEAREST)
@property SamplerWrapMode wrapS;              //!< s-coordinate wrap mode (CLAMP_TO_EDGE)
@property SamplerWrapMode wrapT;              //!< t-coordinate wrap mode (CLAMP_TO_EDGE)
@property SamplerWrapMode wrapR;              //!< r-coordinate wrap mode (CLAMP_TO_EDGE)
@property uint8_t anisotropyLog2;             //!< anisotropy level (0)
@property SamplerCompareMode compareMode;     //!< sampler compare mode (NONE)
@property SamplerCompareFunc compareFunc;     //!< sampler comparison function (LE)

@property (nonatomic, readonly, nonnull) void* sampler  NS_SWIFT_UNAVAILABLE("Don't access the raw pointers");
- (nonnull id) init: (nonnull void*) sampler NS_SWIFT_UNAVAILABLE("Instances are created internally");
- (nonnull id) init;

@end
#endif /* TextureSampler_h */
