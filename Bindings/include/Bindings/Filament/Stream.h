//
//  Stream.h

//  Created by Stef Tervelde on 30.06.22.
//
#import <Foundation/Foundation.h>

#ifndef Stream_h
#define Stream_h

@interface Stream : NSObject

@property (nonatomic, readonly, nonnull) void* stream  NS_SWIFT_UNAVAILABLE("Don't access the raw pointers");
- (nonnull id) init: (nonnull void*) stream NS_SWIFT_UNAVAILABLE("Instances are created internally");
- (nonnull id) init NS_UNAVAILABLE;
#warning("TODO")
@end


#endif /* Stream_h */
