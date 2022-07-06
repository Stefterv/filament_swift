//
//  RenderTarget.mm
//  swift-gltf-viewer
//
//  Created by Stef Tervelde on 30.06.22.
//
#import "Bindings/Filament/RenderTarget.h"
#import <filament/RenderTarget.h>

@implementation RenderTarget{
    filament::RenderTarget* nativeTarget;
}

- (id) init:(void *)target{
    self->_target = target;
    self->nativeTarget = (filament::RenderTarget*)target;
    return self;
}

@end
