//
//  NodeManager.mm
//  swift-gltf-viewer
//
//  Created by Stef Tervelde on 10.09.23.
//
#import "Bindings/GLTFIO/NodeManager.h"
#import <gltfio/NodeManager.h>
#import <utils/Entity.h>

@implementation NodeManager{
    filament::gltfio::NodeManager* nativeManager;
}

- (id) init:(void *)Manager{
    self->_Manager = Manager;
    self->nativeManager = (filament::gltfio::NodeManager*)Manager;
    return self;
}

- (void)destroy:(Entity)e {
    nativeManager->destroy(utils::Entity::import(e));
}

- (nonnull NSString *)getExtras:(EntityInstance)ci {
    auto extras = nativeManager->getExtras(ci);
    return [[NSString alloc] initWithUTF8String:extras.c_str()];
}

- (EntityInstance)getInstance:(Entity)e {
    return nativeManager->getInstance(utils::Entity::import(e));
}

- (nonnull NSArray<NSString *> *)getMorphTargetNames:(EntityInstance)ci {
    auto names = nativeManager->getMorphTargetNames(ci);
    auto res = [[NSMutableArray alloc] init];
    for(auto i = 0; i<names.size(); i++){
        auto name = names[i];
        [res addObject:[[NSString alloc] initWithUTF8String:name.data()]];
    }
    return res;
}

- (bool)hasComponent:(Entity)e {
    return nativeManager->hasComponent(utils::Entity::import(e));
}

- (void)setExtras:(EntityInstance)ci :(nonnull NSString *)extras {
    nativeManager->setExtras(ci, utils::CString(extras.UTF8String));
}

- (void)setMorphTargetNames:(EntityInstance)ci :(nonnull NSArray<NSString *> *)names {
    auto _names = utils::FixedCapacityVector<utils::CString>((u_int)names.count);
    for(auto i = 0; i<names.count; i++){
        auto name = utils::CString(names[i].UTF8String);
        _names[i] = name;
    }
    nativeManager->setMorphTargetNames(ci,  _names);
}

- (void)create:(Entity)entity {
    nativeManager->create(utils::Entity::import(entity));
}

- (void)setSceneMembership:(EntityInstance)ci :(u_int32_t)scenes {
    auto mask = filament::gltfio::NodeManager::SceneMask();
    mask.setValue(scenes);
    nativeManager->setSceneMembership(ci, mask);
}

- (u_int32_t)getSceneMembership:(EntityInstance)ci {
    return nativeManager->getSceneMembership(ci).getValue();
}

@end
