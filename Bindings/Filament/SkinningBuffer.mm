//
//  SkinningBuffer.mm

//  Created by Stef Tervelde on 30.06.22.
//
#import "Bindings/Filament/SkinningBuffer.h"
#import <filament/SkinningBuffer.h>

@implementation SkinningBuffer{
    filament::SkinningBuffer* nativeBuffer;
}

- (id) init:(void *)buffer{
    self->_buffer = buffer;
    self->nativeBuffer = (filament::SkinningBuffer*)buffer;
    return self;
}

- (void)setBones:(nonnull Engine *)engine :(nonnull const simd_float4 *)transforms :(size_t)count :(size_t)offset {
#warning Bone/float4 array from swift
//    nativeBuffer->setBones((filament::Engine*) engine.engine, (filament::RenderableManager::Bone() , count, offset);
}

- (size_t)getBoneCount {
    return nativeBuffer->getBoneCount();
}

@end
