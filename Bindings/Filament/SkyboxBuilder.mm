//
//  SkyboxBuilder.mm

//  Created by Stef Tervelde on 30.06.22.
//
#import "Bindings/Filament/SkyboxBuilder.h"
#import <filament/Skybox.h>

@implementation SkyboxBuilder{
    filament::Skybox::Builder* nativeBuilder;
}

- (id) init:(void *)builder{
    self->_builder = builder;
    self->nativeBuilder = (filament::Skybox::Builder*)builder;
    return self;
}

@end
