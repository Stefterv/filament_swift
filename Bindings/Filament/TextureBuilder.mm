//
//  TextureBuilder.mm

//  Created by Stef Tervelde on 05.07.22.
//
#import "Bindings/Filament/TextureBuilder.h"
#import <filament/Texture.h>

@implementation TextureBuilder{
    filament::Texture::Builder* nativeBuilder;
}

- (id) init:(void *)builder{
    self->_builder = builder;
    self->nativeBuilder = (filament::Texture::Builder*)builder;
    return self;
}
- (id) init{
    return [self init: new filament::Texture::Builder()];
}
- (instancetype)width:(int)width{
    nativeBuilder->width(width);
    return self;
}
- (instancetype)height:(int)height{
    nativeBuilder->height(height);
    return self;
}
- (instancetype)depth:(int)depth{
    nativeBuilder->depth(depth);
    return self;
}
- (instancetype)levels:(int)levels{
    nativeBuilder->levels(levels);
    return self;
}
- (instancetype)sampler:(SamplerType)target{
    nativeBuilder->sampler( (filament::Texture::Sampler) target);
    return self;
}
- (instancetype)format:(InternalFormat)format{
    nativeBuilder->format( (filament::Texture::InternalFormat) format);
    return self;
}
- (instancetype)usage:(TextureUsage)usage{
    nativeBuilder->usage( (filament::Texture::Usage) usage);
    return self;
}
- (instancetype)swizzle:(Swizzle)r :(Swizzle)g :(Swizzle)b :(Swizzle)a{
    nativeBuilder->swizzle(
                           (filament::Texture::Swizzle) r,
                           (filament::Texture::Swizzle) g,
                           (filament::Texture::Swizzle) b,
                           (filament::Texture::Swizzle) a
                           );
    return self;
}
- (Texture *)build:(Engine *)engine{
    auto texture = nativeBuilder->build( *(filament::Engine*)engine.engine);
    return [[Texture alloc] init:texture];
}
- (instancetype)import:(CFTypeRef)texture{
    nativeBuilder->import((intptr_t) texture);
    return self;
}


@end
