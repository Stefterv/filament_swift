//
//  NameComponentManager.mm
//  swift-gltf-viewer
//
//  Created by Stef Tervelde on 10.09.23.
//
#import "Bindings/Utils/NameComponentManager.h"
#import <utils/NameComponentManager.h>

@implementation NameComponentManager{
    utils::NameComponentManager* nativeManager;
}

- (id) init:(void *)manager{
    self->_manager = manager;
    self->nativeManager = (utils::NameComponentManager*) manager;
    return self;
}

#warning("TODO")

@end
