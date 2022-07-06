//
//  MaterialInstance.mm
//  swift-gltf-viewer
//
//  Created by Stef Tervelde on 30.06.22.
//
#import "Bindings/Filament/MaterialInstance.h"
#import <filament/MaterialInstance.h>

@implementation MaterialInstance{
    filament::MaterialInstance* nativeInstance;
}

- (id) init:(void *)instance{
    self->_instance = instance;
    self->nativeInstance = (filament::MaterialInstance*)instance;
    return self;
}

@end
