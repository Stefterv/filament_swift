//
//  NodeManager.h
//  swift-gltf-viewer
//
//  Created by Stef Tervelde on 10.09.23.
//
#import <Foundation/Foundation.h>
#import "../Filament/Engine.h"
#import "../Filament/Entity.h"

#ifndef NodeManager_h
#define NodeManager_h

/**
 * NodeManager is used to add annotate entities with glTF-specific information.
 *
 * Node components are created by gltfio and exposed to users to allow inspection.
 *
 * Nodes do not store the glTF hierarchy or names; see TransformManager and NameComponentManager.
 */
@interface NodeManager : NSObject

@property (nonatomic, readonly, nonnull) void* Manager  NS_SWIFT_UNAVAILABLE("Don't access the raw pointers");
- (nonnull id) init: (nonnull void*) Manager NS_SWIFT_UNAVAILABLE("Instances are created internally");
- (nonnull id) init NS_UNAVAILABLE;

/**
 * Returns whether a particular Entity is associated with a component of this NodeManager
 * @param e An Entity.
 * @return true if this Entity has a component associated with this manager.
 */
- (bool) hasComponent: (Entity) e;

/**
 * Gets an Instance representing the node component associated with the given Entity.
 * @param e An Entity.
 * @return An Instance object, which represents the node component associated with the Entity e.
 * @note Use Instance::isValid() to make sure the component exists.
 * @see hasComponent()
 */
- (EntityInstance) getInstance: (Entity) e;

/**
 * Creates a node component and associates it with the given entity.
 * @param entity            An Entity to associate a node component with.
 *
 * If this component already exists on the given entity, it is first destroyed as if
 * destroy(Entity e) was called.
 *
 * @see destroy()
 */
- (void) create: (Entity) entity;

/**
 * Destroys this component from the given entity.
 * @param e An entity.
 *
 * @see create()
 */
- (void) destroy: (Entity) e;

- (void) setMorphTargetNames: (EntityInstance) ci :(nonnull NSArray<NSString*>*) names;
- (nonnull NSArray<NSString*>*) getMorphTargetNames: (EntityInstance) ci;

- (void) setExtras: (EntityInstance) ci :(nonnull NSString*) extras;
- (nonnull NSString*) getExtras: (EntityInstance) ci;
- (void) setSceneMembership: (EntityInstance) ci :(u_int32_t) scenes;
- (u_int32_t) getSceneMembership: (EntityInstance) ci;

@end


#endif /* NodeManager_h */
