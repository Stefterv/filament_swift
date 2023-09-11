//
//  SwapChain.h
//
//  Created by Stef Tervelde on 29.06.22.
//

#import <Foundation/Foundation.h>

#ifndef SwapChain_h
#define SwapChain_h

/**
 * A swap chain represents an Operating System's *native* renderable surface.
 *
 * Typically it's a native window or a view. Because a SwapChain is initialized from a
 * native object, it is given to filament as a `void *`, which must be of the proper type
 * for each platform filament is running on.
 *
 * \code
 * SwapChain* swapChain = engine->createSwapChain(nativeWindow);
 * \endcode
 *
 * When Engine::create() is used without specifying a Platform, the `nativeWindow`
 * parameter above must be of type:
 *
 * Platform        | nativeWindow type
 * :---------------|:----------------------------:
 * Android         | ANativeWindow*
 * macOS - OpenGL  | NSView*
 * macOS - Metal   | CAMetalLayer*
 * iOS - OpenGL    | CAEAGLLayer*
 * iOS - Metal     | CAMetalLayer*
 * X11             | Window
 * Windows         | HWND
 *
 * Otherwise, the `nativeWindow` is defined by the concrete implementation of Platform.
 *
 *
 * Examples:
 *
 * Android
 * -------
 *
 * On Android, an `ANativeWindow*` can be obtained from a Java `Surface` object using:
 *
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *  #include <android/native_window_jni.h>
 *  // parameters
 *  // env:         JNIEnv*
 *  // surface:     jobject
 *  ANativeWindow* win = ANativeWindow_fromSurface(env, surface);
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *
 * \warning
 * Don't use reflection to access the `mNativeObject` field, it won't work.
 *
 * A `Surface` can be retrieved from a `SurfaceView` or `SurfaceHolder` easily using
 * `SurfaceHolder.getSurface()` and/or `SurfaceView.getHolder()`.
 *
 * \note
 * To use a `TextureView` as a SwapChain, it is necessary to first get its `SurfaceTexture`,
 * for instance using `TextureView.SurfaceTextureListener` and then create a `Surface`:
 *
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.java}
 *  // using a TextureView.SurfaceTextureListener:
 *  public void onSurfaceTextureAvailable(SurfaceTexture surfaceTexture, int width, int height) {
 *      mSurface = new Surface(surfaceTexture);
 *      // mSurface can now be used in JNI to create an ANativeWindow.
 *  }
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *
 * Linux
 * -----
 *
 * Example using SDL:
 *
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * SDL_SysWMinfo wmi;
 * SDL_VERSION(&wmi.version);
 * SDL_GetWindowWMInfo(sdlWindow, &wmi);
 * Window nativeWindow = (Window) wmi.info.x11.window;
 *
 * using namespace filament;
 * Engine* engine       = Engine::create();
 * SwapChain* swapChain = engine->createSwapChain((void*) nativeWindow);
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *
 * Windows
 * -------
 *
 * Example using SDL:
 *
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * SDL_SysWMinfo wmi;
 * SDL_VERSION(&wmi.version);
 * ASSERT_POSTCONDITION(SDL_GetWindowWMInfo(sdlWindow, &wmi), "SDL version unsupported!");
 * HDC nativeWindow = (HDC) wmi.info.win.hdc;
 *
 * using namespace filament;
 * Engine* engine       = Engine::create();
 * SwapChain* swapChain = engine->createSwapChain((void*) nativeWindow);
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *
 * OSX
 * ---
 *
 * On OSX, any `NSView` can be used *directly* as a `nativeWindow` with createSwapChain().
 *
 * Example using SDL/Objective-C:
 *
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.mm}
 *  #include <filament/Engine.h>
 *
 *  #include <Cocoa/Cocoa.h>
 *  #include <SDL_syswm.h>
 *
 *  SDL_SysWMinfo wmi;
 *  SDL_VERSION(&wmi.version);
 *  NSWindow* win = (NSWindow*) wmi.info.cocoa.window;
 *  NSView* view = [win contentView];
 *  void* nativeWindow = view;
 *
 *  using namespace filament;
 *  Engine* engine       = Engine::create();
 *  SwapChain* swapChain = engine->createSwapChain(nativeWindow);
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *
 * @see Engine
 */
@class Engine;

@interface SwapChain : NSObject

@property (nonatomic, readonly, nonnull) void* swapchain NS_SWIFT_UNAVAILABLE("Don't access the raw pointers");
- (nonnull id) init: (nonnull void*) swapchain NS_SWIFT_UNAVAILABLE("Instances are created internally");
- (nonnull id) init NS_UNAVAILABLE;
/**
 * Return whether createSwapChain supports the SWAP_CHAIN_CONFIG_SRGB_COLORSPACE flag.
 * The default implementation returns false.
 *
 * @param engine A pointer to the filament Engine
 * @return true if SWAP_CHAIN_CONFIG_SRGB_COLORSPACE is supported, false otherwise.
 */
+ (bool) isSRGBSwapChainSupported: (nonnull Engine*) engine;
/**
 * @return the native <code>Object</code> this <code>SwapChain</code> was created from or null
 *         for a headless SwapChain.
 */
- (nonnull void*) getNativeWindow;

/**
 * FrameScheduledCallback is a callback function that notifies an application when Filament has
 * completed processing a frame and that frame is ready to be scheduled for presentation.
 *
 * Typically, Filament is responsible for scheduling the frame's presentation to the SwapChain.
 * If a SwapChain::FrameScheduledCallback is set, however, the application bares the
 * responsibility of scheduling a frame for presentation by calling the backend::PresentCallable
 * passed to the callback function. Currently this functionality is only supported by the Metal
 * backend.
 *
 * A FrameScheduledCallback can be set on an individual SwapChain through
 * SwapChain::setFrameScheduledCallback. If the callback is set, then the SwapChain will *not*
 * automatically schedule itself for presentation. Instead, the application must call the
 * PresentCallable passed to the FrameScheduledCallback.
 *
 * @param callback    A callback, or nullptr to unset.
 * @param user        An optional pointer to user data passed to the callback function.
 *
 * @remark Only Filament's Metal backend supports PresentCallables and frame callbacks. Other
 * backends ignore the callback (which will never be called) and proceed normally.
 *
 * @remark The SwapChain::FrameScheduledCallback is called on an arbitrary thread.
 *
 * @see PresentCallable
 */
#warning Callback from swift
//- (void) setFrameScheduledCallback: (FrameScheduledCallback) callback:(nullable void*) user;

/**
 * FrameCompletedCallback is a callback function that notifies an application when a frame's
 * contents have completed rendering on the GPU.
 *
 * Use SwapChain::setFrameCompletedCallback to set a callback on an individual SwapChain. Each
 * time a frame completes GPU rendering, the callback will be called.
 *
 * If handler is nullptr, the callback is guaranteed to be called on the main Filament thread.
 *
 * Use \c setFrameCompletedCallback() (with default arguments) to unset the callback.
 *
 * @param handler     Handler to dispatch the callback or nullptr for the default handler.
 * @param callback    Callback called when each frame completes.
 *
 * @remark Only Filament's Metal backend supports frame callbacks. Other backends ignore the
 * callback (which will never be called) and proceed normally.
 *
 * @see CallbackHandler
 */
//- (void) setFrameCompletedCallback: (nullable backend::CallbackHandler*) handler :(FrameCompletedCallback) callback;
@end


#endif /* SwapChain_h */
