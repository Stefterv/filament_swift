//
//  MorphTarget.mm
//
//  Created by Stef Tervelde on 30.06.22.
//
#import "Bindings/Filament/MorphTargetBuffer.h"
#import <filament/MorphTargetBuffer.h>

@implementation MorphTargetBuffer{
    filament::MorphTargetBuffer* nativeBuffer;
}

- (id) init:(void *)buffer{
    self->_buffer = buffer;
    self->nativeBuffer = (filament::MorphTargetBuffer*)buffer;
    return self;
}

- (size_t)getVertexCount {
    return nativeBuffer->getVertexCount();
}

- (size_t)getCount {
    return nativeBuffer->getCount();
}

- (void)setPositionsAt:(nonnull Engine *)engine :(size_t)targetIndex :(nonnull const simd_float3 *)positions :(size_t)count :(size_t)offset {
#warning  Get simd_float3 array from swift
//    nativeBuffer->setPositionsAt((filament::Engine*)engine.engine, targetIndex, pos, count);
}

- (void)setTangentsAt:(nonnull Engine *)engine :(size_t)targetIndex :(nonnull const simd_short4 *)tangents :(size_t)count :(size_t)offset {
}

@end
