//
//  RenderTarget.h
//  swift-gltf-viewer
//
//  Created by Stef Tervelde on 30.06.22.
//
#import <Foundation/Foundation.h>

#ifndef RenderTarget_h
#define RenderTarget_h

@interface RenderTarget : NSObject

@property (nonatomic, readonly, nonnull) void* target  NS_SWIFT_UNAVAILABLE("Don't access the raw pointers");
- (nonnull id) init: (nonnull void*) target NS_SWIFT_UNAVAILABLE("Create a new renderer with engine.createRenderer");
- (nonnull id) init NS_UNAVAILABLE;

@end


#endif /* RenderTarget_h */
