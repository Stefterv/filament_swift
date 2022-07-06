//
//  RenderTargetBuilder.mm
//  swift-gltf-viewer
//
//  Created by Stef Tervelde on 05.07.22.
//
#import "Bindings/Filament/RenderTargetBuilder.h"
#import <filament/RenderTarget.h>

@implementation RenderTargetBuilder{
    filament::RenderTarget::Builder* nativeBuilder;
}

- (id) init:(void *)builder{
    self->_builder = builder;
    self->nativeBuilder = (filament::RenderTarget::Builder*)builder;
    return self;
}

@end
