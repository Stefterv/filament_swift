//
//  ResourceLoader.mm

//  Created by Stef Tervelde on 30.06.22.
//
#import "Bindings/GLTFIO/ResourceLoader.h"
#import <gltfio/ResourceLoader.h>
@implementation ResourceConfiguration

@end

@implementation ResourceLoader{
    filament::gltfio::ResourceLoader* nativeLoader;
}

- (nonnull id) init: (ResourceConfiguration*) config{
    auto _config = filament::gltfio::ResourceConfiguration();
    _config.engine = (filament::Engine*) config.engine.engine;
    _config.normalizeSkinningWeights = config.normalizeSkinningWeights;
    auto loader = new filament::gltfio::ResourceLoader(_config);
    self->_loader = loader;
    self->nativeLoader = loader;
    
    return self;
}
- (void)addResourceData:(NSString *)uri :(NSData *)buffer{
    nativeLoader->addResourceData([uri UTF8String],filament::gltfio::ResourceLoader::BufferDescriptor(buffer.bytes, buffer.length));
}
- (void)addTextureProvider:(NSString *)mimeType :(TextureProvider *)provider{
    nativeLoader->addTextureProvider([mimeType UTF8String], (filament::gltfio::TextureProvider*) provider.provider);
}
- (bool)hasResourceData:(NSString *)uri{
    return nativeLoader->hasResourceData([uri UTF8String]);
}
- (void)evictResourceData{
    nativeLoader->evictResourceData();
}
- (instancetype) loadResources:(FilamentAsset *)asset{
    nativeLoader->loadResources((filament::gltfio::FilamentAsset*) asset.asset);
    return self;
}
- (bool)asyncBeginLoad:(FilamentAsset *)asset{
    return nativeLoader->asyncBeginLoad( (filament::gltfio::FilamentAsset*) asset.asset);
}
- (double)asyncGetLoadProgress{
    return nativeLoader->asyncGetLoadProgress();
}
- (void)asyncCancelLoad{
    nativeLoader->asyncCancelLoad();
}
- (void)asyncUpdateLoad{
    nativeLoader->asyncUpdateLoad();
}




@end
