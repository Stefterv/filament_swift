//
//  Box.h

//  Created by Stef Tervelde on 30.06.22.
//
#import <Foundation/Foundation.h>
#import <simd/simd.h>

#ifndef Box_h
#define Box_h

typedef struct{
    simd_float3 center;
    simd_float3 halfExtent;
} Box;
typedef struct{
    simd_float3 min;
    simd_float3 max;
} Aabb;


#endif /* Box_h */
