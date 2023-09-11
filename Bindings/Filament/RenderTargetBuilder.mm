//
//  RenderTargetBuilder.mm

//  Created by Stef Tervelde on 05.07.22.
//
#import "Bindings/Filament/RenderTargetBuilder.h"
#import <filament/RenderTarget.h>

@implementation RenderTargetBuilder{
    filament::RenderTarget::Builder* nativeBuilder;
}

- (id) init:(void *)builder{
    self->_builder = builder;
    self->nativeBuilder = (filament::RenderTarget::Builder*)builder;
    return self;
}

- (nonnull instancetype)face:(AttachmentPoint)attachment :(TextureCubemapFace)face {
    nativeBuilder->face((filament::RenderTarget::AttachmentPoint) attachment, (filament::RenderTarget::CubemapFace) face);
}

- (nonnull instancetype)layer:(AttachmentPoint)attachment :(uint32_t)layer {
    nativeBuilder->layer((filament::RenderTarget::AttachmentPoint) attachment, layer);
}

- (nonnull instancetype)mipLevel:(AttachmentPoint)attachment :(uint8_t)level {
    nativeBuilder->mipLevel((filament::RenderTarget::AttachmentPoint) attachment, level);
}

- (nonnull instancetype)texture:(AttachmentPoint)attachment :(nonnull Texture *)texture {
    nativeBuilder->texture((filament::RenderTarget::AttachmentPoint) attachment, (filament::Texture*) texture.texture);
}

- (nonnull RenderTarget *)build:(nonnull Engine *)engine {
    return [[RenderTarget alloc] init:nativeBuilder->build(*(filament::Engine*) engine.engine)];
}

@end
