//
//  IndirectLightBuilder.h

//  Created by Stef Tervelde on 30.06.22.
//
#import <Foundation/Foundation.h>
#import <simd/simd.h>
#import "IndirectLight.h"
#import "Texture.h"
#import "Engine.h"

#ifndef IndirectLightBuilder_h
#define IndirectLightBuilder_h

NS_SWIFT_NAME(IndirectLight.Builder)
@interface IndirectLightBuilder : NSObject

@property (nonatomic, readonly, nonnull) void* builder  NS_SWIFT_UNAVAILABLE("Don't access the raw pointers");
- (nonnull id) init: (nonnull void*) builder NS_SWIFT_UNAVAILABLE("Instances are created internally");
- (nonnull id) init;

NS_ASSUME_NONNULL_BEGIN
- (instancetype) reflections: (Texture*) cubemap;
/**
 * Sets the irradiance as Spherical Harmonics.
 *
 * <p>The irradiance coefficients must be pre-convolved by <code>&lt n &sdot l &gt</code> and
 * pre-multiplied by the Lambertian diffuse BRDF <code>1/&pi</code> and
 * specified as Spherical Harmonics coefficients.</p>
 *
 * <p>Additionally, these Spherical Harmonics coefficients must be pre-scaled by the
 * reconstruction factors A<sup>l,m</sup>.</p>
 *
 * <p>The final coefficients can be generated using the <code>cmgen</code> tool.</p>
 *
 * <p>The index in the <code>sh</code> array is given by:
 *  <br><code>index(l, m) = 3 &times (l * (l + 1) + m)</code>
 *  <br><code>sh[index(l,m) + 0] = L<sub>R</sub><sup>l,m</sup>
 *                      &times 1/&pi
 *                      &times A<sup>l,m</sup>
 *                      &times C<sup>l</sup> </code>
 *  <br><code>sh[index(l,m) + 1] = L<sub>G</sub><sup>l,m</sup>
 *                      &times 1/&pi
 *                      &times A<sup>l,m</sup>
 *                      &times C<sup>l</sup> </code>
 *  <br><code>sh[index(l,m) + 2] = L<sub>B</sub><sup>l,m</sup>
 *                      &times 1/&pi
 *                      &times A<sup>l,m</sup>
 *                      &times C<sup>l</sup> </code>
 * </p>
 *
 * <center>
 * <table border="1" cellpadding="3">
 *     <tr><th> index </th><th> l </th><th> m </th><th> A<sup>l,m</sup> </th><th> C<sup>l</sup> </th>
 *                  <th> 1/&pi &times A<sup>l,m</sup> &times C<sup>l</sup></th></tr>
 *     <tr align="right"><td>0</td><td>0</td><td> 0</td><td> 0.282095</td><td>3.1415926</td><td> 0.282095</td></tr>
 *     <tr align="right"><td>1</td><td>1</td><td>-1</td><td>-0.488602</td><td>2.0943951</td><td>-0.325735</td></tr>
 *     <tr align="right"><td>2</td><td>1</td><td> 0</td><td> 0.488602</td><td>2.0943951</td><td> 0.325735</td></tr>
 *     <tr align="right"><td>3</td><td>1</td><td> 1</td><td>-0.488602</td><td>2.0943951</td><td>-0.325735</td></tr>
 *     <tr align="right"><td>4</td><td>2</td><td>-2</td><td> 1.092548</td><td>0.785398 </td><td> 0.273137</td></tr>
 *     <tr align="right"><td>5</td><td>2</td><td>-1</td><td>-1.092548</td><td>0.785398 </td><td>-0.273137</td></tr>
 *     <tr align="right"><td>6</td><td>2</td><td> 0</td><td> 0.315392</td><td>0.785398 </td><td> 0.078848</td></tr>
 *     <tr align="right"><td>7</td><td>2</td><td> 1</td><td>-1.092548</td><td>0.785398 </td><td>-0.273137</td></tr>
 *     <tr align="right"><td>8</td><td>2</td><td> 2</td><td> 0.546274</td><td>0.785398 </td><td> 0.136569</td></tr>
 * </table>
 * </center>
 *
 *
 * <p>Only 1, 2 or 3 bands are allowed.</p>
 *
 * <p>Because the coefficients are pre-scaled, <code>sh[0]</code> is the environment's
 * average irradiance.</p>
 *
 * @param bands     Number of spherical harmonics bands. Must be 1, 2 or 3.
 * @param sh        Array containing the spherical harmonics coefficients.
 *                  The size of the array must be <code>3 &times bands<sup>2</sup></code>
 *                  (i.e. 1, 4 or 9 <code>float3</code> coefficients respectively).
 *
 * @return This Builder, for chaining calls.
 *
 * @exception ArrayIndexOutOfBoundsException if the <code>sh</code> array length is smaller
 *            than 3 &times bands<sup>2</sup>
 */
- (instancetype) irradiance: (int) bands :(simd_double3x3) sh;
/**
 * Sets the irradiance from the radiance expressed as Spherical Harmonics.
 *
 * <p>The radiance must be specified as Spherical Harmonics coefficients L<sup>l,m</sup>, where
 * each coefficient is comprised of three floats for red, green and blue components, respectively</p>
 *
 * <p>The index in the <code>sh</code> array is given by:
 *  <br><code>index(l, m) = 3 &times (l * (l + 1) + m)</code>
 *  <br><code>sh[index(l,m) + 0] = L<sub>R</sub><sup>l,m</sup></code>
 *  <br><code>sh[index(l,m) + 1] = L<sub>G</sub><sup>l,m</sup></code>
 *  <br><code>sh[index(l,m) + 2] = L<sub>B</sub><sup>l,m</sup></code>
 * </p>
 *
 * <center>
 * <table border="1" cellpadding="3">
 *     <tr><th> index </th><th> l </th><th> m </th>
 *     <tr align="right"><td>0</td><td>0</td><td> 0</td>
 *     <tr align="right"><td>1</td><td>1</td><td>-1</td>
 *     <tr align="right"><td>2</td><td>1</td><td> 0</td>
 *     <tr align="right"><td>3</td><td>1</td><td> 1</td>
 *     <tr align="right"><td>4</td><td>2</td><td>-2</td>
 *     <tr align="right"><td>5</td><td>2</td><td>-1</td>
 *     <tr align="right"><td>6</td><td>2</td><td> 0</td>
 *     <tr align="right"><td>7</td><td>2</td><td> 1</td>
 *     <tr align="right"><td>8</td><td>2</td><td> 2</td>
 * </table>
 * </center>
 *
 * @param bands     Number of spherical harmonics bands. Must be 1, 2 or 3.
 * @param sh        Array containing the spherical harmonics coefficients.
 *                  The size of the array must be 3 &times <code>bands<sup>2</sup></code>
 *                  (i.e. 1, 4 or 9 <code>float3</code> coefficients respectively).
 *
 * @return This Builder, for chaining calls.
 *
 * @exception ArrayIndexOutOfBoundsException if the <code>sh</code> array length is smaller
 *            than 3 &times bands<sup>2</sup>
 */
- (instancetype) radiance: (int) bands :(simd_double3x3) sh;
/**
 * Sets the irradiance as a cubemap.
 * <p></p>
 * The irradiance can alternatively be specified as a cubemap instead of Spherical
 * Harmonics coefficients. It may or may not be more efficient, depending on your
 * hardware (essentially, it's trading ALU for bandwidth).
 * <p></p>
 * This irradiance cubemap can be generated with the <code>cmgen</code> tool.
 *
 * @param cubemap   Cubemap representing the Irradiance pre-convolved by
 *                  <code>&lt n &sdot l &gt</code>.
 *
 * @return This Builder, for chaining calls.
 *
 * @see #irradiance(int bands, float[] sh)
 */
- (instancetype) irradiance: (Texture*) cubemap;
/**
 * Environment intensity (optional).
 *
 * <p>Because the environment is encoded usually relative to some reference, the
 * range can be adjusted with this method.</p>
 *
 * @param envIntensity  Scale factor applied to the environment and irradiance such that
 *                      the result is in <i>lux</i>, or <i>lumen/m^2</i> (default = 30000)
 *
 * @return This Builder, for chaining calls.
 */
- (instancetype) intensity: (double) intensity;
/**
 * Specifies the rigid-body transformation to apply to the IBL.
 *
 * @param rotation 3x3 rotation matrix. Must be a rigid-body transform.
 *
 * @return This Builder, for chaining calls.
 */
- (instancetype) rotation: (simd_double3x3) rotation;
- (IndirectLight*) build: (Engine*) engine;

NS_ASSUME_NONNULL_END
@end


#endif /* IndirectLightBuilder_h */
