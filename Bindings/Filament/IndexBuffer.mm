//
//  IndexBuffer.mm

//  Created by Stef Tervelde on 30.06.22.
//
#import "Bindings/Filament/IndexBuffer.h"
#import <filament/IndexBuffer.h>
#import "Bindings/Filament/Engine.h"

@implementation IndexBuffer{
    filament::IndexBuffer* nativeBuffer;
}

- (id) init:(void *)buffer{
    self->_buffer = buffer;
    self->nativeBuffer = (filament::IndexBuffer*)buffer;
    return self;
}
- (void)setBuffer:(Engine *)engine :(NSData *)buffer :(uint32_t)byteOffset{
    const auto deleter = [](void* buffer, size_t size, void* user) {
        delete (uint8_t*) buffer;
    };
    auto start = (uint8_t*) buffer.bytes;
    auto bytes = new uint8_t[buffer.length];
    std::copy(start, start+buffer.length, bytes);
    
    
    nativeBuffer->setBuffer(*(filament::Engine*) engine.engine, filament::IndexBuffer::BufferDescriptor(bytes, buffer.length, deleter));
}
- (size_t)getIndexCount{
    return nativeBuffer->getIndexCount();
}
- (void)setBuffer:(Engine *)engine :(NSData *)buffer{
    [self setBuffer:engine :buffer :0];
}
@end
