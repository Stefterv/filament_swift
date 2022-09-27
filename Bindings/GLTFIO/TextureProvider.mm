//
//  TextureProvider.mm
//  Dummy
//
//  Created by Stef Tervelde on 27.09.22.
//
#import "Bindings/GLTFIO/TextureProvider.h"
#import <gltfio/TextureProvider.h>

@implementation TextureProvider{
    filament::gltfio::TextureProvider* nativeProvider;
}

- (id) init:(void *)provider{
    self->_provider = provider;
    self->nativeProvider = (filament::gltfio::TextureProvider*)provider;
    return self;
}

+ (instancetype)createStbProvider:(Engine *)engine{
    auto _engine = (filament::Engine*) engine.engine;
    auto provider = filament::gltfio::createStbProvider(_engine);
    return [[TextureProvider alloc] init:provider];
}
+ (instancetype)createKtx2Provider:(Engine *)engine{
    auto _engine = (filament::Engine*) engine.engine;
    auto provider = filament::gltfio::createKtx2Provider(_engine);
    return [[TextureProvider alloc] init:provider];
}

@end
