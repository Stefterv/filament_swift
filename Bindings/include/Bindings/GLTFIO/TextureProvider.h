//
//  TextureProvider.h
//  Dummy
//
//  Created by Stef Tervelde on 27.09.22.
//
#import <Foundation/Foundation.h>
#import "../Filament/Engine.h"

#ifndef TextureProvider_h
#define TextureProvider_h

@interface TextureProvider : NSObject

@property (nonatomic, readonly, nonnull) void* provider  NS_SWIFT_UNAVAILABLE("Don't access the raw pointers");
- (nonnull id) init: (nonnull void*) provider NS_SWIFT_UNAVAILABLE("Instances are created internally");
- (nonnull id) init NS_UNAVAILABLE;

/**
 * Creates a simple decoder based on stb_image that can handle "image/png" and "image/jpeg".
 * This works only if your build configuration includes STB.
 */
+ (nonnull instancetype) createStbProvider: (nonnull Engine*) engine;
/**
 * Creates a decoder that can handle certain types of "image/ktx2" content as specified in
 * the KHR_texture_basisu specification.
 */
+ (nonnull instancetype) createKtx2Provider: (nonnull Engine*) engine;
@end


#endif /* TextureProvider_h */
