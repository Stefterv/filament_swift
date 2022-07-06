//
//  Texture.mm
//  swift-gltf-viewer
//
//  Created by Stef Tervelde on 30.06.22.
//
#import "Bindings/Filament/Texture.h"
#import <filament/Texture.h>

@implementation Texture{
    filament::Texture* nativeTexture;
}

- (id) init:(void *)texture{
    self->_texture = texture;
    self->nativeTexture = (filament::Texture*)texture;
    return self;
}

@end
