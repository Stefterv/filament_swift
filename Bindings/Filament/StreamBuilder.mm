//
//  StreamBuilder.mm

//  Created by Stef Tervelde on 30.06.22.
//
#import "Bindings/Filament/StreamBuilder.h"
#import "Bindings/Filament/Engine.h"
#import <filament/Stream.h>

@implementation StreamBuilder{
    filament::Stream::Builder* nativeBuilder;
}

- (id) init:(void *)builder{
    self->_builder = builder;
    self->nativeBuilder = (filament::Stream::Builder*)builder;
    return self;
}

- (nonnull instancetype)height:(uint32_t)height {
    nativeBuilder->height(height);
    return self;
}

- (nonnull instancetype)stream:(nonnull void *)stream {
    nativeBuilder->stream(stream);
    return self;
}

- (nonnull instancetype)width:(uint32_t)width {
    nativeBuilder->width(width);
    return self;
}

- (nonnull Stream *)build:(nonnull Engine *)engine {
    return [[Stream alloc] init: nativeBuilder->build(*(filament::Engine*) engine.engine)];
}

@end
