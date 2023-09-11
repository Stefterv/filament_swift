//
//  Ktx1Loader.h

//  Created by Stef Tervelde on 05.07.22.
//
#import <Foundation/Foundation.h>
#import "../Filament/Engine.h"

#ifndef Ktx1Loader_h
#define Ktx1Loader_h

@interface Ktx1Loader : NSObject

NS_ASSUME_NONNULL_BEGIN
/**
 * Creates a Texture object from a KTX bundle, populates all of its faces and miplevels,
 * and automatically destroys the bundle after all the texture data has been uploaded.
 *
 * @param engine Used to create the Filament Texture
 * @param ktx In-memory representation of a KTX file
 * @param srgb Requests an sRGB format from the KTX file
 */
+ (Texture*) createTexture: (Engine*) engine :(NSData*) buffer :(bool) srgb;
+ (IndirectLight*) createIndirectLight: (Engine*) engine :(NSData*) buffer :(bool) srgb;
+ (Skybox*) createSkybox: (Engine*) engine :(NSData*) buffer :(bool) srgb;
+ (simd_double3x3) getSphericalHarmonics:(NSData*) buffer;

NS_ASSUME_NONNULL_END
#warning Rework to KtxReader1 and KtxReader2
@end


#endif /* Ktx1Loader_h */
