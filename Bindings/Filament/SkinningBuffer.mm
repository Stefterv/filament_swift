//
//  SkinningBuffer.mm
//  swift-gltf-viewer
//
//  Created by Stef Tervelde on 30.06.22.
//
#import "Bindings/Filament/SkinningBuffer.h"
#import <filament/SkinningBuffer.h>

@implementation SkinningBuffer{
    filament::SkinningBuffer* nativeBuffer;
}

- (id) init:(void *)buffer{
    self->_buffer = buffer;
    self->nativeBuffer = (filament::SkinningBuffer*)buffer;
    return self;
}

@end
