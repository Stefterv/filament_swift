//
//  TransformManager.mm

//  Created by Stef Tervelde on 30.06.22.
//
#import "Bindings/Filament/TransformManager.h"
#import <filament/TransformManager.h>
#import <utils/Entity.h>
#import <utils/EntityInstance.h>
#import "../Math.h"

@implementation TransformManager{
    filament::TransformManager* nativeManager;
}

- (id) init:(void *)manager{
    self->_manager = manager;
    self->nativeManager = (filament::TransformManager*)manager;
    return self;
}

- (bool)hasComponent:(Entity)entity{
    return nativeManager->hasComponent(utils::Entity::import(entity));
}

- (EntityInstance)getInstance:(Entity)entity{
    return nativeManager->getInstance(utils::Entity::import(entity));
}
- (void)setAccurateTranslationsEnabled:(bool)enable{
    nativeManager->setAccurateTranslationsEnabled(enable);
}
- (bool)isAccurateTranslationsEnabled{
    return nativeManager->isAccurateTranslationsEnabled();
}
- (EntityInstance)create:(Entity)entity{
    nativeManager->create(utils::Entity::import(entity));
    return [self getInstance: entity];
}

- (EntityInstance)create:(Entity)entity :(EntityInstance)parent :(simd_double4x4)localTransform{
    nativeManager->create(utils::Entity::import(entity), parent, MAT4_FROM_SIMD(localTransform));
    return [self getInstance: entity];
}
- (void)destroy:(Entity)entity{
    nativeManager->destroy(utils::Entity::import(entity));
}

- (Entity)getParent:(Entity)entity{
    auto parent = nativeManager->getParent([self getInstance:entity]);
    return utils::Entity::smuggle(parent);
}

- (void)setParent:(EntityInstance)instance :(EntityInstance)parent{
    nativeManager->setParent(instance, parent);
}
- (void)setTransform:(EntityInstance)instance :(simd_double4x4)localTransform{
    nativeManager->setTransform(instance, MAT4_FROM_SIMD(localTransform));
}
- (simd_double4x4)getTransform:(EntityInstance)instance{
    auto transform = nativeManager->getTransform(instance);
    return SIMD_DOUBLE4X4_FROM_MAT4(transform);
}
- (simd_double4x4)getWorldTransform:(EntityInstance)instance{
    auto transform = nativeManager->getWorldTransform(instance);
    return SIMD_DOUBLE4X4_FROM_MAT4(transform);
}
- (void)openLocalTransformTransaction{
    nativeManager->openLocalTransformTransaction();
}
- (void) commitLocalTransformTransaction{
    nativeManager->commitLocalTransformTransaction();
}

@end
