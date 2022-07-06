//
//  Scene.mm
//  
//
//  Created by Stef Tervelde on 29.06.22.
//


#import "Bindings/Filament/Scene.h"
#import <filament/Scene.h>
#import <utils/Entity.h>

@implementation Scene{
    filament::Scene* nativeScene;
}

- (id) init:(void *)scene{
    self->_scene = scene;
    self->nativeScene = (filament::Scene*)scene;
    return self;
}

- (Skybox *)getSkybox{
    auto skybox = nativeScene->getSkybox();
    return [[Skybox alloc] init: skybox];
}
- (void)setSkybox:(Skybox *)skybox{
    nativeScene->setSkybox((filament::Skybox*) skybox.skybox);
}

- (void)setIndirectLight:(IndirectLight *)light{
    nativeScene->setIndirectLight((filament::IndirectLight*)light.light);
}
- (void)addEntity:(Entity)entity{
    nativeScene->addEntity(utils::Entity::import(entity));
}
- (bool)hasEntity:(Entity)entity{
    return nativeScene->hasEntity(utils::Entity::import(entity));
}
- (void)removeEntity:(Entity)entity{
    nativeScene->remove(utils::Entity::import(entity));
}
- (size_t)getRenderableCount{
    return nativeScene->getRenderableCount();
}
- (size_t)getLightCount{
    return nativeScene->getLightCount();
}


@end
