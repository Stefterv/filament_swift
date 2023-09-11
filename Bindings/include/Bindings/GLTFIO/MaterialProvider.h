//
//  MaterialProvider.h

//  Created by Stef Tervelde on 30.06.22.
//
#import <Foundation/Foundation.h>
#import "../Filament/Engine.h"
#import "../Filament/Material.h"
#import "../Filament/VertexAttribute.h"

#ifndef MaterialProvider_h
#define MaterialProvider_h

NS_SWIFT_NAME(MaterialProvider.AlphaMode)
typedef NS_ENUM(NSInteger, AlphaMode) {
    AlphaModeOpaque,
    AlphaModeMask,
    AlphaModeBlend
};

NS_SWIFT_NAME(MaterialProvider.MaterialKey)
@interface MaterialKey : NSObject
@property bool unlit;
@property bool hasVertexColors;
@property bool hasBaseColorTexture;
@property bool hasNormalTexture;
@property bool hasOcclusionTexture;
@property bool hasEmissiveTexture;
@property bool useSpecularGlossiness;
@property int alphaMode;                       // 0 = OPAQUE, 1 = MASK, 2 = BLEND
@property bool enableDiagnostics;
@property bool hasMetallicRoughnessTexture; // piggybacks with specularRoughness
@property int metallicRoughnessUV;             // piggybacks with specularRoughness
@property int baseColorUV;
@property bool hasClearCoatTexture;
@property int clearCoatUV;
@property bool hasClearCoatRoughnessTexture;
@property int clearCoatRoughnessUV;
@property bool hasClearCoatNormalTexture;
@property int clearCoatNormalUV;
@property bool hasClearCoat;
@property bool hasTransmission;
@property bool hasTextureTransforms;
@property int emissiveUV;
@property int aoUV;
@property int normalUV;
@property bool hasTransmissionTexture;
@property int transmissionUV;
@property bool hasSheenColorTexture;
@property int sheenColorUV;
@property bool hasSheenRoughnessTexture;
@property int sheenRoughnessUV;
@property bool hasVolumeThicknessTexture;
@property int volumeThicknessUV;
@property bool hasSheen;
@property bool hasIOR;
@end


NS_SWIFT_NAME(glTFIO.MaterialProvider)
@interface MaterialProvider : NSObject

@property (nonatomic, readonly, nonnull) void* provider  NS_SWIFT_UNAVAILABLE("Don't access the raw pointers");
- (nonnull id) init: (nonnull void*) provider NS_SWIFT_UNAVAILABLE("Create a new provider MaterialProvider.createUberShaderProvider");
- (nonnull id) init NS_UNAVAILABLE;

/**
 * Creates or fetches a compiled Filament material, then creates an instance from it.
 *
 * @param config Specifies requirements; might be mutated due to resource constraints.
 * @param uvmap Output argument that gets populated with a small table that maps from a glTF uv
 *              index to a Filament uv index.
 * @param label Optional tag that is not a part of the cache key.
 * @param extras Optional extras as stringified JSON (not a part of the cache key).
 *               Does not store the pointer.
 */
- (nonnull MaterialInstance*) createMaterialInstance: (nonnull MaterialKey*) config :(nonnull void*) uvmap :(nullable NSString*) label :(nullable NSString*) extras;

/**
 * Creates or fetches a compiled Filament material corresponding to the given config.
 */
- (nonnull Material*) getMaterial: (nonnull MaterialKey*) config :(nonnull void*) uvmap :(nonnull NSString*) label;

/**
 * Gets a weak reference to the array of cached materials.
 */
- (nonnull NSArray<Material*>*) getMaterials;

/**
 * Destroys all cached materials.
 *
 * This is not called automatically when MaterialProvider is destroyed, which allows
 * clients to take ownership of the cache if desired.
 */
- (void) destroyMaterials;

/**
 * Returns true if the presence of the given vertex attribute is required.
 *
 * Some types of providers (e.g. ubershader) require dummy attribute values
 * if the glTF model does not provide them.
 */
- (bool) needsDummyData: (VertexAttribute) attrib;
/**
 * Creates a material provider that builds materials on the fly, composing GLSL at run time.
 *
 * @param optimizeShaders Optimizes shaders, but at significant cost to construction time.
 * @return New material provider that can build materials at run time.
 *
 * Requires \c libfilamat to be linked in. Not available in \c libgltfio_core.
 *
 * @see createUbershaderProvider
 */
+ (nonnull instancetype) createUberShaderProvider: (nonnull Engine*) engine;
/**
 * Creates a material provider that loads a small set of pre-built materials.
 *
 * @return New material provider that can quickly load a material from a cache.
 *
 * @see createJitShaderProvider
 */
+ (nonnull instancetype) createJitShaderProvider: (nonnull Engine*) engine :(bool) optimizeShaders;

@end


#endif /* MaterialProvider_h */
