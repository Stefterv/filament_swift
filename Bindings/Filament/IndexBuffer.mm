//
//  IndexBuffer.mm
//  swift-gltf-viewer
//
//  Created by Stef Tervelde on 30.06.22.
//
#import "Bindings/Filament/IndexBuffer.h"
#import <filament/IndexBuffer.h>

@implementation IndexBuffer{
    filament::IndexBuffer* nativeBuffer;
}

- (id) init:(void *)buffer{
    self->_buffer = buffer;
    self->nativeBuffer = (filament::IndexBuffer*)buffer;
    return self;
}
#warning Delete
@end
