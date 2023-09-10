//
//  EntityManager.mm
//  
//
//  Created by Stef Tervelde on 29.06.22.
//

#import "Bindings/Filament/EntityManager.h"
#import <utils/EntityManager.h>

@implementation EntityManager{
    utils::EntityManager* nativeManager;
}

- (id) init:(void *)manager{
    self->_manager = manager;
    self->nativeManager = (utils::EntityManager*) manager;
    return self;
}

- (Entity) create{
    return utils::Entity::smuggle(nativeManager->create());
}


- (void)destroy:(Entity)entity{
    auto entities = new utils::Entity[1];
    entities[0] =  utils::Entity::import(entity);
    nativeManager->destroy(1, entities);
    delete[] entities;
}
- (bool)isAlive:(Entity)entity{
    return nativeManager->isAlive(utils::Entity::import(entity));
}

+ (instancetype)get{
    return [[EntityManager alloc] init: &utils::EntityManager::get()];
}

@end
