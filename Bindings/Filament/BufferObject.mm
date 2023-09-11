//
//  BufferObject.mm
//  swift-gltf-viewer
//
//  Created by Stef Tervelde on 10.09.23.
//
#import "Bindings/Filament/BufferObject.h"
#import <filament/BufferObject.h>
#import <filament/Engine.h>

@implementation BufferObject{
    filament::BufferObject* nativeObject;
}

- (id) init:(void *)BufferObject{
    self->_BufferObject = BufferObject;
    self->nativeObject = (filament::BufferObject*)BufferObject;
    return self;
}

- (void)setBuffer:(nonnull Engine *)engine :(nonnull NSData *)buffer :(uint32_t)byteOffset {
    const auto deleter = [](void* buffer, size_t size, void* user) {
        delete (uint8_t*) buffer;
    };
    auto start = (uint8_t*) buffer.bytes;
    auto bytes = new uint8_t[buffer.length];
    std::copy(start, start+buffer.length, bytes);
    nativeObject->setBuffer(*(filament::Engine*)engine.engine, filament::BufferObject::BufferDescriptor(bytes, buffer.length, deleter), byteOffset);
}

- (size_t)getByteCount {
    return nativeObject->getByteCount();
}

@end
