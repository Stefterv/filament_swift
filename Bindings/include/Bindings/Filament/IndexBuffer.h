//
//  IndexBuffer.h
//
//  Created by Stef Tervelde on 30.06.22.
//
#import <Foundation/Foundation.h>



#ifndef IndexBuffer_h
#define IndexBuffer_h

@class Engine;

@interface IndexBuffer : NSObject

@property (nonatomic, readonly, nonnull) void* buffer  NS_SWIFT_UNAVAILABLE("Don't access the raw pointers");
- (nonnull id) init: (nonnull void*) buffer NS_SWIFT_UNAVAILABLE("Create a new renderer with engine.createRenderer");
- (nonnull id) init NS_UNAVAILABLE;
- (void) setBuffer: (nonnull Engine*) engine :(nonnull NSData*) buffer :(uint32_t) byteOffset;
- (void) setBuffer: (nonnull Engine*) engine :(nonnull NSData*) buffer;
- (size_t) getIndexCount;
@end


#endif /* IndexBuffer_h */
