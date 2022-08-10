//
//  ColorGradingBuilder.mm

//  Created by Stef Tervelde on 30.06.22.
//
#import "Bindings/Filament/ColorGradingBuilder.h"
#import <filament/ColorGrading.h>
#import "Bindings/Filament/ToneMapper.h"
#import "../Math.h"

@implementation ColorGradingBuilder{
    filament::ColorGrading::Builder* nativeBuilder;
}

- (id) init:(void *)builder{
    self->_builder = builder;
    self->nativeBuilder = (filament::ColorGrading::Builder*)builder;
    return self;
}

- (instancetype)quality:(int)qualityLevel{
    nativeBuilder->quality( (filament::ColorGrading::QualityLevel) qualityLevel);
    return self;
}
- (instancetype)format:(int)format{
    nativeBuilder->format( (filament::ColorGrading::LutFormat) format);
    return self;
}
- (instancetype)dimensions:(int)dim{
    nativeBuilder->dimensions(dim);
    return self;
}
- (instancetype)toneMapper:(ToneMapper *)toneMapper{
    nativeBuilder->toneMapper( (filament::ToneMapper*) toneMapper.mapper);
    return self;
}
- (instancetype)luminanceScaling:(bool)luminanceScaling{
    nativeBuilder->luminanceScaling(luminanceScaling);
    return self;
}
- (instancetype)gamutMapping:(bool)gamutMapping{
    nativeBuilder->gamutMapping(gamutMapping);
    return self;
}
- (instancetype)exposure:(double)exposure{
    nativeBuilder->exposure(exposure);
    return self;
}
- (instancetype)nightAdaptation:(double)adaptation{
    nativeBuilder->nightAdaptation(adaptation);
    return self;
}
- (instancetype)whiteBalance:(double)temperature :(double)tint{
    nativeBuilder->whiteBalance(temperature, tint);
    return self;
}
- (instancetype)channelMixer:(simd_double3)outRed :(simd_double3)outGreen :(simd_double3)outBlue{
    nativeBuilder->channelMixer(FLOAT3_FROM_SIMD(outRed), FLOAT3_FROM_SIMD(outGreen), FLOAT3_FROM_SIMD(outBlue));
    return self;
}
- (instancetype)shadowsMidtonesHighlights:(simd_double4)shadows :(simd_double4)midtones :(simd_double4)highlights :(simd_double4)ranges{
    nativeBuilder->shadowsMidtonesHighlights(FLOAT4_FROM_SIMD(shadows), FLOAT4_FROM_SIMD(midtones), FLOAT4_FROM_SIMD(highlights), FLOAT4_FROM_SIMD(ranges));
    return self;
}
- (instancetype)slopeOffsetPower:(simd_double3)slope :(simd_double3)offset :(simd_double3)power{
    nativeBuilder->slopeOffsetPower(FLOAT3_FROM_SIMD(slope), FLOAT3_FROM_SIMD(offset), FLOAT3_FROM_SIMD(power));
    return self;
}
- (instancetype)contrast:(double)contrast{
    nativeBuilder->contrast(contrast);
    return self;
}
- (instancetype)vibrance:(double)vibrance{
    nativeBuilder->vibrance(vibrance);
    return self;
}
- (instancetype)saturation:(double)saturation{
    nativeBuilder->saturation(saturation);
    return self;
}
- (instancetype)curves:(simd_double3)shadowGamma :(simd_double3)midPoint :(simd_double3)highlightScale{
    nativeBuilder->curves(FLOAT3_FROM_SIMD(shadowGamma), FLOAT3_FROM_SIMD(midPoint), FLOAT3_FROM_SIMD(highlightScale));
    return self;
}
- (ColorGrading *)build:(Engine *)engine{
    return [[ColorGrading alloc] init: nativeBuilder->build(*(filament::Engine*) engine.engine)];
}

@end
