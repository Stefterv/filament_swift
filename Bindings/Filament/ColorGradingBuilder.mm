//
//  ColorGradingBuilder.mm
//  swift-gltf-viewer
//
//  Created by Stef Tervelde on 30.06.22.
//
#import "Bindings/Filament/ColorGradingBuilder.h"
#import <filament/ColorGrading.h>

@implementation ColorGradingBuilder{
    filament::ColorGrading::Builder* nativeBuilder;
}

- (id) init:(void *)builder{
    self->_builder = builder;
    self->nativeBuilder = (filament::ColorGrading::Builder*)builder;
    return self;
}

@end
