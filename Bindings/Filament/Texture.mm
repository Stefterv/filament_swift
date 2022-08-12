//
//  Texture.mm

//  Created by Stef Tervelde on 30.06.22.
//
#import "Bindings/Filament/Texture.h"
#import <filament/Texture.h>
#import "Bindings/Filament/Engine.h"
#import "Bindings/Filament/Stream.h"

@implementation Texture{
    filament::Texture* nativeTexture;
}

- (id) init:(void *)texture{
    self->_texture = texture;
    self->nativeTexture = (filament::Texture*)texture;
    return self;
}

- (unsigned long)getWidth:(int)level{
    return nativeTexture->getWidth();
}
- (unsigned long)getHeight:(int)level{
    return nativeTexture->getHeight();
}
- (unsigned long)getDepth:(int)getDepth{
    return nativeTexture->getWidth();
}
- (unsigned long)getLevels{
    return nativeTexture->getLevels();
}
- (SamplerType) getTarget{
    return (SamplerType) nativeTexture->getTarget();
}
- (InternalFormat)getFormat{
    return (InternalFormat) nativeTexture->getFormat();
}
- (void)setImage:(Engine *)engine :(int)level :(NSData *)buffer{
# warning Add PixelBufferDescriptorpixelbuffer
//    nativeTexture->setImage(*(filament::Engine*) engine.engine, level, filament::Texture::PixelBufferDescriptor(buffer.bytes, buffer.length));
}
- (void)setImage:(Engine *)engine :(int)level :(NSData *)buffer :(simd_double2x3)faceOffset{
}
- (void)setImage:(Engine *)engine :(int)level :(int)xoffset :(int)yoffset :(int)width :(int)height :(NSData *)buffer{
}
- (void)setImage:(Engine *)engine :(int)level :(int)xoffset :(int)yoffset :(int)zoffset :(int)width :(int)height :(int)depth :(NSData *)buffer{
}
- (void)setExternalImage:(Engine *)engine :(CVPixelBufferRef)image{
    nativeTexture->setExternalImage(*(filament::Engine*) engine.engine, image);
}
- (void)setExternalStream:(Engine *)engine :(Stream *)stream{
    nativeTexture->setExternalStream(*(filament::Engine*) engine.engine, (filament::Stream*) stream.stream);
}
- (void)generateMipmaps:(Engine *)engine{
    nativeTexture->generateMipmaps( *(filament::Engine*) engine.engine);
}
- (void)generatePrefilterMipmap:(Engine *)engine :(NSData *)buffer :(simd_double2x3)faceOffset :(PrefilterOptions *)options{
# warning Add PixelBufferDescriptorpixelbuffer
    //nativeTexture->generatePrefilterMipmap(*(filament::Engine*) engine.engine, <#PixelBufferDescriptor &&buffer#>, <#const FaceOffsets &faceOffsets#>)
}
@end
