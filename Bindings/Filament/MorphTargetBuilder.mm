//
//  MorphTargetBuilder.mm

//  Created by Stef Tervelde on 30.06.22.
//
#import "Bindings/Filament/MorphTargetBuilder.h"
#import <filament/MorphTargetBuffer.h>

@implementation MorphTargetBuilder{
    filament::MorphTargetBuffer::Builder* nativeBuilder;
}

- (id) init:(void *)builder{
    self->_builder = builder;
    self->nativeBuilder = (filament::MorphTargetBuffer::Builder*)builder;
    return self;
}

@end
