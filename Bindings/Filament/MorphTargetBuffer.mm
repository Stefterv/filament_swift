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

@end
