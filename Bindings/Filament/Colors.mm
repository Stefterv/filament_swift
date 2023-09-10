//
//  Colors.mm
//  swift-gltf-viewer
//
//  Created by Stef Tervelde on 10.09.23.
//
#import "Bindings/Filament/Colors.h"
#import <filament/Color.h>

@implementation Colors{
    filament::Color* nativeColors;
}

- (id) init:(void *)Colors{
    self->_Colors = Colors;
    self->nativeColors = (filament::Color*)Colors;
    return self;
}

@end
