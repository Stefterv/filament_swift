//
//  MaterialProvider.mm
//  swift-gltf-viewer
//
//  Created by Stef Tervelde on 30.06.22.
//
#import "Bindings/GLTFIO/MaterialProvider.h"
#import <filament/Engine.h>
#import <gltfio/MaterialProvider.h>
#import <gltfio/materials/uberarchive.h>



@implementation MaterialProvider{
    filament::gltfio::MaterialProvider* nativeProvider;
}

- (id)init:(void *)provider{
    self->_provider = provider;
    self->nativeProvider = (filament::gltfio::MaterialProvider*) provider;
    return self;
}

- (MaterialInstance *)createMaterialInstance:(MaterialKey *)config :(NSArray<NSNumber *> *)uvmap :(NSString *)label :(NSString *)extras{
    auto instance = nativeProvider->createMaterialInstance(nil, nil, [label UTF8String], [extras UTF8String]);
    return [[MaterialInstance alloc] init:instance];
}

- (NSArray<Material *> *)getMaterials{
    auto materials = nativeProvider->getMaterials();
    auto count = nativeProvider->getMaterialsCount();
    
    auto results = [[NSMutableArray<Material*> alloc] initWithCapacity:count];
    for(auto i = 0; i<count; i++){
        auto material = materials[i];
        results[i] = [[Material alloc] init:&material];
    }
    return results;
}
- (bool)needsDummyData:(VertexAttribute)attrib{
    return nativeProvider->needsDummyData( (filament::VertexAttribute) attrib);
}


+ (instancetype)createUberShaderProvider:(Engine *)engine{
    auto provider = filament::gltfio::createUbershaderProvider((filament::Engine*) engine.engine, UBERARCHIVE_DEFAULT_DATA, UBERARCHIVE_DEFAULT_SIZE);
    return [[MaterialProvider alloc] init:provider];
}
+ (instancetype)createJitShaderProvider:(Engine *)engine :(bool)optimizeShaders{
//    auto provider = filament::gltfio::createJitShaderProvider((filament::Engine*) engine.engine, optimizeShaders);
//    return [[MaterialProvider alloc] init:provider];
}


@end
