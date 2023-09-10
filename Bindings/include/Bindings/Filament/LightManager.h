//
//  LightManager.h

//  Created by Stef Tervelde on 30.06.22.
//
#import <Foundation/Foundation.h>
#import "Entity.h"
#import <simd/simd.h>

#ifndef LightManager_h
#define LightManager_h


@interface LightManager : NSObject

/**
 * LightManager allows you to create a light source in the scene, such as a sun or street lights.
 * <p>
 * At least one light must be added to a scene in order to see anything
 * (unless the {@link Material.Shading#UNLIT} is used).
 * </p>
 *
 * <h1><u>Creation and destruction</u></h1>
 * <p>
 * A Light component is created using the {@link LightManager.Builder} and destroyed by calling
 * {@link LightManager#destroy}.
 * </p>
 * <pre>
 *  Engine engine = Engine.create();
 *  int sun = EntityManager.get().create();
 *
 *  LightManager.Builder(Type.SUN)
 *              .castShadows(true)
 *              .build(engine, sun);
 *
 *  engine.getLightManager().destroy(sun);
 * </pre>
 *
 * <h1><u>Light types</u></h1>
 *
 * Lights come in three flavors:
 * <ul>
 * <li>directional lights</li>
 * <li>point lights</li>
 * <li>spot lights</li>
 * </ul>
 *
 *
 * <h2><u>Directional lights</u></h2>
 * <p>
 * Directional lights have a direction, but don't have a position. All light rays are
 * parallel and come from infinitely far away and from everywhere. Typically a directional light
 * is used to simulate the sun.
 * </p>
 * <p>
 * Directional lights and spot lights are able to cast shadows.
 * </p>
 * <p>
 * To create a directional light use {@link Type#DIRECTIONAL} or {@link Type#SUN}, both are similar,
 * but the later also draws a sun's disk in the sky and its reflection on glossy objects.
 * </p>
 * <p>
 * <b>warning:</b> Currently, only a single directional light is supported. If several directional lights
 * are added to the scene, the dominant one will be used.
 * </p>
 *
 * <h2><u>Point lights</u></h2>
 *
 * Unlike directional lights, point lights have a position but emit light in all directions.
 * The intensity of the light diminishes with the inverse square of the distance to the light.
 * {@link Builder#falloff} controls the distance beyond which the light has no more influence.
 * <p>
 * A scene can have multiple point lights.
 * </p>
 *
 * <h2><u>Spot lights</u></h2>
 * <p>
 * Spot lights are similar to point lights but the light they emit is limited to a cone defined by
 * {@link Builder#spotLightCone} and the light's direction.
 * </p>
 * <p>
 * A spot light is therefore defined by a position, a direction and inner and outer cones. The
 * spot light's influence is limited to inside the outer cone. The inner cone defines the light's
 * falloff attenuation.
 * </p>
 * A physically correct spot light is a little difficult to use because changing the outer angle
 * of the cone changes the illumination levels, as the same amount of light is spread over a
 * changing volume. The coupling of illumination and the outer cone means that an artist cannot
 * tweak the influence cone of a spot light without also changing the perceived illumination.
 * It therefore makes sense to provide artists with a parameter to disable this coupling. This
 * is the difference between {@link Type#FOCUSED_SPOT} (physically correct) and {@link Type#SPOT}
 * (decoupled).
 * </p>
 *
 * <h1><u>Performance considerations</u></h1>
 * <p>
 * Generally, adding lights to the scene hurts performance, however filament is designed to be
 * able to handle hundreds of lights in a scene under certain conditions. Here are some tips
 * to keep good performance.
 * </p>
 * <ul>
 * <li> Prefer spot lights to point lights and use the smallest outer cone angle possible.</li>
 * <li> Use the smallest possible falloff distance for point and spot lights.
 *    Performance is very sensitive to overlapping lights. The falloff distance essentially
 *    defines a sphere of influence for the light, so try to position point and spot lights
 *    such that they don't overlap too much.</li>
 *    On the other hand, a scene can contain hundreds of non overlapping lights without
 *    incurring a significant overhead.
 * </ul>
 */
@property (nonatomic, readonly, nonnull) void* manager  NS_SWIFT_UNAVAILABLE("Don't access the raw pointers");
- (nonnull id) init: (nonnull void*) manager NS_SWIFT_UNAVAILABLE("Instances are created internally");
- (nonnull id) init NS_UNAVAILABLE;

/**
 * Returns the number of components in the LightManager, note that components are not
 * guaranteed to be active. Use the {@link EntityManager#isAlive} before use if needed.
 *
 * @return number of component in the LightManager
 */
- (size_t) getComponentCount;
/**
 * Returns whether a particular Entity is associated with a component of this LightManager
 * @param entity An Entity.
 * @return true if this Entity has a component associated with this manager.
 */
- (bool) hasComponent: (Entity) entity;

/**
 * Gets an Instance representing the Light component associated with the given Entity.
 * @param entity An Entity.
 * @return An Instance object, which represents the Light component associated with the Entity entity.
 *         The instance is 0 if the component doesn't exist.
 * @see #hasComponent
 */
- (EntityInstance) getInstance: (Entity) entity;

/**
 * Destroys this component from the given entity
 * @param entity An Entity.
 */
- (void) destroy: (Entity) entity;

typedef NS_ENUM(NSInteger, LightType) {
    LightTypeSun = 0,
    LightTypeDirectional = 1,
    LightTypePoint = 2,
    LightTypeFocusedSpot = 3,
    LightTypeSpot = 4
};
- (LightType) getType: (EntityInstance) instance;
- (bool) isDirectional: (EntityInstance) instance;
- (bool) isPointLight: (EntityInstance) instance;
- (bool) isSpotLight: (EntityInstance) instance;
/**
 * Enables or disables a light channel.
 * Light channel 0 is enabled by default.
 *
 * @param i        Instance of the component obtained from getInstance().
 * @param channel  Light channel to set
 * @param enable   true to enable, false to disable
 *
 * @see Builder#lightChannel
 */
- (void) setLightChannel: (EntityInstance) instance :(int) channel :(bool) enable;
/**
 * Returns whether a light channel is enabled on a specified renderable.
 * @param i        Instance of the component obtained from getInstance().
 * @param channel  Light channel to query
 * @return         true if the light channel is enabled, false otherwise
 */
- (bool) getLightChannel: (EntityInstance) instance :(int) channel;
/**
 * Dynamically updates the light's position.
 *
 * <p>
 * <b>note:</b> The Light's position is ignored for directional lights
 * ({@link Type#DIRECTIONAL} or {@link Type#SUN})
 * </p>
 *
 * @param i        Instance of the component obtained from getInstance().
 * @param x Light's position x coordinate in world space. The default is 0.
 * @param y Light's position y coordinate in world space. The default is 0.
 * @param z Light's position z coordinate in world space. The default is 0.
 *
 * @see Builder#position
 */
- (void) setPosition: (EntityInstance) instance :(simd_double3) position;

/**
 * returns the light's position in world space
 * @param i     Instance of the component obtained from getInstance().
 * @return      An array of 3 float containing the light's position coordinates.
 */
- (simd_double3) getPosition: (EntityInstance) instance;
/**
 * Dynamically updates the light's direction
 *
 * <p>
 * The light direction is specified in world space and should be a unit vector.
 * </p>
 * <p>
 * <b>note:</b> The Light's direction is ignored for  {@link Type#POINT} lights.
 * </p>
 *
 * @param i Instance of the component obtained from getInstance().
 * @param x light's direction x coordinate (default is 0)
 * @param y light's direction y coordinate (default is -1)
 * @param z light's direction z coordinate (default is 0)
 *
 * @see Builder#direction
 */
- (void) setDirection: (EntityInstance) instance :(simd_double3) direction;
/**
 * returns the light's direction in world space
 * @param i     Instance of the component obtained from getInstance().
 * @param out   An array of 3 float to receive the result or null.
 * @return      An array of 3 float containing the light's direction.
 */
- (simd_double3) getDirection: (EntityInstance) instance;
/**
 * Dynamically updates the light's hue as linear sRGB
 *
 * @param i     Instance of the component obtained from getInstance().
 * @param linearR red component of the color (default is 1)
 * @param linearG green component of the color (default is 1)
 * @param linearB blue component of the color (default is 1)
 *
 * @see Builder#color
 * @see #getInstance
 */
- (void) setColor: (EntityInstance) instance :(simd_double3) linear;
/**
 * Returns the light color
 * @param i     Instance of the component obtained from getInstance().
 * @return      An array of 3 float containing the light's color in linear sRGB
 */
- (simd_double3) getColor: (EntityInstance) instance;
/**
 * Dynamically updates the light's intensity. The intensity can be negative.
 *
 * @param i         Instance of the component obtained from getInstance().
 * @param intensity This parameter depends on the {@link Type}, for directional lights,
 *                  it specifies the illuminance in <i>lux</i> (or <i>lumen/m^2</i>).
 *                  For point lights and spot lights, it specifies the luminous power
 *                  in <i>lumen</i>. For example, the sun's illuminance is about 100,000
 *                  lux.
 *
 * @see Builder#intensity
 */
- (void) setIntensity: (EntityInstance) instance :(double) intensity;

/**
 * Dynamically updates the light's intensity in candela. The intensity can be negative.
 *
 * This method is equivalent to calling setIntensity for directional lights (Type.DIRECTIONAL
 * or Type.SUN).
 *
 * @param i         Instance of the component obtained from getInstance().
 * @param intensity Luminous intensity in <i>candela</i>.
 *
 * @see Builder#intensityCandela
 */
- (void) setIntensityCandela: (EntityInstance) instance :(double) intensity;
/**
 * returns the light's luminous intensity in <i>lumens</i>.
 *<p>
 * <b>note:</b> for {@link Type#FOCUSED_SPOT} lights, the returned value depends on the outer cone angle.
 *</p>
 *
 * @param i     Instance of the component obtained from getInstance().
 *
 * @return luminous intensity in <i>lumen</i>.
 */
- (double) getIntensity: (EntityInstance) instance;
/**
 * Set the falloff distance for point lights and spot lights.
 *
 * @param i       Instance of the component obtained from getInstance().
 * @param falloff falloff distance in world units. Default is 1 meter.
 *
 * @see Builder#falloff
 */
- (void) setFalloff: (EntityInstance) instance :(double) falloff;
/**
 * returns the falloff distance of this light.
 * @param i     Instance of the component obtained from getInstance().
 * @return      the falloff distance of this light.
 */
- (double) getFalloff: (EntityInstance) instance;
/**
 * Dynamically updates a spot light's cone as angles
 *
 * @param i     Instance of the component obtained from getInstance().
 * @param inner inner cone angle in *radians* between 0 and pi/2
 * @param outer outer cone angle in *radians* between inner and pi/2
 *
 * @see Builder#spotLightCone
 */
- (void) setSpotLightCone: (EntityInstance) instance :(double) inner :(double) outer;
/**
 * Dynamically updates the angular radius of a Type.SUN light
 *
 * The Sun as seen from Earth has an angular size of 0.526° to 0.545°
 *
 * @param i     Instance of the component obtained from getInstance().
 * @param angularRadius sun's radius in degrees. Default is 0.545°.
 */
- (void) setSunAngularRadius: (EntityInstance) instance :(double) angularRadius;
/**
 * returns the angular radius if the sun in degrees.
 * @param i     Instance of the component obtained from getInstance().
 * @return the angular radius if the sun in degrees.
 */
- (double) getSunAngularRadius: (EntityInstance) instance;
/**
 * Dynamically updates the halo radius of a Type.SUN light. The radius
 * of the halo is defined as a multiplier of the sun angular radius.
 *
 * @param i     Instance of the component obtained from getInstance().
 * @param haloSize radius multiplier. Default is 10.0.
 */
- (void) setSunHaloSize: (EntityInstance) instance :(double) haloSize;
/**
 * returns the halo size of a Type.SUN light as a multiplier of the
 * sun angular radius.
 * @param i     Instance of the component obtained from getInstance().
 * @return the halo size
 */
- (double) getSunHaloSize: (EntityInstance) instance;
/**
 * Dynamically updates the halo falloff of a Type.SUN light. The falloff
 * is a dimensionless number used as an exponent.
 *
 * @param i     Instance of the component obtained from getInstance().
 * @param haloFalloff halo falloff. Default is 80.0.
 */
- (void) setSunHaloFalloff: (EntityInstance) instance :(double) haloFalloff;
/**
 * returns the halo falloff of a Type.SUN light as a dimensionless value.
 * @param i     Instance of the component obtained from getInstance().
 * @return the halo falloff
 */
- (double) getSunHaloFalloff: (EntityInstance) instance;
/**
 * Whether this Light casts shadows (disabled by default)
 *
 * <p>
 * <b>warning:</b> {@link Type#POINT} cannot cast shadows.
 * </p>
 *
 * @param i     Instance of the component obtained from getInstance().
 * @param shadowCaster Enables or disables casting shadows from this Light.
 */
- (void) setShadowCaster: (EntityInstance) instance :(bool) shadowCaster;
/**
 * returns whether this light casts shadows.
 * @param i     Instance of the component obtained from getInstance().
 */
- (bool) isShadowCaster: (EntityInstance) instance;
- (double) getOuterConeAngle: (EntityInstance) instance;
- (double) getInnerConeAngle: (EntityInstance) instance;
@end





#endif /* LightManager_h */
