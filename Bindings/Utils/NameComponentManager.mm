//
//  NameComponentManager.mm
//  swift-gltf-viewer
//
//  Created by Stef Tervelde on 10.09.23.
//
#import "Bindings/Utils/NameComponentManager.h"
#import <utils/NameComponentManager.h>
#import <utils/EntityManager.h>

@implementation NameComponentManager{
    utils::NameComponentManager* nativeManager;
}

- (EntityInstance)getInstance:(Entity)e {
    return nativeManager->getInstance(utils::Entity::import(e));
}

- (nonnull NSString *)getName:(EntityInstance)instance {
    auto name = nativeManager->getName(instance);
    return [[NSString alloc] initWithUTF8String:name];
}

- (nonnull id)init:(nonnull EntityManager *)em {
    auto manager = utils::NameComponentManager(*(utils::EntityManager*)em.manager);
    self->_manager = (void*)&manager;
    self->nativeManager = &manager;
}

- (void)removeComponent:(Entity)e {
    nativeManager->removeComponent(utils::Entity::import(e));
}

- (void)setName:(EntityInstance)instance :(nonnull NSString *)name {
    nativeManager->setName(instance, name.UTF8String);
}

- (void)addComponent:(Entity)e {
    nativeManager->addComponent(utils::Entity::import(e));
}

@end
