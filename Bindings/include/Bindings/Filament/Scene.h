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


/**
 * Sets the Skybox.
 *
 * The Skybox is drawn last and covers all pixels not touched by geometry.
 *
 * @param skybox The Skybox to use to fill untouched pixels, or nullptr to unset the Skybox.
 */
- (void) setSkybox: (nullable Skybox*) skybox;
/**
 * Returns the Skybox associated with the Scene.
 *
 * @return The associated Skybox, or nullptr if there is none.
 */
- (nullable Skybox*) getSkybox;
/**
 * Set the IndirectLight to use when rendering the Scene.
 *
 * Currently, a Scene may only have a single IndirectLight. This call replaces the current
 * IndirectLight.
 *
 * @param ibl The IndirectLight to use when rendering the Scene or nullptr to unset.
 * @see getIndirectLight
 */
- (void) setIndirectLight: (nullable IndirectLight*) light;
/**
 * Get the IndirectLight or nullptr if none is set.
 *
 * @return the the IndirectLight or nullptr if none is set
 * @see setIndirectLight
 */
- (nullable IndirectLight*) getIndirectLight;
/**
 * Adds an Entity to the Scene.
 *
 * @param entity The entity is ignored if it doesn't have a Renderable or Light component.
 *
 * \attention
 *  A given Entity object can only be added once to a Scene.
 *
 */
- (void) addEntity: (Entity) entity;
/**
 * Adds a list of entities to the Scene.
 *
 * @param entities Array containing entities to add to the scene.
 * @param count Size of the entity array.
 */
- (void) addEntities: (nonnull NSArray<NSNumber*>*) entities;
/**
 * Removes the Renderable from the Scene.
 *
 * @param entity The Entity to remove from the Scene. If the specified
 *                   \p entity doesn't exist, this call is ignored.
 */
- (void) remove: (Entity) entity;
/**
 * Removes a list of entities to the Scene.
 *
 * This is equivalent to calling remove in a loop.
 * If any of the specified entities do not exist in the scene, they are skipped.
 *
 * @param entities Array containing entities to remove from the scene.
 * @param count Size of the entity array.
 */
- (void) removeEntities: (nonnull NSArray<NSNumber*>*) entities;
/**
 * Returns the number of Renderable objects in the Scene.
 *
 * @return number of Renderable objects in the Scene.
 */
- (size_t) getRenderableCount;
/**
 * Returns the total number of Light objects in the Scene.
 *
 * @return The total number of Light objects in the Scene.
 */
- (size_t) getLightCount;
/**
 * Returns true if the given entity is in the Scene.
 *
 * @return Whether the given entity is in the Scene.
 */
- (bool) hasEntity: (Entity) entity;

@end


#endif /* Header_h */
