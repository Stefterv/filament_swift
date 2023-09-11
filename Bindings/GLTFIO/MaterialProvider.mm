//
//  MaterialProvider.mm

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

- (MaterialInstance *)createMaterialInstance:(MaterialKey *)config :(void*)uvmap :(NSString *)label :(NSString *)extras{
    auto conf = filament::gltfio::MaterialKey();
    conf.unlit = config.unlit;
    conf.hasVertexColors = config.hasVertexColors;
    conf.hasBaseColorTexture = config.hasBaseColorTexture;
    conf.hasNormalTexture = config.hasNormalTexture;
    conf.hasOcclusionTexture = config.hasOcclusionTexture;
    conf.hasEmissiveTexture = config.hasEmissiveTexture;
    conf.useSpecularGlossiness = config.useSpecularGlossiness;
    conf.alphaMode = (filament::gltfio::AlphaMode) config.alphaMode;                       // 0 = OPAQUE, 1 = MASK, 2 = BLEND
    conf.enableDiagnostics = config.enableDiagnostics;
    conf.hasMetallicRoughnessTexture = config.hasMetallicRoughnessTexture; // piggybacks with specularRoughness
    conf.metallicRoughnessUV = config.metallicRoughnessUV;             // piggybacks with specularRoughness
    conf.baseColorUV = config.baseColorUV;
    conf.hasClearCoatTexture = config.hasClearCoatTexture;
    conf.clearCoatUV = config.clearCoatUV;
    conf.hasClearCoatRoughnessTexture = config.hasClearCoatRoughnessTexture;
    conf.clearCoatRoughnessUV = config.clearCoatRoughnessUV;
    conf.hasClearCoatNormalTexture = config.hasClearCoatNormalTexture;
    conf.clearCoatNormalUV = config.clearCoatNormalUV;
    conf.hasClearCoat = config.hasClearCoat;
    conf.hasTransmission = config.hasTransmission;
    conf.hasTextureTransforms = config.hasTextureTransforms;
    conf.emissiveUV = config.emissiveUV;
    conf.aoUV = config.aoUV;
    conf.normalUV = config.normalUV;
    conf.hasTransmissionTexture = config.hasTransmissionTexture;
    conf.transmissionUV = config.transmissionUV;
    conf.hasSheenColorTexture = config.hasSheenColorTexture;
    conf.sheenColorUV = config.sheenColorUV;
    conf.hasSheenRoughnessTexture = config.hasSheenRoughnessTexture;
    conf.sheenRoughnessUV = config.sheenRoughnessUV;
    conf.hasVolumeThicknessTexture = config.hasVolumeThicknessTexture;
    conf.volumeThicknessUV = config.volumeThicknessUV;
    conf.hasSheen = config.hasSheen;
    conf.hasIOR = config.hasIOR;
#warning  UVmap
    auto instance = nativeProvider->createMaterialInstance(&conf, nil, [label UTF8String], [extras UTF8String]);
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


- (nonnull Material *)getMaterial:(nonnull MaterialKey *)config :(nonnull void *)uvmap :(nonnull NSString *)label {
    auto conf = filament::gltfio::MaterialKey();
    conf.unlit = config.unlit;
    conf.hasVertexColors = config.hasVertexColors;
    conf.hasBaseColorTexture = config.hasBaseColorTexture;
    conf.hasNormalTexture = config.hasNormalTexture;
    conf.hasOcclusionTexture = config.hasOcclusionTexture;
    conf.hasEmissiveTexture = config.hasEmissiveTexture;
    conf.useSpecularGlossiness = config.useSpecularGlossiness;
    conf.alphaMode = (filament::gltfio::AlphaMode) config.alphaMode;                       // 0 = OPAQUE, 1 = MASK, 2 = BLEND
    conf.enableDiagnostics = config.enableDiagnostics;
    conf.hasMetallicRoughnessTexture = config.hasMetallicRoughnessTexture; // piggybacks with specularRoughness
    conf.metallicRoughnessUV = config.metallicRoughnessUV;             // piggybacks with specularRoughness
    conf.baseColorUV = config.baseColorUV;
    conf.hasClearCoatTexture = config.hasClearCoatTexture;
    conf.clearCoatUV = config.clearCoatUV;
    conf.hasClearCoatRoughnessTexture = config.hasClearCoatRoughnessTexture;
    conf.clearCoatRoughnessUV = config.clearCoatRoughnessUV;
    conf.hasClearCoatNormalTexture = config.hasClearCoatNormalTexture;
    conf.clearCoatNormalUV = config.clearCoatNormalUV;
    conf.hasClearCoat = config.hasClearCoat;
    conf.hasTransmission = config.hasTransmission;
    conf.hasTextureTransforms = config.hasTextureTransforms;
    conf.emissiveUV = config.emissiveUV;
    conf.aoUV = config.aoUV;
    conf.normalUV = config.normalUV;
    conf.hasTransmissionTexture = config.hasTransmissionTexture;
    conf.transmissionUV = config.transmissionUV;
    conf.hasSheenColorTexture = config.hasSheenColorTexture;
    conf.sheenColorUV = config.sheenColorUV;
    conf.hasSheenRoughnessTexture = config.hasSheenRoughnessTexture;
    conf.sheenRoughnessUV = config.sheenRoughnessUV;
    conf.hasVolumeThicknessTexture = config.hasVolumeThicknessTexture;
    conf.volumeThicknessUV = config.volumeThicknessUV;
    conf.hasSheen = config.hasSheen;
    conf.hasIOR = config.hasIOR;
    auto material = nativeProvider->getMaterial(&conf, nullptr);
    return [[Material alloc] init:material];
}

- (void)destroyMaterials {
    nativeProvider->destroyMaterials();
}

@end
