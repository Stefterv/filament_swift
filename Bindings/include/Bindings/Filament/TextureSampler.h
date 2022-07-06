//
//  TextureSampler.h
//  swift-gltf-viewer
//
//  Created by Stef Tervelde on 30.06.22.
//
#import <Foundation/Foundation.h>

#ifndef TextureSampler_h
#define TextureSampler_h

@interface TextureSampler : NSObject

@property (nonatomic, readonly, nonnull) void* sampler  NS_SWIFT_UNAVAILABLE("Don't access the raw pointers");
- (nonnull id) init: (nonnull void*) sampler NS_SWIFT_UNAVAILABLE("Create a new renderer with engine.createRenderer");
- (nonnull id) init NS_UNAVAILABLE;

@end


#endif /* TextureSampler_h */
