//
//  LightBuilder.h

//  Created by Stef Tervelde on 30.06.22.
//
#import <Foundation/Foundation.h>
#import "LightManager.h"
#import "Engine.h"
#import <simd/simd.h>

#ifndef LightBuilder_h
#define LightBuilder_h

NS_SWIFT_NAME(LightManager.Builder)
@interface LightBuilder : NSObject

@property (nonatomic, readonly, nonnull) void* builder  NS_SWIFT_UNAVAILABLE("Don't access the raw pointers");
- (nonnull id) init: (LightType) type;
- (nonnull id) init NS_UNAVAILABLE;

NS_ASSUME_NONNULL_BEGIN

/**
 * Enables or disables a light channel. Light channel 0 is enabled by default.
 *
 * @param channel Light channel to enable or disable, between 0 and 7.
 * @param enable Whether to enable or disable the light channel.
 */
- (instancetype) lightChannel: (int) channel :(bool) enable;
/**
 * Whether this Light casts shadows (disabled by default)
 *
 * <p>
 * <b>warning:</b>
 *  {@link Type#POINT} lights cannot cast shadows.
 * </p>
 *
 * @param enable Enables or disables casting shadows from this Light.
 *
 * @return This Builder, for chaining calls.
 */
- (instancetype) castShadows: (bool) enable;
/**
 * Sets the shadow map options for this light.
 * @param options A {@link ShadowOptions} instance
 * @return This Builder, for chaining calls.
 * @see ShadowOptions
 */
//- (instancetype) shadowOptions;
/**
 * Whether this light casts light (enabled by default)
 *
 * <p>
 * In some situations it can be useful to have a light in the scene that doesn't
 * actually emit light, but does cast shadows.
 * </p>
 *
 * @param enabled Enables or disables lighting from this Light.
 *
 * @return This Builder, for chaining calls.
 */
- (instancetype) castLight: (bool) enabled;
/**
 * Sets the initial position of the light in world space.
 * <p>
 * <b>note:</b> The Light's position is ignored for directional lights
 * ({@link Type#DIRECTIONAL} or {@link Type#SUN})
 * </p>
 *
 * @param position the position of the light
 *
 * @return This Builder, for chaining calls.
 */
- (instancetype) position: (simd_double3) position;
/**
 * Sets the initial direction of a light in world space.
 * <p>
 * The light direction is specified in world space and should be a unit vector.
 * </p>
 * <p>
 * <b>note:</b> The Light's direction is ignored for  {@link Type#POINT} lights.
 * </p>
 *
 * @param direction the direction of the light
 *
 * @return This Builder, for chaining calls.
 */
- (instancetype) direction: (simd_double3) direction;
/**
 * Sets the initial color of a light.
 * <p>
 * The light color is specified in the linear sRGB color-space. The default is white.
 * </p>
 *
 * @param linear the RGB components of the color (default is for all is 1)
 * @return This Builder, for chaining calls.
 * @see #setColor
 */
- (instancetype) color: (simd_double3) linear;
/**
 * Sets the initial intensity of a light.
 *
 * This method overrides any prior calls to #intensity or #intensityCandela.
 *
 * @param intensity This parameter depends on the {@link Type}, for directional lights,
 *                  it specifies the illuminance in <i>lux</i> (or <i>lumen/m^2</i>).
 *                  For point lights and spot lights, it specifies the luminous power
 *                  in <i>lumen</i>. For example, the sun's illuminance is about 100,000
 *                  lux.
 *
 * @return This Builder, for chaining calls.
 *
 * @see #setIntensity
 */
- (instancetype) intensity: (double) intensity;
/**
 * Sets the initial intensity of a spot or point light in candela.
 *
 * @param intensity Luminous intensity in <i>candela</i>.
 *
 * This method is equivalent to calling the plain intensity method for directional lights
 * (Type.DIRECTIONAL or Type.SUN).
 *
 * This method overrides any prior calls to #intensity or #intensityCandela.
 *
 * @return This Builder, for chaining calls.
 */
- (instancetype) intensityCandela: (double) intensity;
/**
 * Set the falloff distance for point lights and spot lights.
 *<p>
 * At the falloff distance, the light has no more effect on objects.
 *</p>
 *
 *<p>
 * The falloff distance essentially defines a <b>sphere of influence</b> around the light,
 * and therefore has an impact on performance. Larger falloffs might reduce performance
 * significantly, especially when many lights are used.
 *</p>
 *
 *<p>
 * Try to avoid having a large number of light's spheres of influence overlap.
 *</p>
 *
 * The Light's falloff is ignored for directional lights
 * ({@link Type#DIRECTIONAL} or {@link Type#SUN})
 *
 * @param radius Falloff distance in world units. Default is 1 meter.
 *
 * @return This Builder, for chaining calls.
 */
- (instancetype) falloff: (double) radius;

/**
 * Defines a spot light's angular falloff attenuation.
 * <p>
 * A spot light is defined by a position, a direction and two cones, inner and outer.
 * These two cones are used to define the angular falloff attenuation of the spot light
 * and are defined by the angle from the center axis to where the falloff begins (i.e.
 * cones are defined by their half-angle).
 * </p>
 * <p>
 * <b>note:</b> The spot light cone is ignored for directional and point lights.
 * </p>
 *
 * @param inner inner cone angle in <i>radian</i> between 0 and pi/2
 * @param outer outer cone angle in <i>radian</i> between inner and pi/2
 * @return This Builder, for chaining calls.
 *
 * @see Type#SPOT
 * @see Type#FOCUSED_SPOT
 */
- (instancetype) spotLightCone: (double) inner :(double) outer;

/**
 * Defines the angular radius of the sun, in degrees, between 0.25° and 20.0°
 *
 * The Sun as seen from Earth has an angular size of 0.526° to 0.545°
 *
 * @param angularRadius sun's radius in degree. Default is 0.545°.
 * @return This Builder, for chaining calls.
 */
- (instancetype) sunAngularRadius: (double) angularRadius;

/**
 * Defines the halo radius of the sun. The radius of the halo is defined as a
 * multiplier of the sun angular radius.
 *
 * @param haloSize radius multiplier. Default is 10.0.
 *
 * @return This Builder, for chaining calls.
 */
- (instancetype) sunHaloSize: (double) haloSize;

/**
 * Defines the halo falloff of the sun. The falloff is a dimensionless number
 * used as an exponent.
 *
 * @param haloFalloff halo falloff. Default is 80.0.
 *
 * @return This Builder, for chaining calls.
 */
- (instancetype) sunHaloFalloff: (double) haloFalloff;
/**
 * Adds the Light component to an entity.
 *
 * <p>
 * If this component already exists on the given entity, it is first destroyed as if
 * {@link #destroy} was called.
 * </p>
 *
 * <b>warning:</b>
 * Currently, only 2048 lights can be created on a given Engine.
 *
 * @param engine Reference to the {@link Engine} to associate this light with.
 * @param entity Entity to add the light component to.
 */
- (instancetype) build: (Engine*) engine :(Entity) entity;

NS_ASSUME_NONNULL_END
@end


#endif /* LightBuilder_h */
