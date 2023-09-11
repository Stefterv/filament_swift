//
//  RenderableManager.mm

//  Created by Stef Tervelde on 30.06.22.
//
#import "Bindings/Filament/RenderableManager.h"
#import <filament/RenderableManager.h>
#import <filament/Box.h>
#import <utils/Entity.h>
#import "../Math.h"

@implementation RenderableManager{
    filament::RenderableManager* nativeManager;
}

- (id) init:(void *)manager{
    self->_manager = manager;
    self->nativeManager = (filament::RenderableManager*)manager;
    return self;
}

- (void)setAxisAlignedBoundingBox:(EntityInstance)instance :(Box)aabb{
    nativeManager->setAxisAlignedBoundingBox(instance, {
        .center=*(filament::math::float3*)&aabb.center,
        .halfExtent=*(filament::math::float3*)&aabb.halfExtent
    });
}
- (Box)getAxisAlignedBoundingBox:(EntityInstance)instance{
    auto box = nativeManager->getAxisAlignedBoundingBox(instance);
    return {
        .center=*(simd_float3*)&box.center,
        .halfExtent=*(simd_float3*)&box.halfExtent
    };
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
- (u_int32_t)getEnabledAttributesAt:(EntityInstance)instance :(size_t)primitiveIndex {
    return nativeManager->getEnabledAttributesAt(instance, primitiveIndex).getValue();
}

- (bool)getFogEnabled:(EntityInstance)instance {
    return nativeManager->getFogEnabled(instance);
}

- (EntityInstance)getInstance:(Entity)e {
    return nativeManager->getInstance(utils::Entity::import(e));
}

- (uint8_t)getLayerMask:(EntityInstance)instance {
    return nativeManager->getLayerMask(instance);
}

- (nullable MorphTargetBuffer *)getMorphTargetBufferAt:(EntityInstance)instance :(uint8_t)level :(size_t)primitiveIndex {
    auto buffer = nativeManager->getMorphTargetBufferAt(instance, level, primitiveIndex);
    return [[MorphTargetBuffer alloc] init:buffer];
}

- (size_t)getMorphTargetCount:(EntityInstance)instance {
    return nativeManager->getMorphTargetCount(instance);
}

- (bool)hasComponent:(Entity)e {
    return nativeManager->hasComponent(utils::Entity::import(e));
}

- (void)setBones:(EntityInstance)instance :(nonnull const simd_float4 *)transforms :(size_t)boneCount :(size_t)offset {
#warning  Get float4 array from swift
}

- (void)setChannel:(EntityInstance)instance :(uint8_t)channel {
    nativeManager->setChannel(instance, channel);
}

- (void)setFogEnabled:(EntityInstance)instance :(bool)enable {
    nativeManager->setFogEnabled(instance, enable);
}

- (void)setMorphTargetBufferAt:(EntityInstance)instance :(uint8_t)level :(size_t)primitiveIndex :(nonnull MorphTargetBuffer *)morphTargetBuffer :(size_t)offset :(size_t)count {
    nativeManager->setMorphTargetBufferAt(instance, level, primitiveIndex, (filament::MorphTargetBuffer*)morphTargetBuffer.buffer, offset, count);
}

- (void)setMorphTargetBufferAt:(EntityInstance)instance :(uint8_t)level :(size_t)primitiveIndex :(nonnull MorphTargetBuffer *)morphTargetBuffer {
    nativeManager->setMorphTargetBufferAt(instance, level, primitiveIndex, (filament::MorphTargetBuffer*)morphTargetBuffer.buffer);
}

- (void)setMorphWeights:(EntityInstance)instance :(nonnull const float *)weights :(size_t)count :(size_t)offset {
#warning  Get float array from swift
}

- (void)setSkinningBuffer:(EntityInstance)instance :(nonnull SkinningBuffer *)skinningBuffer :(size_t)count :(size_t)offset {
    nativeManager->setSkinningBuffer(instance, (filament::SkinningBuffer*)skinningBuffer.buffer, count, offset);
}

- (void)destroy:(Entity)e {
    nativeManager->destroy(utils::Entity::import(e));
}

@end
