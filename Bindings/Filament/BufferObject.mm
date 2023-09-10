//
//  BufferObject.mm
//  swift-gltf-viewer
//
//  Created by Stef Tervelde on 10.09.23.
//
#import "Bindings/Filament/BufferObject.h"
#import <filament/BufferObject.h>

@implementation BufferObject{
    filament::BufferObject* nativeObject;
}

- (id) init:(void *)BufferObject{
    self->_BufferObject = BufferObject;
    self->nativeObject = (filament::BufferObject*)BufferObject;
    return self;
}

@end
