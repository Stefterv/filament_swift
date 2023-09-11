//
//  Renderer.h
//
//  Created by Stef Tervelde on 29.06.22.
//

#import <Foundation/Foundation.h>
#import <simd/simd.h>
#import <CoreImage/CoreImage.h>

#import "SwapChain.h"
#import "View.h"
#import "Viewport.h"
#import "Texture.h"
#import "RenderTarget.h"

#ifndef Renderer_h
#define Renderer_h

NS_SWIFT_NAME(Renderer.DisplayInfo)
@interface DisplayInfo : NSObject
@property double refreshRate;
@end

NS_SWIFT_NAME(Renderer.FrameRateOptions)
@interface FrameRateOptions : NSObject
@property double interval;
@property double headRoomRatio;
@property double scaleRate;
@property double history;
@end

NS_SWIFT_NAME(Renderer.ClearOptions)
@interface ClearOptions : NSObject
@property CIColor*_Nonnull clearColor;
@property bool clear;
@property bool discard;
@end


/**
 * A <code>Renderer</code> instance represents an operating system's window.
 *
 * <p>
 * Typically, applications create a <code>Renderer</code> per window. The <code>Renderer</code> generates
 * drawing commands for the render thread and manages frame latency.
 * <br>
 * A Renderer generates drawing commands from a View, itself containing a Scene description.
 * </p>
 *
 * <h1>Creation and Destruction</h1>
 *
 * <p>A <code>Renderer</code> is created using {@link Engine#createRenderer} and destroyed
 * using {@link Engine#destroyRenderer}.</p>
 *
 * @see Engine
 * @see View
 */
@interface Renderer: NSObject

@property (nonatomic, readonly, nonnull) void* renderer NS_SWIFT_UNAVAILABLE("Don't access the raw pointers");
- (nonnull id) init: (nonnull void*) renderer NS_SWIFT_UNAVAILABLE("Instances are created internally");
- (nonnull id) init NS_UNAVAILABLE;

- (void) setDisplayInfo :(nonnull DisplayInfo*) info;

- (void) setFrameRateOptions :(nonnull FrameRateOptions*) info;

- (void) setClearOptions :(nonnull ClearOptions*) info;

/**
 * Set the time at which the frame must be presented to the display.
 * <p>
 * This must be called between {@link #beginFrame} and {@link #endFrame}.
 * </p>
 *
 * @param monotonicClockNanos  The time in nanoseconds corresponding to the system monotonic
 *                             up-time clock. The presentation time is typically set in the
 *                             middle of the period of interest and cannot be too far in the
 *                             future as it is limited by how many buffers are available in
 *                             the display sub-system. Typically it is set to 1 or 2 vsync
 *                             periods away.
 */
- (void) setPresentationTime :(long) monotonicClockNanos;
/**
 * Sets up a frame for this <code>Renderer</code>.
 * <p><code>beginFrame</code> manages frame pacing, and returns whether or not a frame should be
 * drawn. The goal of this is to skip frames when the GPU falls behind in order to keep the frame
 * latency low.</p>
 *
 * <p>If a given frame takes too much time in the GPU, the CPU will get ahead of the GPU. The
 * display will draw the same frame twice producing a stutter. At this point, the CPU is
 * ahead of the GPU and depending on how many frames are buffered, latency increases.
 * beginFrame() attempts to detect this situation and returns <code>false</code> in that case,
 * indicating to the caller to skip the current frame.</p>
 *
 * <p>All calls to render() must happen <b>after</b> beginFrame().</p>
 *
 * @param swapChain the {@link SwapChain} instance to use
 * @param frameTimeNanos The time in nanoseconds when the frame started being rendered,
 *                       in the {@link System#nanoTime()} timebase. Divide this value by 1000000 to
 *                       convert it to the {@link android.os.SystemClock#uptimeMillis()}
 *                       time base. This typically comes from
 *                       {@link android.view.Choreographer.FrameCallback}.
 *
 * @return <code>true</code>: the current frame must be drawn, and {@link #endFrame} must be called<br>
 *         <code>false</code>: the current frame should be skipped, when skipping a frame,
 *         the whole frame is canceled, and {@link #endFrame} must not
 *         be called. However, the user can choose to proceed as though <code>true</code> was
 *         returned and produce a frame anyways, by making calls to {@link #render(View)},
 *         in which case {@link #endFrame} must be called.
 *
 * @see #endFrame
 * @see #render
 */
- (bool) beginFrame: (nonnull SwapChain*) swapChain;
/**
 * Finishes the current frame and schedules it for display.
 * <p>
 * <code>endFrame()</code> schedules the current frame to be displayed on the
 * <code>Renderer</code>'s window.
 * </p>
 *
 * <br><p>All calls to render() must happen <b>before</b> endFrame().</p>
 *
 * @see #beginFrame
 * @see #render
 */
- (void) endFrame;
/**
 * Renders a {@link View} into this <code>Renderer</code>'s window.
 *
 * <p>
 * This is filament's main rendering method, most of the CPU-side heavy lifting is performed
 * here. The purpose of the <code>render()</code> function is to generate render commands which
 * are asynchronously executed by the {@link Engine}'s render thread.
 * </p>
 *
 * <p><code>render()</code> generates commands for each of the following stages:</p>
 * <ul>
 * <li>Shadow map passes, if needed</li>
 * <li>Depth pre-pass</li>
 * <li>SSAO pass, if enabled</li>
 * <li>Color pass</li>
 * <li>Post-processing pass</li>
 * </ul>
 * <p>
 * A typical render loop looks like this:
 *
 * <pre>
 * void renderLoop(Renderer renderer, SwapChain swapChain) {
 *     do {
 *         // typically we wait for VSYNC and user input events
 *         if (renderer.beginFrame(swapChain)) {
 *             renderer.render(mView);
 *             renderer.endFrame();
 *         }
 *     } while (!quit());
 * }
 * </pre>
 *
 * <ul>
 * <li><code>render()</code> must be called <b>after</b> {@link #beginFrame} and <b>before</b>
 * {@link #endFrame}.</li>
 *
 * <li><code>render()</code> must be called from the {@link Engine}'s main thread
 * (or external synchronization must be provided). In particular, calls to <code>render()</code>
 * on different <code>Renderer</code> instances <b>must</b> be synchronized.</li>
 *
 * <li><code>render()</code> performs potentially heavy computations and cannot be multi-threaded.
 * However, internally, it is highly multi-threaded to both improve performance and mitigate
 * the call's latency.</li>
 *
 * <li><code>render()</code> is typically called once per frame (but not necessarily).</li>
 * </ul>
 *
 * @param view the {@link View} to render
 * @see #beginFrame
 * @see #endFrame
 * @see View
 */
- (void) render: (nonnull View*) view;
/**
 * Renders a standalone {@link View} into its associated <code>RenderTarget</code>.
 *
 * <p>
 * This call is mostly equivalent to calling {@link #render(View)} inside a
 * {@link #beginFrame} / {@link #endFrame} block, but incurs less overhead. It can be used
 * as a poor man's compute API.
 * </p>
 *
 * <ul>
 * <li><code>renderStandaloneView()</code> must be called <b>outside</b> of
 * {@link #beginFrame} / {@link #endFrame}.</li>
 *
 * <li><code>renderStandaloneView()</code> must be called from the {@link Engine}'s main thread
 * (or external synchronization must be provided). In particular, calls to
 * <code>renderStandaloneView()</code> on different <code>Renderer</code> instances <b>must</b>
 * be synchronized.</li>
 *
 * <li><code>renderStandaloneView()</code> performs potentially heavy computations and cannot be
 * multi-threaded. However, internally, it is highly multi-threaded to both improve performance
 * and mitigate the call's latency.</li>
 *
 * @param view the {@link View} to render. This View must have an associated {@link RenderTarget}
 * @see View
 */
- (void) renderStandaloneView: (nonnull View*) view;
/**
 * Copies the currently rendered {@link View} to the indicated {@link SwapChain}, using the
 * indicated source and destination rectangle.
 *
 * <p><code>copyFrame()</code> should be called after a frame is rendered using {@link #render}
 * but before {@link #endFrame} is called.</p>
 *
 * @param dstSwapChain the {@link SwapChain} into which the frame should be copied
 * @param dstViewport the destination rectangle in which to draw the view
 * @param srcViewport the source rectangle to be copied
 * @param flags one or more <code>CopyFrameFlag</code> behavior configuration flags
 */
- (void) copyFrame: (nonnull SwapChain*) dstSwapChain :(Viewport) dstViewport :(Viewport) srcViewport :(int) flags;
/**
 * Reads back the content of the {@link SwapChain} associated with this <code>Renderer</code>.
 *
 *<pre>
 *
 *  Framebuffer as seen on         User buffer (PixelBufferDescriptor)
 *  screen
 *  +--------------------+
 *  |                    |                .stride         .alignment
 *  |                    |         ----------------------->-->
 *  |                    |         O----------------------+--+   low addresses
 *  |                    |         |          |           |  |
 *  |             w      |         |          | .top      |  |
 *  |       <--------->  |         |          V           |  |
 *  |       +---------+  |         |     +---------+      |  |
 *  |       |     ^   |  | ======> |     |         |      |  |
 *  |   x   |    h|   |  |         |.left|         |      |  |
 *  +------>|     v   |  |         +---->|         |      |  |
 *  |       +.........+  |         |     +.........+      |  |
 *  |            ^       |         |                      |  |
 *  |          y |       |         +----------------------+--+  high addresses
 *  O------------+-------+
 *
 *</pre>
 *
 *
 * <p><code>readPixels</code> must be called within a frame, meaning after {@link #beginFrame}
 * and before {@link #endFrame}. Typically, <code>readPixels</code> will be called after
 * {@link #render}.</p>
 * <br>
 * <p>After calling this method, the callback associated with <code>buffer</code>
 * will be invoked on the main thread, indicating that the read-back has completed.
 * Typically, this will happen after multiple calls to {@link #beginFrame},
 * {@link #render}, {@link #endFrame}.</p>
 * <br>
 * <p><code>readPixels</code> is intended for debugging and testing.
 * It will impact performance significantly.</p>
 *
 * @param xoffset   left offset of the sub-region to read back
 * @param yoffset   bottom offset of the sub-region to read back
 * @param width     width of the sub-region to read back
 * @param height    height of the sub-region to read back
 * @param buffer    client-side buffer where the read-back will be written
 *
 *                  <p>
 *                  The following format are always supported:
 *                      <li>{@link Texture.Format#RGBA}</li>
 *                      <li>{@link Texture.Format#RGBA_INTEGER}</li>
 *                  </p>
 *
 *                  <p>
 *                  The following types are always supported:
 *                      <li>{@link Texture.Type#UBYTE}</li>
 *                      <li>{@link Texture.Type#UINT}</li>
 *                      <li>{@link Texture.Type#INT}</li>
 *                      <li>{@link Texture.Type#FLOAT}</li>
 *                  </p>
 *
 *                  <p>Other combination of format/type may be supported. If a combination is
 *                  not supported, this operation may fail silently. Use a DEBUG build
 *                  to get some logs about the failure.</p>
 *
 * @exception BufferOverflowException if the specified parameters would result in reading
 * outside of <code>buffer</code>.
 */
- (nonnull NSData*) readPixels: (int) xoffset :(int) yoffset :(int) width :(int) height;
/**
 * Reads back the content of a specified {@link RenderTarget}.
 *
 *<pre>
 *
 *  Framebuffer as seen on         User buffer (PixelBufferDescriptor)
 *  screen
 *  +--------------------+
 *  |                    |                .stride         .alignment
 *  |                    |         ----------------------->-->
 *  |                    |         O----------------------+--+   low addresses
 *  |                    |         |          |           |  |
 *  |             w      |         |          | .top      |  |
 *  |       <--------->  |         |          V           |  |
 *  |       +---------+  |         |     +---------+      |  |
 *  |       |     ^   |  | ======> |     |         |      |  |
 *  |   x   |    h|   |  |         |.left|         |      |  |
 *  +------>|     v   |  |         +---->|         |      |  |
 *  |       +.........+  |         |     +.........+      |  |
 *  |            ^       |         |                      |  |
 *  |          y |       |         +----------------------+--+  high addresses
 *  O------------+-------+
 *
 *</pre>
 *
 *
 * <p>Typically <code>readPixels</code> will be called after {@link #render} and before
 * {@link #endFrame}.</p>
 * <br>
 * <p>After calling this method, the callback associated with <code>buffer</code>
 * will be invoked on the main thread, indicating that the read-back has completed.
 * Typically, this will happen after multiple calls to {@link #beginFrame},
 * {@link #render}, {@link #endFrame}.</p>
 * <br>
 * <p>OpenGL only: if issuing a <code>readPixels</code> on a {@link RenderTarget} backed by a
 * {@link Texture} that had data uploaded to it via {@link Texture#setImage}, the data returned
 * from <code>readPixels</code> will be y-flipped with respect to the {@link Texture#setImage}
 * call.</p>
 * <p><code>readPixels</code> is intended for debugging and testing.
 * It will impact performance significantly.</p>
 *
 * @param renderTarget  {@link RenderTarget} to read back from
 * @param xoffset       left offset of the sub-region to read back
 * @param yoffset       bottom offset of the sub-region to read back
 * @param width         width of the sub-region to read back
 * @param height        height of the sub-region to read back
 * @param buffer        client-side buffer where the read-back will be written
 *
 *                  <p>
 *                  The following format are always supported:
 *                      <li>{@link Texture.Format#RGBA}</li>
 *                      <li>{@link Texture.Format#RGBA_INTEGER}</li>
 *                  </p>
 *
 *                  <p>
 *                  The following types are always supported:
 *                      <li>{@link Texture.Type#UBYTE}</li>
 *                      <li>{@link Texture.Type#UINT}</li>
 *                      <li>{@link Texture.Type#INT}</li>
 *                      <li>{@link Texture.Type#FLOAT}</li>
 *                  </p>
 *
 *                  <p>Other combination of format/type may be supported. If a combination is
 *                  not supported, this operation may fail silently. Use a DEBUG build
 *                  to get some logs about the failure.</p>
 *
 * @exception BufferOverflowException if the specified parameters would result in reading
 * outside of <code>buffer</code>.
 */
- (nonnull NSData*) readPixels: (nonnull RenderTarget*) target :(int) xoffset :(int) yoffset :(int) width :(int) height;
/**
 * Returns a timestamp (in seconds) for the last call to {@link #beginFrame}. This value is
 * constant for all {@link View views} rendered during a frame. The epoch is set with
 * {@link #resetUserTime}.
 * <br>
 * <p>In materials, this value can be queried using <code>vec4 getUserTime()</code>. The value
 * returned is a <code>highp vec4</code> encoded as follows:</p>
 * <pre>
 *      time.x = (float)Renderer.getUserTime();
 *      time.y = Renderer.getUserTime() - time.x;
 * </pre>
 *
 * It follows that the following invariants are true:
 * <pre>
 *      (double)time.x + (double)time.y == Renderer.getUserTime()
 *      time.x == (float)Renderer.getUserTime()
 * </pre>
 *
 * This encoding allows the shader code to perform high precision (i.e. double) time
 * calculations when needed despite the lack of double precision in the shader, e.g.:
 * <br>
 *      To compute <code>(double)time * vertex</code> in the material, use the following construct:
 * <pre>
 *              vec3 result = time.x * vertex + time.y * vertex;
 * </pre>
 *
 * Most of the time, high precision computations are not required, but be aware that the
 * precision of <code>time.x</code> rapidly diminishes as time passes:
 *
 * <center>
 * <table border="1">
 *     <tr align="center"><th> time    </th><th> precision </th></tr>
 *     <tr align="center"><td> 16.7s   </td><td> us        </td></tr>
 *     <tr align="center"><td> 4h39.7s </td><td> ms        </td></tr>
 *     <tr align="center"><td> 77h     </td><td> 1/60s     </td></tr>
 * </table>
 * </center>
 * <p>
 *
 * In other words, it is only possible to get microsecond accuracy for about 16s or millisecond
 * accuracy for just under 5h. This problem can be mitigated by calling {@link #resetUserTime},
 * or using high precision time as described above.
 *
 * @return the time in seconds since {@link #resetUserTime} was last called
 *
 * @see #resetUserTime
 */
- (double) getUserTime;
/**
 * Sets the user time epoch to now, i.e. resets the user time to zero.
 * <br>
 * <p>Use this method used to keep the precision of time high in materials, in practice it should
 * be called at least when the application is paused, e.g.
 * <code>Activity.onPause</code> in Android.</p>
 *
 * @see #getUserTime
 */
- (void) resetUserTime;
@end

#endif /* Renderer_h */
