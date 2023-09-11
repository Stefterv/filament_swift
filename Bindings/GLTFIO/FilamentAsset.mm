//
//  FilamentAsset.mm

//  Created by Stef Tervelde on 30.06.22.
//
#import "Bindings/GLTFIO/FilamentAsset.h"
#import "Bindings/GLTFIO/FilamentInstance.h"
#import "Bindings/Filament/Scene.h"
#import "Bindings/Filament/Engine.h"
#import <gltfio/FilamentAsset.h>
#import <utils/Entity.h>
#import <filament/Scene.h>

@implementation FilamentAsset{
    filament::gltfio::FilamentAsset* nativeAsset;
}

- (id) init:(void *)asset{
    self->_asset = asset;
    self->nativeAsset = (filament::gltfio::FilamentAsset*)asset;
    return self;
}
+ (NSArray<NSNumber*>*)getEntitiesArray: (const void*) array :(unsigned long)count{
    auto typedArray = (utils::Entity*) array;
    auto target = [[NSMutableArray alloc] initWithCapacity:count];
    for(auto i = 0; i<count; i++){
        auto ent = typedArray[i];
        auto num = utils::Entity::smuggle(ent);
        target[i] = [[NSNumber alloc] initWithUnsignedInt: num];
    }
    return target;
}
- (NSArray<NSNumber *> *)getEntities{
    auto ents = nativeAsset->getEntities();
    auto count = nativeAsset->getEntityCount();

    return [FilamentAsset getEntitiesArray:ents :count];
}
- (NSArray<NSNumber *> *)getLightEntities{
    auto ents = nativeAsset->getLightEntities();
    auto count = nativeAsset->getLightEntityCount();
    return [FilamentAsset getEntitiesArray:ents :count];
}
- (NSArray<NSNumber *> *)getRenderableEntities{
    auto ents = nativeAsset->getRenderableEntities();
    auto count = nativeAsset->getRenderableEntityCount();
    return [FilamentAsset getEntitiesArray:ents :count];
}
- (NSArray<NSNumber *> *)getCameraEntities{
    auto ents = nativeAsset->getCameraEntities();
    auto count = nativeAsset->getCameraEntityCount();
    return [FilamentAsset getEntitiesArray:ents :count];
}
- (Entity)getRoot{
    return utils::Entity::smuggle(nativeAsset->getRoot());
}
- (Entity)popRenderable{
    return utils::Entity::smuggle(nativeAsset->popRenderable());
}
- (size_t)popRenderables:(NSMutableArray<NSNumber *>*)entities{
    if(entities == nil){
        return nativeAsset->popRenderables(nil, 0);
    }
    utils::Entity ents[entities.count];
    for(auto i = 0; i<entities.count; i++){
        ents[i] = utils::Entity::import(entities[i].unsignedIntValue);
    }
    
    auto count = nativeAsset->popRenderables(ents, entities.count);
    for (auto j = 0; j<count; j++) {
        entities[j] = [NSNumber numberWithUnsignedInt:utils::Entity::smuggle(ents[j])];
    }
    return count;
    
}
- (NSArray<NSString*>*)getResourceUris{
    auto uris = nativeAsset->getResourceUris();
    auto count = nativeAsset->getResourceUriCount();
    auto result = [[NSMutableArray<NSString*> alloc] initWithCapacity:count];
    for(auto i = 0; i<count; i++){
        result[i] = [[NSString alloc] initWithUTF8String:uris[i]];
    }
    return result;
}
- (Aabb *)getBoundingBox{
    auto box = nativeAsset->getBoundingBox();
    auto res = new Aabb();
    res->min = simd_make_float3(box.min.r, box.min.g, box.min.b);
    res->max = simd_make_float3(box.max.r, box.max.g, box.max.b);
    return res;
}
- (NSString *)getName:(Entity)entity{
    auto name = nativeAsset->getName(utils::Entity::import(entity));
    return [[NSString alloc] initWithUTF8String:name];
}
- (Entity)getFirstEntityByName:(NSString *)name{
    auto entity = nativeAsset->getFirstEntityByName([name UTF8String]);
    return utils::Entity::smuggle(entity);
}
- (NSArray<NSNumber *> *)getEntitiesByName:(NSString *)name{
    auto count = nativeAsset->getEntitiesByName([name UTF8String], nil, 0);
    utils::Entity ents[count];
    nativeAsset->getEntitiesByName([name UTF8String], ents, count);
    return [FilamentAsset getEntitiesArray:ents :count];
}
- (NSArray<NSNumber *> *)getEntitiesByPrefix:(NSString *)name{
    auto count = nativeAsset->getEntitiesByPrefix([name UTF8String], nil, 0);
    utils::Entity ents[count];
    nativeAsset->getEntitiesByPrefix([name UTF8String], ents, count);
    return [FilamentAsset getEntitiesArray:ents :count];
}
- (NSString *)getExtras:(Entity)entity{
    auto name = nativeAsset->getExtras(utils::Entity::import(entity));
    if(name == nil){
        return nil;
    }
    return [[NSString alloc] initWithUTF8String:name];
}
- (void)addEntitiesToScene:(nonnull Scene *)targetScene :(nonnull NSArray<NSNumber*>*)entities :(uint32_t)sceneFilter {
    auto scene = (filament::Scene*) targetScene.scene;
    utils::Entity ents[entities.count];
    for (auto i = 0; i<entities.count; i++) {
        ents[i] = utils::Entity::import([entities[i] unsignedIntValue]);
    }
    
    auto filter = filament::gltfio::NodeManager::SceneMask();
    filter.setValue(sceneFilter);
    nativeAsset->addEntitiesToScene(*scene, ents, entities.count, filter);
}

- (bool)areFilamentComponentsDetached {
    return nativeAsset->areFilamentComponentsDetached();
}

- (void)detachFilamentComponents {
    nativeAsset->detachFilamentComponents();
}

- (nonnull Engine *)getEngine {
    auto engine = nativeAsset->getEngine();
    return [[Engine alloc] init: engine];
}

- (nonnull NSArray<NSNumber *> *)getEntitiesByName:(nonnull NSString *)name :(size_t)maxCount {
    utils::Entity ents[maxCount];
    auto size = nativeAsset->getEntitiesByName(name.UTF8String, ents, maxCount);
    auto res = [[NSMutableArray alloc] init];
    for(auto i = 0; i<size; i++){
        auto ent = utils::Entity::smuggle(ents[i]);
        auto number = [[NSNumber alloc] initWithUnsignedInt:ent];
        [res addObject: number];
    }
    return res;
}

- (nonnull NSArray<NSNumber *> *)getEntitiesByPrefix:(nonnull NSString *)prefix :(size_t)maxCount {
    utils::Entity ents[maxCount];
    auto size = nativeAsset->getEntitiesByPrefix(prefix.UTF8String, ents, maxCount);
    auto res = [[NSMutableArray alloc] init];
    for(auto i = 0; i<size; i++){
        auto ent = utils::Entity::smuggle(ents[i]);
        auto number = [[NSNumber alloc] initWithUnsignedInt:ent];
        [res addObject: number];
    }
    return res;
}

- (nonnull FilamentInstance *)getInstance {
    return [[FilamentInstance alloc] init: nativeAsset->getInstance()];
}

- (size_t)getMorphTargetCountAt:(Entity)entity {
    auto ent = utils::Entity::import(entity);
    nativeAsset->getMorphTargetCountAt(ent);
}

- (nonnull NSString *)getMorphTargetNameAt:(Entity)entity :(size_t)targetIndex {
    auto ent = utils::Entity::import(entity);
    auto name = nativeAsset->getMorphTargetNameAt(ent, targetIndex);
    return [[NSString alloc] initWithUTF8String:name];
}

- (size_t)getSceneCount {
    return nativeAsset->getSceneCount();
}

- (nonnull NSString *)getSceneName:(size_t)sceneIndex {
    return [[NSString alloc] initWithUTF8String:nativeAsset->getSceneName(sceneIndex)];
}

- (const void *)getSourceAsset {
    return nativeAsset->getSourceAsset();
}

- (Entity)getWireframe {
    auto ent = utils::Entity::smuggle(nativeAsset->getWireframe());
    return ent;
}

- (void)releaseSourceData {
    nativeAsset->releaseSourceData();
}

@end
