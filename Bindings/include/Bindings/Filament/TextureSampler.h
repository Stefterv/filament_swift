//
//  TextureSampler.h

//  Created by Stef Tervelde on 30.06.22.
//
#import <Foundation/Foundation.h>

#ifndef TextureSampler_h
#define TextureSampler_h

@interface TextureSampler : NSObject

@property (nonatomic, readonly, nonnull) void* sampler  NS_SWIFT_UNAVAILABLE("Don't access the raw pointers");
- (nonnull id) init: (nonnull void*) sampler NS_SWIFT_UNAVAILABLE("Instances are created internally");
- (nonnull id) init;

@end


#endif /* TextureSampler_h */
