//
//  FilamentInstance.mm

//  Created by Stef Tervelde on 30.06.22.
//
#import "Bindings/GLTFIO/FilamentInstance.h"
#import <gltfio/FilamentInstance.h>
#import "Bindings/GLTFIO/FilamentAsset.h"
#import "Bindings/GLTFIO/Animator.h"

@implementation FilamentInstance{
    filament::gltfio::FilamentInstance* nativeInstance;
}

- (id) init:(void *)instance{
    self->_instance = instance;
    self->nativeInstance = (filament::gltfio::FilamentInstance*)instance;
    return self;
}

- (FilamentAsset *)getAsset{
    return [[FilamentAsset alloc] init: (void*)nativeInstance->getAsset()];
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

- (void)attachSkin:(size_t)skinIndex :(Entity)target {
    nativeInstance->attachSkin(skinIndex, utils::Entity::import(target));
}

- (void)detachMaterialInstances {
    nativeInstance->detachMaterialInstances();
}

- (void)detachSkin:(size_t)skinIndex :(Entity)target {
    nativeInstance->detachSkin(skinIndex, utils::Entity::import(target));
}

- (const simd_float4x4*)getInverseBindMatricesAt:(size_t)skinIndex {
    auto start = nativeInstance->getInverseBindMatricesAt(skinIndex);
    auto count = nativeInstance->getJointCountAt(skinIndex);
    auto joints = new simd_float4x4 [count];
    for(auto i = 0; i<count; i++){
        auto mat = start[i];
        joints[i] = simd_matrix(
            simd_make_float4(mat(0,0), mat(0,1), mat(0,2), mat(0,3)),
            simd_make_float4(mat(1,0), mat(1,1), mat(1,2), mat(1,3)),
            simd_make_float4(mat(2,0), mat(2,1), mat(2,2), mat(2,3)),
            simd_make_float4(mat(3,0), mat(3,1), mat(3,2), mat(3,3))
       );
    }
#warning Return simd_array
    return joints;
}

- (nonnull NSArray<NSNumber *> *)getJointsAt:(size_t)skinIndex {
    auto joints = nativeInstance->getJointsAt(skinIndex);
    auto size = nativeInstance->getJointCountAt(skinIndex);
    return [FilamentAsset getEntitiesArray: joints :size];
}

- (nonnull NSArray<MaterialInstance *> *)getMaterialInstances {
    auto instances = nativeInstance->getMaterialInstances();
    auto count = nativeInstance->getMaterialInstanceCount();
    auto res = [[NSMutableArray alloc] init];
    for (auto i = 0; i<count; i++) {
        [res addObject:[[MaterialInstance alloc] init:instances[i]]];
    }
    return res;
}

- (size_t)getMaterialVariantCount {
    return nativeInstance->getMaterialVariantCount();
}

- (nullable NSString *)getMaterialVariantName:(size_t)variantIndex {
    return [[NSString alloc] initWithUTF8String:nativeInstance->getMaterialVariantName(variantIndex)];
}

- (size_t)getSkinCount {
    return nativeInstance->getSkinCount();
}

- (nonnull NSString *)getSkinNameAt:(size_t)skinIndex {
    return [[NSString alloc] initWithUTF8String:nativeInstance->getSkinNameAt(skinIndex)];
}

- (void)recomputeBoundingBoxes {
    nativeInstance->recomputeBoundingBoxes();
}

@end
