//
//  MaterialBuilder.h

//  Created by Stef Tervelde on 30.06.22.
//
#import <Foundation/Foundation.h>
#import "Engine.h"
#import "Material.h"

#ifndef MaterialBuilder_h
#define MaterialBuilder_h

@interface MaterialBuilder : NSObject

@property (nonatomic, readonly, nonnull) void* builder  NS_SWIFT_UNAVAILABLE("Don't access the raw pointers");
NS_ASSUME_NONNULL_BEGIN
- (id) init;

- (instancetype) payload: (nonnull NSData*) buffer;
- (Material*) build: (nonnull Engine*) engine;
NS_ASSUME_NONNULL_END
#warning("TODO Comments")
@end


#endif /* MaterialBuilder_h */
