//
//  RenderableBuilder.mm

//  Created by Stef Tervelde on 30.06.22.
//
#import "Bindings/Filament/RenderableBuilder.h"
#import <filament/RenderableManager.h>
#import <filament/VertexBuffer.h>
#import <filament/IndexBuffer.h>
#import <utils/Entity.h>
#import "Bindings/Filament/Engine.h"
#import "../Math.h"

@implementation RenderableBuilder{
    filament::RenderableManager::Builder* nativeBuilder;
}

- (id) init:(int)count{
    auto builder = new filament::RenderableManager::Builder(count);
    self->_builder = builder;
    self->nativeBuilder = builder;
    return self;
}

typedef struct
{
    float x;
    float y;
    float z;
    float w;
    float u;
    float v;
} Vertex;

- (instancetype)geometry:(int)index :(PrimitiveType)type :(VertexBuffer *)vertices2 :(IndexBuffer *)indices2 :(NSInteger)offset :(NSInteger)count :(Engine*) engine{
    auto vertexBuffer2 = (filament::VertexBuffer*) vertices2.buffer;
    auto indexBuffer2 = (filament::IndexBuffer*) indices2.buffer;
    nativeBuilder->geometry(index,filament::RenderableManager::PrimitiveType::TRIANGLES, vertexBuffer2, indexBuffer2, offset, count);
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
- (instancetype)boundingBox:(Box)aabb{
    nativeBuilder->boundingBox({
        .center=*(filament::math::float3*)&aabb.center,
        .halfExtent=*(filament::math::float3*)&aabb.halfExtent
    });
    return self;
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
