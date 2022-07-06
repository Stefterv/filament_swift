//
//  Ktx1Loader.h
//  swift-gltf-viewer
//
//  Created by Stef Tervelde on 05.07.22.
//
#import <Foundation/Foundation.h>
#import "../Filament/Engine.h"

#ifndef Ktx1Loader_h
#define Ktx1Loader_h

@interface Ktx1Loader : NSObject

NS_ASSUME_NONNULL_BEGIN
+ (Texture*) createTexture: (Engine*) engine :(NSData*) buffer :(bool) srgb;
+ (IndirectLight*) createIndirectLight: (Engine*) engine :(NSData*) buffer :(bool) srgb;
+ (Skybox*) createSkybox: (Engine*) engine :(NSData*) buffer :(bool) srgb;
+ (simd_double3x3) getSphericalHarmonics:(NSData*) buffer;

NS_ASSUME_NONNULL_END
@end


#endif /* Ktx1Loader_h */
