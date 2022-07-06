//
//  FilamentInstance.mm
//  swift-gltf-viewer
//
//  Created by Stef Tervelde on 30.06.22.
//
#import "Bindings/GLTFIO/FilamentInstance.h"
#import <gltfio/FilamentInstance.h>

@implementation FilamentInstance{
    filament::gltfio::FilamentInstance* nativeInstance;
}

- (id) init:(void *)instance{
    self->_instance = instance;
    self->nativeInstance = (filament::gltfio::FilamentInstance*)instance;
    return self;
}

- (FilamentAsset *)getAsset{
    return [[FilamentAsset alloc] init:nativeInstance->getAsset()];
}
- (Entity)getRoot{
    auto entity = nativeInstance->getRoot();
    return utils::Entity::smuggle(entity);
}
- (NSArray<NSNumber *> *)getEntities{
    auto ents = nativeInstance->getEntities();
    auto count = nativeInstance->getEntityCount();
    
    return [FilamentAsset getEntitiesArray:ents :count];
    
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
- (Animator *)getAnimator{
    return [[Animator alloc] init:nativeInstance->getAnimator()];
}
- (void)applyMaterialVariant:(size_t)index{
    nativeInstance->applyMaterialVariant(index);
}

@end
