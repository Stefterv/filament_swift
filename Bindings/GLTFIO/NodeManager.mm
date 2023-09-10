//
//  NodeManager.mm
//  swift-gltf-viewer
//
//  Created by Stef Tervelde on 10.09.23.
//
#import "Bindings/GLTFIO/NodeManager.h"
#import <gltfio/NodeManager.h>

@implementation NodeManager{
    filament::gltfio::NodeManager* nativeManager;
}

- (id) init:(void *)Manager{
    self->_Manager = Manager;
    self->nativeManager = (filament::gltfio::NodeManager*)Manager;
    return self;
}

#warning("TODO")

@end
