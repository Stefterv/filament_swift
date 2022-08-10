//
//  SkinningBufferBuilder.h

//  Created by Stef Tervelde on 30.06.22.
//
#import <Foundation/Foundation.h>

#ifndef SkinningBufferBuilder_h
#define SkinningBufferBuilder_h

@interface SkinningBufferBuilder : NSObject

@property (nonatomic, readonly, nonnull) void* builder  NS_SWIFT_UNAVAILABLE("Don't access the raw pointers");
- (nonnull id) init: (nonnull void*) builder NS_SWIFT_UNAVAILABLE("Create a new renderer with engine.createRenderer");
- (nonnull id) init NS_UNAVAILABLE;

@end


#endif /* SkinningBufferBuilder_h */
