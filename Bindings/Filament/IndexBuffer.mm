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
    nativeBuffer->setBuffer(*(filament::Engine*) engine.engine, filament::IndexBuffer::BufferDescriptor(buffer.bytes, buffer.length));
}
- (void)setBuffer:(Engine *)engine :(NSData *)buffer{
    [self setBuffer:engine :buffer :0];
}
@end
