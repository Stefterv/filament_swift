//
//  TransformManager.mm
//  swift-gltf-viewer
//
//  Created by Stef Tervelde on 30.06.22.
//
#import "Bindings/Filament/TransformManager.h"
#import <filament/TransformManager.h>

@implementation TransformManager{
    filament::TransformManager* nativeManager;
}

- (id) init:(void *)manager{
    self->_manager = manager;
    self->nativeManager = (filament::TransformManager*)manager;
    return self;
}

@end
