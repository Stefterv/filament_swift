//
//  Colors.h
//  swift-gltf-viewer
//
//  Created by Stef Tervelde on 10.09.23.
//
#import <Foundation/Foundation.h>

#ifndef Colors_h
#define Colors_h

//! types of RGB colors
typedef NS_ENUM(NSInteger, RgbType){
    sRGB,   //!< the color is defined in Rec.709-sRGB-D65 (sRGB) space
    LinearRgb, //!< the color is defined in Rec.709-Linear-D65 ("linear sRGB") space
};

//! types of RGBA colors
typedef NS_ENUM(NSInteger, RgbaType){
    /**
     * the color is defined in Rec.709-sRGB-D65 (sRGB) space and the RGB values
     * have not been pre-multiplied by the alpha (for instance, a 50%
     * transparent red is <1,0,0,0.5>)
     */
    sRGBA,
    /**
     * the color is defined in Rec.709-Linear-D65 ("linear sRGB") space and the
     * RGB values have not been pre-multiplied by the alpha (for instance, a 50%
     * transparent red is <1,0,0,0.5>)
     */
    LinearRgba,
    /**
     * the color is defined in Rec.709-sRGB-D65 (sRGB) space and the RGB values
     * have been pre-multiplied by the alpha (for instance, a 50%
     * transparent red is <0.5,0,0,0.5>)
     */
    PremultipliedsRgba,
    /**
     * the color is defined in Rec.709-Linear-D65 ("linear sRGB") space and the
     * RGB values have been pre-multiplied by the alpha (for instance, a 50%
     * transparent red is <0.5,0,0,0.5>)
     */
    PremultipliedLinear
};


@interface Colors : NSObject

@property (nonatomic, readonly, nonnull) void* Colors  NS_SWIFT_UNAVAILABLE("Don't access the raw pointers");
- (nonnull id) init: (nonnull void*) Colors NS_SWIFT_UNAVAILABLE("Instances are created internally");
- (nonnull id) init NS_UNAVAILABLE;
/*
 Implement in swift
*/
@end

#endif /* Colors_h */
