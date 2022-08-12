//
//  IndirectLightBuilder.mm

//  Created by Stef Tervelde on 30.06.22.
//
#import "Bindings/Filament/IndirectLightBuilder.h"
#import <filament/IndirectLight.h>
#import "../Math.h"

@implementation IndirectLightBuilder{
    filament::IndirectLight::Builder* nativeBuilder;
}

- (id) init:(void *)builder{
    self->_builder = builder;
    self->nativeBuilder = (filament::IndirectLight::Builder*)builder;
    return self;
}
- (id)init{
    return [self init: new filament::IndirectLight::Builder()];
}

- (instancetype)reflections:(Texture *)cubemap{
    nativeBuilder->reflections((filament::Texture*) cubemap.texture);
    return self;
}
- (instancetype)irradiance:(int)bands :(simd_double3x3)sh{
    auto cols = sh.columns;
    filament::math::float3 harmonics[9]{
        cols[0][0], cols[0][1], cols[0][2],
        cols[1][0], cols[1][1], cols[1][2],
        cols[2][0], cols[2][1], cols[2][2],
    };
    
    nativeBuilder->irradiance(bands, harmonics);
    return self;
}
- (instancetype)irradiance:(Texture *)cubemap{
    nativeBuilder->irradiance( (filament::Texture*) cubemap.texture);
    return self;
}
- (instancetype)radiance:(int)bands :(simd_double3x3)sh{
    auto cols = sh.columns;
    filament::math::float3 harmonics[9]{
        cols[0][0], cols[0][1], cols[0][2],
        cols[1][0], cols[1][1], cols[1][2],
        cols[2][0], cols[2][1], cols[2][2],
        
    };
    nativeBuilder->radiance(bands, harmonics);
    return self;
}
- (instancetype)intensity:(double)intensity{
    nativeBuilder->intensity(intensity);
    return self;
}
- (instancetype)rotation:(simd_double3x3)rotation{
    nativeBuilder->rotation(MAT3F_FROM_SIMD(rotation));
    return self;
}
- (IndirectLight *)build:(Engine *)engine{
    auto light = nativeBuilder->build(*(filament::Engine*) engine.engine);
    return [[IndirectLight alloc] init:light];
}

@end
