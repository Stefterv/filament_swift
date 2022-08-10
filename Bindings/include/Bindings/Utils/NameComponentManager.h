//
//  NameComponentManager.h

//  Created by Stef Tervelde on 01.07.22.
//
#import <Foundation/Foundation.h>

#ifndef NameComponentManager_h
#define NameComponentManager_h

@interface NameComponentManager : NSObject

@property (nonatomic, readonly, nonnull) void* manager  NS_SWIFT_UNAVAILABLE("Don't access the raw pointers");
- (nonnull id) init: (nonnull void*) manager NS_SWIFT_UNAVAILABLE("Create a new renderer with engine.createRenderer");
- (nonnull id) init NS_UNAVAILABLE;

@end


#endif /* NameComponentManager_h */
