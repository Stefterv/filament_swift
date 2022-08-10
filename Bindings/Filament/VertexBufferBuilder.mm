//
//  VertexBufferBuilder.mm
//
//  Created by Stef Tervelde on 10.08.22.
//
#import "Bindings/Filament/VertexBufferBuilder.h"
#import <filament/VertexBuffer.h>

@implementation VertexBufferBuilder{
    filament::VertexBuffer::Builder* nativeBuffer;
}

- (id) init:(void *)buffer{
    self->_buffer = buffer;
    self->nativeBuffer = (filament::VertexBuffer::Builder*)buffer;
    return self;
}
- (id)init{
    return [self init: new filament::VertexBuffer::Builder()];
}

- (VertexBuffer *)build:(Engine *)engine{
    auto buffer = nativeBuffer->build(*(filament::Engine*) engine.engine);
    return [[VertexBuffer alloc] init:buffer];
}

@end
