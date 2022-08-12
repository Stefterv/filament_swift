//
//  Math.h

//  Created by Stef Tervelde on 30.06.22.
//

#ifndef Math_h
#define Math_h

#import <math/mat4.h>
#import <simd/simd.h>




#define FLOAT3_FROM_SIMD(m) (filament::math::float3(m[0],m[1],m[2]))
#define FLOAT4_FROM_SIMD(m) (filament::math::float4(m[0],m[1],m[2], m[3]))
#define FLOAT3X9_FROM_SIMD(m) (filament::math::float3[]){ \
        m.columns[0][0], m.columns[0][1], m.columns[0][2], \
        m.columns[0][0], m.columns[0][1], m.columns[0][2], \
        m.columns[0][0], m.columns[0][1], m.columns[0][2]}

#define MAT3_FROM_SIMD(m) (filament::math::mat3 \
        (m.columns[0][0], m.columns[0][1], m.columns[0][2], \
         m.columns[1][0], m.columns[1][1], m.columns[1][2], \
         m.columns[2][0], m.columns[2][1], m.columns[2][2]))
#define MAT3F_FROM_SIMD(m) (filament::math::mat3f \
        (m.columns[0][0], m.columns[0][1], m.columns[0][2], \
         m.columns[1][0], m.columns[1][1], m.columns[1][2], \
         m.columns[2][0], m.columns[2][1], m.columns[2][2]))
#define MAT4_FROM_SIMD(m) (filament::math::mat4 \
        (m.columns[0][0], m.columns[0][1], m.columns[0][2], m.columns[0][3], \
         m.columns[1][0], m.columns[1][1], m.columns[1][2], m.columns[1][3], \
         m.columns[2][0], m.columns[2][1], m.columns[2][2], m.columns[2][3], \
         m.columns[3][0], m.columns[3][1], m.columns[3][2], m.columns[3][3]))
#define MAT4F_FROM_SIMD(m) (filament::math::mat4f \
        (m.columns[0][0], m.columns[0][1], m.columns[0][2], m.columns[0][3], \
         m.columns[1][0], m.columns[1][1], m.columns[1][2], m.columns[1][3], \
         m.columns[2][0], m.columns[2][1], m.columns[2][2], m.columns[2][3], \
         m.columns[3][0], m.columns[3][1], m.columns[3][2], m.columns[3][3]))
#define FROM_BOX(box) (filament::Box{ FLOAT3_FROM_SIMD(box.center), FLOAT3_FROM_SIMD(box.halfExtent) })
#define TO_BOX(box) [[Box alloc] initWithVector:SIMD_DOUBLE3_FROM_FLOAT3(box.center) Extent:SIMD_DOUBLE3_FROM_FLOAT3(box.halfExtent)];


#define SIMD_DOUBLE3_FROM_FLOAT3(m) (simd_make_double3(m[0],m[1],m[2]))
#define SIMD_FLOAT4X4_FROM_MAT4(m) (simd_matrix( \
        simd_make_float4(m[0][0], m[0][1], m[0][2], m[0][3]), \
        simd_make_float4(m[1][0], m[1][1], m[1][2], m[1][3]), \
        simd_make_float4(m[2][0], m[2][1], m[2][2], m[2][3]), \
        simd_make_float4(m[3][0], m[3][1], m[3][2], m[3][3])))
#define SIMD_DOUBLE4X4_FROM_MAT4(m) (simd_matrix( \
        simd_make_double4(m[0][0], m[0][1], m[0][2], m[0][3]), \
        simd_make_double4(m[1][0], m[1][1], m[1][2], m[1][3]), \
        simd_make_double4(m[2][0], m[2][1], m[2][2], m[2][3]), \
        simd_make_double4(m[3][0], m[3][1], m[3][2], m[3][3])))
#define SIMD_DOUBLE3X3_FROM_MAT3X3(m) (simd_matrix( \
        simd_make_double3(m[0][0], m[0][1], m[0][2]), \
        simd_make_double3(m[1][0], m[1][1], m[1][2]), \
        simd_make_double3(m[2][0], m[2][1], m[2][2])))

#endif /* Math_h */
