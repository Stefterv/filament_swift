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
- (instancetype)bufferCount:(int)bufferCount{
    nativeBuffer->bufferCount(bufferCount);
    return self;
}
- (instancetype)vertexCount:(NSInteger)vertexCount{
    nativeBuffer->vertexCount((unsigned int)vertexCount);
    return self;
}
- (instancetype)enableBufferObjects:(bool)enabled{
    nativeBuffer->enableBufferObjects(enabled);
    return self;
}
- (instancetype)enableBufferObjects{
    nativeBuffer->enableBufferObjects();
    return self;
}
- (instancetype)attribute:(VertexAttribute)attribute :(int)bufferIndex :(AttributeType)attributeType :(int)byteOffset :(int)byteStride{
    nativeBuffer->attribute( (filament::VertexAttribute) attribute, bufferIndex, (filament::VertexBuffer::AttributeType) attributeType, byteOffset, byteStride);
    return self;
}
- (instancetype)attribute:(VertexAttribute)attribute :(int)bufferIndex :(AttributeType)attributeType{
    return [self attribute:attribute :bufferIndex :attributeType :0 :0];
}
- (instancetype)normalized:(VertexAttribute)attribute :(bool)normalize{
    nativeBuffer->normalized((filament::VertexAttribute) attribute, normalize);
    return self;
}
- (instancetype)normalized:(VertexAttribute)attribute{
    return [self normalized:attribute :true];
}


- (VertexBuffer *)build:(Engine *)engine{
    auto buffer = nativeBuffer->build(*(filament::Engine*) engine.engine);
    return [[VertexBuffer alloc] init:buffer];
}

@end
