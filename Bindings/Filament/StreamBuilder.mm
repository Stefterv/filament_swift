//
//  StreamBuilder.mm

//  Created by Stef Tervelde on 30.06.22.
//
#import "Bindings/Filament/StreamBuilder.h"
#import <filament/Stream.h>

@implementation StreamBuilder{
    filament::Stream::Builder* nativeBuilder;
}

- (id) init:(void *)builder{
    self->_builder = builder;
    self->nativeBuilder = (filament::Stream::Builder*)builder;
    return self;
}

@end
