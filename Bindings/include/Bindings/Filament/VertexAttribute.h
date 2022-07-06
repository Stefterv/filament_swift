//
//  VertexAttribute.h
//
//  Created by Stef Tervelde on 05.07.22.
//

#ifndef VertexAttribute_h
#define VertexAttribute_h

/**
 * Vertex attribute types
 */
typedef NS_ENUM(NSInteger, VertexAttribute) {
    // Update hasIntegerTarget() in VertexBuffer when adding an attribute that will
    // be read as integers in the shaders

    POSITION        = 0, //!< XYZ position (float3)
    TANGENTS        = 1, //!< tangent, bitangent and normal, encoded as a quaternion (float4)
    COLOR           = 2, //!< vertex color (float4)
    UV0             = 3, //!< texture coordinates (float2)
    UV1             = 4, //!< texture coordinates (float2)
    BONE_INDICES    = 5, //!< indices of 4 bones, as unsigned integers (uvec4)
    BONE_WEIGHTS    = 6, //!< weights of the 4 bones (normalized float4)
    // -- we have 1 unused slot here --
    CUSTOM0         = 8,
    CUSTOM1         = 9,
    CUSTOM2         = 10,
    CUSTOM3         = 11,
    CUSTOM4         = 12,
    CUSTOM5         = 13,
    CUSTOM6         = 14,
    CUSTOM7         = 15,

    // Aliases for legacy vertex morphing.
    // See RenderableManager::Builder::morphing().
    MORPH_POSITION_0 = CUSTOM0,
    MORPH_POSITION_1 = CUSTOM1,
    MORPH_POSITION_2 = CUSTOM2,
    MORPH_POSITION_3 = CUSTOM3,
    MORPH_TANGENTS_0 = CUSTOM4,
    MORPH_TANGENTS_1 = CUSTOM5,
    MORPH_TANGENTS_2 = CUSTOM6,
    MORPH_TANGENTS_3 = CUSTOM7,

    // this is limited by driver::MAX_VERTEX_ATTRIBUTE_COUNT
};

#endif /* VertexAttribute_h */
