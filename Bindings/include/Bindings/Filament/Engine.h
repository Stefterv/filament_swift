//
//  Engine.h
//
//  Created by Stef Tervelde on 29.06.22.
//

#ifndef Engine_h
#define Engine_h

#import <UIKit/UIKit.h>
#import <Foundation/Foundation.h>

#import "Renderer.h"
#import "Scene.h"
#import "SwapChain.h"
#import "Camera.h"
#import "Entity.h"
#import "EntityManager.h"
#import "TransformManager.h"
#import "LightManager.h"

typedef NS_ENUM(NSInteger, Backend) {
    BackendDefault,
    BackendOpenGL,
    BackendVulkan,
    BackendMetal,
    BackendNoop,
};

@class RenderableManager;
@class View;

/**
 * Engine is filament's main entry-point.
 * <p>
 * An Engine instance main function is to keep track of all resources created by the user and
 * manage the rendering thread as well as the hardware renderer.
 * <p>
 * To use filament, an Engine instance must be created first:
 *
 * <pre>
 * import Filament
 *
 * let engine = Engine.create();
 * </pre>
 * <p>
 * Engine essentially represents (or is associated to) a hardware context
 * (e.g. an OpenGL ES context).
 * <p>
 * Rendering typically happens in an operating system's window (which can be full screen), such
 * window is managed by a {@link Renderer}.
 *
 * <h1><u>Resource Tracking</u></h1>
 * <p>
 * Each <code>Engine</code> instance keeps track of all objects created by the user, such as vertex
 * and index buffers, lights, cameras, etc...
 * The user is expected to free those resources, however, leaked resources are freed when the
 * engine instance is destroyed and a warning is emitted in the console.
 *
 * <h1><u>Thread safety</u></h1>
 * <p>
 * An <code>Engine</code> instance is not thread-safe. The implementation makes no attempt to
 * synchronize calls to an <code>Engine</code> instance methods.
 * If multi-threading is needed, synchronization must be external.
 *
 * <h1><u>Multi-threading</u></h1>
 * <p>
 * When created, the <code>Engine</code> instance starts a render thread as well as multiple worker
 * threads, these threads have an elevated priority appropriate for rendering, based on the
 * platform's best practices. The number of worker threads depends on the platform and is
 * automatically chosen for best performance.
 * <p>
 * On platforms with asymmetric cores (e.g. ARM's Big.Little), <code>Engine</code> makes some
 * educated guesses as to which cores to use for the render thread and worker threads. For example,
 * it'll try to keep an OpenGL ES thread on a Big core.
 *
 * <h1><u>Swap Chains</u></h1>
 * <p>
 * A swap chain represents an Operating System's <b>native</b> renderable surface.
 * Typically it's a window or a view. Because a {@link SwapChain} is initialized from a native
 * object, it is given to filament as an <code>Object</code>, which must be of the proper type for
 * each platform filament is running on.
 * <p>
 *
 * @see SwapChain
 * @see Renderer
 */


@interface Engine : NSObject

@property (nonatomic, readonly, nonnull) void* engine NS_SWIFT_UNAVAILABLE("Don't access the raw pointers");
- (nonnull id) init: (nonnull void*) engine NS_SWIFT_UNAVAILABLE("Create a new engine with Engine.create");
- (nonnull id) init NS_UNAVAILABLE;

/**
 * Creates an instance of Engine using the default Backend
 * This method is one of the few thread-safe methods.
 *
 * \returns A newly created <code>Engine</code>, or <code>null</code> if the GPU driver couldn't
 *         be initialized, for instance if it doesn't support the right version of OpenGL or
 *         OpenGL ES.
 *
 * \exception IllegalStateException can be thrown if there isn't enough memory to
 * allocate the command buffer.
 *
 */
+ (nonnull instancetype)create;

/**
 * Creates an instance of Engine using the specified {@link Backend}
 * <p>
 * This method is one of the few thread-safe methods.
 *
 * \param backend           driver backend to use
 *
 * \return A newly created <code>Engine</code>, or <code>null</code> if the GPU driver couldn't
 *         be initialized, for instance if it doesn't support the right version of OpenGL or
 *         OpenGL ES.
 *
 * \exception IllegalStateException can be thrown if there isn't enough memory to
 * allocate the command buffer.
 *
 */
+ (nonnull instancetype)create: (Backend)backend;

/**
 * Destroy the Engine instance and all associated resources.
 *
 * Engine.destroy() should be called last and after all other resources have been destroyed,
 * it ensures all filament resources are freed.
 *
 * Destroy performs the following tasks:
 * 1. Destroy all internal software and hardware resources.
 * 2. Free all user allocated resources that are not already destroyed and logs a warning.
 *    This indicates a "leak" in the user's code.
 * 3. Terminate the rendering engine's thread.
 *
 * \param engine Filament Engine to be destroyed.
 *               \p engine is cleared upon return.
 *
 * This method is thread-safe.
 */
+ (void)destroy: (nonnull Engine*)engine;

/**
 * @return the backend used by this <code>Engine</code>
 */
- (Backend) getBackend;

/**
 * Creates an opaque {@link SwapChain} from the given OS native window handle.
 *
 * @param layer on iOS, <b>must be</b> an instance of {@link CALayer}
 *
 * @return a newly created {@link SwapChain} object
 *
 * @exception IllegalStateException can be thrown if the SwapChain couldn't be created
 */
- (nonnull SwapChain*) createSwapChain: (nonnull CALayer*) layer;

/**
 * Creates a headless {@link SwapChain}
 *
 * @param width  width of the rendering buffer
 * @param height height of the rendering buffer
 * @param flags  configuration flags, see {@link SwapChain}
 *
 * @return a newly created {@link SwapChain} object
 *
 * @exception IllegalStateException can be thrown if the SwapChain couldn't be created
 *
 * @see SwapChain#CONFIG_DEFAULT
 * @see SwapChain#CONFIG_TRANSPARENT
 * @see SwapChain#CONFIG_READABLE
*/

- (nonnull SwapChain*) createSwapChain: (uint32_t) width :(uint32_t) height;

/**
 * Destroys a {@link SwapChain} and frees all its associated resources.
 * @param swapChain the {@link SwapChain} to destroy
 */

- (void) destroySwapChain: (nonnull SwapChain*) swapchain;

/**
 * Creates a {\link Renderer}.
 * \return a newly created {\link Renderer}
 * \exception IllegalStateException can be thrown if the {\link Renderer} couldn't be created
 */
- (nonnull Renderer*) createRenderer;
/**
 * Destroys a {@link Renderer} and frees all its associated resources.
 * @param renderer the {@link Renderer} to destroy
 */
- (void) destroyRenderer: (nonnull Renderer*) renderer;

/**
 * Creates and adds a {@link Camera} component to a given <code>entity</code>.
 *
 * @param entity <code>entity</code> to add the camera component to
 * @return A newly created {@link Camera}
 * @exception IllegalStateException can be thrown if the {@link Camera} couldn't be created
 */
- (nonnull Camera*) createCamera: (Entity) entity;


/**
 * Returns the Camera component of the given <code>entity</code>.
 *
 * @param entity An <code>entity</code>.
 * @return the Camera component for this entity or null if the entity doesn't have a Camera
 *         component
 */
- (nullable Camera*) getCameraComponent: (Entity) entity;


- (void) destroyCameraComponent: (Entity) entity;

/**
 * Creates a {@link Scene}.
 * @return a newly created {@link Scene}
 * @exception IllegalStateException can be thrown if the {@link Scene} couldn't be created
 */
- (nonnull Scene*) createScene;

/**
 * Destroys a {@link Scene} and frees all its associated resources.
 * @param scene the {@link Scene} to destroy
 */
- (void) destroyScene: (nonnull Scene*) scene;

/**
 * Creates a {@link View}.
 * @return a newly created {@link View}
 * @exception IllegalStateException can be thrown if the {@link View} couldn't be created
 */
- (nonnull View*) createView;

/**
 * Destroys a {@link View} and frees all its associated resources.
 * @param view the {@link View} to destroy
 */
- (void) destroyView: (nonnull View*) view;

/**
 * Destroys an <code>entity</code> and all its components.
 * <p>
 * It is recommended to destroy components individually before destroying their
 * <code>entity</code>, this gives more control as to when the destruction really happens.
 * Otherwise, orphaned components are garbage collected, which can happen at a later time.
 * Even when component are garbage collected, the destruction of their <code>entity</code>
 * terminates their participation immediately.
 *
 * @param entity the <code>entity</code> to destroy
 */
- (void) destroyEntity: (Entity) entity;

- (nonnull TransformManager*) getTransformManager;

- (nonnull LightManager*) getLightManager;

- (nonnull EntityManager*) getEntityManager;

- (nonnull RenderableManager*) getRenderableManager;

@end

#endif /* Engine_h */
