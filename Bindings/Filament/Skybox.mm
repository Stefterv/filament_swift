//
//  Skybox.mm

//  Created by Stef Tervelde on 30.06.22.
//
#import "Bindings/Filament/Skybox.h"
#import <filament/Skybox.h>
#import <math/mat4.h>

@implementation Skybox{
    filament::Skybox* nativeSkybox;
}

- (id) init:(void *)skybox{
    self->_skybox = skybox;
    self->nativeSkybox = (filament::Skybox*)skybox;
    return self;
}

- (uint8_t)getLayerMask {
    return nativeSkybox->getLayerMask();
}

- (nullable Texture *)getTexture {
    return [[Texture alloc] init: (void*)nativeSkybox->getTexture()];
    
}

- (void)setColor:(simd_float4)color {
    nativeSkybox->setColor(filament::math::float4(color[0], color[1], color[2], color[3]));
}

- (void)setLayerMask:(uint8_t)select :(uint8_t)values {
    nativeSkybox->setLayerMask(select, values);
}

- (float)getIntensity {
    return nativeSkybox->getIntensity();
}

@end
