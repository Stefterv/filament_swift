//
//  IndexBufferBuilder.h
//
//  Created by Stef Tervelde on 10.08.22.
//
#import <Foundation/Foundation.h>
#import "IndexBuffer.h"
#import "Engine.h"

#ifndef IndexBufferBuilder_h
#define IndexBufferBuilder_h

typedef NS_ENUM(NSInteger, IndexType) {
    _USHORT,
    _UINT
};


NS_SWIFT_NAME(IndexBuffer.Builder)
@interface IndexBufferBuilder : NSObject

@property (nonatomic, readonly, nonnull) void* buffer  NS_SWIFT_UNAVAILABLE("Don't access the raw pointers");
- (nonnull id) init: (nonnull void*) buffer NS_SWIFT_UNAVAILABLE("Create a new renderer with engine.createRenderer");
- (nonnull id) init;

NS_ASSUME_NONNULL_BEGIN
- (instancetype) indexCount: (uint32_t) indexCount;
- (instancetype) bufferType: (IndexType) type;
- (IndexBuffer*) build: (Engine*) engine;
NS_ASSUME_NONNULL_END
@end


#endif /* IndexBufferBuilder_h */
