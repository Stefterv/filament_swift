//
//  MorphTargetBuilder.mm

//  Created by Stef Tervelde on 30.06.22.
//
#import "Bindings/Filament/MorphTargetBufferBuilder.h"
#import <filament/MorphTargetBuffer.h>

@implementation MorphTargetBufferBuilder{
    filament::MorphTargetBuffer::Builder* nativeBuilder;
}

- (id) init:(void *)builder{
    self->_builder = builder;
    self->nativeBuilder = (filament::MorphTargetBuffer::Builder*)builder;
    return self;
}

- (nonnull instancetype)count:(size_t)count {
    nativeBuilder->count(count);
    return self;
}

- (nonnull instancetype)vertexCount:(size_t)vertexCount {
    nativeBuilder->vertexCount(vertexCount);
    return self;
}

- (nonnull MorphTargetBuffer *)build:(nonnull Engine *)engine {
    return [[MorphTargetBuffer alloc] init:nativeBuilder->build(*(filament::Engine*)engine.engine)];
}

@end
