//
//  LightBuilder.mm

//  Created by Stef Tervelde on 30.06.22.
//
#import "Bindings/Filament/LightBuilder.h"
#import "Bindings/Filament/LightManager.h"
#import <filament/LightManager.h>
#import <filament/Engine.h>
#import "../Math.h"

@implementation LightBuilder{
    filament::LightManager::Builder* nativeBuilder;
}

- (id) init: (LightType) type{
    auto builder = new filament::LightManager::Builder( (filament::LightManager::Type) type);
    self->_builder = builder;
    self->nativeBuilder = builder;
    return self;
}

- (instancetype)lightChannel:(int)channel :(bool)enable{
    nativeBuilder->lightChannel(channel, enable);
    return self;
}
- (instancetype)castShadows:(bool)enable{
    nativeBuilder->castShadows(enable);
    return self;
}
- (instancetype)castLight:(bool)enabled{
    nativeBuilder->castLight(enabled);
    return self;
}
- (instancetype)position:(simd_double3)position{
    nativeBuilder->position(FLOAT3_FROM_SIMD(position));
    return self;
}
- (instancetype)direction:(simd_double3)direction{
    nativeBuilder->direction(FLOAT3_FROM_SIMD(direction));
    return self;
}
- (instancetype)color:(simd_double3)linear{
    nativeBuilder->color(FLOAT3_FROM_SIMD(linear));
    return self;
}
- (instancetype)intensity:(double)intensity{
    nativeBuilder->intensity(intensity);
    return self;
}
- (instancetype)intensityCandela:(double)intensity{
    nativeBuilder->intensityCandela(intensity);
    return self;
}
- (instancetype)falloff:(double)radius{
    nativeBuilder->falloff(radius);
    return self;
}
- (instancetype)spotLightCone:(double)inner :(double)outer{
    nativeBuilder->spotLightCone(inner, outer);
    return self;
}
- (instancetype)sunAngularRadius:(double)angularRadius{
    nativeBuilder->sunAngularRadius(angularRadius);
    return self;
}
- (instancetype)sunHaloSize:(double)haloSize{
    nativeBuilder->sunHaloSize(haloSize);
    return self;
}
- (instancetype)sunHaloFalloff:(double)haloFalloff{
    nativeBuilder->sunHaloFalloff(haloFalloff);
    return self;
}
- (instancetype)build:(Engine *)engine :(Entity)entity{
    nativeBuilder->build( *(filament::Engine*)engine.engine , utils::Entity::import(entity));
    return self;
}

@end
