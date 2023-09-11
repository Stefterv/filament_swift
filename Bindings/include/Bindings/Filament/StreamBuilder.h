//
//  StreamBuilder.h

//  Created by Stef Tervelde on 30.06.22.
//
#import <Foundation/Foundation.h>
#import "Stream.h"

#ifndef StreamBuilder_h
#define StreamBuilder_h

@class Engine;

@interface StreamBuilder : NSObject

@property (nonatomic, readonly, nonnull) void* builder  NS_SWIFT_UNAVAILABLE("Don't access the raw pointers");
- (nonnull id) init: (nonnull void*) builder NS_SWIFT_UNAVAILABLE("Instances are created internally");
- (nonnull id) init NS_UNAVAILABLE;
NS_ASSUME_NONNULL_BEGIN
/**
 * Creates a NATIVE stream. Native streams can sample data directly from an
 * opaque platform object such as a SurfaceTexture on Android.
 *
 * @param stream An opaque native stream handle. e.g.: on Android this is an
 *                     `android/graphics/SurfaceTexture` JNI jobject. The wrap mode must
 *                     be CLAMP_TO_EDGE.
 *
 * @return This Builder, for chaining calls.
 */
- (instancetype) stream: (void*) stream;

/**
 *
 * @param width initial width of the incoming stream. Whether this value is used is
 *              stream dependent. On Android, it must be set when using
 *              Builder::stream(long externalTextureId).
 *
 * @return This Builder, for chaining calls.
 */
- (instancetype) width: (uint32_t) width;

/**
 *
 * @param height initial height of the incoming stream. Whether this value is used is
 *              stream dependent. On Android, it must be set when using
 *              Builder::stream(long externalTextureId).
 *
 * @return This Builder, for chaining calls.
 */
- (instancetype) height: (uint32_t) height;

/**
 * Creates the Stream object and returns a pointer to it.
 *
 * @param engine Reference to the filament::Engine to associate this Stream with.
 *
 * @return pointer to the newly created object, or nullptr if the stream couldn't be created.
 */
-(Stream*) build: (Engine*) engine;
NS_ASSUME_NONNULL_END
@end


#endif /* StreamBuilder_h */
