//
//  BufferObjectBuilder.mm
//  swift-gltf-viewer
//
//  Created by Stef Tervelde on 10.09.23.
//
#import "Bindings/Filament/BufferObjectBuilder.h"
#import <filament/BufferObject.h>

@implementation BufferObjectBuilder{
    filament::BufferObject::Builder* nativeBuilder;
}

- (id) init:(void *)Builder{
    self->_Builder = Builder;
    self->nativeBuilder = (filament::BufferObject::Builder*)Builder;
    return self;
}

@end
