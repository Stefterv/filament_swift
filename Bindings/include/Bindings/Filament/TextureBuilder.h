//
//  TextureBuilder.h
//  swift-gltf-viewer
//
//  Created by Stef Tervelde on 05.07.22.
//
#import <Foundation/Foundation.h>

#ifndef TextureBuilder_h
#define TextureBuilder_h

NS_SWIFT_NAME(Texture.Builder);
@interface TextureBuilder : NSObject

@property (nonatomic, readonly, nonnull) void* builder  NS_SWIFT_UNAVAILABLE("Don't access the raw pointers");
- (nonnull id) init: (nonnull void*) builder NS_SWIFT_UNAVAILABLE("Create a new renderer with engine.createRenderer");
- (nonnull id) init NS_UNAVAILABLE;

@end


#endif /* TextureBuilder_h */
