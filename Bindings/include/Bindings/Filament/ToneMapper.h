//
//  ToneMapper.h
//  swift-gltf-viewer
//
//  Created by Stef Tervelde on 30.06.22.
//
#import <Foundation/Foundation.h>

#ifndef ToneMapper_h
#define ToneMapper_h

@interface ToneMapper : NSObject

@property (nonatomic, readonly, nonnull) void* mapper  NS_SWIFT_UNAVAILABLE("Don't access the raw pointers");
- (nonnull id) init: (nonnull void*) mapper NS_SWIFT_UNAVAILABLE("Create a new renderer with engine.createRenderer");
- (nonnull id) init NS_UNAVAILABLE;

@end


#endif /* ToneMapper_h */
