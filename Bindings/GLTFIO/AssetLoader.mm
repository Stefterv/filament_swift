//
//  AssetLoader.mm

//  Created by Stef Tervelde on 30.06.22.
//
#import "Bindings/GLTFIO/AssetLoader.h"
#import <gltfio/AssetLoader.h>

@implementation AssetConfiguration



@end

@implementation AssetLoader{
    filament::gltfio::AssetLoader* nativeLoader;
}

- (id) init:(void *)loader{
    self->_loader = loader;
    self->nativeLoader = (filament::gltfio::AssetLoader*)loader;
    return self;
}
+ (instancetype)create:(AssetConfiguration *)config1{
    auto config2 = filament::gltfio::AssetConfiguration();
    config2.engine = (filament::Engine*) config1.engine.engine;
    config2.entities = (utils::EntityManager*) config1.entities.manager;
    config2.materials = (filament::gltfio::MaterialProvider*) config1.materials.provider;;
    config2.names = (utils::NameComponentManager*) config1.names.manager;
    auto loader = filament::gltfio::AssetLoader::create(config2);
    return [[AssetLoader alloc] init:loader];
}

- (FilamentAsset *)createAssetFromBinary:(NSData*)bytes{
    auto asset = nativeLoader->createAssetFromBinary((uint8_t*)bytes.bytes, (uint32_t)bytes.length);
    return [[FilamentAsset alloc] init:asset];
}

- (FilamentAsset *)createAssetFromJson:(NSData*)bytes{
    auto asset = nativeLoader->createAssetFromJson((uint8_t*)bytes.bytes, (uint32_t)bytes.length);
    
    return [[FilamentAsset alloc] init:asset];
}

- (FilamentInstance *)createInstance:(FilamentAsset *)primary{
    auto instance = nativeLoader->createInstance((filament::gltfio::FilamentAsset*) primary.asset);
    return [[FilamentInstance alloc] init: instance];
}
- (FilamentAsset *)createInstancedAsset:(NSArray *)bytes :(NSMutableArray<FilamentInstance *> *)instances{
    auto count = [bytes count];
    auto cppbytes = new UInt8[count];
    
    auto i = 0;
    
    for(NSNumber* byte in bytes){
        cppbytes[i++] = [byte unsignedIntValue];
    }
    auto numInstances = [instances count];
    auto cppInstances = new filament::gltfio::FilamentInstance*[numInstances];
    
    auto asset = nativeLoader->createInstancedAsset(cppbytes, (uint32_t)count, cppInstances, numInstances);
    delete[] cppbytes;
    
    for(auto j = 0; j<numInstances; j++){
        auto instance = cppInstances[j];
        [instances addObject:[[FilamentInstance alloc] init:instance]];
    }
    
    return [[FilamentAsset alloc] init:asset];
}

- (void)destroyAsset:(FilamentAsset *)asset{
    nativeLoader->destroyAsset((filament::gltfio::FilamentAsset*) asset.asset);
}

@end
