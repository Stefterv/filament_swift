//
//  BufferObjectBuilder.mm
//  swift-gltf-viewer
//
//  Created by Stef Tervelde on 10.09.23.
//
#import "Bindings/Filament/BufferObjectBuilder.h"
#import <filament/BufferObject.h>
#import <filament/Engine.h>

@implementation BufferObjectBuilder{
    filament::BufferObject::Builder* nativeBuilder;
}

- (id) init:(void *)Builder{
    self->_Builder = Builder;
    self->nativeBuilder = (filament::BufferObject::Builder*)Builder;
    return self;
}
- (nonnull instancetype)bindingType:(BindingType)bindingType {
    nativeBuilder->bindingType((filament::BufferObject::BindingType)bindingType);
    return self;
}
- (nonnull instancetype)size:(uint32_t)byteCount {
    nativeBuilder->size(byteCount);
    return self;
}
- (nonnull BufferObject *)build:(nonnull Engine *)engine {
    auto nativeBuffer = nativeBuilder->build(*(filament::Engine*)engine.engine);
    return [[BufferObject alloc] init:nativeBuffer];
}

@end
