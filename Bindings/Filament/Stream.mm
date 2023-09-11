//
//  Stream.mm

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

- (int64_t)getTimestamp {
    return nativeStream->getTimestamp();
}

- (void)setDimensions:(uint32_t)width :(uint32_t)height {
    nativeStream->setDimensions(width, height);
}

- (StreamType)getStreamType {
    return (StreamType) nativeStream->getStreamType();
}

@end
