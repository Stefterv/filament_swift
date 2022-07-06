//
//  TextureBuilder.mm
//  swift-gltf-viewer
//
//  Created by Stef Tervelde on 05.07.22.
//
#import "Bindings/Filament/TextureBuilder.h"
#import <filament/Texture.h>

@implementation TextureBuilder{
    filament::Texture::Builder* nativeBuilder;
}

- (id) init:(void *)builder{
    self->_builder = builder;
    self->nativeBuilder = (filament::Texture::Builder*)builder;
    return self;
}

@end
