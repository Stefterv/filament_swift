//
//  ResourceLoader.mm

//  Created by Stef Tervelde on 30.06.22.
//
#import "Bindings/GLTFIO/ResourceLoader.h"
#import <gltfio/ResourceLoader.h>
@implementation ResourceLoaderOptions{
    
}

@end

@implementation ResourceLoader{
    filament::gltfio::ResourceLoader* nativeLoader;
}

- (id)init:(Engine *)engine :(ResourceLoaderOptions *)options{
    auto config = filament::gltfio::ResourceConfiguration();
    config.engine = (filament::Engine*) engine.engine;
    config.ignoreBindTransform = options.ignoreBindTransform;
    config.normalizeSkinningWeights = options.normalizeSkinningWeights;
    config.recomputeBoundingBoxes = options.recomputeBoundingBoxes;
    auto loader = new filament::gltfio::ResourceLoader(config);
    self->_loader = loader;
    self->nativeLoader = loader;
    
    return self;
}


- (instancetype) loadResources:(FilamentAsset *)asset{
    nativeLoader->loadResources((filament::gltfio::FilamentAsset*) asset.asset);
    return self;
}
- (void)addResourceData:(NSString *)uri :(NSData *)buffer{
    nativeLoader->addResourceData([uri UTF8String],filament::gltfio::ResourceLoader::BufferDescriptor(buffer.bytes, buffer.length));
}
- (bool)asyncBeginLoad:(FilamentAsset *)asset{
    return nativeLoader->asyncBeginLoad( (filament::gltfio::FilamentAsset*) asset.asset);
}
- (void)asyncCancelLoad{
    nativeLoader->asyncCancelLoad();
}
- (void)asyncUpdateLoad{
    nativeLoader->asyncUpdateLoad();
}
- (double)asyncGetLoadProgress{
    return nativeLoader->asyncGetLoadProgress();
}
- (void)evictResourceData{
    nativeLoader->evictResourceData();
}
- (bool)hasResourceData:(NSString *)uri{
    return nativeLoader->hasResourceData([uri UTF8String]);
}

@end
