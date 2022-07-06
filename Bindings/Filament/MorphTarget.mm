//
//  MorphTarget.mm
//
//  Created by Stef Tervelde on 30.06.22.
//
#import "Bindings/Filament/MorphTarget.h"
#import <filament/MorphTargetBuffer.h>

@implementation MorphTarget{
    filament::MorphTargetBuffer* nativeBuffer;
}

- (id) init:(void *)buffer{
    self->_buffer = buffer;
    self->nativeBuffer = (filament::MorphTargetBuffer*)buffer;
    return self;
}

@end
