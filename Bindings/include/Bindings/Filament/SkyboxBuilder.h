//
//  SkyboxBuilder.h

//  Created by Stef Tervelde on 30.06.22.
//
#import <Foundation/Foundation.h>
#import "Skybox.h"

#ifndef SkyboxBuilder_h
#define SkyboxBuilder_h

@interface SkyboxBuilder : NSObject

@property (nonatomic, readonly, nonnull) void* builder  NS_SWIFT_UNAVAILABLE("Don't access the raw pointers");
- (nonnull id) init: (nonnull void*) builder NS_SWIFT_UNAVAILABLE("Instances are created internally");
- (nonnull id) init NS_UNAVAILABLE;
NS_ASSUME_NONNULL_BEGIN
/**
 * Set the environment map (i.e. the skybox content).
 *
 * The Skybox is rendered as though it were an infinitely large cube with the camera
 * inside it. This means that the cubemap which is mapped onto the cube's exterior
 * will appear mirrored. This follows the OpenGL conventions.
 *
 * The cmgen tool generates reflection maps by default which are therefore ideal to use
 * as skyboxes.
 *
 * @param cubemap This Texture must be a cube map.
 *
 * @return This Builder, for chaining calls.
 *
 * @see Texture
 */
- (instancetype) environment: (Texture*) cubemap;

/**
 * Indicates whether the sun should be rendered. The sun can only be
 * rendered if there is at least one light of type SUN in the scene.
 * The default value is false.
 *
 * @param show True if the sun should be rendered, false otherwise
 *
 * @return This Builder, for chaining calls.
 */
- (instancetype) showSun: (bool) show;

/**
 * Skybox intensity when no IndirectLight is set on the Scene.
 *
 * This call is ignored when an IndirectLight is set on the Scene, and the intensity
 * of the IndirectLight is used instead.
 *
 * @param envIntensity  Scale factor applied to the skybox texel values such that
 *                      the result is in lux, or lumen/m^2 (default = 30000)
 *
 * @return This Builder, for chaining calls.
 *
 * @see IndirectLight::Builder::intensity
 */
- (instancetype) intensity: (float) envIntensity;

/**
 * Sets the skybox to a constant color. Default is opaque black.
 *
 * Ignored if an environment is set.
 *
 * @param color the constant color
 *
 * @return This Builder, for chaining calls.
 */
- (instancetype) color:(simd_float4) color;

/**
 * Creates the Skybox object and returns a pointer to it.
 *
 * @param engine Reference to the filament::Engine to associate this Skybox with.
 *
 * @return pointer to the newly created object, or nullptr if the light couldn't be created.
 */
- (Skybox*) build: (Engine*) engine;
NS_ASSUME_NONNULL_END
@end


#endif /* SkyboxBuilder_h */
