//
//  Skybox.mm

//  Created by Stef Tervelde on 30.06.22.
//
#import "Bindings/Filament/Skybox.h"
#import <filament/Skybox.h>

@implementation Skybox{
    filament::Skybox* nativeSkybox;
}

- (id) init:(void *)skybox{
    self->_skybox = skybox;
    self->nativeSkybox = (filament::Skybox*)skybox;
    return self;
}

@end
