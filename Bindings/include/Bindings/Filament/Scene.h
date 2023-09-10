//
//  Scene.h
//  
//
//  Created by Stef Tervelde on 29.06.22.
//
#import <Foundation/Foundation.h>
#import "Skybox.h"
#import "IndirectLight.h"
#import "Entity.h"

#ifndef Scene_h
#define Scene_h

/**
 * A <code>Scene</code> is a flat container of {@link RenderableManager} and {@link LightManager}
 * components.
 * <br>
 * <p>A <code>Scene</code> doesn't provide a hierarchy of objects, i.e.: it's not a scene-graph.
 * However, it manages the list of objects to render and the list of lights. These can
 * be added or removed from a <code>Scene</code> at any time.
 * Moreover clients can use {@link TransformManager} to create a graph of transforms.</p>
 * <br>
 * <p>A {@link RenderableManager} component <b>must</b> be added to a <code>Scene</code> in order
 * to be rendered, and the <code>Scene</code> must be provided to a {@link View}.</p>
 *
 * <h1>Creation and Destruction</h1>
 *
 * A <code>Scene</code> is created using {@link Engine#createScene} and destroyed using
 * {@link Engine#destroyScene(Scene)}.
 *
 * @see View
 * @see LightManager
 * @see RenderableManager
 * @see TransformManager
 */

@interface Scene: NSObject


@property (nonatomic, readonly, nonnull) void* scene NS_SWIFT_UNAVAILABLE("Don't access the raw pointers");
- (nonnull id) init: (nonnull void*) scene NS_SWIFT_UNAVAILABLE("Create a new renderer with engine.createScene");
- (nonnull id) init NS_UNAVAILABLE;

- (nullable Skybox*) getSkybox;
- (void) setSkybox: (nullable Skybox*) skybox;

- (void) setIndirectLight: (nullable IndirectLight*) light;

- (void) addEntity: (Entity) entity;
- (bool) hasEntity: (Entity) entity;
- (void) removeEntity: (Entity) entity;

- (size_t) getRenderableCount;
- (size_t) getLightCount;

@end


#endif /* Header_h */
