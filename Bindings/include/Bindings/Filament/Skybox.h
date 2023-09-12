//
//  Skybox.h

//  Created by Stef Tervelde on 30.06.22.
//
#import <Foundation/Foundation.h>
#import <simd/simd.h>
#import "Texture.h"

#ifndef Skybox_h
#define Skybox_h

/**
 * Skybox
 *
 * When added to a Scene, the Skybox fills all untouched pixels.
 *
 * Creation and destruction
 * ========================
 *
 * A Skybox object is created using the Skybox::Builder and destroyed by calling
 * Engine::destroy(const Skybox*).
 *
 * ~~~~~~~~~~~{.cpp}
 *  filament::Engine* engine = filament::Engine::create();
 *
 *  filament::IndirectLight* skybox = filament::Skybox::Builder()
 *              .environment(cubemap)
 *              .build(*engine);
 *
 *  engine->destroy(skybox);
 * ~~~~~~~~~~~
 *
 *
 * @note
 * Currently only Texture based sky boxes are supported.
 *
 * @see Scene, IndirectLight
 */
@interface Skybox : NSObject

@property (nonatomic, readonly, nonnull) void* skybox  NS_SWIFT_UNAVAILABLE("Don't access the raw pointers");
- (nonnull id) init: (nonnull void*) skybox NS_SWIFT_UNAVAILABLE("Instances are created internally");
- (nonnull id) init NS_UNAVAILABLE;

- (void) setColor: (simd_float4) color;

/**
 * Sets bits in a visibility mask. By default, this is 0x1.
 *
 * This provides a simple mechanism for hiding or showing this Skybox in a Scene.
 *
 * @see View::setVisibleLayers().
 *
 * For example, to set bit 1 and reset bits 0 and 2 while leaving all other bits unaffected,
 * call: `setLayerMask(7, 2)`.
 *
 * @param select the set of bits to affect
 * @param values the replacement values for the affected bits
 */
- (void) setLayerMask: (uint8_t) select :(uint8_t) values;

/**
 * @return the visibility mask bits
 */
- (uint8_t) getLayerMask;

/**
 * Returns the skybox's intensity in lux, or lumen/m^2.
 */
- (float) getIntensity;

/**
 * @return the associated texture, or null if it does not exist
 */
- (nullable Texture*) getTexture;
@end


#endif /* Skybox_h */
