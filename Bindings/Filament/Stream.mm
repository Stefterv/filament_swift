//
//  Stream.mm
//  swift-gltf-viewer
//
//  Created by Stef Tervelde on 30.06.22.
//
#import "Bindings/Filament/Stream.h"
#import <filament/Stream.h>

@implementation Stream{
    filament::Stream* nativeStream;
}

- (id) init:(void *)stream{
    self->_stream = stream;
    self->nativeStream = (filament::Stream*)stream;
    return self;
}

@end
