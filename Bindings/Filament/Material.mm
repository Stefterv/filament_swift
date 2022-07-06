//
//  Material.mm
//  swift-gltf-viewer
//
//  Created by Stef Tervelde on 30.06.22.
//
#import "Bindings/Filament/Material.h"
#import <filament/Material.h>

@implementation Material{
    filament::Material* nativeMaterial;
}

- (id) init:(void *)material{
    self->_material = material;
    self->nativeMaterial = (filament::Material*)material;
    return self;
}

- (MaterialInstance *)createInstance{
    
}

@end
