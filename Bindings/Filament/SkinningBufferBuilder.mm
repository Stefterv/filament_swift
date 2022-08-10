//
//  SkinningBufferBuilder.mm

//  Created by Stef Tervelde on 30.06.22.
//
#import "Bindings/Filament/SkinningBufferBuilder.h"
#import <filament/SkinningBuffer.h>

@implementation SkinningBufferBuilder{
    filament::SkinningBuffer::Builder* nativeBuilder;
}

- (id) init:(void *)builder{
    self->_builder = builder;
    self->nativeBuilder = (filament::SkinningBuffer::Builder*)builder;
    return self;
}

@end
