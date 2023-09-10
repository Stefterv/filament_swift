//
//  TextureBuilder.h

//  Created by Stef Tervelde on 05.07.22.
//
#import <Foundation/Foundation.h>

#import "Texture.h"
#import "Engine.h"

#ifndef TextureBuilder_h
#define TextureBuilder_h



NS_SWIFT_NAME(Texture.Builder)
@interface TextureBuilder : NSObject

@property (nonatomic, readonly, nonnull) void* builder  NS_SWIFT_UNAVAILABLE("Don't access the raw pointers");
- (nonnull id) init: (nonnull void*) builder NS_SWIFT_UNAVAILABLE("Instances are created internally");
- (nonnull id) init;

NS_ASSUME_NONNULL_BEGIN
- (instancetype) width: (int) width;
- (instancetype) height: (int) height;
- (instancetype) depth: (int) depth;
/**
 * Specifies the number of mipmap levels
 * @param levels must be at least 1 and less or equal to <code>floor(log<sub>2</sub>(max(width, height))) + 1</code>. Default is 1.
 * @return This Builder, for chaining calls.
 */
- (instancetype) levels: (int) levels;
- (instancetype) sampler: (SamplerType) target;
/**
 * Specifies the texture's internal format.
 * <p>The internal format specifies how texels are stored (which may be different from how
 * they're specified in {@link #setImage}). {@link InternalFormat InternalFormat} specifies
 * both the color components and the data type used.</p>
 * @param format texture's {@link InternalFormat internal format}.
 * @return This Builder, for chaining calls.
 */
- (instancetype) format: (InternalFormat) format;
- (instancetype) usage: (TextureUsage) flags;
/**
 * Specifies how a texture's channels map to color components
 *
 * @param r  texture channel for red component
 * @param g  texture channel for green component
 * @param b  texture channel for blue component
 * @param a  texture channel for alpha component
 * @return This Builder, for chaining calls.
 */
- (instancetype) swizzle: (Swizzle) r  :(Swizzle) g :(Swizzle) b :(Swizzle) a;
- (Texture*) build: (Engine*) engine;
/* no user serviceable parts below */

/**
 * Specify a native texture to import as a Filament texture.
 *
 * The texture id is backend-specific:
 *   - OpenGL: GLuint texture ID
 *   - Metal: id<MTLTexture>
 *
 * With Metal, the id<MTLTexture> object should be cast to an intptr_t using
 * CFBridgingRetain to transfer ownership to Filament. Filament will release ownership of
 * the texture object when the Filament texture is destroyed.
 *
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
 *  id <MTLTexture> metalTexture = ...
 *  filamentTexture->import((intptr_t) CFBridgingRetain(metalTexture));
 *  // free to release metalTexture
 *
 *  // after using texture:
 *  engine->destroy(filamentTexture);   // metalTexture is released
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *
 * @warning This method should be used as a last resort. This API is subject to change or
 * removal.
 *
 * @param id a backend specific texture identifier
 *
 * @return This Builder, for chaining calls.
 */
- (instancetype) import: (CFTypeRef) texture;

NS_ASSUME_NONNULL_END
@end


#endif /* TextureBuilder_h */
