//
//  SkyboxBuilder.mm

//  Created by Stef Tervelde on 30.06.22.
//
#import "Bindings/Filament/SkyboxBuilder.h"
#import "Bindings/Filament/Engine.h"
#import <filament/Skybox.h>
#import <math/mat4.h>

@implementation SkyboxBuilder{
    filament::Skybox::Builder* nativeBuilder;
}

- (id) init:(void *)builder{
    self->_builder = builder;
    self->nativeBuilder = (filament::Skybox::Builder*)builder;
    return self;
}

- (nonnull instancetype)color:(simd_float4)color {
    nativeBuilder->color(filament::math::float4(color[0], color[1], color[2], color[3]));
    return self;
}

- (nonnull instancetype)environment:(nonnull Texture *)cubemap {
    nativeBuilder->environment((filament::Texture*) cubemap.texture);
    return self;
}

- (nonnull instancetype)intensity:(float)envIntensity {
    nativeBuilder->intensity(envIntensity);
    return self;
}

- (nonnull instancetype)showSun:(bool)show {
    nativeBuilder->showSun(show);
    return self;
}

- (nonnull Skybox *)build:(nonnull Engine *)engine {
    return [[Skybox alloc] init:nativeBuilder->build(*(filament::Engine*) engine.engine)];
}

@end
