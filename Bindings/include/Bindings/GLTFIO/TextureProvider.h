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

+ (nonnull instancetype) createStbProvider: (nonnull Engine*) engine;
+ (nonnull instancetype) createKtx2Provider: (nonnull Engine*) engine;
#warning("TODO Comments")
@end


#endif /* TextureProvider_h */
