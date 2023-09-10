//
//  ColorGradingBuilder.h

//  Created by Stef Tervelde on 30.06.22.
//
#import <Foundation/Foundation.h>
#import <simd/simd.h>
#import "ColorGrading.h"
#import "ToneMapper.h"
#import "Engine.h"

#ifndef ColorGradingBuilder_h
#define ColorGradingBuilder_h

@interface ColorGradingBuilder : NSObject

@property (nonatomic, readonly, nonnull) void* builder  NS_SWIFT_UNAVAILABLE("Don't access the raw pointers");
- (nonnull id) init: (nonnull void*) builder NS_SWIFT_UNAVAILABLE("Instances are created internally");
- (nonnull id) init NS_UNAVAILABLE;

NS_ASSUME_NONNULL_BEGIN
/**
 * Sets the quality level of the color grading. When color grading is implemented using
 * a 3D LUT, the quality level may impact the resolution and bit depth of the backing
 * 3D texture. For instance, a low quality level will use a 16x16x16 10 bit LUT, a medium
 * quality level will use a 32x32x32 10 bit LUT, a high quality will use a 32x32x32 16 bit
 * LUT, and a ultra quality will use a 64x64x64 16 bit LUT.
 *
 * The default quality is {@link QualityLevel#MEDIUM}.
 *
 * @param qualityLevel The desired quality of the color grading process
 *
 * @return This Builder, for chaining calls
 */
- (instancetype) quality: (int) qualityLevel;
/**
 * When color grading is implemented using a 3D LUT, this sets the texture format of
 * of the LUT. This overrides the value set by quality().
 *
 * The default is INTEGER
 *
 * @param format The desired format of the 3D LUT.
 *
 * @return This Builder, for chaining calls
 */
- (instancetype) format: (int) format;
/**
 * When color grading is implemented using a 3D LUT, this sets the dimension of the LUT.
 * This overrides the value set by quality().
 *
 * The default is 32
 *
 * @param dim The desired dimension of the LUT. Between 16 and 64.
 *
 * @return This Builder, for chaining calls
 */
- (instancetype) dimensions: (int) dim;
/**
 * Selects the tone mapping operator to apply to the HDR color buffer as the last
 * operation of the color grading post-processing step.
 *
 * The default tone mapping operator is {@link ToneMapper.ACESLegacy}.
 *
 * The specified tone mapper must have a lifecycle that exceeds the lifetime of
 * this builder. Since the build(Engine&) method is synchronous, it is safe to
 * delete the tone mapper object after that finishes executing.
 *
 * @param toneMapper The tone mapping operator to apply to the HDR color buffer
 *
 * @return This Builder, for chaining calls
 */
- (instancetype) toneMapper: (ToneMapper*) toneMapper;
/**
 * Enables or disables the luminance scaling component (LICH) from the exposure value
 * invariant luminance system (EVILS). When this setting is enabled, pixels with high
 * chromatic values will roll-off to white to offer a more natural rendering. This step
 * also helps avoid undesirable hue skews caused by out of gamut colors clipped
 * to the destination color gamut.
 *
 * When luminance scaling is enabled, tone mapping is performed on the luminance of each
 * pixel instead of per-channel.
 *
 * @param luminanceScaling Enables or disables EVILS post-tone mapping
 *
 * @return This Builder, for chaining calls
 */
- (instancetype) luminanceScaling: (bool) luminanceScaling;
/**
 * Enables or disables gamut mapping to the destination color space's gamut. When gamut
 * mapping is turned off, out-of-gamut colors are clipped to the destination's gamut,
 * which may produce hue skews (blue skewing to purple, green to yellow, etc.). When
 * gamut mapping is enabled, out-of-gamut colors are brought back in gamut by trying to
 * preserve the perceived chroma and lightness of the original values.
 *
 * @param gamutMapping Enables or disables gamut mapping
 *
 * @return This Builder, for chaining calls
 */
- (instancetype) gamutMapping: (bool) gamutMapping;
/**
 * Adjusts the exposure of this image. The exposure is specified in stops:
 * each stop brightens (positive values) or darkens (negative values) the image by
 * a factor of 2. This means that an exposure of 3 will brighten the image 8 times
 * more than an exposure of 0 (2^3 = 8 and 2^0 = 1). Contrary to the camera's exposure,
 * this setting is applied after all post-processing (bloom, etc.) are applied.
 *
 * @param exposure Value in EV stops. Can be negative, 0, or positive.
 *
 * @return This Builder, for chaining calls
 */
- (instancetype) exposure: (double) exposure;
/**
 * Controls the amount of night adaptation to replicate a more natural representation of
 * low-light conditions as perceived by the human vision system. In low-light conditions,
 * peak luminance sensitivity of the eye shifts toward the blue end of the color spectrum:
 * darker tones appear brighter, reducing contrast, and colors are blue shifted (the darker
 * the more intense the effect).
 *
 * @param adaptation Amount of adaptation, between 0 (no adaptation) and 1 (full adaptation).
 *
 * @return This Builder, for chaining calls
 */
- (instancetype) nightAdaptation: (double) adaptation;
/**
 * Adjusts the while balance of the image. This can be used to remove color casts
 * and correct the appearance of the white point in the scene, or to alter the
 * overall chromaticity of the image for artistic reasons (to make the image appear
 * cooler or warmer for instance).
 *
 * The while balance adjustment is defined with two values:
 * <ul>
 * <li>Temperature, to modify the color temperature. This value will modify the colors
 * on a blue/yellow axis. Lower values apply a cool color temperature, and higher
 * values apply a warm color temperature. The lowest value, -1.0f, is equivalent to
 * a temperature of 50,000K. The highest value, 1.0f, is equivalent to a temperature
 * of 2,000K.</li>
 * <li>Tint, to modify the colors on a green/magenta axis. The lowest value, -1.0f, will
 * apply a strong green cast, and the highest value, 1.0f, will apply a strong magenta
 * cast.</li>
 * </ul>
 *
 * Both values are expected to be in the range <code>[-1.0..+1.0]</code>. Values outside
 * of that range will be clipped to that range.
 *
 * @param temperature Modification on the blue/yellow axis, as a value between -1.0 and +1.0.
 * @param tint Modification on the green/magenta axis, as a value between -1.0 and +1.0.
 *
 * @return This Builder, for chaining calls
 */
- (instancetype) whiteBalance: (double) temperature :(double) tint;
/**
 * The channel mixer adjustment modifies each output color channel using the specified
 * mix of the source color channels.
 *
 * By default each output color channel is set to use 100% of the corresponding source
 * channel and 0% of the other channels. For instance, the output red channel is set to
 * <code>{1.0, 0.0, 1.0}</code> or 100% red, 0% green and 0% blue.
 *
 * Each output channel can add or subtract data from the source channel by using values
 * in the range <code>[-2.0..+2.0]</code>. Values outside of that range will be clipped
 * to that range.
 *
 * Using the channel mixer adjustment you can for instance create a monochrome output
 * by setting all 3 output channels to the same mix. For instance:
 * </code>{0.4, 0.4, 0.2}</code> for all 3 output channels(40% red, 40% green and 20% blue).
 *
 * More complex mixes can be used to create more complex effects. For instance, here is
 * a mix that creates a sepia tone effect:
 * <ul>
 * <li><code>outRed   = {0.255, 0.858, 0.087}</code></li>
 * <li><code>outGreen = {0.213, 0.715, 0.072}</code></li>
 * <li><code>outBlue  = {0.170, 0.572, 0.058}</code></li>
 * </ul>
 *
 * @param outRed The mix of source RGB for the output red channel, between -2.0 and +2.0
 * @param outGreen The mix of source RGB for the output green channel, between -2.0 and +2.0
 * @param outBlue The mix of source RGB for the output blue channel, between -2.0 and +2.0
 *
 * @return This Builder, for chaining calls
 */
- (instancetype) channelMixer: (simd_double3) outRed :(simd_double3) outGreen :(simd_double3) outBlue;
/**
 * Adjusts the colors separately in 3 distinct tonal ranges or zones: shadows, mid-tones,
 * and highlights.
 *
 * The tonal zones are by the ranges parameter: the x and y components define the beginning
 * and end of the transition from shadows to mid-tones, and the z and w components define
 * the beginning and end of the transition from mid-tones to highlights.
 *
 * A smooth transition is applied between the zones which means for instance that the
 * correction color of the shadows range will partially apply to the mid-tones, and the
 * other way around. This ensure smooth visual transitions in the final image.
 *
 * Each correction color is defined as a linear RGB color and a weight. The weight is a
 * value (which may be positive or negative) that is added to the linear RGB color before
 * mixing. This can be used to darken or brighten the selected tonal range.
 *
 * Shadows/mid-tones/highlights adjustment are performed linear space.
 *
 * @param shadows Linear RGB color (.rgb) and weight (.w) to apply to the shadows
 * @param midtones Linear RGB color (.rgb) and weight (.w) to apply to the mid-tones
 * @param highlights Linear RGB color (.rgb) and weight (.w) to apply to the highlights
 * @param ranges Range of the shadows (x and y), and range of the highlights (z and w)
 *
 * @return This Builder, for chaining calls
 */
- (instancetype) shadowsMidtonesHighlights: (simd_double4) shadows :(simd_double4) midtones :(simd_double4) highlights :(simd_double4) ranges;
/**
 * Applies a slope, offset, and power, as defined by the ASC CDL (American Society of
 * Cinematographers Color Decision List) to the image. The CDL can be used to adjust the
 * colors of different tonal ranges in the image.
 *
 * The ASC CDL is similar to the lift/gamma/gain controls found in many color grading tools.
 * Lift is equivalent to a combination of offset and slope, gain is equivalent to slope,
 * and gamma is equivalent to power.
 *
 * The slope and power values must be strictly positive. Values less than or equal to 0 will
 * be clamped to a small positive value, offset can be any positive or negative value.
 *
 * Version 1.2 of the ASC CDL adds saturation control, which is here provided as a separate
 * API. See the saturation() method for more information.
 *
 * Slope/offset/power adjustments are performed in log space.
 *
 * @param slope Multiplier of the input color, must be a strictly positive number
 * @param offset Added to the input color, can be a negative or positive number, including 0
 * @param power Power exponent of the input color, must be a strictly positive number
 *
 * @return This Builder, for chaining calls
 */
- (instancetype) slopeOffsetPower: (simd_double3) slope :(simd_double3) offset :(simd_double3) power;
/**
 * Adjusts the contrast of the image. Lower values decrease the contrast of the image
 * (the tonal range is narrowed), and higher values increase the contrast of the image
 * (the tonal range is widened). A value of 1.0 has no effect.
 *
 * The contrast is defined as a value in the range <code>[0.0...2.0]</code>. Values
 * outside of that range will be clipped to that range.
 *
 * Contrast adjustment is performed in log space.
 *
 * @param contrast Contrast expansion, between 0.0 and 2.0. 1.0 leaves contrast unaffected
 *
 * @return This Builder, for chaining calls
 */
- (instancetype) contrast: (double) contrast;
/**
 * Adjusts the saturation of the image based on the input color's saturation level.
 * Colors with a high level of saturation are less affected than colors with low saturation
 * levels.
 *
 * Lower vibrance values decrease intensity of the colors present in the image, and
 * higher values increase the intensity of the colors in the image. A value of 1.0 has
 * no effect.
 *
 * The vibrance is defined as a value in the range <code>[0.0...2.0]</code>. Values outside
 * of that range will be clipped to that range.
 *
 * Vibrance adjustment is performed in linear space.
 *
 * @param vibrance Vibrance, between 0.0 and 2.0. 1.0 leaves vibrance unaffected
 *
 * @return This Builder, for chaining calls
 */
- (instancetype) vibrance: (double) vibrance;
/**
 * Adjusts the saturation of the image. Lower values decrease intensity of the colors
 * present in the image, and higher values increase the intensity of the colors in the
 * image. A value of 1.0 has no effect.
 *
 * The saturation is defined as a value in the range <code>[0.0...2.0]</code>.
 * Values outside of that range will be clipped to that range.
 *
 * Saturation adjustment is performed in linear space.
 *
 * @param saturation Saturation, between 0.0 and 2.0. 1.0 leaves saturation unaffected
 *
 * @return This Builder, for chaining calls
 */
- (instancetype) saturation: (double) saturation;
/**
 * Applies a curve to each RGB channel of the image. Each curve is defined by 3 values:
 * a gamma value applied to the shadows only, a mid-point indicating where shadows stop
 * and highlights start, and a scale factor for the highlights.
 *
 * The gamma and mid-point must be strictly positive values. If they are not, they will be
 * clamped to a small positive value. The scale can be any negative of positive value.
 *
 * Curves are applied in linear space.
 *
 * @param shadowGamma Power value to apply to the shadows, must be strictly positive
 * @param midPoint Mid-point defining where shadows stop and highlights start, must be strictly positive
 * @param highlightScale Scale factor for the highlights, can be any negative or positive value
 *
 * @r
 */
- (instancetype) curves: (simd_double3) shadowGamma :(simd_double3) midPoint :(simd_double3) highlightScale;
/**
 * Creates the IndirectLight object and returns a pointer to it.
 *
 * @param engine The {@link Engine} to associate this <code>IndirectLight</code> with.
 *
 * @return A newly created <code>IndirectLight</code>
 *
 * @exception IllegalStateException if a parameter to a builder function was invalid.
 */
- (nonnull ColorGrading*) build: (nonnull Engine*) engine;

NS_ASSUME_NONNULL_END

@end


#endif /* ColorGradingBuilder_h */
