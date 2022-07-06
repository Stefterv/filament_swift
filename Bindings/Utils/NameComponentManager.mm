//
//  NameComponentManager.mm
//  swift-gltf-viewer
//
//  Created by Stef Tervelde on 01.07.22.
//
#import "Bindings/Utils/NameComponentManager.h"
#import <utils/NameComponentManager.h>

@implementation NameComponentManager{
    utils::NameComponentManager* nativeManager;
}

- (id) init:(void *)manager{
    self->_manager = manager;
    self->nativeManager = (utils::NameComponentManager*)manager;
    return self;
}

@end
