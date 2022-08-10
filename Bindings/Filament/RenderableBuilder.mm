//
//  RenderableBuilder.mm
//  swift-gltf-viewer
//
//  Created by Stef Tervelde on 30.06.22.
//
#import "Bindings/Filament/RenderableBuilder.h"
#import <filament/RenderableManager.h>
#import <utils/Entity.h>

@implementation RenderableBuilder{
    filament::RenderableManager::Builder* nativeBuilder;
}

- (id) init:(int)count{
    auto builder = new filament::RenderableManager::Builder(count);
    self->_builder = builder;
    self->nativeBuilder = builder;
    return self;
}

- (instancetype)geometry:(int)index :(PrimitiveType)type :(VertexBuffer *)vertices :(IndexBuffer *)indices :(int)offset :(int)count{
#warning Rebuild sending geometry to filament
    nativeBuilder->geometry(index,(filament::RenderableManager::PrimitiveType) type, (filament::VertexBuffer*)vertices.buffer, (filament::IndexBuffer*)indices.buffer, offset, count);
    return self;
}
- (instancetype)material:(int)index :(MaterialInstance *)material{
    nativeBuilder->material(index,(filament::MaterialInstance*) material.instance);
    return self;
}
- (instancetype)blendOrder:(int)index :(uint16_t)blendOrder{
    nativeBuilder->blendOrder(index, blendOrder);
    return self;
}
- (instancetype)globalBlendOrderEnabled:(int)index :(bool)enabled{
    nativeBuilder->globalBlendOrderEnabled(index, enabled);
    return self;
}
- (instancetype)boundingBox:(Box *)aabb{
#warning After Box
//    nativeBuilder->boundingBox(<#const Box &axisAlignedBoundingBox#>)
}
- (instancetype)layerMask:(uint8_t)select :(uint8_t)value{
    nativeBuilder->layerMask(select, value);
    return self;
}
- (instancetype)priority:(int)priority{
    nativeBuilder->priority(priority);
    return self;
}

- (instancetype)culling:(bool)enabled{
    nativeBuilder->culling(enabled);
    return self;
}
- (instancetype)lightChannel:(int)channel :(bool)enable{
    nativeBuilder->lightChannel(channel, enable);
    return self;
}

- (instancetype)instances:(uint16_t)instanceCount{
    nativeBuilder->instances(instanceCount);
    return self;
}
- (instancetype)castShadows:(bool)enabled{
    nativeBuilder->castShadows(enabled);
    return self;
}
- (instancetype)receiveShadows:(bool)enabled{
    nativeBuilder->receiveShadows(enabled);
    return self;
}
- (instancetype)screenSpaceContactShadows:(bool)enabled{
    nativeBuilder->screenSpaceContactShadows(enabled);
    return self;
}
- (instancetype)enableSkinningBuffers:(bool)enabled{
    nativeBuilder->enableSkinningBuffers(enabled);
    return self;
}
- (instancetype)build:(Engine *)engine :(Entity)entity{
    nativeBuilder->build( *(filament::Engine*)engine.engine , utils::Entity::import(entity));
    return self;
}

@end
