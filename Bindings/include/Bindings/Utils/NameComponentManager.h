//
//  NameComponentManager.h
//  swift-gltf-viewer
//
//  Created by Stef Tervelde on 10.09.23.
//
#import <Foundation/Foundation.h>
#import "../Filament/EntityManager.h"

#ifndef NameComponentManager_h
#define NameComponentManager_h

/**
 * \class NameComponentManager NameComponentManager.h utils/NameComponentManager.h
 * \brief Allows clients to associate string labels with entities.
 *
 * To access the name of an existing entity, clients should first use NameComponentManager to get a
 * temporary handle called an \em instance. Please note that instances are ephemeral; clients should
 * store entities, not instances.
 *
 * Usage example:
 *
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * auto names = new NameComponentManager(EntityManager::get());
 * names->addComponent(myEntity);
 * names->setName(names->getInstance(myEntity), "Jeanne d'Arc");
 * ...
 * printf("%s\n", names->getName(names->getInstance(myEntity));
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */
@interface NameComponentManager : NSObject

@property (nonatomic, readonly, nonnull) void* manager  NS_SWIFT_UNAVAILABLE("Don't access the raw pointers");
- (nonnull id) init NS_UNAVAILABLE;
/**
 * Creates a new name manager associated with the given entity manager.
 *
 * Note that multiple string labels could be associated with each entity simply by
 * creating multiple instances of NameComponentManager.
 */
- (nonnull id) init: (nonnull EntityManager*) em;

/**
 * Checks if the given entity already has a name component.
 */

/**
 * Gets a temporary handle that can be used to access the name.
 *
 * @return Non-zero handle if the entity has a name component, 0 otherwise.
 */
- (EntityInstance) getInstance: (Entity) e;

/**
 * Adds a name component to the given entity if it doesn't already exist.
 */
- (void) addComponent: (Entity) e;

/**
 * Removes the name component to the given entity if it exists.
 */
- (void) removeComponent: (Entity) e;

/**
 * Stores a copy of the given string and associates it with the given instance.
 */
- (void) setName: (EntityInstance) instance :(nonnull NSString*) name;

/**
 * Retrieves the string associated with the given instance, or nullptr if none exists.
 *
 * @return pointer to the copy that was made during setName()
 */
- (nonnull NSString*) getName: (EntityInstance) instance;
@end
#endif /* NameComponentManager_h */
