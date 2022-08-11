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

    VertexAttributePosition        = 0, //!< XYZ position (float3)
    VertexAttributeTangents        = 1, //!< tangent, bitangent and normal, encoded as a quaternion (float4)
    VertexAttributeColor           = 2, //!< vertex color (float4)
    VertexAttributeUv0             = 3, //!< texture coordinates (float2)
    VertexAttributeUv1             = 4, //!< texture coordinates (float2)
    VertexAttributeBoneIndices    = 5, //!< indices of 4 bones, as unsigned integers (uvec4)
    VertexAttributeBoneWeights    = 6, //!< weights of the 4 bones (normalized float4)
    // -- we have 1 unused slot here --
    VertexAttributeCustom0         = 8,
    VertexAttributeCustom1         = 9,
    VertexAttributeCustom2         = 10,
    VertexAttributeCustom3         = 11,
    VertexAttributeCustom4         = 12,
    VertexAttributeCustom5         = 13,
    VertexAttributeCustom6         = 14,
    VertexAttributeCustom7         = 15,

    // Aliases for legacy vertex morphing.
    // See RenderableManager::Builder::morphing().
    VertexAttributeMorph_Position_0 = VertexAttributeCustom0,
    VertexAttributeMorph_Position_1 = VertexAttributeCustom1,
    VertexAttributeMorph_Position_2 = VertexAttributeCustom2,
    VertexAttributeMorph_Position_3 = VertexAttributeCustom3,
    VertexAttributeMorph_Tangents_0 = VertexAttributeCustom4,
    VertexAttributeMorph_Tangents_1 = VertexAttributeCustom5,
    VertexAttributeMorph_Tangents_2 = VertexAttributeCustom6,
    VertexAttributeMorph_Tangents_3 = VertexAttributeCustom7,

    // this is limited by driver::MAX_VERTEX_ATTRIBUTE_COUNT
};

#endif /* VertexAttribute_h */
