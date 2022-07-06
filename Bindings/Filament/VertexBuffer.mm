//
//  VertexBuffer.mm
//  swift-gltf-viewer
//
//  Created by Stef Tervelde on 30.06.22.
//
#import "Bindings/Filament/VertexBuffer.h"
#import <filament/VertexBuffer.h>

@implementation VertexBuffer{
    filament::VertexBuffer* nativeBuffer;
}

- (id) init:(void *)buffer{
    self->_buffer = buffer;
    self->nativeBuffer = (filament::VertexBuffer*)buffer;
    return self;
}

@end
