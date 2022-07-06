//
//  Texture.h
//  swift-gltf-viewer
//
//  Created by Stef Tervelde on 30.06.22.
//
#import <Foundation/Foundation.h>

#ifndef Texture_h
#define Texture_h

NS_SWIFT_NAME(Texture.PixelBufferDescriptor)
@interface PixelBufferDescriptor : NSObject
@property (nonatomic, readonly, nonnull) void* buffer  NS_SWIFT_UNAVAILABLE("Don't access the raw pointers");
- (nonnull id) init: (nonnull void*) buffer NS_SWIFT_UNAVAILABLE("Create a new renderer with engine.createRenderer");
- (nonnull id) init NS_UNAVAILABLE;
@end

@interface Texture : NSObject

@property (nonatomic, readonly, nonnull) void* texture  NS_SWIFT_UNAVAILABLE("Don't access the raw pointers");
- (nonnull id) init: (nonnull void*) texture NS_SWIFT_UNAVAILABLE("Create a new renderer with engine.createRenderer");
- (nonnull id) init NS_UNAVAILABLE;

@end


#endif /* Texture_h */
