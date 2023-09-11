//
//  RenderTarget.mm

//  Created by Stef Tervelde on 30.06.22.
//
#import "Bindings/Filament/RenderTarget.h"
#import <filament/RenderTarget.h>

@implementation RenderTarget{
    filament::RenderTarget* nativeTarget;
}

- (id) init:(void *)target{
    self->_target = target;
    self->nativeTarget = (filament::RenderTarget*)target;
    return self;
}

- (uint32_t)getLayer:(AttachmentPoint)attachment {
    return nativeTarget->getLayer((filament::RenderTarget::AttachmentPoint) attachment);
}

- (uint8_t)getMipLevel:(AttachmentPoint)attachment {
    return nativeTarget->getMipLevel((filament::RenderTarget::AttachmentPoint) attachment);
}

- (uint8_t)getSupportedColorAttachmentsCount {
    return nativeTarget->getSupportedColorAttachmentsCount();
}

- (nonnull Texture *)getTexture:(AttachmentPoint)attachment {
    auto texture = nativeTarget->getTexture((filament::RenderTarget::AttachmentPoint) attachment);
    return [[Texture alloc] init:texture];
}

- (TextureCubemapFace)getFace:(AttachmentPoint)attachment {
    return (TextureCubemapFace)nativeTarget->getFace((filament::RenderTarget::AttachmentPoint) attachment);
}

@end
