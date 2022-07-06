//
//  IndirectLightBuilder.mm
//  swift-gltf-viewer
//
//  Created by Stef Tervelde on 30.06.22.
//
#import "Bindings/Filament/IndirectLightBuilder.h"
#import <filament/IndirectLight.h>

@implementation IndirectLightBuilder{
    filament::IndirectLight::Builder* nativeBuilder;
}

- (id) init:(void *)builder{
    self->_builder = builder;
    self->nativeBuilder = (filament::IndirectLight::Builder*)builder;
    return self;
}

@end
