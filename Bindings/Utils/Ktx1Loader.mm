//
//  Ktx1Loader.mm
//  swift-gltf-viewer
//
//  Created by Stef Tervelde on 05.07.22.
//
#import "Bindings/Utils/Ktx1Loader.h"
#import <ktxreader/Ktx1Reader.h>
#import <filament/Engine.h>
#import <filament/IndirectLight.h>
#import <filament/Skybox.h>

@implementation Ktx1Loader

+ (Texture *)createTexture:(Engine *)engine :(NSData *)buffer :(bool)srgb{
    auto nEngine = (filament::Engine*) engine.engine;
    
    auto bundle = ktxreader::Ktx1Bundle((uint8_t*)buffer.bytes, (uint32_t)buffer.length);
    
    auto texture = ktxreader::Ktx1Reader::createTexture(nEngine, &bundle, srgb);
    return [[Texture alloc] init:texture];
}

+ (IndirectLight *)createIndirectLight:(Engine *)engine :(NSData *)buffer :(bool)srgb{
    auto nEngine = (filament::Engine*) engine.engine;
    auto bytes = (uint8_t*) buffer.bytes;
    auto length = (uint32_t) buffer.length;
    
    auto bundle = new ktxreader::Ktx1Bundle(bytes, length);
    
    auto texture = ktxreader::Ktx1Reader::createTexture(nEngine, bundle, srgb);
    filament::math::float3 harmonics[9];
    bundle->getSphericalHarmonics(harmonics);
    
    auto light = filament::IndirectLight::Builder()
        .reflections(texture)
        .irradiance(3, harmonics)
        .intensity(30000)
        .build(*nEngine)
    ;
    return [[IndirectLight alloc] init:light];
}

+ (Skybox *)createSkybox:(Engine *)engine :(NSData *)buffer :(bool)srgb{
    auto nEngine = (filament::Engine*) engine.engine;
    auto bytes = (uint8_t*) buffer.bytes;
    auto length = (uint32_t) buffer.length;
    
    auto bundle = new ktxreader::Ktx1Bundle(bytes, length);
    
    auto texture = ktxreader::Ktx1Reader::createTexture(nEngine, bundle, srgb);
    
    auto skybox = filament::Skybox::Builder()
        .environment(texture)
        .build(*nEngine);
    
    return [[Skybox alloc] init: skybox];
    
}

@end
