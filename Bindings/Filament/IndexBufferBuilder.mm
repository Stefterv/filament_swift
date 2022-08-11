//
//  IndexBufferBuilder.mm

//
//  Created by Stef Tervelde on 10.08.22.
//
#import "Bindings/Filament/IndexBufferBuilder.h"
#import <filament/IndexBuffer.h>

@implementation IndexBufferBuilder{
    filament::IndexBuffer::Builder* nativeBuffer;
}

- (id) init:(void *)buffer{
    self->_buffer = buffer;
    self->nativeBuffer = (filament::IndexBuffer::Builder*)buffer;
    return self;
}
- (id)init{
    return [self init: new filament::IndexBuffer::Builder()];
}
- (instancetype)indexCount:(NSInteger)indexCount{
    nativeBuffer->indexCount((uint32_t) indexCount);
    return self;
}
- (instancetype)bufferType:(IndexType)type{
    nativeBuffer->bufferType((filament::IndexBuffer::IndexType) type);
    return self;
}
- (IndexBuffer *)build:(Engine *)engine{
    auto buffer = nativeBuffer->build(*(filament::Engine*) engine.engine);
    return [[IndexBuffer alloc] init:buffer];
}

@end
