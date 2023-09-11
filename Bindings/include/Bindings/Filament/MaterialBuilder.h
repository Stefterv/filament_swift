//
//  MaterialBuilder.h

//  Created by Stef Tervelde on 30.06.22.
//
#import <Foundation/Foundation.h>
#import "Engine.h"
#import "Material.h"

#ifndef MaterialBuilder_h
#define MaterialBuilder_h

@interface MaterialBuilder : NSObject

@property (nonatomic, readonly, nonnull) void* builder  NS_SWIFT_UNAVAILABLE("Don't access the raw pointers");
NS_ASSUME_NONNULL_BEGIN
- (id) init;

/**
 * Specifies the material data. The material data is a binary blob produced by
 * libfilamat or by matc.
 *
 * @param payload Pointer to the material data, must stay valid until build() is called.
 * @param size Size of the material data pointed to by "payload" in bytes.
 */
- (instancetype) payload: (nonnull NSData*) buffer;
/**
 * Specialize a constant parameter specified in the material definition with a concrete
 * value for this material. Once build() is called, this constant cannot be changed.
 * Will throw an exception if the name does not match a constant specified in the
 * material definition or if the type provided does not match.
 *
 * @tparam T The type of constant parameter, either int32_t, float, or bool.
 * @param name The name of the constant parameter specified in the material definition, such
 *             as "myConstant".
 * @param value The value to use for the constant parameter, must match the type specified
 *              in the material definition.
 */
- (instancetype) constantInt: (nonnull NSString*) name :(int) value;
- (instancetype) constantFloat: (nonnull NSString*) name :(float) value;
- (instancetype) constantBool: (nonnull NSString*) name :(bool) value;
/**
 * Creates the Material object and returns a pointer to it.
 *
 * @param engine Reference to the filament::Engine to associate this Material with.
 *
 * @return pointer to the newly created object or nullptr if exceptions are disabled and
 *         an error occurred.
 *
 * @exception utils::PostConditionPanic if a runtime error occurred, such as running out of
 *            memory or other resources.
 * @exception utils::PreConditionPanic if a parameter to a builder function was invalid.
 */
- (Material*) build: (nonnull Engine*) engine;
NS_ASSUME_NONNULL_END
@end


#endif /* MaterialBuilder_h */
