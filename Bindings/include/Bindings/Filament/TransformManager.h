//
//  TransformManager.h

//  Created by Stef Tervelde on 30.06.22.
//
#import <Foundation/Foundation.h>
#import <simd/simd.h>
#import "Entity.h"

#ifndef TransformManager_h
#define TransformManager_h

/**
 * <code>TransformManager</code> is used to add transform components to entities.
 *
 * <p>A transform component gives an entity a position and orientation in space in the coordinate
 * space of its parent transform. The <code>TransformManager</code> takes care of computing the
 * world-space transform of each component (i.e. its transform relative to the root).</p>
 *
 * <h1>Creation and destruction</h1>
 *
 * A transform component is created using {@link TransformManager#create} and destroyed by calling
 * {@link TransformManager#destroy}.
 *
 * <pre>
 *  Engine engine = Engine.create();
 *  EntityManager entityManager = EntityManager().get();
 *  int object = entityManager.create();
 *
 *  TransformManager tcm = engine.getTransformManager();
 *
 *  // create the transform component
 *  tcm.create(object);
 *
 *  // set its transform
 *  float[] transform = ...; // transform to set
 *  EntityInstance i = tcm.getInstance(object);
 *  tcm.setTransform(i, transform));
 *
 *  // destroy the transform component
 *  tcm.destroy(object);
 * </pre>
 *
 */

@interface TransformManager : NSObject

@property (nonatomic, readonly, nonnull) void* manager  NS_SWIFT_UNAVAILABLE("Don't access the raw pointers");
- (nonnull id) init: (nonnull void*) manager NS_SWIFT_UNAVAILABLE("Instances are created internally");
- (nonnull id) init NS_UNAVAILABLE;

/**
 * Returns whether a particular {@link Entity} is associated with a component of this
 * <code>TransformManager</code>
 *
 * @param entity an {@link Entity}
 * @return true if this {@link Entity} has a component associated with this manager
 */
- (bool) hasComponent: (Entity) entity;

/**
 * Gets an {@link EntityInstance} representing the transform component associated with the
 * given {@link Entity}.
 *
 * @param entity an {@link Entity}
 * @return an {@link EntityInstance}, which represents the transform component associated with
 * the {@link Entity} <code>entity</code>
 * @see #hasComponent
 */
- (EntityInstance) getInstance: (Entity) entity;
/**
 * Enables or disable the accurate translation mode. Disabled by default.
 *
 * When accurate translation mode is active, the translation component of all transforms is
 * maintained at double precision. This is only useful if the mat4 version of setTransform()
 * is used, as well as getTransformAccurate().
 *
 * @param enable true to enable the accurate translation mode, false to disable.
 *
 * @see #isAccurateTranslationsEnabled
 * @see #create(int, int, double[])
 * @see #setTransform(int, double[])
 * @see #getTransform(int, double[])
 * @see #getWorldTransform(int, double[])
 */
- (void) setAccurateTranslationsEnabled: (bool) enable;
- (bool) isAccurateTranslationsEnabled;

/**
 * Creates a transform component and associates it with the given entity. The component is
 * initialized with the identity transform.
 * If this component already exists on the given entity, it is first
 * destroyed as if {@link #destroy} was called.
 *
 * @param entity an {@link Entity} to associate a transform component to.
 * @see #destroy
 */
- (EntityInstance) create: (Entity) entity;
/**
 * Creates a transform component with a parent and associates it with the given entity.
 * If this component already exists on the given entity, it is first
 * destroyed as if {@link #destroy} was called.
 *
 * @param entity         an {@link Entity} to associate a transform component to.
 * @param parent         the  {@link EntityInstance} of the parent transform
 * @param localTransform the transform, relative to the parent, to initialize the transform
 *                       component with.
 * @see #destroy
 */

- (EntityInstance) create: (Entity) entity :(EntityInstance) parent :(simd_double4x4) localTransform;
/**
 * Destroys this component from the given entity, children are orphaned.
 *
 * @param entity an {@link Entity}.
 *               If this transform had children, these are orphaned, which means their local
 *               transform becomes a world transform. Usually it's nonsensical.
 *               It's recommended to make sure that a destroyed transform doesn't have children.
 * @see #create
 */
- (void) destroy: (Entity) entity;
/**
 * Re-parents an entity to a new one.
 *
 * @param i         the {@link EntityInstance} of the transform component to re-parent
 * @param newParent the {@link EntityInstance} of the new parent transform.
 *                  It is an error to re-parent an entity to a descendant and will cause
 *                  undefined behaviour.
 * @see #getInstance
 */
- (void) setParent: (EntityInstance) instance :(EntityInstance) parent;
/**
 * Returns the actual parent entity of an {@link EntityInstance} originally defined
 * by {@link #setParent(int, int)}.
 *
 * @param i the {@link EntityInstance} of the transform component to get the parent from.
 * @return the parent {@link Entity}.
 * @see #getInstance
 */
- (Entity) getParent: (Entity) entity;
/**
 * Sets a local transform of a transform component.
 * <p>This operation can be slow if the hierarchy of transform is too deep, and this
 * will be particularly bad when updating a lot of transforms. In that case,
 * consider using {@link #openLocalTransformTransaction} / {@link #commitLocalTransformTransaction}.</p>
 *
 * @param i              the {@link EntityInstance} of the transform component to set the local
 *                       transform to.
 * @param localTransform the local transform (i.e. relative to the parent).
 * @see #getTransform
 */
- (void) setTransform: (EntityInstance) instance :(simd_double4x4) localTransform;
/**
 * Returns the local transform of a transform component.
 *
 * @param i                 the {@link EntityInstance} of the transform component to query the
 *                          local transform from.
 * @param outLocalTransform a 16 <code>float</code> array to receive the result.
 *                          If <code>null</code> is given,  a new suitable array is allocated.
 * @return the local transform of the component (i.e. relative to the parent). This always
 * returns the value set by setTransform().
 * @see #setTransform
 */
- (simd_double4x4) getTransform: (EntityInstance) instance;
/**
 * Returns the world transform of a transform component.
 *
 * @param i                 the {@link EntityInstance} of the transform component to query the
 *                          world transform from.
 * @param outWorldTransform a 16 <code>float</code> array to receive the result.
 *                          If <code>null</code> is given,  a new suitable array is allocated
 * @return The world transform of the component (i.e. relative to the root). This is the
 * composition of this component's local transform with its parent's world transform.
 * @see #setTransform
 */
- (simd_double4x4) getWorldTransform: (EntityInstance) instance;
/**
 * Opens a local transform transaction. During a transaction, {@link #getWorldTransform} can
 * return an invalid transform until {@link #commitLocalTransformTransaction} is called.
 * However, {@link #setTransform} will perform significantly better and in constant time.
 *
 * <p>This is useful when updating many transforms and the transform hierarchy is deep (say more
 * than 4 or 5 levels).</p>
 *
 * <p>If the local transform transaction is already open, this is a no-op.</p>
 *
 * @see #commitLocalTransformTransaction
 * @see #setTransform
 */
- (void) openLocalTransformTransaction;
/**
 * Commits the currently open local transform transaction. When this returns, calls
 * to {@link #getWorldTransform} will return the proper value.
 *
 * <p>Failing to call this method when done updating the local transform will cause
 * a lot of rendering problems. The system never closes the transaction
 * automatically.</p>
 *
 * <p>If the local transform transaction is not open, this is a no-op.</p>
 *
 * @see #openLocalTransformTransaction
 * @see #setTransform
 */
- (void) commitLocalTransformTransaction;
@end


#endif /* TransformManager_h */
