//
//  VertexBuffer.mm
//
//  Created by Stef Tervelde on 30.06.22.
//
#import "Bindings/Filament/VertexBuffer.h"
#import <filament/VertexBuffer.h>
#import "Bindings/Filament/Engine.h"

@implementation VertexBuffer{
    filament::VertexBuffer* nativeBuffer;
}

- (id) init:(void *)buffer{
    self->_buffer = buffer;
    self->nativeBuffer = (filament::VertexBuffer*)buffer;
    return self;
}
- (size_t)getVertexCount{
    return nativeBuffer->getVertexCount();
}
- (void)setBufferAt:(Engine *)engine :(int)bufferIndex :(NSData *)data :(int)byteOffset{
    const auto deleter = [](void* buffer, size_t size, void* user) {
        printf("Clear!");
        delete (uint8_t*) buffer;
    };
    auto start = (uint8_t*) data.bytes;
    auto bytes = new uint8_t[data.length];
    std::copy(start, start+data.length, bytes);
    auto test2 = bytes[1];
    auto test3 = bytes[2];
    auto test4 = bytes[3];
    auto test5 = (float*)data.bytes;
    auto le = data.length;
    
    nativeBuffer->setBufferAt( *(filament::Engine*) engine.engine, bufferIndex, filament::backend::BufferDescriptor(bytes, data.length, deleter), byteOffset);
}
- (void)setBufferAt:(Engine *)engine :(int)bufferIndex :(NSData *)data{
    [self setBufferAt:engine :bufferIndex :data :0];
}

@end
