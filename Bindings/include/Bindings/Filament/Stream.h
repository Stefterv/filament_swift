//
//  Stream.h

//  Created by Stef Tervelde on 30.06.22.
//
#import <Foundation/Foundation.h>

#ifndef Stream_h
#define Stream_h

/**
 * Stream is used to attach a video stream to a Filament `Texture`.
 *
 * Note that the `Stream` class is fairly Android centric. It supports two different
 * configurations:
 *
 *   - ACQUIRED.....connects to an Android AHardwareBuffer
 *   - NATIVE.......connects to an Android SurfaceTexture
 *
 * Before explaining these different configurations, let's review the high-level structure of an AR
 * or video application that uses Filament:
 *
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * while (true) {
 *
 *     // Misc application work occurs here, such as:
 *     // - Writing the image data for a video frame into a Stream
 *     // - Moving the Filament Camera
 *
 *     if (renderer->beginFrame(swapChain)) {
 *         renderer->render(view);
 *         renderer->endFrame();
 *     }
 * }
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *
 * Let's say that the video image data at the time of a particular invocation of `beginFrame`
 * becomes visible to users at time A. The 3D scene state (including the camera) at the time of
 * that same invocation becomes apparent to users at time B.
 *
 * - If time A matches time B, we say that the stream is \em{synchronized}.
 * - Filament invokes low-level graphics commands on the \em{driver thread}.
 * - The thread that calls `beginFrame` is called the \em{main thread}.
 *
 * For ACQUIRED streams, there is no need to perform the copy because Filament explictly acquires
 * the stream, then releases it later via a callback function. This configuration is especially
 * useful when the Vulkan backend is enabled.
 *
 * For NATIVE streams, Filament does not make any synchronization guarantee. However they are simple
 * to use and do not incur a copy. These are often appropriate in video applications.
 *
 * Please see `sample-stream-test` and `sample-hello-camera` for usage examples.
 *
 * @see backend::StreamType
 * @see Texture#setExternalStream
 * @see Engine#destroyStream
 */
//! Stream for external textures
typedef NS_ENUM(NSInteger, StreamType){
    NATIVE,     //!< Not synchronized but copy-free. Good for video.
    ACQUIRED,   //!< Synchronized, copy-free, and take a release callback. Good for AR but requires API 26+.
};

@interface Stream : NSObject

@property (nonatomic, readonly, nonnull) void* stream  NS_SWIFT_UNAVAILABLE("Don't access the raw pointers");
- (nonnull id) init: (nonnull void*) stream NS_SWIFT_UNAVAILABLE("Instances are created internally");
- (nonnull id) init NS_UNAVAILABLE;
/**
 * Indicates whether this stream is a NATIVE stream or ACQUIRED stream.
 */
- (StreamType) getStreamType;

/**
 * Updates an ACQUIRED stream with an image that is guaranteed to be used in the next frame.
 *
 * This method tells Filament to immediately "acquire" the image and trigger a callback
 * when it is done with it. This should be called by the user outside of beginFrame / endFrame,
 * and should be called only once per frame. If the user pushes images to the same stream
 * multiple times in a single frame, only the final image is honored, but all callbacks are
 * invoked.
 *
 * This method should be called on the same thread that calls Renderer::beginFrame, which is
 * also where the callback is invoked. This method can only be used for streams that were
 * constructed without calling the `stream` method on the builder.
 *
 * @see Stream for more information about NATIVE and ACQUIRED configurations.
 *
 * @param image      Pointer to AHardwareBuffer, casted to void* since this is a public header.
 * @param callback   This is triggered by Filament when it wishes to release the image.
 *                   It callback tales two arguments: the AHardwareBuffer and the userdata.
 * @param userdata   Optional closure data. Filament will pass this into the callback when it
 *                   releases the image.
 */
#warning Callback from swift
//- (void) setAcquiredImage: (void*) image :(Callback) callback :(void*) userdata;

/**
 * @see setAcquiredImage(void*, Callback, void*)
 *
 * @param image      Pointer to AHardwareBuffer, casted to void* since this is a public header.
 * @param handler    Handler to dispatch the AcquiredImage or nullptr for the default handler.
 * @param callback   This is triggered by Filament when it wishes to release the image.
 *                   It callback tales two arguments: the AHardwareBuffer and the userdata.
 * @param userdata   Optional closure data. Filament will pass this into the callback when it
 *                   releases the image.
 */
//- (void) setAcquiredImage: (void*) image :(backend::CallbackHandler*) handler :(Callback) callback :(void*) userdata;

/**
 * Updates the size of the incoming stream. Whether this value is used is
 *              stream dependent. On Android, it must be set when using
 *              Builder::stream(long externalTextureId).
 *
 * @param width     new width of the incoming stream
 * @param height    new height of the incoming stream
 */
- (void) setDimensions: (uint32_t) width :(uint32_t) height;

/**
 * Returns the presentation time of the currently displayed frame in nanosecond.
 *
 * This value can change at any time.
 *
 * @return timestamp in nanosecond.
 */
- (int64_t) getTimestamp;
@end


#endif /* Stream_h */
