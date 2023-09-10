//
//  RenderTarget.h

//  Created by Stef Tervelde on 30.06.22.
//
#import <Foundation/Foundation.h>

#ifndef RenderTarget_h
#define RenderTarget_h

@interface RenderTarget : NSObject

@property (nonatomic, readonly, nonnull) void* target  NS_SWIFT_UNAVAILABLE("Don't access the raw pointers");
- (nonnull id) init: (nonnull void*) target NS_SWIFT_UNAVAILABLE("Instances are created internally");
- (nonnull id) init NS_UNAVAILABLE;
#warning("TODO")
@end


#endif /* RenderTarget_h */
