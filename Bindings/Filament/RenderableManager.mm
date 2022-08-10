//
//  RenderableManager.mm
//  swift-gltf-viewer
//
//  Created by Stef Tervelde on 30.06.22.
//
#import "Bindings/Filament/RenderableManager.h"
#import <filament/RenderableManager.h>
#import <filament/Box.h>

@implementation RenderableManager{
    filament::RenderableManager* nativeManager;
}

- (id) init:(void *)manager{
    self->_manager = manager;
    self->nativeManager = (filament::RenderableManager*)manager;
    return self;
}

- (void)setAxisAlignedBoundingBox:(EntityInstance)instance :(Box *)aabb{
# warning Figure out box
}

- (Box *)getAxisAlignedBoundingBox:(EntityInstance)instance{
# warning Figure out box
}

- (void)setLayerMask:(EntityInstance)instance :(uint8_t)select :(uint8_t)value{
    nativeManager->setLayerMask(instance, select, value);
}
- (void)setPriority:(EntityInstance)instance :(int)priority{
    nativeManager->setPriority(instance, priority);
}
- (void)setCulling:(EntityInstance)instance :(bool)enabled{
    nativeManager->setCulling(instance, enabled);
}
- (void)setLightChannel:(EntityInstance)instance :(uint8_t)channel :(bool)value{
    nativeManager->setLightChannel(instance, channel, value);
}
- (bool)getLightChannel:(EntityInstance)instance :(uint8_t)channel{
    return nativeManager->getLightChannel(instance, channel);
}
- (void)setCastShadows:(EntityInstance)instance :(bool)enabled{
    nativeManager->setCastShadows(instance, enabled);
}
- (void)setReceiveShadows:(EntityInstance)instance :(bool)enabled{
    nativeManager->setReceiveShadows(instance, enabled);
}
- (void)setScreenSpaceContactShadows:(EntityInstance)instance :(bool)enabled{
    nativeManager->setScreenSpaceContactShadows(instance, enabled);
}
- (bool)isShadowCaster:(EntityInstance)instance{
    return nativeManager->isShadowCaster(instance);
}
- (bool)isShadowReceiver:(EntityInstance)instance{
    return nativeManager->isShadowReceiver(instance);
}
- (size_t)getPrimitiveCount:(EntityInstance)instance{
    return nativeManager->getPrimitiveCount(instance);
}
- (void)setMaterialInstanceAt:(EntityInstance)instance :(int)primitiveIndex :(MaterialInstance *)materialInstance{
    nativeManager->setMaterialInstanceAt(instance, primitiveIndex, (filament::MaterialInstance*) materialInstance.instance);
}
- (MaterialInstance *)getMaterialInstanceAt:(EntityInstance)instance :(int)primitiveIndex{
    return [[MaterialInstance alloc] init: nativeManager->getMaterialInstanceAt(instance, primitiveIndex)];
}
- (void)setGeometryAt:(EntityInstance)instance :(int)primitiveIndex :(PrimitiveType)type :(VertexBuffer *)vertices :(IndexBuffer *)indices :(int)offset :(int)count{
    nativeManager->setGeometryAt(instance, primitiveIndex, (filament::RenderableManager::PrimitiveType) type, (filament::VertexBuffer*)vertices.buffer, (filament::IndexBuffer*)indices.buffer, offset, count);
}
- (void)setBlendOrderAt:(EntityInstance)instance :(int)primitiveIndex :(int)blendOrder{
    nativeManager->setBlendOrderAt(instance, primitiveIndex, blendOrder);
}
- (void)setGlobalBlendOrderEnabledAt:(EntityInstance)instance :(int)primitiveIndex :(int)blendOrder{
    nativeManager->setGlobalBlendOrderEnabledAt(instance, primitiveIndex, blendOrder);
}
@end
