//
//  SkinningBufferBuilder.mm

//  Created by Stef Tervelde on 30.06.22.
//
#import "Bindings/Filament/SkinningBufferBuilder.h"
#import "Bindings/Filament/Engine.h"
#import <filament/SkinningBuffer.h>
#import <filament/Engine.h>

@implementation SkinningBufferBuilder{
    filament::SkinningBuffer::Builder* nativeBuilder;
}

- (id) init:(void *)builder{
    self->_builder = builder;
    self->nativeBuilder = (filament::SkinningBuffer::Builder*)builder;
    return self;
}



- (nonnull instancetype)initialize:(bool)initialize {
    nativeBuilder->initialize(initialize);
    return self;
}

- (nonnull instancetype)boneCount:(uint32_t)boneCount {
    nativeBuilder->boneCount(boneCount);
    return self;
}
- (nonnull SkinningBuffer *)build:(nonnull Engine *)engine {
    auto buffer = nativeBuilder->build(*(filament::Engine*) engine.engine);
    return [[SkinningBuffer alloc] init:buffer];
}

@end
