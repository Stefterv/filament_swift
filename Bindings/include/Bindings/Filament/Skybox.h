//
//  Skybox.h

//  Created by Stef Tervelde on 30.06.22.
//
#import <Foundation/Foundation.h>

#ifndef Skybox_h
#define Skybox_h

@interface Skybox : NSObject

@property (nonatomic, readonly, nonnull) void* skybox  NS_SWIFT_UNAVAILABLE("Don't access the raw pointers");
- (nonnull id) init: (nonnull void*) skybox NS_SWIFT_UNAVAILABLE("Create a new renderer with engine.createRenderer");
- (nonnull id) init NS_UNAVAILABLE;

@end


#endif /* Skybox_h */
